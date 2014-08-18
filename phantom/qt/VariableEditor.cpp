/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableEditor.h"
#include "VariableEditor.hxx"
#include "VariableModel.h"
#include "VariableNode.h"
#include "VariableWidget.h"
#include <QAction>
#include <QMenu>
#include <QScrollBar>
#include <QtGui/QToolButton>
#include <QtGui/QPushButton>
#include "BoolCheckBoxEditor.h"
#include "EnumComboBoxEditor.h"
#include "NumberLineEditor.h"
#include "StringLineEditor.h"
#include "CharLineEditor.h"
#include "BitFieldEditor.h"
#include "DataComboBoxEditor.h"
#include "ClassComboBoxEditor.h"
#include "phantom/serialization/Node.h"
#include "phantom/reflection/Expression.h"
#include "phantom/std/string.h"
#include "ExpressionCommand.h"
/* *********************************************** */
o_registerN((phantom, qt), VariableEditor);
 
namespace phantom { namespace qt {

    class VariableEditorManager : public QtAbstractPropertyManager
    {
    public:
        VariableEditorManager(VariableEditor* a_pVariableEditor)
            : m_pVariableEditor(a_pVariableEditor)
        {

        }
        void initializeProperty(QtProperty *property) {}
        void uninitializeProperty(QtProperty *property) 
        {
            o_assert(m_pVariableEditor->getVariableNode(property) == nullptr);
        }

        QString valueText(const QtProperty *property) const 
        {
            return m_pVariableEditor->valueText(property);
        }

        QIcon valueIcon(const QtProperty *property) const 
        {
            return m_pVariableEditor->valueIcon(property);
        }
        VariableEditor* m_pVariableEditor;
    };

    class VariableEditorFactory : public QtAbstractEditorFactory<VariableEditorManager>
    {
        
    public:
        VariableEditorFactory(VariableEditorManager* a_pManager)
            : QtAbstractEditorFactory<VariableEditorManager>(a_pManager)
            , m_pManager(a_pManager)
        {

        }
        QWidget* createEditor(VariableEditorManager* a_pModel, QtProperty *property, QWidget *parent)
        {
            return m_pManager->m_pVariableEditor->createEditor(a_pModel->m_pVariableEditor, property, parent);
        }

        void connectPropertyManager(VariableEditorManager *a_pManager)
        {

        }

        void disconnectPropertyManager(VariableEditorManager *a_pManager)
        {

        }

        VariableEditorManager* m_pManager;

    };

