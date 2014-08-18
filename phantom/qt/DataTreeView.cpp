/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "DataTreeView.h"
#include "DataTreeView.hxx"
#include "phantom/serialization/Node.h"
#include "phantom/serialization/Trashbin.h"
#include "phantom/util/Message.h"
#include <QHeaderView>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QMenu>
/* *********************************************** */
o_registerN((phantom, qt), DataTreeView);
o_registerN((phantom, qt), AddDataAction);
o_registerN((phantom, qt), AddNodeAction);
o_registerN((phantom, qt), LoadNodeAction);
o_registerN((phantom, qt), UnloadNodeAction);
o_registerN((phantom, qt), RemoveDataAction);

namespace phantom { namespace qt {
    /*
class DataTreeViewPrivate : public QTreeWidgetPrivate
{
    friend class QTreeModel;
    Q_DECLARE_PUBLIC(DataTreeView);
};*/



class DataTreeViewItemAdder : public phantom::TVisitor<phantom::serialization::Node>
    , public phantom::TVisitor<phantom::data>
{
public:
    DataTreeViewItemAdder(DataTreeView* a_pDataTreeView)
        : m_pDataTreeView(a_pDataTreeView)
    {

    }
    virtual void apply(phantom::serialization::Node* a_pNode);
    virtual void apply(phantom::data* a_pData);

protected:
    DataTreeView*   m_pDataTreeView;
};



class DataTreeViewNodeDisconnector : public phantom::TVisitor<phantom::serialization::Node>
{
public:
    DataTreeViewNodeDisconnector(DataTreeView* a_pDataTreeView)
        : m_pDataTreeView(a_pDataTreeView)
    {

    }
    virtual void apply(phantom::serialization::Node* a_pNode);

protected:
    DataTreeView*   m_pDataTreeView;
};

DataTreeView::DataTreeView( Message* a_pRootMessage ) 
    : m_pDataBase(NULL)
    , m_pMessage(a_pRootMessage)
    , m_bHideInternal(true)
    , m_bHideComponentData(true)
	, m_bIsChangingSelection(false)
    , m_AddDataActionDelegate(this, &DataTreeView::defaultAddDataActionDelegate)
    , m_AddNodeActionDelegate(this, &DataTreeView::defaultAddNodeActionDelegate)
    , m_RemoveDataActionDelegate(this, &DataTreeView::defaultRemoveDataActionDelegate)
    , m_LoadNodeActionDelegate(this, &DataTreeView::defaultLoadNodeActionDelegate)
    , m_UnloadNodeActionDelegate(this, &DataTreeView::defaultUnloadNodeActionDelegate)
    , m_RecursiveLoadNodeActionDelegate(this, &DataTreeView::defaultRecursiveLoadNodeActionDelegate)
    , m_DataAttributeChangeDelegate(this, &DataTreeView::defaultDataAttributeChangeDelegate)
    , m_NodeAttributeChangeDelegate(this, &DataTreeView::defaultNodeAttributeChangeDelegate)
    , m_uiNameAttributeIndex(0xffffffff)
    , m_uiCategoryAttributeIndex(0xffffffff)
    , m_NodeLoadedIcon(":/../../bin/resources/icons/folder.png")
    , m_NodeUnloadedIcon(":/../../bin/resources/icons/folder.png")
    , m_NodeRootIcon(":/../../bin/resources/icons/database.png")
    , m_bEditorOpened(false)
{

	QObject::connect(this, SIGNAL(itemSelectionChanged()), SLOT(slotSelectionChanged()));
    QObject::connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(slotItemClicked(QTreeWidgetItem*,int)));
    QObject::connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(slotItemDoubleClicked(QTreeWidgetItem*,int)));

    header()->setResizeMode(QHeaderView::ResizeToContents);

    QStringList headerLabels;
    headerLabels.append("data");
    headerLabels.append("");
    headerLabels.append("guid");
    headerLabels.append("type");
    setHeaderLabels(headerLabels);
    setColumnCount(4);
    QObject::connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showPopup(const QPoint&)));
    
    setContextMenuPolicy(Qt::CustomContextMenu);
    setMinimumWidth(400);

    setDragDropMode(QAbstractItemView::DragDrop);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setDragEnabled(true);
    setAcceptDrops(true);
}

void DataTreeView::dataBaseLoaded(serialization::DataBase* a_pDB) 
{
    
}
void DataTreeView::dataBaseUnloaded(serialization::DataBase* a_pDB) 
{
    m_pDataBase = nullptr;
    setColumnCount(0);
    clear();
}

void DataTreeViewItemAdder::apply( serialization::Node* a_pNode )
{
    o_connect(a_pNode, loaded(), m_pDataTreeView, nodeLoaded());
    o_connect(a_pNode, aboutToBeUnloaded(), m_pDataTreeView, nodeAboutToBeUnloaded());
    m_pDataTreeView->addNodeItem(a_pNode);    
}

void DataTreeViewItemAdder::apply( phantom::data* a_pData )
{
    m_pDataTreeView->addDataItem(*a_pData);
}

void DataTreeViewNodeDisconnector::apply( serialization::Node* a_pNode )
{
    o_disconnect(a_pNode, loaded(), m_pDataTreeView, nodeLoaded());
    o_disconnect(a_pNode, aboutToBeUnloaded(), m_pDataTreeView, nodeAboutToBeUnloaded());
}

