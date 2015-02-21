/* TODO LICENCE HERE */

#ifndef serialization_DataStateBase_h__
#define serialization_DataStateBase_h__

/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* *********************************************** */
o_declareN(class, (phantom, serialization), DataStateBase)
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export DataStateBase 
{
    friend class Node;
    friend class DataBase;

protected:
    DataStateBase(DataBase* a_pDataBase, const string& a_Url, uint a_uiSerializationFlag = o_save_state)
        : m_pDataBase(a_pDataBase)
        , m_strUrl(a_Url)
        , m_uiSerializationFlag(a_uiSerializationFlag)
        , m_uiCurrentStateId(0)
    {
    }

public:
    const string& getUrl() const { return m_strUrl; }

    virtual bool hasStateSaved(Node* a_pNode, uint a_uiStateId) const = 0;

    void setCurrentStateId(uint a_uiStateId) 
    { 
        m_uiCurrentStateId = a_uiStateId; 
    }

    uint getCurrentStateId() const 
    { 
        return m_uiCurrentStateId; 
    }

protected:
    virtual void loadState(Node* a_pNode, const vector<data>& a_Data, uint a_uiStateId) = 0;
    virtual void saveState(Node* a_pNode, const vector<data>& a_Data, uint a_uiStateId) = 0;
    virtual void loadDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId) = 0;
    virtual void saveDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId) = 0;

protected:
    DataBase* m_pDataBase;
    string  m_strUrl;
    uint    m_uiSerializationFlag;
    uint    m_uiCurrentStateId;
};

o_namespace_end(phantom, serialization)

#endif // serialization_TDataStateBase_h__