    VariableEditor::VariableEditor( const QString& a_VariableColumnName )
        : m_pVariableModel(nullptr)
        , m_bChangingPropertyValue(false)
        , m_bAutoSaveEnabled(true)
        , m_bAutoSaveStateEnabled(true)
        , m_variable_value_set_delegate(&VariableEditor::defaultVariableValueSetDelegate)
        , m_pOpenedEditor(nullptr)
        , m_iUserValueColumnWidth(200)
    {
        m_pManager = new VariableEditorManager(this);
        setFactoryForManager(m_pManager, new VariableEditorFactory(m_pManager));
        setContextMenuPolicy(Qt::CustomContextMenu);
        treeWidget()->setEditTriggers(treeWidget()->editTriggers()|QTreeWidget::AnyKeyPressed);
        setPropertiesWithoutValueMarked(true);
        setResizeMode(Interactive);
        QStringList labels;
        labels.append(QApplication::translate("VariableEditor", a_VariableColumnName.toUtf8().constData(), 0, QApplication::UnicodeUTF8));
        labels.append(QApplication::translate("VariableEditor", "Value", 0, QApplication::UnicodeUTF8));
        labels.append(QApplication::translate("VariableEditor", "Type", 0, QApplication::UnicodeUTF8));
        m_treeWidget->setHeaderLabels(labels);
        registerVariableTypeEditorClass(typeOf<bool>(), typeOf<BoolCheckBoxEditor>());
        registerVariableTypeEditorClass(typeOf<char>(), typeOf<CharLineEditor>());
        registerVariableTypeEditorClass(typeOf<uchar>(), typeOf<TNumberLineEditor<uchar>>());
        registerVariableTypeEditorClass(typeOf<short>(), typeOf<TNumberLineEditor<short>>());
        registerVariableTypeEditorClass(typeOf<ushort>(), typeOf<TNumberLineEditor<ushort>>());
        registerVariableTypeEditorClass(typeOf<int>(), typeOf<TNumberLineEditor<int>>());
        registerVariableTypeEditorClass(typeOf<uint>(), typeOf<TNumberLineEditor<uint>>());
        registerVariableTypeEditorClass(typeOf<long>(), typeOf<TNumberLineEditor<long>>());
        registerVariableTypeEditorClass(typeOf<ulong>(), typeOf<TNumberLineEditor<ulong>>());
        registerVariableTypeEditorClass(typeOf<longlong>(), typeOf<TNumberLineEditor<longlong>>());
        registerVariableTypeEditorClass(typeOf<ulonglong>(), typeOf<TNumberLineEditor<ulonglong>>());
        registerVariableTypeEditorClass(typeOf<float>(), typeOf<TNumberLineEditor<float>>());
        registerVariableTypeEditorClass(typeOf<double>(), typeOf<TNumberLineEditor<double>>());
        registerVariableTypeEditorClass(typeOf<string>(), typeOf<StringLineEditor>());
        registerVariableTypeEditorClass(typeOf<bitfield>(), typeOf<BitFieldEditor>());
    }

    VariableEditor::~VariableEditor( void )
    {
        if(m_pOpenedEditor)
        {
            QObject::disconnect(m_pOpenedEditor, SIGNAL(destroyed()), (QtTreePropertyBrowser*)this, SLOT(slotEditorDestroyed()));
            m_pVariableModel->slotVariableNodeAccessed(m_pOpenedEditor->getVariableNode());
            delete m_pOpenedEditor;
        }
        o_dynamic_delete m_pVariableModel;
    }

