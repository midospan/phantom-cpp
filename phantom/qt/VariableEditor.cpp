/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableEditor.h"
#include "VariableEditor.hxx"
#include "VariableManager.h"
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
#include "phantom/serialization/Node.h"
#include "phantom/std/string.h"
/* *********************************************** */
o_registerN((phantom, qt), VariableEditor);
 
namespace phantom { namespace qt {

    class VariableEditorFactory : public QtAbstractEditorFactory<VariableManager>
    {
        
    public:
        VariableEditorFactory(VariableEditor* a_pEditor)
            : QtAbstractEditorFactory<VariableManager>(a_pEditor)
            , m_pVariableEditor(a_pEditor)
        {

        }
        QWidget* createEditor(VariableManager*a_pManager, QtProperty *property, QWidget *parent)
        {
            return m_pVariableEditor->createEditor(a_pManager, property, parent);
        }

        void connectPropertyManager(VariableManager *manager)
        {

        }

        void disconnectPropertyManager(VariableManager *manager)
        {

        }

        VariableEditor* m_pVariableEditor;

    };

    VariableEditor::VariableEditor( VariableManager* a_pManager, const QString& a_VariableColumnName )
        : m_pManager(a_pManager)
        , m_pDataBase(nullptr)
        , m_bChangingPropertyValue(false)
        , m_bAutoSaveEnabled(true)
        , m_bAutoSaveStateEnabled(true)
        , m_variable_value_set_delegate(&VariableEditor::defaultVariableValueSetDelegate)
        , m_pOpenedEditor(nullptr)
    {
        Q_ASSERT(m_pManager->m_pVariableEditor == nullptr);
        m_pManager->m_pVariableEditor = this;
        setFactoryForManager(m_pManager, new VariableEditorFactory(this));
        QObject::connect(this, SIGNAL(variableChanged(BufferedVariable*)), this, SLOT(slotVariableChanged(BufferedVariable*)));
        QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(createPropertyPopupMenu(QPoint)));
        setContextMenuPolicy(Qt::CustomContextMenu);
        treeWidget()->setEditTriggers(treeWidget()->editTriggers()|QTreeWidget::AnyKeyPressed);
        setPropertiesWithoutValueMarked(true);
        setResizeMode(Interactive);
        QStringList labels;
        labels.append(QApplication::translate("VariableEditor", a_VariableColumnName.toUtf8().constData(), 0, QApplication::UnicodeUTF8));
        labels.append(QApplication::translate("VariableEditor", "Value", 0, QApplication::UnicodeUTF8));
        labels.append(QApplication::translate("VariableEditor", "Type", 0, QApplication::UnicodeUTF8));
        m_treeWidget->setHeaderLabels(labels);
        m_pManager->initialize();
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
        /*connect(m_pManager, SIGNAL(propertyChanged(QtProperty*)),
            this, SLOT(slotPropertyChanged(QtProperty*)));*/
    }

    VariableEditor::~VariableEditor( void )
    {
     /*   disconnect(m_pManager, SIGNAL(propertyChanged(QtProperty*)),
            this, SLOT(slotPropertyChanged(QtProperty*)));*/
        if(m_pOpenedEditor)
        {
            disconnect(m_pOpenedEditor, SIGNAL(destroyed()), this, SLOT(slotEditorDestroyed()));
            emit variableAccessed(m_pOpenedEditor->getVariable());
            delete m_pOpenedEditor;
        }
        o_dynamic_delete m_pManager;
    }

    QWidget* VariableEditor::createEditor(VariableManager*a_pManager, QtProperty *property, QWidget *parent)
    {
        BufferedVariable* pVariable = a_pManager->getVariable(property);
        if(pVariable == NULL) return NULL;
        if(pVariable->testModifiers(o_readonly)) return NULL;

        emit variableAboutToBeAccessed(pVariable);

        phantom::reflection::Type* pVariableType = pVariable->getValueType();

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
        /*else if(pVariableType->asDataPointerType() && m_pDataBase)
        {
            pVariableWidgetEditor = o_new(DataComboBox)(pVariableType, m_EditedData, m_pDataBase);
        }*/
        if(pVariableWidgetEditor)
        {
            VariableWidget* pVariableWidget = new VariableWidget(pVariableWidgetEditor, this);
            //o_assert(m_pOpenedEditor == nullptr);
            m_pOpenedEditor = pVariableWidget;
            pVariableWidget->setVariable(pVariable);
            pVariableWidget->setParent(parent);
            void* pBuffer = pVariableType->allocate();
            pVariableType->safeSetup(pBuffer);
            pVariable->getValue(pBuffer);
            pVariableWidgetEditor->setValue(pBuffer);
            pVariableType->deleteInstance(pBuffer); 
            connect(pVariableWidget, SIGNAL(destroyed()), this, SLOT(slotEditorDestroyed()));
            connect(pVariableWidgetEditor, SIGNAL(valueChanged()), this, SLOT(slotEditorValueChanged()));
            return pVariableWidget;
        }
        else 
        {
            emit variableAccessed(pVariable);
            return nullptr;
        }
        return nullptr;
    }

