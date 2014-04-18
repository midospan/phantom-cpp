#ifndef phantom_qt_VariableModel_h__
#define phantom_qt_VariableModel_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), VariableModel);
o_declareN(class, (phantom, qt), VariableNode);
/* *********************************************** */

namespace phantom { namespace qt {

class VariableEditor;
class VariableAction;
class VariableDecorator;
class VariableNode;
class VariableNodeFactory;

class DataVariable : public reflection::Variable
{
public:
    DataVariable(const phantom::data& a_Data, uint a_Guid)
        : m_Data(a_Data)
        , m_Guid(a_Guid)
    {

    }
    virtual void*             getAddress() const { return m_Data.address(); }

    virtual reflection::Type* getValueType() const { return m_Data.type(); }

    virtual void setValue(const void* a_pSrc) const 
    {
        m_pType->copy(m_pAddress, a_pSrc);
    }
    virtual void getValue(void* a_pDest) const 
    {
        m_pType->copy(a_pDest, m_pAddress);
    }

protected:
    phantom::data m_Data;
    uint m_Guid;
};

class o_qt_export VariableModel 
{
    friend class VariableAction;
    friend class VariableEditor;

public:
    VariableModel();
	~VariableModel(void);

    o_initialize();

    o_terminate();
    
    VariableNode* getRootNode() const { return m_pRootNode; }

    void setRootNode(VariableNode* a_pVariableNode);

    void registerTypeClassVariableNodeFactory(reflection::Class* a_pClass, VariableNodeFactory* a_pFactory)
    {
        m_VariableNodeFactories[a_pClass] = a_pFactory;
    }
    void unregisterTypeClassVariableNodeFactory(reflection::Class* a_pClass, VariableNodeFactory* a_pFactory)
    {
        m_VariableNodeFactories.erase(a_pClass);
    }

    void findTypeClassVariableNodeFactories(reflection::Class* a_pClass, vector<VariableNodeFactory*>& out) const;

protected:
    void registerVariableNode(VariableNode* a_pVariableNode);
    void unregisterVariableNode(VariableNode* a_pVariableNode);

protected:
    o_signal_data(rootNodeChanged, VariableNode*);

protected:
    VariableNode* m_pRootNode;
    serialization::DataBase* m_pDataBase;
    map<reflection::Class*, VariableNodeFactory*> m_VariableNodeFactories;
};

} // qt 
} // phantom 





#endif // phantom_qt_VariableModel_h__