    QWidget* VariableEditor::createEditor(VariableEditor* a_pThis, QtProperty *property, QWidget *parent)
    {
        o_assert(this == a_pThis);
        VariableNode* pVariableNode = getVariableNode(property);
        if(pVariableNode == NULL) 
            return nullptr;
        if(pVariableNode->hasModifier(o_readonly)) 
            return nullptr;
        if(pVariableNode->getExpressionCount() == 0) 
            return nullptr;

        m_pVariableModel->slotVariableNodeAboutToBeAccessed(pVariableNode);

        phantom::reflection::Type* pVariableType = pVariableNode->getValueType();

        o_assert(pVariableType);

        VariableWidgetEditor* pVariableWidgetEditor = nullptr;

        auto found = m_VariableTypeToEditorClass.find(pVariableType);
        if(found != m_VariableTypeToEditorClass.end())
        {
            reflection::Class* pEditorClass = found.value();
            pVariableWidgetEditor = as<VariableWidgetEditor*>(pEditorClass->newInstance());
        }
        else if(pVariableType->asEnum())
        {
            phantom::reflection::Enum* pEnum = pVariableType->asEnum();

            pVariableWidgetEditor = o_new(EnumComboBoxEditor)(pEnum);
        }
        else if(pVariableType->asDataPointerType())
        {
            if(m_pVariableModel->getDataBase())
            {
                vector<void*> addresses;
                addresses.resize(pVariableNode->getExpressionCount());

                for(size_t i = 0; i<addresses.size(); ++i)
                {
                    pVariableNode->getExpression(i)->load(&addresses[i]);
                }
                if(pVariableNode->hasModifier(o_component))
                {
                    vector<reflection::Class*> classes(pVariableNode->getExpressionCount());
                    for(size_t i = 0; i<classes.size(); ++i)
                    {
                        void* pAddress;
                        pVariableNode->getExpression(i)->load(&pAddress);
                        classes[i] = classOf(pAddress);
                    }
                    pVariableWidgetEditor = o_new(ClassComboBoxEditor)(pVariableType->asDataPointerType()->getPointedType()->asClass(), classes);
                }
                else
                {
                    phantom::vector<phantom::data> currentData;
                    currentData.resize(addresses.size());
                    for(size_t i = 0; i<addresses.size(); ++i)
                    {
                        currentData[i] = addresses[i];
                        currentData[i] = currentData[i].cast(pVariableType);
                    }
                    pVariableWidgetEditor = o_new(DataComboBoxEditor)(m_pVariableModel->getDataBase(), pVariableType->asDataPointerType()->getPointedType(), currentData, m_pVariableModel->getData());
                }
                
            }
        }
        if(pVariableWidgetEditor)
        {
            VariableWidget* pVariableWidget = new VariableWidget(pVariableWidgetEditor, this);
            //o_assert(m_pOpenedEditor == nullptr);
            m_pOpenedEditor = pVariableWidget;
            pVariableWidget->setVariableNode(pVariableNode);
            pVariableWidget->setParent(parent);

            vector<void*> buffers(pVariableNode->getExpressionCount());
            for(size_t i = 0; i<buffers.size(); ++i)
            {
                buffers[i] = pVariableType->allocate();
                pVariableType->safeSetup(buffers[i]);
            }
            pVariableNode->getValues(buffers.data());
            pVariableWidgetEditor->setValues(const_cast<const void**>(buffers.data()));
            for(size_t i = 0; i<buffers.size(); ++i)
            {
                pVariableType->deleteInstance(buffers[i]);
            }

            QObject::connect(pVariableWidget, SIGNAL(destroyed()), (QtTreePropertyBrowser*)this, SLOT(slotEditorDestroyed()));
            QObject::connect(pVariableWidgetEditor, SIGNAL(valueChanged()), (QtTreePropertyBrowser*)this, SLOT(slotEditorValueChanged()));
            return pVariableWidget;
        }
        else 
        {
            m_pVariableModel->slotVariableNodeAccessed(pVariableNode);
            return nullptr;
        }
        return nullptr;
    }

    QtBrowserItem* VariableEditor::getBrowserItem(VariableNode* a_pVariable) const 
    {
        const QtProperty* property = getProperty(a_pVariable);
        if(property == nullptr) return nullptr;
        return propertyToBrowserItem(property);
    }

    void VariableEditor::createPropertyPopupMenu( const QPoint& pos )
    {
        /*QTreeWidgetItem* pItem;
        QList<QTreeWidgetItem*> selectedItems = treeWidget()->selectedItems();
        Q_FOREACH(pItem,selectedItems)
        {
            QtBrowserItem* pBrowserItem = m_itemToIndex.value(pItem);
            QtProperty* property = pBrowserItem->property();
            phantom::reflection::Variable* pVariable = m_pVariableModel->getVariable(property);
            phantom::reflection::IteratorVariable* pIteratorVariable = phantom::as<phantom::reflection::IteratorVariable*>(pVariable);
            if(pIteratorVariable == NULL) continue;
            QtProperty* parentProperty = *(property->parentProperties().begin());
            phantom::reflection::Variable* pParentVariable = m_pVariableModel->getVariable(parentProperty);
            if(pParentVariable->testModifiers(o_readonly)) continue;
            QMenu menu(this);
            QAction* pAction = new EraseContainerIteratorAction(pIteratorVariable, this);
            connect(pAction, SIGNAL(triggered()), this, SLOT(reedit()));
            menu.addAction(pAction);
            menu.exec(QCursor::pos());
            return;
        }*/
    }