void DataTreeView::showPopup(const QPoint & pos)
{
    DataTreeViewItem * item = 0 ;
    auto items = selectedItems ();
    if(items.count() == 0) 
        return;

    QMenu menu(this);
    QMenu addMenu(this);
    vector<Action*> actions;

    if(items.count() == 1)
    {
        item = static_cast<DataTreeViewItem*>(items.back());
        {
            switch(item->getType())
            {
            case DataTreeViewItem::e_Type_Data:
                {
                    const phantom::data& d = ((DataTreeViewDataItem*)item)->getData();
                    reflection::Class* pClass = d.type()->asClass();

                    const phantom::data& owner = m_pDataBase->getComponentDataOwner(d);
                    if(owner.isNull())
                    {
                        // Data directly removed from a Node
                        //menu.addAction(new RemoveDataAction(&menu, m_pDataBase->getNode(d), d));
                    }
                    else
                    {
                        // Data first removed from its owner
                        o_assert(owner.type()->asClass());
                        //phantom::reflection::Collection* pCollection = m_pDataBase->getComponentDataManager()->getCollectionContainingData(d);

                    }

                    // Display/Hide action
                    /*if (d.type()->isKindOf(phantom::typeOf<physic::CollisionShape>()))
                    {
                    menu.addAction(new DisplayDataAction(&menu, d, this));
                    menu.addAction(new HideDataAction(&menu, d, this));
                    }*/
                }
                break;
            case DataTreeViewItem::e_Type_Node:
                {
                    serialization::Node* pNode = (serialization::Node*)item->getContent();
                    if(pNode->getState() == serialization::Node::e_Loaded)
                    {
                        addMenu.setTitle("add");
                        addMenu.setIcon(QIcon("resources/icons/famfamfam/add.png"));
                        menu.addMenu(&addMenu);
                        Action* pAction = o_new(AddNodeAction)(this, pNode, m_AddNodeActionDelegate, this);
                        addMenu.addAction(pAction);
                        actions.push_back(pAction);
                        if(pNode != m_pDataBase->rootNode()) 
                        {
                            addMenu.addSeparator();
                            for(auto it = phantom::beginModules(); it != phantom::endModules(); ++it)
                            {
                                Module* pModule = it->second;
                                QMenu* moduleMenu = new QMenu;
                                for(auto it = pModule->beginLanguageElements(); it != pModule->endLanguageElements(); ++it)
                                {
                                    moduleMenu->setTitle(pModule->getName().c_str());
                                    reflection::Class* pClass = (*it)->asClass();
                                    if(pClass 
                                        AND pClass->isPublic() 
                                        AND NOT(pClass->isComponent())
                                        AND NOT(pClass->isAbstract())
                                        AND pClass->isDefaultConstructible()
                                        AND pClass->getSingleton() == nullptr)
                                    {
                                        Action* pAction = o_new(AddDataAction)(this, (serialization::Node*)item->getContent(), pClass, m_AddDataActionDelegate, moduleMenu);
                                        moduleMenu->addAction(pAction);
                                        actions.push_back(pAction);
                                    }
                                }
                                if(!moduleMenu->isEmpty())
                                {
                                    addMenu.addMenu(moduleMenu);
                                }
                            }
                            menu.addSeparator();
                            if(pNode->getParentNode()) // If it's not the root node
                            {
                                Action* pAction = o_new(UnloadNodeAction)(this, pNode, m_UnloadNodeActionDelegate, &menu);
                                menu.addAction(pAction);
                                actions.push_back(pAction);
                            }
                        }

                    }
                    else if(pNode->getState() == serialization::Node::e_Unloaded)
                    {
                        Action* pAction = o_new(LoadNodeAction)(this, pNode, m_LoadNodeActionDelegate, &menu);
                        menu.addAction(pAction);
                        actions.push_back(pAction);
                        pAction = o_new(LoadNodeAction)(this, pNode, m_RecursiveLoadNodeActionDelegate, &menu);
                        menu.addAction(pAction);
                        actions.push_back(pAction);
                    }
                }
                break;
            }
        }
    }

    {
        vector<uint> guids;
        for(auto it = items.begin(); it != items.end(); ++it)
        {
            DataTreeViewItem* item = (DataTreeViewItem*)*it;
            switch(item->getType())
            {
            case DataTreeViewItem::e_Type_Data:
                {
                    guids.push_back(m_pDataBase->getGuid(((DataTreeViewDataItem*)item)->getData()));
                }
                break;
            case DataTreeViewItem::e_Type_Node:
                {
                    guids.push_back(((DataTreeViewNodeItem*)item)->getNode()->getGuid());
                }
                break;
            }
        }
        RemoveDataAction* pRemoveDataAction = o_new(RemoveDataAction)(this, guids, m_RemoveDataActionDelegate, &menu) ;
        menu.addAction(pRemoveDataAction);
        actions.push_back(pRemoveDataAction);
    }
    if(NOT(menu.isEmpty()))
    {
        menu.exec(QCursor::pos());
    }
    for(auto it = actions.begin(); it != actions.end(); ++it)
    {
        o_dynamic_delete *it;
    }
}


void DataTreeView::dataAdded( const phantom::data& a_Data, serialization::Node* a_pNode)
{
    DataTreeViewItem* pParentItem = getItem(a_pNode);
    o_assert(pParentItem AND pParentItem->getType() == DataTreeViewItem::e_Type_Node);
    string name = nameOf(a_Data.type()).c_str();
    addDataItem(a_Data);
    // m_pDataBase->setDataAttributeValue(a_Data, m_uiNameAttributeIndex, name.empty() ? a_Data.type()->getName() : name);
    sortItems(0, Qt::AscendingOrder);
}

void DataTreeView::dataReplaced(const phantom::data& a_Old,const phantom::data& a_New)
{
    DataTreeViewDataItem* pItem = (DataTreeViewDataItem*)getItem(a_Old.address());
    o_assert(pItem);
    pItem->replaceData(a_New);
}

void DataTreeView::dataAboutToBeRemoved( const phantom::data& a_Data, serialization::Node* a_pNode)
{
    removeDataItem(a_Data);
}

