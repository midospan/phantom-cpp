#ifndef phantom_qt_StateMachineInspector_h__
#define phantom_qt_StateMachineInspector_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
#include <QAction>
#include <QTreeWidget>
#include <QToolButton>
#include <QVBoxLayout>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), StateMachineInspector);
/* *********************************************** */

namespace phantom { namespace qt {

class StateMachineInspector;

class StateMachineTreeWidgetItem : public QTreeWidgetItem
{
public:
    enum EType
    {
        e_Type_Track,
        e_Type_Event,
    };

    EType getType() const { return m_eType; }
    void* getContent() const { return m_pContent; }

    virtual void start(const vector<void*>& a_Addresses) {}
    virtual void update(const vector<void*>& a_Addresses) {}
    virtual void stop(const vector<void*>& a_Addresses) {}

protected:
    StateMachineTreeWidgetItem(EType a_eType, void* a_pContent) : m_eType(a_eType), m_pContent(a_pContent) {}
    EType m_eType;
    void* m_pContent;
};

class StateTrackItem : public StateMachineTreeWidgetItem
{
public:
    StateTrackItem(phantom::state::Track* a_pTrack) 
        : StateMachineTreeWidgetItem(e_Type_Track, a_pTrack)
        , m_pTrack(a_pTrack) 
    {
        setText(0, a_pTrack->getName().c_str());
    }

    phantom::state::Track*  getTrack() const { return m_pTrack; }
    virtual void start(const vector<void*>& a_Addresses) 
    {

    }
    virtual void update(const vector<void*>& a_Addresses) 
    {
        phantom::state::State* pState = m_pTrack->getCurrentState(a_Addresses.front());
        bool multipleValues = false;
        for(auto it = a_Addresses.begin()+1; it != a_Addresses.end(); ++it)
        {
            if(pState != m_pTrack->getCurrentState(*it))
            {
                pState = nullptr;
                multipleValues = true;
                break;
            }
        }
        QString text = "";
        if(pState)
        {
            text = pState->getName().c_str();
        }
        else if(multipleValues)
        {
            text = "<multiple values>";
        }
        this->setText(1, text);
    }
    virtual void stop(const vector<void*>& a_Addresses) 
    {
        this->setText(1, "");
    }

protected:
    phantom::state::Track* m_pTrack;
};

class StateEventPostAction : public QAction
{
    Q_OBJECT
public:
    StateEventPostAction(StateMachineInspector* a_pInspector, phantom::state::StateMachine* a_pStateMachine, uint a_uiEventId, const vector<void*>& a_Addresses)
        : QAction(QIcon("resources/icons/famfamfam/time_go.png"), "post", nullptr)
        , m_pInspector(a_pInspector)
        , m_pStateMachine(a_pStateMachine)
        , m_uiEventId(a_uiEventId)
        , m_Addresses(a_Addresses) 
    {
        connect(this, SIGNAL(triggered()), this, SLOT(post()));
    }

protected slots:
    void post();

protected:
    StateMachineInspector* m_pInspector;
    phantom::state::StateMachine* m_pStateMachine;
    uint            m_uiEventId;
    vector<void*>   m_Addresses;
};

class StateEventItem : public StateMachineTreeWidgetItem
{
public:
    StateEventItem(StateMachineInspector* a_pInspector, phantom::state::StateMachine* a_pStateMachine, uint a_uiEvent) 
        : StateMachineTreeWidgetItem(e_Type_Event, nullptr)
        , m_pStateMachine(a_pStateMachine)
        , m_uiEventId(a_uiEvent) 
        , m_pInspector(a_pInspector)
    {
        setText(0, a_pStateMachine->getEventName(m_uiEventId).c_str());
    }

    uint  getEventId() const { return m_uiEventId; }

    virtual void start(const vector<void*>& a_Addresses) 
    {
        QToolButton* pButton = new QToolButton;
        pButton->setDefaultAction(new StateEventPostAction(m_pInspector, m_pStateMachine, m_uiEventId, a_Addresses));
        treeWidget()->setItemWidget(this, 1, pButton);
    }
    virtual void update(const vector<void*>& a_Addresses) {}
    virtual void stop(const vector<void*>& a_Addresses) 
    {
        treeWidget()->setItemWidget(this, 1, NULL);
    }

protected:
    phantom::state::StateMachine*    m_pStateMachine;
    StateMachineInspector*  m_pInspector;
    StateEventPostAction*   m_pPostAction;        
    uint                    m_uiEventId;
};

class o_qt_export StateMachineInspector : public QWidget
{
    Q_OBJECT

    friend class StateEventPostAction;

public:
	StateMachineInspector(void);
	~StateMachineInspector(void) 
    {

    }

	o_initialize() {}

    void editData(const vector<phantom::data>& a_data);

    void setDataBase(serialization::DataBase* a_pDataBase);

    StateMachineTreeWidgetItem* getItem(void* a_pContent) const;

    StateMachineTreeWidgetItem* getItem(void* a_pContent, StateMachineTreeWidgetItem* a_pParentItem) const;

public slots:
    void start();
    void update();
    void stop();

signals:
    void eventPosted(phantom::state::StateMachine* a_pStateMachine, void* a_pInstance, uint a_uiEventId);

protected:
    void dataReplaced(const phantom::data& a_Old, const phantom::data& a_New);
    void dataAboutToBeRemoved(const phantom::data& a_Old, phantom::serialization::Node*);

protected:

    vector<phantom::data>           m_EditedData;
    phantom::state::StateMachine*    m_pStateMachine;
    QTreeWidget*            m_pStateMachineTreeWidget;
    serialization::DataBase*m_pDataBase;
};


} // qt 
} // phantom 


#endif // phantom_qt_StateMachineInspector_h__