    void VariableEditor::updateCustomExtraColumns( QTreeWidgetItem * item, QtProperty * property )
    {
        VariableNode* pVariable = getVariableNode(property);
        if(pVariable == nullptr) 
        {
            item->setText(2, "");
            item->setIcon(2, QIcon());
        }
        else
        {
            phantom::reflection::Type* pType = pVariable->getValueType();
            if(pType)
            {
                string name = nameOf(pType);
                QIcon icon = QIcon(iconOf(pType).c_str());
                string extension = (pVariable->getExpressionCount() > 1) 
                    ? string(" (")+lexical_cast<string>(pVariable->getExpressionCount())+" data)" 
                    : "";
                item->setText(2, (name + extension).c_str());
                item->setIcon(2, icon);
            }
        }
    }

    void VariableEditor::reedit()
    {
        if(m_EditedData.empty()) return;
        int vpos = m_treeWidget->verticalScrollBar()->sliderPosition();
        vector<phantom::data> editedData = m_EditedData;
        VariableModel* pVariableModel = m_pVariableModel;
        setVariableModel(nullptr);
        setVariableModel(pVariableModel);
        m_treeWidget->verticalScrollBar()->setSliderPosition(vpos);
    }

    void VariableEditor::refresh()
    {
        for(size_t i = 0; i< m_treeWidget->topLevelItemCount(); ++i)
        {
            updateItemCascade(m_treeWidget->topLevelItem(i));
        }
    }

    void VariableEditor::updateItemLook( QtBrowserItem* item )
    {
    }

    void VariableEditor::slotEditorDestroyed()
    {
        VariableWidget* pEditor = (VariableWidget*)sender();
        if(pEditor == m_pOpenedEditor)
            m_pOpenedEditor = nullptr;
        m_pVariableModel->slotVariableNodeAccessed(pEditor->getVariableNode());
    }

    void VariableEditor::slotEditorValueChanged()
    {
        VariableWidgetEditor* pEditor = as<VariableWidgetEditor*>((void*)sender());
        Q_ASSERT(pEditor);
        VariableNode* pVariable = pEditor->getVariableNode();
        reflection::Type* pVariableType = pVariable->getValueType();
        void* pBuffer = pVariableType->allocate();
        pVariableType->safeSetup(pBuffer);
        pEditor->getValue(pBuffer);
        m_bChangingPropertyValue = true;
        m_pVariableModel->slotVariableNodeExpressionsAboutToBeAssigned(pVariable);
        m_variable_value_set_delegate(this, pVariable, const_cast<const void*>(pBuffer));
        m_pManager->emitPropertyChanged((QtProperty*)getProperty(pVariable));
        m_pVariableModel->slotVariableNodeExpressionsAssigned(pVariable);
        m_bChangingPropertyValue = false;
        pVariableType->deleteInstance(pBuffer);
    }
/*

    void VariableEditor::edit(const vector<phantom::data>& a_Data)
    {
        if(!m_EditedData.empty())
        {
            clear();
            m_EditedData.clear();
        }
        m_EditedData = a_Data;
        if(m_pDataBase)
        {
            m_pDataBase->sortComponentDataFirst(m_EditedData.begin(), m_EditedData.end());
        }
        if(!m_EditedData.empty())
        {
            m_pEditedType = m_EditedData.front().type();
            for(auto it = m_EditedData.begin()+1; it != m_EditedData.end(); ++it)
            {
                if(m_pEditedType)
                {
                    m_pEditedType = m_pEditedType->getCommonAncestor(it->type());
                }
            }
            if(m_pEditedType != nullptr)
            {
                vector<void*> editedAddresses;
                for(auto it = m_EditedData.begin(); it != m_EditedData.end(); ++it)
                {
                    phantom::data castedData = it->cast(m_pEditedType);
                    o_assert(!castedData.isNull());
                    editedAddresses.push_back(castedData.address());
                }
                
                QVector<QtProperty*> properties;
                m_pVariableModel->createProperties(editedAddresses, m_pEditedType, properties);
                for(auto it = properties.begin(); it != properties.end(); ++it)
                {
                    addProperty(*it);
                }
            }
        }
        setResizeMode(Interactive);
    }*/