void DataTreeView::nodeAdded( serialization::Node* a_pNode,serialization::Node* a_pParentNode)
{
    o_connect(a_pNode, loaded(), this, nodeLoaded());
    o_connect(a_pNode, aboutToBeUnloaded(), this, nodeAboutToBeUnloaded());
    string name = nameOf(typeOf<serialization::Node>()).c_str();
    // m_pDataBase->setNodeAttributeValue(a_pNode, m_uiNameAttributeIndex, name);
    addNodeItem(a_pNode);
}

void DataTreeView::nodeAboutToBeRemoved( serialization::Node* a_pNode,serialization::Node* a_pParentNode)
{
    o_disconnect(a_pNode, loaded(), this, nodeLoaded());
    o_disconnect(a_pNode, aboutToBeUnloaded(), this, nodeAboutToBeUnloaded());
    removeNodeItem(a_pNode);
}

void DataTreeView::dataAttributeValueChanged( const phantom::data& a_Data, size_t a_uiAttributeIndex, const string& a_strValue )
{
    if(m_bEditorOpened)
    {
        QObject::disconnect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(slotItemChanged(QTreeWidgetItem*,int)));
    }
    DataTreeViewItem* pItem = getItem(a_Data.address());
    if(pItem != NULL)
    {
        if(m_uiCategoryAttributeIndex == a_uiAttributeIndex)
        {
            if( a_strValue == "internal" )
            {
                pItem->setHidden(m_bHideInternal); 
            }
            else if( a_strValue == "subData" )
            {
                pItem->setHidden(m_bHideComponentData); 
            }
            else if( a_strValue == "default")
            {
                QBrush b (Qt::darkGray);
                pItem->setForeground( 0 , b );
            }
        }
        else if(a_uiAttributeIndex == m_uiNameAttributeIndex)
        {
            pItem->setText(0, a_strValue.c_str());
        }
    }
    if(m_bEditorOpened)
    {
        QObject::connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(slotItemChanged(QTreeWidgetItem*,int)));
    }
}

void DataTreeView::nodeAttributeValueChanged( serialization::Node* a_pNode, size_t a_uiAttributeIndex, const string& a_strValue )
{
    if(m_bEditorOpened)
    {
        QObject::disconnect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(slotItemChanged(QTreeWidgetItem*,int)));
    }
    DataTreeViewItem* pItem = getItem(a_pNode);
    if(pItem != NULL)
    {
        if(m_uiCategoryAttributeIndex == a_uiAttributeIndex)
        {
            if( a_strValue == "internal" )
            {
                pItem->setHidden(m_bHideInternal); 
            }
            else if( a_strValue == "subData" )
            {
                pItem->setHidden(m_bHideComponentData); 
            }
            else if( a_strValue == "default")
            {
                QBrush b (Qt::darkGray);
                pItem->setForeground( 0 , b );
            }
        }
        else if(a_uiAttributeIndex == m_uiNameAttributeIndex)
        {
            pItem->setText(0, a_strValue.c_str());
        }
    }
    if(m_bEditorOpened)
    {
        QObject::connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(slotItemChanged(QTreeWidgetItem*,int)));
    }
}

void DataTreeView::addDataItem( const phantom::data& a_Data )
{
    DataTreeViewDataItem* pNewItem = new DataTreeViewDataItem(a_Data);
    pNewItem->setIcon(0, QIcon(iconOf(a_Data.type()).c_str()));
    const phantom::data& ownerData = getDataBase()->getComponentDataOwner(a_Data);
	if(ownerData.isNull())
	{
		serialization::Node* pDataNode = getDataBase()->getNode(a_Data);

		DataTreeViewItem* pNodeItem = getItem(pDataNode);
        o_assert(pNodeItem);
        pNodeItem->addChild(pNewItem);
        pNodeItem->setExpanded(true);
	}
	else
	{
		DataTreeViewItem* pDataItem = getItem(ownerData.address());
		o_assert(pDataItem)
	    pDataItem->addChild(pNewItem);
	}

    const string* values = m_pDataBase->getDataAttributeValues(a_Data);
    bool editable = false;
    if(m_uiCategoryAttributeIndex != 0xffffffff)
    {
        editable = true;
        string category = values[m_uiCategoryAttributeIndex];
        if( category == "internal" )
        {
            pNewItem->setHidden(m_bHideInternal); 
        }
        else if( category == "subData" )
        {
            pNewItem->setHidden(m_bHideComponentData); 
        }

    }

    string name = values[m_uiNameAttributeIndex];

    pNewItem->setText(0, name.c_str());

    char buffer[64] = "";
    sprintf(buffer, "%08X", m_pDataBase->getGuid(a_Data));
    pNewItem->setText(2, buffer);
    pNewItem->setText(3, nameOf(a_Data.type()).c_str());
    /*sprintf(buffer, "%08X", (size_t)a_Data.address());
    pNewItem->setText(4, buffer);*/

    if(editable)
    {
        pNewItem->setFlags(Qt::ItemIsEditable | pNewItem->flags());
    }
}

void DataTreeView::addNodeItem( serialization::Node* a_pNode )
{
    DataTreeViewNodeItem* pNewItem = new DataTreeViewNodeItem(a_pNode);
    if(a_pNode->getParentNode())
    {
        serialization::Node* pNodeNode = a_pNode->getParentNode();
        DataTreeViewItem* pParentItem = getItem(pNodeNode);
        o_assert(pParentItem);
        pParentItem->addChild(pNewItem);
    }
    else
    {
        addTopLevelItem(pNewItem);
    }

    const string* values = getDataBase()->getNodeAttributeValues(a_pNode);

    bool editable = false;
    if(m_uiCategoryAttributeIndex != 0xffffffff)
    {
        editable = true;
        string category = values[m_uiCategoryAttributeIndex];
        if( category == "internal" )
        {
            pNewItem->setHidden(m_bHideInternal); 
        }
        else if( category == "subData" )
        {
            pNewItem->setHidden(m_bHideComponentData); 
        }
    }
    string name = values[m_uiNameAttributeIndex];

    pNewItem->setText(0, name.c_str());
    pNewItem->setIcon(0, a_pNode->isLoaded() ? a_pNode->getParentNode() ? m_NodeLoadedIcon : m_NodeRootIcon : QIcon(m_NodeUnloadedIcon.pixmap(16, QIcon::Disabled)));
    char buffer[64] = "";
    sprintf(buffer, "%08X", m_pDataBase->getGuid(a_pNode));
    pNewItem->setText(2, buffer);
    pNewItem->setText(3, nameOf(phantom::typeOf<serialization::Node>()).c_str());

    if(editable)
    {
        pNewItem->setFlags(Qt::ItemIsEditable | pNewItem->flags());
    }

    sortItems(0, Qt::AscendingOrder);
}