    QtBrowserItem* VariableEditor::getBrowserItem(BufferedVariable* a_pVariable) const 
    {
        const QtProperty* property = m_pManager->getProperty(a_pVariable);
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
            phantom::reflection::Variable* pVariable = m_pManager->getVariable(property);
            phantom::reflection::IteratorVariable* pIteratorVariable = phantom::as<phantom::reflection::IteratorVariable*>(pVariable);
            if(pIteratorVariable == NULL) continue;
            QtProperty* parentProperty = *(property->parentProperties().begin());
            phantom::reflection::Variable* pParentVariable = m_pManager->getVariable(parentProperty);
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
        BufferedVariable* pVariable = m_pManager->getVariable(property);
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
        /*if(isEnabled())
        {
            phantom::reflection::Variable* pVariable = m_pManager->getVariable(item->property());
            if(pVariable && pVariable->getModifiers().matchesMask(o_readonly))
            {
                browserItemToItem(item)->setForeground(1, QColor(128,128,128));
            }
            else 
            {
                browserItemToItem(item)->setForeground(0, QColor(0,0,0));
                browserItemToItem(item)->setForeground(1, QColor(0,0,0));
                browserItemToItem(item)->setForeground(2, QColor(0,0,0));
            }
        }
        else 
        {
            browserItemToItem(item)->setForeground(0, QColor(128,128,128));
            browserItemToItem(item)->setForeground(1, QColor(128,128,128));
            browserItemToItem(item)->setForeground(2, QColor(128,128,128));
        }*/
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
        void* pBuffer = pEditor->getType()->newInstance();
        pEditor->getValue(pBuffer);
        m_bChangingPropertyValue = true;
        emit variableAboutToBeChanged(pEditor->getVariable());
        m_variable_value_set_delegate(pEditor->getVariable(), pBuffer);
        m_pManager->emitPropertyChanged((QtProperty*)m_pManager->getProperty(pEditor->getVariable()));
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
        emit variableChanged(pEditor->getVariable());
        m_bChangingPropertyValue = false;
        pEditor->getType()->deleteInstance(pBuffer);
    }

    void VariableEditor::edit(const vector<phantom::data>& a_Data)
    {
        if(!m_EditedData.empty())
        {
            clear();
            m_EditedData.clear();
        }
        m_EditedData = a_Data;
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
                m_pManager->createProperties(editedAddresses, m_pEditedType, properties);
                for(auto it = properties.begin(); it != properties.end(); ++it)
                {
                    addProperty(*it);
                }
            }
        }
        setResizeMode(Interactive);
    }

    void VariableEditor::slotVariableChanged( BufferedVariable* a_pVariable )
    {
        BufferedVariable* pParentVariable = a_pVariable->getParentVariable();
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
            m_pManager->getProperty(a_pVariable)->setModified(!a_pVariable->getValueType()->areValueEqual(pBufferCurrent, pBufferDefault));
        }

        BufferedVariable* pBufferedVariable = as<BufferedVariable*>(a_pVariable);
        reflection::Class* pVariableClass = pBufferedVariable ? pBufferedVariable->getVariableClass() : classOf(a_pVariable);
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

    void VariableEditor::defaultVariableValueSetDelegate( phantom::reflection::Variable* a_pVariable, void const* valueSource )
    {
        a_pVariable->setValue(valueSource);
    }

    void VariableEditor::setVariableValueSetDelegate( variable_value_set_delegate d )
    {
        m_variable_value_set_delegate = d;
    }


}}