    void VariableEditor::slotVariableChanged( VariableNode* a_pVariable )
    {
        VariableNode* pParentVariable = a_pVariable->getParentNode();
        while(pParentVariable)
        {
            updateBrowserItem(getBrowserItem(pParentVariable));
            pParentVariable = pParentVariable->getParentNode();
        }
        if(a_pVariable->getRange())
        {
            void * pBufferCurrent = a_pVariable->getValueType()->newInstance();
            void * pBufferDefault = a_pVariable->getValueType()->newInstance();
            a_pVariable->getValue(pBufferCurrent);
            a_pVariable->getRange()->getDefault(pBufferDefault);
            getProperty(a_pVariable)->setModified(!a_pVariable->getValueType()->areValueEqual(pBufferCurrent, pBufferDefault));
        }

        VariableNode* pVariableNode = as<VariableNode*>(a_pVariable);
       
        if(pVariableNode->isChangingStructure())
        {
            reedit();
        }
    }

    void VariableEditor::registerVariableTypeEditorClass( reflection::Type* a_pType, reflection::Class* a_pClass )
    {
        Q_ASSERT(a_pClass->isKindOf(typeOf<VariableWidgetEditor>()));
        m_VariableTypeToEditorClass[a_pType] = a_pClass;
    }

    void VariableEditor::defaultVariableValueSetDelegate( VariableEditor* a_pVariableEditor, VariableNode* a_pVariable, void const* a_pValue )
    {
        size_t count = a_pVariable->getExpressionCount();
        for(size_t i = 0; i<count; ++i)
        {
            /*UndoStack* pUndoStack = a_pVariable->getExpressionUndoStack(i);
            if(pUndoStack)
            {
                reflection::Expression* pExpression = a_pVariable->getExpression(i);
                reflection::Type* pEffectiveType = pExpression->getValueType()->removeReference();
                variant value = pExpression->get();
                o_assert(pEffectiveType == value.type());

                string oldValueStr;
                pEffectiveType->valueToLiteral(oldValueStr, value.buffer());
                string undoExpressionStr = pExpression->getName() + " = " + oldValueStr;

                string newValueStr;
                pEffectiveType->valueToLiteral(newValueStr, a_ppValueSources[i]);
                string redoExpressionStr = pExpression->getName() + " = " + newValueStr;

                //pUndoStack->pushCommand(o_new(ExpressionCommand)(undoExpressionStr, redoExpressionStr));
            }
            else */a_pVariable->getExpression(i)->store(a_pValue);
        }
    }

    void VariableEditor::setVariableValueSetDelegate( variable_value_set_delegate d )
    {
        m_variable_value_set_delegate = d;
    }

    void VariableEditor::registerProperty( QtProperty* property, VariableNode* a_pVariable )
    {
        o_assert(getVariableNode(property) == NULL);
        m_Variables[property] = a_pVariable;
        m_Properties[a_pVariable] = property;
    }

    QtProperty* VariableEditor::unregisterProperty( VariableNode* a_pVariable )
    {
        auto found = m_Properties.find(a_pVariable);
        o_assert(found != m_Properties.end());
        QtProperty* property = found->second;
        m_Variables.erase(property);
        m_Properties.erase(found);
        return property;
    }

    QtProperty* VariableEditor::getProperty( VariableNode* a_pVariable ) const
    {
        auto found = m_Properties.find(a_pVariable);
        return (found == m_Properties.end()) ? NULL : found->second;
    }

    VariableNode* VariableEditor::getVariableNode( QtProperty* property ) const
    {
        auto found = m_Variables.find(property);
        return (found == m_Variables.end()) ? NULL : found->second;
    }