void DataTreeView::removeDataItem( const phantom::data& a_Data )
{
    DataTreeViewItem* pItem = getItem(a_Data.address());
    o_assert(pItem);
	const phantom::data& ownerData = getDataBase()->getComponentDataOwner(a_Data);
	if(ownerData.isNull())
	{
		serialization::Node* pDataNode = getDataBase()->getNode(a_Data);

		DataTreeViewItem* pNodeItem = getItem(pDataNode);
		o_assert(pNodeItem);
		pNodeItem->removeChild(pItem);
	}
	else
	{
		DataTreeViewItem* pDataItem = getItem(ownerData.address());
		o_assert(pDataItem);
		pDataItem->removeChild(pItem);
	}
	sortItems(0, Qt::AscendingOrder);
}

void DataTreeView::removeNodeItem( serialization::Node* a_pNode )
{
    DataTreeViewItem* pItem = getItem(a_pNode);
    o_assert(pItem); // we should not be able to remove the root node
    o_assert(a_pNode->getParentNode()); // we should not be able to remove the root node
    DataTreeViewItem* pParentItem = getItem(a_pNode->getParentNode());
    o_assert(pItem AND pParentItem AND pParentItem->getType() == DataTreeViewItem::e_Type_Node);
    pParentItem->removeChild(pItem);
    sortItems(0, Qt::AscendingOrder);
}

void DataTreeView::nodeLoaded()
{
    serialization::Node* pNode = as<serialization::Node*>(phantom::connection::sender());
    phantom::vector<phantom::data> allData;
    pNode->fetchData(allData);
    pNode->getOwnerDataBase()->sortOwnerDataFirst(allData.begin(), allData.end());
    for (auto it = allData.begin(); it != allData.end(); it++)
    {
        DataTreeViewItem* pItem = getItem(it->address());
        o_assert(pItem == nullptr);
        addDataItem(*it);
    }
    DataTreeViewItem* pNodeItem = getItem(pNode);
    pNodeItem->setIcon(0, pNode->getParentNode() ? m_NodeLoadedIcon : m_NodeRootIcon);
}

void DataTreeView::nodeAboutToBeUnloaded()
{
    serialization::Node* pNode = as<serialization::Node*>(phantom::connection::sender());
    phantom::vector<phantom::data> allData;
    pNode->fetchData(allData);
    pNode->getOwnerDataBase()->sortComponentDataFirst(allData.begin(), allData.end());
	for (auto it = allData.begin(); it != allData.end(); it++)
	{
		DataTreeViewItem* pItem = getItem(it->address());
        o_assert(pItem);
        removeDataItem(*it);
    }
    DataTreeViewItem* pNodeItem = getItem(pNode);
    pNodeItem->setIcon(0, QIcon(m_NodeUnloadedIcon.pixmap(16, QIcon::Disabled)));
}

void DataTreeView::addClassComponentDataActionCascade( QMenu* a_pMenu, const phantom::data& a_Data, phantom::reflection::Collection* a_pCollection, phantom::reflection::Class* a_pComponentDataClass )
{
    /*if(NOT(a_pComponentDataClass->isAbstract()) AND a_pComponentDataClass->isPublic())
    {
        a_pMenu->addAction(new AddComponentDataAction(a_Data, a_pCollection, a_pComponentDataClass, a_pMenu));
    }*/
    size_t i = 0;
    size_t count = a_pComponentDataClass->getDerivedClassCount();
    for(;i<count;++i)
    {
        addClassComponentDataActionCascade( a_pMenu, a_Data, a_pCollection, a_pComponentDataClass->getDerivedClass(i) );
    }
}

QMimeData* DataTreeView::mimeData(const QList<QTreeWidgetItem*> list) const
{
    reflection::Class* pCommonClass = nullptr;
    bool commonClassInitialized = false;

    if(list.count() == 0) return nullptr;

    QByteArray encoded;
    QDataStream stream(&encoded, QIODevice::WriteOnly);
    stream << list.count();
    bool nodeFound = false;
    bool dataFound = false;


    Q_FOREACH(QTreeWidgetItem* item, list)
    {
        DataTreeViewItem* pItem = static_cast<DataTreeViewItem*>(item);
        reflection::Class* pItemClass = nullptr;
        if(pItem->getType() == DataTreeViewItem::e_Type_Data)
        {
            dataFound = true;
            DataTreeViewDataItem* pDataItem = static_cast<DataTreeViewDataItem*>(pItem);
            pItemClass = pDataItem->getData().type()->asClass();
            o_assert(pItemClass);
            stream << (size_t)pDataItem->getData().address() << (size_t)pItemClass;
        }
        else if(pItem->getType() == DataTreeViewItem::e_Type_Node)
        {
            nodeFound = true;
            DataTreeViewNodeItem* pNodeItem = static_cast<DataTreeViewNodeItem*>(pItem);
            pItemClass = phantom::typeOf<serialization::Node>();
            stream << (size_t)pNodeItem->getNode() << (size_t)pItemClass;
        }
        if(NOT(commonClassInitialized))
        {
            pCommonClass = pItemClass;
            commonClassInitialized = true;
        }
        pCommonClass = commonSuperClass(pCommonClass, pItemClass);

    }

    if((dataFound AND nodeFound)) return nullptr;

    QMimeData* pMimeData = new QMimeData;

    QString mimeType = dataFound ? "application/database-data" : "application/database-node";

    pMimeData->setData(mimeType, encoded);

    return pMimeData;
}

