#ifndef phantom_qt_VariableNode_h__
#define phantom_qt_VariableNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), VariableNode);
/* *********************************************** */

namespace phantom { namespace qt {

enum EVariableNodeProperty
{
    e_VariableNodeProperty_ReloadOnChildChange = 0x1,
};

o_declare_flags(VariableNodeProperties, EVariableNodeProperty);

class o_qt_export VariableNode 
{
public:

    enum EClassDisplayPolicy
    {
        e_ClassDisplayPolicy_Tree,
        e_ClassDisplayPolicy_List,
    };

    VariableNode(const string& a_strName, const vector<reflection::Variable*>& a_Variables);
    VariableNode(const vector<reflection::Variable*>& a_Variables);
    VariableNode(const string& a_strName);
    ~VariableNode();

    o_initialize();
    o_terminate();

    const vector<void*>& getAddresses() const { return m_Addresses;}

    bool hasModifier(bitfield a_Modifier) const { return m_Modifiers.matchesMask(a_Modifier); }

    bool hasMultipleValues() const;

    bool hasVariables() const { return !m_Variables.empty(); }

    reflection::Class* getVariableClass() const;

    reflection::Type*  getValueType() const;

    void flush() const;

    void update() const;

    void  getValue(void* a_pDest) const;

    void  setValue(void const* a_pSrc) const;

    void getValues(void** a_pMultipleDest) const;

    void setValues(void const ** a_pMultipleSrc) const;

    VariableNode* getParentNode() const { return m_pParentNode; }

    VariableNode* getPrev() const { return m_pParentNode ? m_pParentNode->getPrevChild((VariableNode*)this) : nullptr; }

    VariableNode* getNext() const { return m_pParentNode ? m_pParentNode->getNextChild((VariableNode*)this) : nullptr; }

    VariableNode* getNextChild(VariableNode* a_pCurrent) const;

    VariableNode* getPrevChild(VariableNode* a_pCurrent) const;

    void* getAddress() const { return nullptr; }

    const vector<reflection::Variable*>& getVariables() const { return m_Variables; }

    reflection::Variable* getVariable(size_t i) const { return m_Variables[i]; }

    size_t getVariableCount() const { return m_Variables.size(); }

    reflection::Range* getRange() const { return m_Variables.size() ? m_Variables[0]->getRange() : nullptr; } 

    void setName(const string& a_strName)
    {
        if(m_strName == a_strName) return;
        m_strName = a_strName;
        o_emit nameChanged(a_strName);
    }

    const string& getName() const { return m_strName; }

    vector<VariableNode*>::const_iterator beginChildNodes() const { return m_ChildNodes.begin(); }

    vector<VariableNode*>::const_iterator endChildNodes() const { return m_ChildNodes.end(); }

    void addChildNode(VariableNode* a_pVariableNode);
    void removeChildNode(VariableNode* a_pVariableNode);

protected:
    o_signal_data(nameChanged, const string&);
    o_signal_data(valueChanged);
    o_signal_data(childNodeAdded, VariableNode*);
    o_signal_data(childNodeAboutToBeRemoved, VariableNode*);

protected:
    void checkCommonAncestorType()
    {
        m_pVariableType = nullptr;
        o_assert(!m_Variables.empty());
        {
            m_pVariableType = m_Variables.front()->getValueType();
            for(auto it = m_Variables.begin()+1; it != m_Variables.end(); ++it)
            {
                o_assert(m_pVariableType == (*it)->getValueType());
            }
        }
    }

protected:
    string                  m_strName;
    vector<reflection::Variable*> m_Variables;
    vector<void*>           m_Addresses;
    vector<bool>            m_Buffered;
    reflection::Type*       m_pVariableType;
    VariableNode*           m_pParentNode;
    vector<VariableNode*>   m_ChildNodes;
    EClassDisplayPolicy     m_eClassDisplayPolicy;
    bitfield                m_Modifiers;
};

}}


#endif // phantom_qt_VariableNode_h__