    QString VariableEditor::valueText( const QtProperty *property ) const
    {
        if(property == nullptr) return "";
        VariableNode* pVariable = getVariableNode((QtProperty*)property);
        o_assert(getProperty(pVariable) == property);

        o_assert(pVariable);

        m_pVariableModel->slotVariableNodeAboutToBeAccessed(pVariable);

        QString text = valueText(pVariable) 
// #if defined(DEBUG)
//             + '(' + (pVariable->getExpressionCount() ? pVariable->getExpression(0)->getName().c_str() : "") + ')';
// #endif
        ;
        m_pVariableModel->slotVariableNodeAccessed(pVariable);

        return text;
    }

    QString VariableEditor::valueText( VariableNode*  pVariable ) const
    {
        if(pVariable->getExpressionCount()) 
        {
            if(pVariable->hasMultipleValues() && !pVariable->hasModifier(o_component))
            {
                return "<multiple values>";
            }

            reflection::Type*  type = pVariable->getValueType();

            reflection::ContainerClass* pContainerClass = type->asContainerClass();
            string qualifiedName = type->getQualifiedName();
            /*if(pContainerClass && qualifiedName != "::std::basic_string")
            {
                void* pContainer = pVariable->getAddress();
                if(pContainer)
                {
                    size_t count = pContainerClass->getCount(pVariable->getAddress());
                    return QString("[")+QString::number(count)+"]";
                }
            }
            else */if((type->asDataPointerType() != nullptr) && m_pVariableModel->getDataBase())
            {
                void* value = NULL;
                pVariable->getValue(&value);
                if(value == NULL)
                {
                    return "none";
                }
                uint guid = m_pVariableModel->getDataBase()->getGuid(value);
                if(guid == 0xFFFFFFFF ) 
                {
                    if(pVariable->hasModifier(o_component))
                    {
                        vector<void*> addresses;
                        addresses.resize(pVariable->getExpressionCount());
                        for(size_t i = 0; i<addresses.size(); ++i)
                        {
                            pVariable->getExpression(i)->load(&addresses[i]);
                        }
                        reflection::Class* pCommonClass = classOf(addresses[0]);
                        for(size_t i = 1; i<addresses.size(); ++i)
                        {
                            if(classOf(addresses[i]) != pCommonClass)
                            {
                                return "<multiple values>";
                            }
                        }
                        if(pCommonClass)
                        {
                            return nameOf(pCommonClass).c_str();
                        }
                        return "none";
                    }
                    return "internal";
                }
                else 
                {
                    phantom::data d = m_pVariableModel->getDataBase()->getData(guid);
                    return QString(m_pVariableModel->getDataBase()->getDataAttributeValue(d, m_pVariableModel->getDataBase()->getAttributeIndex("name")).c_str());
                }
            }

            // Construct a temporary buffer to receive the value (don't install rtti to improve performance)

            reflection::Expression* pExpression = pVariable->getExpression(0);

            string result;
            if(pExpression->hasEffectiveAddress())
            {
                void* pEffectiveAddress = pExpression->loadEffectiveAddress();
                type->valueToString(result, pEffectiveAddress);

                QtProperty* property = getProperty(pVariable);
                if(property AND pVariable->getRange() AND !pVariable->hasMultipleValues())
                {
                    auto pEffectiveType = pVariable->getValueType()->removeReference()->removeConst();
                    void * pBufferDefault = pEffectiveType->newInstance();
                    pVariable->getRange()->getDefault(pBufferDefault);
                    property->setModified(!pEffectiveType->areValueEqual(pEffectiveAddress, pBufferDefault));
                }
            }
            else
            {
                void* pBufferCurrent = pVariable->getValueType()->removeReference()->removeConst()->allocate();
                pVariable->getValueType()->removeReference()->removeConst()->safeConstruct(pBufferCurrent);
                pVariable->getValueType()->removeReference()->removeConst()->initialize(pBufferCurrent);
                pVariable->getValue(pBufferCurrent);

                type->valueToString(result, pBufferCurrent);

                pVariable->getValueType()->removeReference()->removeConst()->terminate(pBufferCurrent);
                pVariable->getValueType()->removeReference()->removeConst()->destroy(pBufferCurrent);
                pVariable->getValueType()->removeReference()->removeConst()->deallocate(pBufferCurrent);
            }

            return result.c_str();
        }
        else 
        {
            QString compound;
            if(pVariable->beginChildNodes() != pVariable->endChildNodes())
            {
                compound = "[";
                int c = 0;
                for(auto it = pVariable->beginChildNodes(); it != pVariable->endChildNodes(); ++it)
                {
                    QString vt = valueText(*it);
                    if(vt.isEmpty()) continue;

                    if(c++ > 0)
                    {
                        compound += " | ";
                    }
                    compound += (*it)->getName().c_str();
                    compound += "=";
                    compound += vt;
                }
                compound += "]";
            }
            return compound;
        }
        return "";
    }