void DataTreeView::dragEnterEvent( QDragEnterEvent *event )
{
    QTreeWidget::dragEnterEvent(event);
    std::cout<<"dragEnterEvent"<<std::endl;
    
}

void DataTreeView::dragLeaveEvent( QDragLeaveEvent *event )
{
    QTreeWidget::dragLeaveEvent(event);
    std::cout<<"dragLeaveEvent"<<std::endl;
}

void DataTreeView::dropEvent( QDropEvent* event )
{
    QTreeWidget::dropEvent(event);
    std::cout<<"dropEvent"<<std::endl;
}

phantom::reflection::Class* DataTreeView::commonSuperClass( phantom::reflection::Class* a_pFirst, phantom::reflection::Class* a_pSecond ) const
{
    if(a_pFirst == nullptr) return nullptr;
    if(a_pSecond == nullptr) return nullptr;
    if(a_pFirst == a_pSecond) return a_pFirst;

    if(a_pFirst->isKindOf(a_pSecond)) return a_pSecond;
    if(a_pSecond->isKindOf(a_pFirst)) return a_pFirst;

    size_t i = 0;
    size_t count = a_pFirst->getSuperClassCount();
    for(;i<count;++i)
    {
        reflection::Class* pCommon = commonSuperClass(a_pFirst->getSuperClass(i), a_pSecond);
        if(pCommon) return pCommon;
    }
    return nullptr;
}

DataTreeView::~DataTreeView( void )
{

}

void DataTreeView::keyPressEvent( QKeyEvent* a_pEvent )
{
    if(a_pEvent->key() == Qt::Key_F2 && selectedItems().size())
    {
        editItem(selectedItems().back(), 0);
    }
    // TODO : Select all items with ctrl-a ?
}

void DataTreeView::slotItemClicked(QTreeWidgetItem* item, int col)
{
	// Add to the current selection
	/*if (QApplication::keyboardModifiers() & Qt::ControlModifier)
	{
		DataTreeViewItem* pItem = static_cast<DataTreeViewItem*>(item);
		if(pItem->getType() == DataTreeViewItem::e_Type_Data)
		{
			if (pItem->isSelected())
			{
				emit dataDeselected(((DataTreeViewDataItem*)pItem)->getData());
			}
			else
			{
				emit dataSelected(((DataTreeViewDataItem*)pItem)->getData());
			}
		}
		else if(pItem->getType() == DataTreeViewItem::e_Type_Node)
		{
			if (pItem->isSelected())
			{
				emit nodeDeselected(((DataTreeViewNodeItem*)pItem)->getNode());
			}
			else
			{
				emit nodeSelected(((DataTreeViewNodeItem*)pItem)->getNode());
			}
		}
	}*/

    DataTreeViewItem*   pItem = static_cast<DataTreeViewItem*>(item);
    if(pItem->getType() == DataTreeViewItem::e_Type_Data)
    {
        emit dataClicked(((DataTreeViewDataItem*)pItem)->getData());
    }
    else if(pItem->getType() == DataTreeViewItem::e_Type_Node)
    {
        emit nodeClicked(((DataTreeViewNodeItem*)pItem)->getNode());
    }
}

void DataTreeView::slotItemDoubleClicked(QTreeWidgetItem* item, int col)
{
    DataTreeViewItem*   pItem = static_cast<DataTreeViewItem*>(item);
    if(pItem->getType() == DataTreeViewItem::e_Type_Data)
    {
        emit dataDoubleClicked(((DataTreeViewDataItem*)pItem)->getData());
    }
}

void DataTreeView::slotCurrentChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
	// Select a list
	/*if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
	{
		// Search others items
		bool bFound = true;
		phantom::vector<DataTreeViewItem*> items;
		DataTreeViewItem* pNextItem = static_cast<DataTreeViewItem*>(current);
		items.push_back(pNextItem);
		while (pNextItem != previous)
		{
			pNextItem = static_cast<DataTreeViewItem*>(itemBelow(pNextItem));
			if (pNextItem == NULL)
			{
				bFound = false;
				break;
			}
			else
			{
				items.push_back(pNextItem);
			}
		}

		if (NOT(bFound))
		{
			bFound = true;
			pNextItem = static_cast<DataTreeViewItem*>(current);
			while (pNextItem != previous)
			{
				pNextItem = static_cast<DataTreeViewItem*>(itemAbove(pNextItem));
				if (pNextItem == NULL)
				{
					bFound = false;
					break;
				}
				else
				{
					items.push_back(pNextItem);
				}
			}
		}

		if (bFound)
		{
			DataTreeViewItem* pItem;
			phantom::vector<DataTreeViewItem*>::iterator it = items.begin();
			phantom::vector<DataTreeViewItem*>::iterator end = items.end();
			for (; it != end; it++)
			{
				pItem = *it;
				if(pItem->getType() == DataTreeViewItem::e_Type_Data)
				{
					emit dataSelected(((DataTreeViewDataItem*)pItem)->getData());
				}
				else if(pItem->getType() == DataTreeViewItem::e_Type_Node)
				{
					emit nodeSelected(((DataTreeViewNodeItem*)pItem)->getNode());
				}
			}
		}
	}

	// New selection
	else if (NOT(QApplication::keyboardModifiers() & Qt::ControlModifier))
	{
		//emit allDeselected();

		DataTreeViewItem* pItem = static_cast<DataTreeViewItem*>(current);
		if(pItem->getType() == DataTreeViewItem::e_Type_Data)
		{
			emit dataSelected(((DataTreeViewDataItem*)pItem)->getData());
		}
		else if(pItem->getType() == DataTreeViewItem::e_Type_Node)
		{
			emit nodeSelected(((DataTreeViewNodeItem*)pItem)->getNode());
		}
	}*/
}

