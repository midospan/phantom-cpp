#ifndef phantom_qt_DataTreeView_h__
#define phantom_qt_DataTreeView_h__

/* ****************** Includes ******************* */
#include <phantom/qt/qt.h>
#include <phantom/qt/Action.h>
#include <QTreeWidget>
#include <phantom/util/TVisitor.h>
#include <QAction>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), Node)
o_declareN(class, (phantom, qt), DataTreeView);
o_declareN(class, (phantom, qt), AddDataAction);
o_declareN(class, (phantom, qt), AddNodeAction);
o_declareN(class, (phantom, qt), LoadNodeAction);
o_declareN(class, (phantom, qt), UnloadNodeAction);
o_declareN(class, (phantom, qt), RemoveDataAction);
o_declareN(class, (phantom, qt), UndoStack);
/* *********************************************** */

namespace phantom { 

class Message;

namespace qt {

class DataTreeView;
class Project;
class UndoCommand;

class DataTreeViewItem : public QTreeWidgetItem
{
public:
    enum Type
    {
        e_Type_Node,
        e_Type_Data,
    };

    virtual void*   getContent() const = 0;
    virtual Type    getType() const = 0;
};

class DataTreeViewNodeItem : public DataTreeViewItem
{
public:
    DataTreeViewNodeItem(phantom::serialization::Node* a_pNode)
        : m_pNode(a_pNode) {}

    phantom::serialization::Node*   getNode() const { return m_pNode; }
    virtual void*   getContent() const { return m_pNode; }
    virtual Type    getType() const { return e_Type_Node; }
    bool operator<(const QTreeWidgetItem & other) const
    {
        const DataTreeViewItem* dataTreeViewItem = static_cast<const DataTreeViewItem*>(&other);
        if(dataTreeViewItem->getType() == e_Type_Data)
        {
            return true;
        }
        return DataTreeViewItem::operator<(other);
    }

protected:
    phantom::serialization::Node* m_pNode;

};

class DataTreeViewDataItem : public DataTreeViewItem
{
public:
    DataTreeViewDataItem(const phantom::data& a_Data)
        : m_Data(a_Data) {}

    const phantom::data&   getData() const { return m_Data; }
    virtual void*   getContent() const { return m_Data.address(); }
    virtual Type    getType() const { return e_Type_Data; }
    bool operator<(const QTreeWidgetItem & other) const
    {
        const DataTreeViewItem* dataTreeViewItem = static_cast<const DataTreeViewItem*>(&other);
        if(dataTreeViewItem->getType() == e_Type_Node)
        {
            return false;
        }
        return DataTreeViewItem::operator<(other);
    }

    void replaceData(const phantom::data& d);

protected:
    phantom::data   m_Data;
};

class DataTreeViewItemAdder;
class DataTreeViewNodeDisconnector;
class o_qt_export DataTreeView : public QTreeWidget
{
    friend class DataTreeViewItemAdder;
    friend class DataTreeViewNodeDisconnector;

    Q_OBJECT

public:
    typedef fastdelegate::FastDelegate< void ( DataTreeView*, phantom::serialization::Node*, reflection::Type* ) > new_data_action_delegate;
    typedef fastdelegate::FastDelegate< void ( DataTreeView*, phantom::serialization::Node* ) > node_action_delegate;
    typedef fastdelegate::FastDelegate< void ( DataTreeView*, const vector<uint>& a_Guids ) > remove_data_action_delegate;
    typedef fastdelegate::FastDelegate< void ( DataTreeView*, const phantom::data&, size_t, const string&) > data_attribute_change_delegate;
    typedef fastdelegate::FastDelegate< void ( DataTreeView*, phantom::serialization::Node*, size_t, const string& ) > node_attribute_change_delegate;

    void defaultAddDataActionDelegate(DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pOwnerNode, reflection::Type* a_pType);

    void defaultAddNodeActionDelegate(DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pParentNode);

    void defaultRemoveDataActionDelegate(DataTreeView* a_pDataTreeView, const vector<uint>& a_Guid);

    void defaultLoadNodeActionDelegate(DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode);

    void defaultUnloadNodeActionDelegate(DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode);

    void defaultRecursiveLoadNodeActionDelegate(DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode);

    void defaultNodeAttributeChangeDelegate(DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode, size_t a_uiAttributeIndex, const string& a_Value);

    void defaultDataAttributeChangeDelegate(DataTreeView* a_pDataTreeView, const phantom::data& a_Data, size_t a_uiAttributeIndex, const string& a_Value);

public:
	DataTreeView(Message* a_pRootMessage = nullptr);
	~DataTreeView(void);

	o_initialize() {};

    serialization::DataBase* getDataBase() const {return m_pDataBase;}
    void setDataBase(serialization::DataBase* a_pDataBase, size_t a_uiNameAttributeIndex = 0);