    QIcon VariableEditor::valueIcon( const QtProperty *property ) const
    {
        VariableNode*  pVariable = getVariableNode((QtProperty*)property);
        if(pVariable != NULL ) 
        {
            return valueIcon(pVariable); 
        }
        return QIcon();

    }

    QIcon VariableEditor::valueIcon( VariableNode* a_pVariable ) const
    {
        reflection::Type* type = a_pVariable->getValueType();

        if(type == nullptr)
            return QIcon();

        if(type->asEnum())
        {
            reflection::Enum* pEnum = type->asEnum();
            size_t value = 0;
            a_pVariable->getValue(&value);
            size_t i = 0;
            size_t count = pEnum->getConstantCount();
            for(;i<count;++i)
            {
                size_t constantValue = 0;
                reflection::Constant* pConstant = pEnum->getConstant(i);
                pConstant->getValue(&constantValue);
                if(constantValue == value)
                {
                    return QIcon(iconOf(pConstant).c_str());
                }
            }
        }
        else if(type == typeOf<bool>())
        {
            bool value = false;
            a_pVariable->getValue(&value);
            return value ? QIcon(":/../../bin/resources/icons/accept.png") : QIcon(":/../../bin/resources/icons/exclamation.png");
        }
        /*reflection::ValueMember* pValueMember = as<reflection::ValueMember*>(a_pVariable->getExpression(0)->getHatchedElement());
        if(pValueMember)
        {
            return QIcon(pValueMember->getMetaDataValue(getIconMetaDataIndex()).c_str());
        }*/
        return QIcon(a_pVariable->getValueType()->getMetaDataValue(getIconMetaDataIndex()).c_str());
    }

    void VariableEditor::variableChildNodeAdded( VariableNode* a_pVariableNode )
    {
        QObject::disconnect(treeWidget()->header(), SIGNAL(sectionResized(int, int, int)), this, SLOT(columnSectionResized(int, int, int)));
        setResizeMode(ResizeToContents);
        o_connect(a_pVariableNode, childNodeAdded(VariableNode*), this, variableChildNodeAdded(VariableNode*));
        o_connect(a_pVariableNode, childNodeAboutToBeRemoved(VariableNode*), this, variableChildNodeAboutToBeRemoved(VariableNode*));
        if(a_pVariableNode->getParentNode()) // not Root
        {
            QtProperty* property = m_pManager->addProperty(a_pVariableNode->getName().c_str());
            registerProperty(property, a_pVariableNode);
            if(a_pVariableNode->getParentNode() == m_pVariableModel->getRootNode()) // First level
            {
                addProperty(property);
            }
            else 
            {
                getProperty(a_pVariableNode->getParentNode())->addSubProperty(property);
            }
        }
        for(auto it = a_pVariableNode->beginChildNodes(); it != a_pVariableNode->endChildNodes(); ++it)
        {
            variableChildNodeAdded(*it);
        }
        treeWidget()->setColumnWidth(1, m_iUserValueColumnWidth);
        setResizeMode(Interactive);
        QObject::connect(treeWidget()->header(), SIGNAL(sectionResized(int, int, int)), this, SLOT(columnSectionResized(int, int, int)));
    }