void DataTreeView::slotSelectionChanged()
{
	if (NOT(m_bIsChangingSelection))
	{
		QList<QTreeWidgetItem*> items = selectedItems();

		phantom::vector<phantom::data> datas;
		phantom::vector<serialization::Node*> nodes;

		DataTreeViewItem* pItem;
		QList<QTreeWidgetItem*>::iterator it = items.begin();
		QList<QTreeWidgetItem*>::iterator end = items.end();
		for (; it != end; it++)
		{
			pItem = static_cast<DataTreeViewItem*>(*it);
			if(pItem->getType() == DataTreeViewItem::e_Type_Data)
			{
				datas.push_back(((DataTreeViewDataItem*)pItem)->getData());
			}
			else if(pItem->getType() == DataTreeViewItem::e_Type_Node)
			{
				nodes.push_back(((DataTreeViewNodeItem*)pItem)->getNode());
			}
		}

        emit selectionChanged(datas, nodes);
        emit selectionChanged(datas);
	}
}

void DataTreeView::select(const phantom::vector<phantom::data>& a_Datas, const phantom::vector<serialization::Node*>& a_Nodes)
{
	m_bIsChangingSelection = true;

	// Old items
    QList<QTreeWidgetItem*> oldItems = selectedItems();
    QList<QTreeWidgetItem*> newItems;

	// New datas
	for (auto itData = a_Datas.begin(); itData != a_Datas.end(); itData++)
	{
		QTreeWidgetItem* pItem = (QTreeWidgetItem*)getItem(itData->address());

		QList<QTreeWidgetItem*>::iterator it = std::find(oldItems.begin(), oldItems.end(), pItem);
		if (it == oldItems.end())
		{
			newItems.push_back(pItem);
		}
		else
		{
			oldItems.erase(it);
		}
	}

	// New nodes
	for (auto itNode = a_Nodes.begin(); itNode != a_Nodes.end(); itNode++)
	{
		QTreeWidgetItem* pItem = (QTreeWidgetItem*)getItem(*itNode);

        QList<QTreeWidgetItem*>::iterator it = std::find(oldItems.begin(), oldItems.end(), pItem);
        if (it == oldItems.end())
        {
            newItems.push_back(pItem);
        }
        else
        {
            oldItems.erase(it);
        }
	}

	// Remove old items
	for (auto itItem = oldItems.begin(); itItem != oldItems.end(); itItem++)
	{
		(*itItem)->setSelected(false);
    }
    for (auto itItem = newItems.begin(); itItem != newItems.end(); itItem++)
    {
        (*itItem)->setSelected(true);
    }

	m_bIsChangingSelection = false;
}

void DataTreeView::defaultAddDataActionDelegate( DataTreeView* a_pDataTreeView, serialization::Node* a_pOwnerNode, reflection::Type* a_pType )
{
    a_pOwnerNode->newData(a_pType);
}

void DataTreeView::defaultAddNodeActionDelegate( DataTreeView* a_pDataTreeView, serialization::Node* a_pParentNode )
{
    a_pParentNode->newChildNode();
}

void DataTreeView::defaultLoadNodeActionDelegate( DataTreeView* a_pDataTreeView, serialization::Node* a_pNode )
{
    if(a_pNode->getParentNode() && !a_pNode->getParentNode()->isLoaded())
        defaultLoadNodeActionDelegate(a_pDataTreeView, a_pNode->getParentNode());
    vector<string> missingTypes;
    if(a_pNode->canLoad(&missingTypes) && a_pNode->getParentNode()->isLoaded())
    {
        a_pNode->load();
    }
    else if(m_pMessage)
    {
        Message* pMessage = m_pMessage->error(this, "Cannot load node : %s", m_pDataBase->getNodeAttributeValue(a_pNode, m_uiNameAttributeIndex).c_str());
        for(auto it = missingTypes.begin(); it != missingTypes.end(); ++it)
        {
            pMessage->error(this, "Missing class : %s", (*it).c_str());
        }
    }
}

void DataTreeView::defaultUnloadNodeActionDelegate( DataTreeView* a_pDataTreeView, serialization::Node* a_pNode )
{
    for(size_t i = 0; i<a_pNode->getChildNodeCount(); ++i)
    {
        serialization::Node* pNode = a_pNode->getChildNode(i);
        if(pNode->isLoaded())
        {
            defaultUnloadNodeActionDelegate(a_pDataTreeView, pNode);
        }
    }
    a_pNode->unload();
}

void DataTreeView::defaultRecursiveLoadNodeActionDelegate( DataTreeView* a_pDataTreeView, serialization::Node* a_pNode )
{
    if(a_pNode->getParentNode() && !a_pNode->getParentNode()->isLoaded())
        defaultLoadNodeActionDelegate(a_pDataTreeView, a_pNode->getParentNode());
    vector<string> missingTypes;
    if(a_pNode->getParentNode()->isLoaded() && a_pNode->canLoad(&missingTypes))
    {
        a_pNode->load();
        for(size_t i = 0; i<a_pNode->getChildNodeCount(); ++i)
        {
            defaultRecursiveLoadNodeActionDelegate(a_pDataTreeView, a_pNode->getChildNode(i));
        }
    }
    else 
    {
        if(m_pMessage)
        {
            Message* pMessage = m_pMessage->error(this, "Cannot load node : %s", m_pDataBase->getNodeAttributeValue(a_pNode, m_uiNameAttributeIndex).c_str());
            for(auto it = missingTypes.begin(); it != missingTypes.end(); ++it)
            {
                pMessage->error(this, "Missing class : %s", (*it).c_str());
            }
        }
    }
}