    UndoStack* getUndoStack() const {return m_pUndoStack;}
    void setUndoStack(UndoStack* a_pUndoStack);

    void setMessage(Message* a_pMessage) { m_pMessage = a_pMessage; }

    DataTreeViewItem* getItem(void* a_pContent) const;
    DataTreeViewItem* getItem(void* a_pContent, DataTreeViewItem* a_pParentItem) const;

	void displayData(const phantom::data& d) { emit dataDisplayed(d); }
	void hideData(const phantom::data& d) { emit dataHidden(d); }

    void select(const phantom::vector<phantom::data>& a_Datas, const phantom::vector<phantom::serialization::Node*>& a_Nodes);

    void setAddDataActionDelegate(new_data_action_delegate d) { m_AddDataActionDelegate = d; }
    void setAddNodeActionDelegate(node_action_delegate d) { m_AddNodeActionDelegate = d; }
    void setRemoveDataActionDelegate(remove_data_action_delegate d) { m_RemoveDataActionDelegate = d; }
    void setLoadNodeActionDelegate(node_action_delegate d) { m_LoadNodeActionDelegate = d; }
    void setUnloadNodeActionDelegate(node_action_delegate d) { m_UnloadNodeActionDelegate = d; }
    void setRecursiveLoadNodeActionDelegate(node_action_delegate d) { m_RecursiveLoadNodeActionDelegate = d; }
    void setDataAttributeChangeDelegate(data_attribute_change_delegate d) { m_DataAttributeChangeDelegate = d; }
    void setNodeAttributeChangeDelegate(node_attribute_change_delegate d) { m_NodeAttributeChangeDelegate = d; }

protected:
    void addDataItem(const phantom::data& a_Data);
    void addNodeItem(phantom::serialization::Node* a_pNode);
    void removeDataItem(const phantom::data& a_Data);
    void removeNodeItem(phantom::serialization::Node* a_pNode);
    void dataBaseLoaded(phantom::serialization::DataBase* a_pDB) ;
    void dataBaseUnloaded(phantom::serialization::DataBase* a_pDB) ;

	void keyPressEvent(QKeyEvent* a_pEvent);

    void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
    virtual bool edit ( const QModelIndex & index, EditTrigger trigger, QEvent * event );
    
protected slots:
    void slotItemClicked(QTreeWidgetItem* item, int col);
    void slotItemDoubleClicked(QTreeWidgetItem* item, int col);
    void slotItemChanged(QTreeWidgetItem* item, int col);
    void slotCurrentChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
	void slotSelectionChanged();

    void showPopup(const QPoint & pos);
    
    void dataAdded(const phantom::data&,phantom::serialization::Node*);
    void dataReplaced(const phantom::data&,const phantom::data&);
    void dataAboutToBeRemoved(const phantom::data&,phantom::serialization::Node*);
    void nodeAdded(phantom::serialization::Node* a_pNode,phantom::serialization::Node*);
    void nodeAboutToBeRemoved(phantom::serialization::Node* a_pNode,phantom::serialization::Node*);
    void nodeLoaded();
    void nodeAboutToBeUnloaded();
    void dataAttributeValueChanged( const phantom::data& a_Data, size_t a_uiAttributeIndex, const string& a_strValue);
    void dataModifiersChanged( const phantom::data& a_Data, bitfield a_Modifiers);
    void nodeAttributeValueChanged( phantom::serialization::Node* a_pNode, size_t a_uiAttributeIndex, const string& a_strValue);
	void addClassComponentDataActionCascade( QMenu* a_pMenu, const phantom::data& a_Data, phantom::reflection::Collection* a_pCollection, phantom::reflection::Class* a_pComponentDataClass );

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent* event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void dataClicked(const phantom::data& d);
    void nodeClicked(phantom::serialization::Node* a_pNode);

    void selectionChanged(const phantom::vector<phantom::data>& a_Datas, const phantom::vector<phantom::serialization::Node*>& a_Nodes);
    void selectionChanged(const phantom::vector<phantom::data>& a_Datas);

    void dataDoubleClicked(const phantom::data& d);