    void VariableEditor::variableChildNodeAboutToBeRemoved( VariableNode* a_pVariableNode )
    {
        if(a_pVariableNode->getParentNode()) // not Root
        {
            if(a_pVariableNode->getParentNode() == m_pVariableModel->getRootNode()) // First level
            {
                delete unregisterProperty(a_pVariableNode);
            }
        }
        for(auto it = a_pVariableNode->beginChildNodes(); it != a_pVariableNode->endChildNodes(); ++it)
        {
            variableChildNodeAboutToBeRemoved(*it);
        }
        o_disconnect(a_pVariableNode, childNodeAdded(VariableNode*), this, variableChildNodeAdded(VariableNode*));
        o_disconnect(a_pVariableNode, childNodeAboutToBeRemoved(VariableNode*), this, variableChildNodeAboutToBeRemoved(VariableNode*));
    }

    void VariableEditor::setVariableModel( VariableModel* a_pVariableModel )
    {
        if(m_pVariableModel == a_pVariableModel) return; 
        if(m_pVariableModel)
        {
            o_disconnect(a_pVariableModel, rootNodeAdded(VariableNode*), this, variableChildNodeAdded(VariableNode*));
            o_disconnect(a_pVariableModel, rootNodeAboutToBeRemoved(VariableNode*), this, variableChildNodeAboutToBeRemoved(VariableNode*));
            o_disconnect(a_pVariableModel, variableNodeExpressionsAboutToBeAssigned(VariableNode*), this, variableNodeExpressionsAboutToBeAssigned(VariableNode*));
            o_disconnect(a_pVariableModel, variableNodeExpressionsAssigned(VariableNode*), this, variableNodeExpressionsAssigned(VariableNode*));
            if(m_pVariableModel->getRootNode())
            {
                variableChildNodeAboutToBeRemoved(m_pVariableModel->getRootNode());
            }
        }
        m_pVariableModel = a_pVariableModel;
        if(m_pVariableModel)
        {
            o_connect(a_pVariableModel, rootNodeAdded(VariableNode*), this, variableChildNodeAdded(VariableNode*));
            o_connect(a_pVariableModel, rootNodeAboutToBeRemoved(VariableNode*), this, variableChildNodeAboutToBeRemoved(VariableNode*));
            o_connect(a_pVariableModel, variableNodeExpressionsAboutToBeAssigned(VariableNode*), this, variableNodeExpressionsAboutToBeAssigned(VariableNode*));
            o_connect(a_pVariableModel, variableNodeExpressionsAssigned(VariableNode*), this, variableNodeExpressionsAssigned(VariableNode*));
            if(a_pVariableModel->getRootNode())
            {
                variableChildNodeAdded(m_pVariableModel->getRootNode());
            }
        }
    }

    void VariableEditor::variableNodeExpressionsAboutToBeAssigned( VariableNode* a_pVariableNode )
    {
    }

    void VariableEditor::variableNodeExpressionsAssigned( VariableNode* a_pVariableNode )
    {
        QtProperty* pProperty = getProperty(a_pVariableNode);
        if(pProperty)
        {
            refresh();//updateItemParents(browserItemToItem(propertyToBrowserItem(pProperty)));
        }
    }

    void VariableEditor::variableNodeAboutToBeAccessed( VariableNode* a_pVariableNode )
    {

    }

    void VariableEditor::variableNodeAccessed( VariableNode* a_pVariableNode )
    {

    }

    void VariableEditor::columnSectionResized( int logicalIndex, int oldSize, int newSize )
    {
        if(logicalIndex == 1)
            m_iUserValueColumnWidth = newSize;
    }

}}