void DataTreeView::setDataBase( serialization::DataBase* a_pDataBase, size_t a_uiNameAttributeIndex, size_t a_uiCategoryAttributeIndex )
{
    o_assert(a_uiNameAttributeIndex != a_uiCategoryAttributeIndex);
    if(m_pDataBase == a_pDataBase) return;
    if(m_pDataBase)
    {

        DataTreeViewNodeDisconnector   disconnector(this);
        m_pDataBase->rootNode()->applyNodeVisitor(&disconnector);
        o_disconnect(m_pDataBase, dataAdded(const phantom::data&,serialization::Node*), this, dataAdded(const phantom::data&,serialization::Node*));
        o_disconnect(m_pDataBase, dataReplaced(const phantom::data&,const phantom::data&), this, dataReplaced(const phantom::data&,const phantom::data&));
        o_disconnect(m_pDataBase, dataAboutToBeRemoved(const phantom::data&,serialization::Node*), this, dataAboutToBeRemoved(const phantom::data&,serialization::Node*));
        o_disconnect(m_pDataBase, nodeAdded(serialization::Node*,serialization::Node*), this, nodeAdded(serialization::Node*,serialization::Node*));
        o_disconnect(m_pDataBase, nodeAboutToBeRemoved(serialization::Node*,serialization::Node*), this, nodeAboutToBeRemoved(serialization::Node*,serialization::Node*));
        o_disconnect(m_pDataBase, dataAttributeValueChanged( const phantom::data&, size_t, const string&), this, dataAttributeValueChanged( const phantom::data&, size_t, const string&));
        o_disconnect(m_pDataBase, nodeAttributeValueChanged( serialization::Node*, size_t, const string&), this, nodeAttributeValueChanged( serialization::Node*, size_t, const string&));
        setColumnCount(0);
        clear();
        m_uiNameAttributeIndex = 0xffffffff;
        m_uiCategoryAttributeIndex = 0xffffffff;
    }
    m_pDataBase = a_pDataBase;
    if(m_pDataBase)
    {
        o_assert(m_pDataBase->getAttributeName(a_uiNameAttributeIndex).size());
        m_uiNameAttributeIndex = a_uiNameAttributeIndex;
        m_uiCategoryAttributeIndex = a_uiCategoryAttributeIndex;
        QStringList headerLabels;
        headerLabels.append("name");
        headerLabels.append("");
        headerLabels.append("guid");
        headerLabels.append("type");
#ifdef _DEBUG
        headerLabels.append("address");
#endif
        setHeaderLabels(headerLabels);
        DataTreeViewItemAdder   adder(this);
        m_pDataBase->rootNode()->applyNodeVisitor(&adder);
        m_pDataBase->rootNode()->applyDataVisitor(&adder);
        o_connect(m_pDataBase, dataAdded(const phantom::data&,serialization::Node*), this, dataAdded(const phantom::data&,serialization::Node*));
        o_connect(m_pDataBase, dataReplaced(const phantom::data&,const phantom::data&), this, dataReplaced(const phantom::data&,const phantom::data&));
        o_connect(m_pDataBase, dataAboutToBeRemoved(const phantom::data&,serialization::Node*), this, dataAboutToBeRemoved(const phantom::data&,serialization::Node*));
        o_connect(m_pDataBase, nodeAdded(serialization::Node*,serialization::Node*), this, nodeAdded(serialization::Node*,serialization::Node*));
        o_connect(m_pDataBase, nodeAboutToBeRemoved(serialization::Node*,serialization::Node*), this, nodeAboutToBeRemoved(serialization::Node*,serialization::Node*));
        o_connect(m_pDataBase, dataAttributeValueChanged( const phantom::data&, size_t, const string&), this, dataAttributeValueChanged( const phantom::data&, size_t, const string&));
        o_connect(m_pDataBase, nodeAttributeValueChanged( serialization::Node*, size_t, const string&), this, nodeAttributeValueChanged( serialization::Node*, size_t, const string&));
    }
}

void DataTreeView::slotItemChanged( QTreeWidgetItem* a_pItem, int a_iColumn )
{
    if(a_iColumn == 0)
    {
        DataTreeViewItem* pItem = static_cast<DataTreeViewItem*>(a_pItem);
        if(pItem->getType() == DataTreeViewItem::e_Type_Data)
        {
            phantom::data d = ((DataTreeViewDataItem*)pItem)->getData();
            m_DataAttributeChangeDelegate(this, d, 0, pItem->text(0).toAscii().constData());
        }
        else if(pItem->getType() == DataTreeViewItem::e_Type_Node)
        {
            serialization::Node* pNode = ((DataTreeViewNodeItem*)pItem)->getNode();
            m_NodeAttributeChangeDelegate(this, pNode, 0, pItem->text(0).toAscii().constData());
        }
    }
    sortItems(0, Qt::AscendingOrder);
}

DataTreeViewItem* DataTreeView::getItem( void* a_pContent ) const
{
    int i = 0;
    int count = topLevelItemCount () ;
    for(;i<count;++i)
    {
        DataTreeViewItem* pItem = static_cast<DataTreeViewItem*>( topLevelItem(i) );
        if(pItem->getContent() == a_pContent) return pItem;
        pItem = getItem(a_pContent, pItem);
        if(pItem) return pItem;
    }
    return NULL;
}

