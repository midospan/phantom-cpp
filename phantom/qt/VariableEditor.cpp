/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableEditor.h"
#include "VariableEditor.hxx"
#include "VariableModel.h"
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
#include "ComponentDataComboBoxEditor.h"
#include "phantom/serialization/Node.h"
#include "phantom/std/string.h"
/* *********************************************** */
o_registerN((phantom, qt), VariableEditor);
 
namespace phantom { namespace qt {

    class VariableEditorFactory : public QtAbstractEditorFactory<VariableEditor>
    {
        
    public:
        VariableEditorFactory(VariableEditor* a_pEditor)
            : QtAbstractEditorFactory<VariableModel>(a_pEditor)
            , m_pVariableEditor(a_pEditor)
        {

        }
        QWidget* createEditor(VariableModel*a_pManager, QtProperty *property, QWidget *parent)
        {
            return m_pVariableEditor->createEditor(a_pManager, property, parent);
        }

        void connectPropertyManager(VariableEditor *manager)
        {

        }

        void disconnectPropertyManager(VariableEditor *manager)
        {

        }

        VariableEditor* m_pVariableEditor;

    };

    VariableEditor::VariableEditor( const QString& a_VariableColumnName )
        : m_pVariableModel(a_pManager)
        , m_pDataBase(nullptr)
        , m_bChangingPropertyValue(false)
        , m_bAutoSaveEnabled(true)
        , m_bAutoSaveStateEnabled(true)
        , m_variable_value_set_delegate(&VariableEditor::defaultVariableValueSetDelegate)
        , m_pOpenedEditor(nullptr)
    {
        Q_ASSERT(m_pVariableModel->m_pVariableEditor == nullptr);
        m_pVariableModel->m_pVariableEditor = this;
        setFactoryForManager(m_pVariableModel, new VariableEditorFactory(this));
        setContextMenuPolicy(Qt::CustomContextMenu);
        treeWidget()->setEditTriggers(treeWidget()->editTriggers()|QTreeWidget::AnyKeyPressed);
        setPropertiesWithoutValueMarked(true);
        setResizeMode(Interactive);
        QStringList labels;
        labels.append(QApplication::translate("VariableEditor", a_VariableColumnName.toUtf8().constData(), 0, QApplication::UnicodeUTF8));
        labels.append(QApplication::translate("VariableEditor", "Value", 0, QApplication::UnicodeUTF8));
        labels.append(QApplication::translate("VariableEditor", "Type", 0, QApplication::UnicodeUTF8));
        m_treeWidget->setHeaderLabels(labels);
        m_pVariableModel->initialize();
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
            disconnect(m_pOpenedEditor, SIGNAL(destroyed()), this, SLOT(slotEditorDestroyed()));
            emit variableAccessed(m_pOpenedEditor->getVariable());
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

        emit variableAboutToBeAccessed(pVariableNode);

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
            vector<void*> addresses;
            addresses.resize(pVariableNode->getVariableCount());
            
            for(size_t i = 0; i<addresses.size(); ++i)
            {
                pVariableNode->getVariable(i)->getValue(&addresses[i]);
                if(std::find(m_EditedData.begin(), m_EditedData.end(), addresses[i]) != m_EditedData.end())
                {

                }
            }
            if(m_pDataBase)
            {
                if(pVariableNode->isComponent())
                {
                    for(size_t i = 0; i<addresses.size(); ++i)
                    {
                        pVariableNode->getVariable(i)->getValue(&addresses[i]);
                        if(std::find(m_EditedData.begin(), m_EditedData.end(), addresses[i]) != m_EditedData.end())
                        {
                            emit variableAccessed(pVariableNode);
                            return nullptr;
                        }
                    }
                    pVariableWidgetEditor = o_new(ComponentDataComboBoxEditor)(pVariableType->asDataPointerType()->getPointedType()->asClass(), addresses);
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
                    pVariableWidgetEditor = o_new(DataComboBoxEditor)(m_pDataBase, pVariableType->asDataPointerType()->getPointedType(), currentData, m_EditedData);
                }
                
            }
        }
        if(pVariableWidgetEditor)
        {
            VariableWidget* pVariableWidget = new VariableWidget(pVariableWidgetEditor, this);
            //o_assert(m_pOpenedEditor == nullptr);
            m_pOpenedEditor = pVariableWidget;
            pVariableWidget->setVariable(pVariableNode);
            pVariableWidget->setParent(parent);

            vector<void*> buffers(pVariableNode->getVariableCount());
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

            connect(pVariableWidget, SIGNAL(destroyed()), this, SLOT(slotEditorDestroyed()));
            connect(pVariableWidgetEditor, SIGNAL(valueChanged()), this, SLOT(slotEditorValueChanged()));
            return pVariableWidget;
        }
        else 
        {
            emit variableAccessed(pVariableNode);
            return nullptr;
        }
        return nullptr;
    }

