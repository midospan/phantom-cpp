/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableEditor.h"
#include "VariableEditor.hxx"
#include "VariableModel.h"
#include "VariableNode.h"
#include "VariableWidget.h"
#include "VariableWidgetEditor.h"
#include <QAction>
#include <QMenu>
#include <QScrollBar>
#include <QtGui/QToolButton>
#include <QtGui/QPushButton>
#include "Menu.h"
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
        labels.append(QApplication::translate("VariableEditor", "Actions", 0, QApplication::UnicodeUTF8));
        labels.append(QApplication::translate("VariableEditor", "Type", 0, QApplication::UnicodeUTF8));
        m_treeWidget->setHeaderLabels(labels);
        QObject::connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showPopup(const QPoint&)));
        setContextMenuPolicy(Qt::CustomContextMenu);
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

        VariableWidgetEditor* pVariableWidgetEditor = pVariableNode->createEditor();

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

    void VariableEditor::showPopup(const QPoint& pos)
    {
        auto items = treeWidget()->selectedItems();
        if(items.count() == 0) 
            return;
        QTreeWidgetItem* pItem = items.back();
        VariableNode* pVariableNode = getVariableNode(itemToBrowserItem(pItem)->property());
        Menu* pMenu = pVariableNode->createMenu();
        if(pMenu)
        {
            pMenu->exec(QCursor::pos());
            o_dynamic_delete pMenu;
        }
    }
    
    void VariableEditor::updateCustomExtraColumns( QTreeWidgetItem * item, QtProperty * property )
    {
        VariableNode* pVariable = getVariableNode(property);
        if(pVariable == nullptr) 
        {
            item->setText(e_Column_Type, "");
            item->setIcon(e_Column_Type, QIcon());
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
                item->setText(e_Column_Type, (name + extension).c_str());
                item->setIcon(e_Column_Type, icon);
            }
        }
    }

    void VariableEditor::reedit()
    {
        if(m_pVariableModel == nullptr) return;
        int vpos = m_treeWidget->verticalScrollBar()->sliderPosition();
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
        m_pVariableModel->setVariableValue(pVariable, const_cast<const void*>(pBuffer));
        m_pManager->emitPropertyChanged((QtProperty*)getProperty(pVariable));
        m_pVariableModel->slotVariableNodeExpressionsAssigned(pVariable);
        m_bChangingPropertyValue = false;
        pVariableType->deleteInstance(pBuffer);
    }

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
        QString text = pVariable->valueText().c_str() ;
        m_pVariableModel->slotVariableNodeAccessed(pVariable);

        return text;
    }

    QIcon VariableEditor::valueIcon( const QtProperty *property ) const
    {
        VariableNode*  pVariable = getVariableNode((QtProperty*)property);
        if(pVariable != NULL ) 
        {
            return pVariable->valueIcon();
        }
        return QIcon();

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
            createActionWidget(property, a_pVariableNode);
        }
        for(auto it = a_pVariableNode->beginChildNodes(); it != a_pVariableNode->endChildNodes(); ++it)
        {
            variableChildNodeAdded(*it);
        }
        treeWidget()->setColumnWidth(e_Column_Value, m_iUserValueColumnWidth);
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
            o_disconnect(m_pVariableModel, changed(), this, refresh());
            o_disconnect(m_pVariableModel, rootNodeAdded(VariableNode*), this, variableChildNodeAdded(VariableNode*));
            o_disconnect(m_pVariableModel, rootNodeAboutToBeRemoved(VariableNode*), this, variableChildNodeAboutToBeRemoved(VariableNode*));
            o_disconnect(m_pVariableModel, variableNodeExpressionsAboutToBeAssigned(VariableNode*), this, variableNodeExpressionsAboutToBeAssigned(VariableNode*));
            o_disconnect(m_pVariableModel, variableNodeExpressionsAssigned(VariableNode*), this, variableNodeExpressionsAssigned(VariableNode*));
            if(m_pVariableModel->getRootNode())
            {
                variableChildNodeAboutToBeRemoved(m_pVariableModel->getRootNode());
            }
        }
        m_pVariableModel = a_pVariableModel;
        if(m_pVariableModel)
        {
            o_connect(m_pVariableModel, changed(), this, refresh());
            o_connect(m_pVariableModel, rootNodeAdded(VariableNode*), this, variableChildNodeAdded(VariableNode*));
            o_connect(m_pVariableModel, rootNodeAboutToBeRemoved(VariableNode*), this, variableChildNodeAboutToBeRemoved(VariableNode*));
            o_connect(m_pVariableModel, variableNodeExpressionsAboutToBeAssigned(VariableNode*), this, variableNodeExpressionsAboutToBeAssigned(VariableNode*));
            o_connect(m_pVariableModel, variableNodeExpressionsAssigned(VariableNode*), this, variableNodeExpressionsAssigned(VariableNode*));
            if(m_pVariableModel->getRootNode())
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

    void VariableEditor::createActionWidget( QtProperty* property, VariableNode* a_pVariable )
    {
        QWidget* pWidget = a_pVariable->createActionWidget();
        if(pWidget)
        {
            pWidget->setParent(treeWidget());
            QTreeWidgetItem* pItem = browserItemToItem(propertyToBrowserItem(property));
            o_assert(pItem);
            treeWidget()->setItemWidget(pItem, e_Column_Actions, pWidget);
            pWidget->show();
        }
    }

}}