DataTreeViewItem* DataTreeView::getItem( void* a_pContent, DataTreeViewItem* a_pParentItem ) const
{
    int i = 0;
    int count = a_pParentItem->childCount();
    for(;i<count;++i)
    {
        DataTreeViewItem* pItem = static_cast<DataTreeViewItem*>( a_pParentItem->child(i) );
        if(pItem->getContent() == a_pContent) return pItem;
        pItem = getItem(a_pContent, pItem);
        if(pItem) return pItem;
    }
    return NULL;
}

void DataTreeView::defaultRemoveDataActionDelegate( DataTreeView* a_pDataTreeView, const vector<uint>& a_Guids )
{
    a_pDataTreeView->getDataBase()->getTrashbin()->add(a_Guids);
}

void DataTreeView::defaultNodeAttributeChangeDelegate( DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode, size_t a_uiAttributeIndex, const string& a_Value )
{
    a_pDataTreeView->getDataBase()->setNodeAttributeValue(a_pNode, a_uiAttributeIndex, a_Value);
}

void DataTreeView::defaultDataAttributeChangeDelegate( DataTreeView* a_pDataTreeView, const phantom::data& a_Data, size_t a_uiAttributeIndex, const string& a_Value )
{
    a_pDataTreeView->getDataBase()->setDataAttributeValue(a_Data, a_uiAttributeIndex, a_Value);
}

void DataTreeView::closeEditor( QWidget *editor, QAbstractItemDelegate::EndEditHint hint )
{
    o_assert(m_bEditorOpened);
    QTreeWidget::closeEditor(editor, hint);
    QObject::disconnect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(slotItemChanged(QTreeWidgetItem*,int)));
    m_bEditorOpened = false;
}

bool DataTreeView::edit( const QModelIndex & index, EditTrigger trigger, QEvent * event )
{
    bool result = QTreeWidget::edit(index, trigger, event);
    if(result)
    {
        o_assert(!m_bEditorOpened);
        m_bEditorOpened = true;
        QObject::connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(slotItemChanged(QTreeWidgetItem*,int)));
    }
    return result;
}

void DataTreeViewDataItem::replaceData( const phantom::data& d )
{
    m_Data = d;
    setText(3, nameOf(d.type()).c_str());
}


AddNodeAction::AddNodeAction( DataTreeView* a_pDataTreeView, serialization::Node* a_pNode, DataTreeView::node_action_delegate a_Delegate, QObject* a_pParent ) 
    : Action(a_pParent) 
    , m_pTargetNode(a_pNode)
    , m_Delegate(a_Delegate)
    , m_pDataTreeView(a_pDataTreeView)
{
}

LoadNodeAction::LoadNodeAction( DataTreeView* a_pDataTreeView, serialization::Node* a_pNode, DataTreeView::node_action_delegate a_Delegate, QObject* a_pParent ) 
    : Action(a_pParent) 
    , m_pTargetNode(a_pNode)
    , m_Delegate(a_Delegate)
    , m_pDataTreeView(a_pDataTreeView)
{
}

UnloadNodeAction::UnloadNodeAction( DataTreeView* a_pDataTreeView, serialization::Node* a_pNode, DataTreeView::node_action_delegate a_Delegate, QObject* a_pParent ) 
    : Action(a_pParent) 
    , m_pTargetNode(a_pNode)
    , m_Delegate(a_Delegate)
    , m_pDataTreeView(a_pDataTreeView)
{
}

AddDataAction::AddDataAction( DataTreeView* a_pDataTreeView, serialization::Node* a_pNode, phantom::reflection::Type* a_pDataType, DataTreeView::new_data_action_delegate a_Delegate, QObject* a_pParent ) 
    : Action(a_pParent) 
    , m_pTargetNode(a_pNode)
    , m_pDataType(a_pDataType)
    , m_Delegate(a_Delegate)
    , m_pDataTreeView(a_pDataTreeView)
{
    setText(nameOf(a_pDataType).c_str());
    setIcon(QIcon(iconOf(a_pDataType).c_str()));
}

RemoveDataAction::RemoveDataAction( DataTreeView* a_pDataTreeView, const vector<uint>& a_Guids, DataTreeView::remove_data_action_delegate a_Delegate, QObject* a_pParent ) 
    : Action(a_pParent) 
    , m_pDataTreeView(a_pDataTreeView)
    , m_Guids(a_Guids)
    , m_Delegate(a_Delegate)
{
    setText("Remove");
    setIcon(QIcon("../../bin/resources/icons/delete.png"));
}


void RemoveDataAction::doAction()
{
#if !defined(_NDEBUG)
    vector<uint> uniqueGuids = m_Guids;
    std::sort(uniqueGuids.begin(), uniqueGuids.end());
    std::unique(uniqueGuids.begin(), uniqueGuids.end());
    o_assert(uniqueGuids.size() == m_Guids.size(), "Doublon guids found in given guid list");
#endif

    vector<uint> guids; 
    map<serialization::Node*, size_t> nodeDataCount;
    vector<phantom::data> datas;
    for(auto it = m_Guids.begin(); it != m_Guids.end(); ++it)
    {
        serialization::Node* pNode = m_pDataTreeView->getDataBase()->getNode(*it);
        if(pNode)
        {
            if(pNode->isLoaded())
            {
                if(pNode->getDataCount() == 0)
                {
                    guids.push_back(*it);
                }
                else nodeDataCount[pNode] = pNode->getDataCount();
            }
        }
        else 
        {
            datas.push_back(m_pDataTreeView->getDataBase()->getData(*it));
            guids.push_back(*it);
        }
    }
    for(auto it = datas.begin(); it != datas.end(); ++it)
    {
        auto found = nodeDataCount.find(m_pDataTreeView->getDataBase()->getNode(*it));
        if(found != nodeDataCount.end())
        {
            o_assert(found->second > 0);
            found->second--;
            if(found->second == 0)
            {
                guids.push_back(found->first->getGuid());
            }
        }
    }
    m_Delegate(m_pDataTreeView, guids);
}

}}