    QtBrowserItem* VariableEditor::getBrowserItem(VariableNode* a_pVariable) const 
    {
        const QtProperty* property = m_pVariableModel->getProperty(a_pVariable);
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
        VariableNode* pVariable = m_pVariableModel->getVariable(property);
        if(pVariable == nullptr) 
        {
            item->setText(2, "");
            item->setIcon(2, QIcon());
        }
        else
        {
            phantom::reflection::Type* pType = pVariable->getValueType();

            string name = pType->getMetaDataValue(getNameMetaDataIndex());
            if(name.empty()) name = pType->getName();
            string icon = pType->getMetaDataValue(getIconMetaDataIndex());
            string extension = (pVariable->getVariableCount() > 1) 
                                ? string(" (")+lexical_cast<string>(pVariable->getVariableCount())+" data)" 
                                : "";
            item->setText(2, (name + extension).c_str());
            item->setIcon(2, QIcon(icon.c_str()));
        }
    }

    void VariableEditor::reedit()
    {
        if(m_EditedData.empty()) return;
        int vpos = m_treeWidget->verticalScrollBar()->sliderPosition();
        vector<phantom::data> editedData = m_EditedData;
        edit(editedData);
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
        emit variableAccessed(pEditor->getVariable());
    }

    void VariableEditor::slotEditorValueChanged()
    {
        VariableWidgetEditor* pEditor = as<VariableWidgetEditor*>(sender());
        Q_ASSERT(pEditor);
        VariableNode* pVariable = pEditor->getVariable();
        reflection::Type* pVariableType = pVariable->getValueType();
        vector<void*> buffers(pVariable->getVariableCount());
        for(size_t i = 0; i<buffers.size(); ++i)
        {
            buffers[i] = pVariableType->allocate();
            pVariableType->safeSetup(buffers[i]);
        }
        pEditor->getValues(buffers.data());
        m_bChangingPropertyValue = true;
        emit variableAboutToBeChanged(pVariable);
        m_variable_value_set_delegate(pVariable, const_cast<const void**>(buffers.data()));
        m_pVariableModel->emitPropertyChanged((QtProperty*)m_pVariableModel->getProperty(pVariable));
        if(m_pDataBase && isAutoSaveEnabled())
        {
            m_pDataBase->rootNode()->addDataComponentsCascade();
            for(auto it = m_EditedData.begin(); it != m_EditedData.end(); ++it)
            {
                m_pDataBase->getNode(*it)->saveData(*it);
            }
        }
        if(m_pDataBase && m_pDataBase->getDataStateBase() && isAutoSaveStateEnabled())
        {
            for(auto it = m_EditedData.begin(); it != m_EditedData.end(); ++it)
            {
                m_pDataBase->getNode(*it)->saveDataState(*it, 0);
            }
        }
        emit variableChanged(pVariable);
        m_bChangingPropertyValue = false;
        for(size_t i = 0; i<buffers.size(); ++i)
        {
            pVariableType->deleteInstance(buffers[i]);
        }
    }

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
            m_pDataBase->sortSubDataFirst(m_EditedData.begin(), m_EditedData.end());
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
    }

    void VariableEditor::slotVariableChanged( VariableNode* a_pVariable )
    {
        VariableNode* pParentVariable = a_pVariable->getParentVariable();
        while(pParentVariable)
        {
            updateBrowserItem(getBrowserItem(pParentVariable));
            pParentVariable = pParentVariable->getParentVariable();
        }
        if(a_pVariable->getRange())
        {
            void * pBufferCurrent = a_pVariable->getValueType()->newInstance();
            void * pBufferDefault = a_pVariable->getValueType()->newInstance();
            a_pVariable->getValue(pBufferCurrent);
            a_pVariable->getRange()->getDefault(pBufferDefault);
            m_pVariableModel->getProperty(a_pVariable)->setModified(!a_pVariable->getValueType()->areValueEqual(pBufferCurrent, pBufferDefault));
        }

        VariableNode* pVariableNode = as<VariableNode*>(a_pVariable);
        reflection::Class* pVariableClass = pVariableNode ? pVariableNode->getVariableClass() : classOf(a_pVariable);
        bool pContainerVariable = pVariableClass->isKindOf(typeOf<ContainerInsertVariable>());
        bool pCollectionInsertVariable = pVariableClass->isKindOf(typeOf<CollectionInsertVariable>());
        bool pCollectionElementVariable = pVariableClass->isKindOf(typeOf<CollectionElementVariable>());
        if(pContainerVariable OR pCollectionInsertVariable OR pCollectionElementVariable)
        {
            reedit();
        }
    }

    void VariableEditor::registerVariableTypeEditorClass( reflection::Type* a_pType, reflection::Class* a_pClass )
    {
        Q_ASSERT(a_pClass->isKindOf(typeOf<VariableWidgetEditor>()));
        m_VariableTypeToEditorClass[a_pType] = a_pClass;
    }

    void VariableEditor::setDataBase( serialization::DataBase* a_pDataBase )
    {
        m_pDataBase = a_pDataBase;
    }

    void VariableEditor::defaultVariableValueSetDelegate( VariableNode* a_pVariable, void const** a_ppValueSources )
    {
        a_pVariable->setValues(a_ppValueSources);
    }

    void VariableEditor::setVariableValueSetDelegate( variable_value_set_delegate d )
    {
        m_variable_value_set_delegate = d;
    }

    void VariableEditor::registerProperty( QtProperty* property, VariableNode* a_pVariable )
    {
        o_assert(getVariable(property) == NULL);
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
        VariableNode* pVariable = getVariable((QtProperty*)property);

        o_assert(pVariable);

        emit variableAboutToBeAccessed(pVariable);

        QString text = valueText(pVariable);

        emit variableAccessed(pVariable);

        return text;
    }

    QString VariableEditor::valueText( VariableNode*  pVariable ) const
    {
        VariableNode*  pVariable = getVariableNode((QtProperty*)property);
        o_assert(pVariable);
        if(!pVariable->hasVariables()) 
        {
            reflection::Class* pVariableClass = pVariable->getVariableClass() ;
            // Insert variables have empty text
            if(pVariableClass->isKindOf(typeOf<ContainerInsertVariable>())
                || pVariableClass->isKindOf(typeOf<ComponentInsertVariable>()))
            {
                return "";
            }

            if(pVariable->hasMultipleValues() && !pVariable->isComponent())
            {
                return "<multiple values>";
            }

            reflection::Type*  type = pVariable->getValueType();

            reflection::ContainerClass* pContainerClass = type->asContainerClass();
            string qualifiedName = type->getQualifiedName();
            if(pContainerClass && qualifiedName != "::std::basic_string")
            {
                void* pContainer = pVariable->getAddress();
                if(pContainer)
                {
                    size_t count = pContainerClass->getCount(pVariable->getAddress());
                    return QString("[")+QString::number(count)+"]";
                }
            }
            else if((type->asDataPointerType() != nullptr) && m_pVariableEditor->m_pDataBase)
            {
                void* value = NULL;
                pVariable->getValue(&value);
                if(value == NULL)
                {
                    return "none";
                }
                uint guid = m_pVariableEditor->m_pDataBase->getGuid(value);
                if(guid == 0xFFFFFFFF ) 
                {
                    if(pVariable->isComponent())
                    {
                        vector<void*> addresses;
                        addresses.resize(pVariable->getVariableCount());
                        for(size_t i = 0; i<addresses.size(); ++i)
                        {
                            pVariable->getVariable(i)->getValue(&addresses[i]);
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
                            string name = pCommonClass->getMetaDataValue(getNameMetaDataIndex());
                            return name.empty() ? pCommonClass->getName().c_str() : name.c_str();
                        }
                        return "none";
                    }
                    return "internal";
                }
                else 
                {
                    data d = m_pVariableEditor->m_pDataBase->getData(guid);
                    return QString(m_pVariableEditor->m_pDataBase->getDataAttributeValue(d, m_pVariableEditor->m_pDataBase->getAttributeIndex("name")).c_str());
                }
            }

            // Construct a temporary buffer to receive the value (don't install rtti to improve performance)

            void* pBufferCurrent = pVariable->getValueType()->removeReference()->removeConst()->allocate();
            pVariable->getValueType()->removeReference()->removeConst()->safeConstruct(pBufferCurrent);
            pVariable->getValueType()->removeReference()->removeConst()->initialize(pBufferCurrent);
            pVariable->getValue(pBufferCurrent);

            string result;

            type->valueToString(result, pBufferCurrent);

            pVariable->getValueType()->removeReference()->removeConst()->terminate(pBufferCurrent);
            pVariable->getValueType()->removeReference()->removeConst()->destroy(pBufferCurrent);
            pVariable->getValueType()->removeReference()->removeConst()->deallocate(pBufferCurrent);

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
                    compound += *it->getName();
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
        VariableNode*  pVariable = getVariable((QtProperty*)property);
        if(pVariable != NULL ) 
        {
            return valueIcon(pVariable); 
        }
        return QIcon();

    }

    QIcon VariableEditor::valueIcon( VariableNode* a_pVariable ) const
    {
        reflection::Type* type = a_pVariable->getValueType();
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
                    return QIcon(pConstant->getMetaDataValue(getIconMetaDataIndex()).c_str());
                }
            }
        }
        else if(type == typeOf<bool>())
        {
            bool value = false;
            a_pVariable->getValue(&value);
            return value ? QIcon(":/../../bin/resources/icons/accept.png") : QIcon(":/../../bin/resources/icons/exclamation.png");
        }
        reflection::ValueMemberBinding* pValueMemberBinding = as<reflection::ValueMemberBinding*>(a_pVariable->getVariable(0));
        if(pValueMemberBinding)
        {
            return QIcon(pValueMemberBinding->getValueMember()->getMetaDataValue(getIconMetaDataIndex()).c_str());
        }
        return QIcon(a_pVariable->getValueType()->getMetaDataValue(getIconMetaDataIndex()).c_str());
    }

    void VariableEditor::variableChildNodeAdded( VariableNode* a_pVariableNode )
    {
        o_connect(a_pVariableNode, childNodeAdded(VariableNode*), this, variableChildNodeAdded(VariableNode*));
        o_connect(a_pVariableNode, childNodeAboutToBeRemoved(VariableNode*), this, variableChildNodeAboutToBeRemoved(VariableNode*));
        if(a_pVariableNode->getParentNode()) // not Root
        {
            if(a_pVariableNode->getParentNode() == m_pVariableModel->getRootNode()) // First level
            {
                QtProperty* property = addProperty(a_pVariableNode->getName().c_str());
                registerProperty(addProperty(property), a_pVariableNode);
            }
            else 
            {
                registerProperty(getProperty(a_pVariableNode->getParentNode())->addSubProperty(addProperty(a_pVariableNode->getName().c_str())));
            }
        }
        for(auto it = a_pVariableNode->beginChildNodes(); it != a_pVariableNode->endChildNodes(); ++it)
        {
            variableChildNodeAdded(*it);
        }
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
            variableChildNodeAboutToBeRemoved(a_pVariableModel->getRootNode());
        }
        m_pVariableModel = a_pVariableModel;
        if(m_pVariableModel)
        {
            variableChildNodeAdded(a_pVariableModel->getRootNode());
        }
    }

    void VariableEditor::variableValueChanged(VariableNode* a_pVariableNode)
    {
        if(a_pVariableNode->getRange() && !a_pVariableNode->hasMultipleValues())
        {
            void * pBufferCurrent = a_pVariableNode->getValueType()->removeReference()->removeConst()->newInstance();
            void * pBufferDefault = a_pVariableNode->getValueType()->removeReference()->removeConst()->newInstance();
            a_pVariableNode->getValue(pBufferCurrent);
            a_pVariableNode->getRange()->getDefault(pBufferDefault);
            getProperty(property)->setModified(!a_pVariableNode->getValueType()->areValueEqual(pBufferCurrent, pBufferDefault));
        }
    }

}}