	void dataHidden(const phantom::data& d);
	void dataDisplayed(const phantom::data& d);


protected: // TODO : put this in Class
    phantom::reflection::Class* commonSuperClass(phantom::reflection::Class* a_pFirst, phantom::reflection::Class* a_pSecond) const;

protected:
    void undoableSetNodeAttribute(phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode, size_t a_uiAttributeIndex, const phantom::string& a_Value);
    void undoableSetDataAttribute(phantom::qt::DataTreeView* a_pDataTreeView, const phantom::data& a_Data, size_t a_uiAttributeIndex, const phantom::string& a_Value);
    void undoableAddData( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pOwnerNode, phantom::reflection::Type* a_pType );
    void undoableAddNode( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pParentNode );
    bool undoableLoadNode( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode, phantom::qt::UndoCommand* a_pParent );
    void undoableLoadNode( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode );
    bool undoableUnloadNode( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode, phantom::qt::UndoCommand* a_pParent );
    void undoableUnloadNode( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode );
    void undoableLoadNodeRecursive( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode );
    void undoableMoveToTrashbin(phantom::qt::DataTreeView* a_pDataTreeView, const phantom::vector<unsigned int>& a_Guids);
    
private:
    virtual QMimeData* mimeData(const QList<QTreeWidgetItem*> list) const;

protected:
    phantom::serialization::DataBase*									m_pDataBase;
    UndoStack*                                                          m_pUndoStack;
    Message*                                                            m_pMessage;
    size_t                                                              m_uiNameAttributeIndex;
    size_t                                                              m_uiCategoryAttributeIndex;
	phantom::vector<phantom::serialization::Node*>						m_NodeLoaded;
	phantom::vector<std::pair<DataTreeViewItem*, DataTreeViewItem*>>	m_DataItemToRemove;
    QList<QTreeWidgetItem*> m_SelectedItems; // TODO : remove and use SelectionManager ?
    new_data_action_delegate                                                m_AddDataActionDelegate;
    node_action_delegate                                                m_AddNodeActionDelegate;
    remove_data_action_delegate                                         m_RemoveDataActionDelegate;
    node_action_delegate                                                m_LoadNodeActionDelegate;
    node_action_delegate                                                m_UnloadNodeActionDelegate;
    node_action_delegate                                                m_RecursiveLoadNodeActionDelegate;
    data_attribute_change_delegate                                      m_DataAttributeChangeDelegate;
    node_attribute_change_delegate                                      m_NodeAttributeChangeDelegate;
    QIcon                                                               m_NodeLoadedIcon;
    QIcon                                                               m_NodeUnloadedIcon;
    QIcon                                                               m_NodeRootIcon;
    bool														        m_bHidePrivate;
    bool														        m_bHideComponentData;
    bool														        m_bIsChangingSelection;
    bool                                                                m_bEditorOpened;
};

class AddDataAction : public Action
{
    Q_OBJECT

public:
    AddDataAction(DataTreeView* a_pDataTreeView, serialization::Node* a_pNode, phantom::reflection::Type* a_pDataType, DataTreeView::new_data_action_delegate a_Delegate, QObject* a_pParent);
    ~AddDataAction(void) {}

    void doAction()
    {
        m_Delegate(m_pDataTreeView, m_pTargetNode, m_pDataType);
    }

protected:
    DataTreeView*                           m_pDataTreeView;
    phantom::serialization::Node*           m_pTargetNode;
    phantom::reflection::Type*              m_pDataType;
    DataTreeView::new_data_action_delegate      m_Delegate;
};

class RemoveDataAction : public Action
{
    Q_OBJECT

public:
    RemoveDataAction(DataTreeView* a_pDataTreeView, const vector<uint>& a_Guids, DataTreeView::remove_data_action_delegate a_Delegate, QObject* a_pParent);
    ~RemoveDataAction(void) {}

    void doAction();

protected:
    DataTreeView*                               m_pDataTreeView;
    vector<uint>                                m_Guids;
    DataTreeView::remove_data_action_delegate   m_Delegate;
};

class AddNodeAction : public Action
{
public:
    AddNodeAction(DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode, DataTreeView::node_action_delegate a_Delegate, QObject* a_pParent);
    ~AddNodeAction(void) {}

    void doAction()
    {
        m_Delegate(m_pDataTreeView, m_pTargetNode);
    }

protected:
    DataTreeView*                       m_pDataTreeView;
    phantom::serialization::Node*       m_pTargetNode;
    DataTreeView::node_action_delegate  m_Delegate;
};

class LoadNodeAction : public Action
{
public:
    LoadNodeAction(DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode, DataTreeView::node_action_delegate a_Delegate, QObject* a_pParent);
    ~LoadNodeAction(void) {}

    void doAction()
    {
        m_Delegate(m_pDataTreeView, m_pTargetNode);
    }

protected:
    DataTreeView*                       m_pDataTreeView;
    phantom::serialization::Node*       m_pTargetNode;
    DataTreeView::node_action_delegate  m_Delegate;
};

class UnloadNodeAction : public Action
{
    Q_OBJECT

public:
    UnloadNodeAction(DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode, DataTreeView::node_action_delegate a_Delegate, QObject* a_pParent);
    ~UnloadNodeAction(void) {}

    void doAction()
    {
        m_Delegate(m_pDataTreeView, m_pTargetNode);
    }

protected:
    DataTreeView*                       m_pDataTreeView;
    phantom::serialization::Node*       m_pTargetNode;
    DataTreeView::node_action_delegate  m_Delegate;
};

} // qt 
} // phantom

#endif // phantom_qt_DataTreeView_h__
