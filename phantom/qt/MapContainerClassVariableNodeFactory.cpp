/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "MapContainerClassVariableNodeFactory.h"
#include "MapContainerClassVariableNodeFactory.hxx"
#include "MapInsertPairVariable.h"
#include "VariableNode.h"
/* *********************************************** */
o_registerN((phantom, qt), MapContainerClassVariableNodeFactory);
 
namespace phantom { 
namespace qt {

void MapContainerClassVariableNodeFactory::addChildNodes(VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Type* a_pType) const 
{
    reflection::MapContainerClass* pMapContainerClass = as<reflection::MapContainerClass*>(a_pVariableNode->getValueType());
    o_assert(pMapContainerClass);
    if(!a_pVariableNode->hasModifier(o_readonly))
    {
        vector<reflection::Variable*> groupedVariables;
        for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
        {
            groupedVariables.push_back(o_new(MapInsertPairVariable)(*it, pMapContainerClass));
        }
        a_pVariableNode->addChildNode(o_new(VariableNode)(groupedVariables));
    }
    vector<vector<reflection::Variable*>> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        vector<reflection::IteratorVariable*>   vars;
        pMapContainerClass->createIteratorVariables(*it, vars);
        size_t count = vars.size();
        groupedVariables.resize(std::max(groupedVariables.size(), count));
        for(size_t i = 0; i<count; ++i)
        {
            groupedVariables[i].push_back(vars[i]);
        }
    }
    size_t i = 0;
    for(auto it = groupedVariables.begin(); it != groupedVariables.end(); ++it)
    {
        VariableNode* pChildVariable = o_new(VariableNode)(*it);
        a_pVariableNode->addChildNode(pChildVariable);
    }
}

void MapContainerClassVariableNodeFactory::addChildNodes(VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Type* a_pType) const 
{
    reflection::MapContainerClass* pMapContainerClass = as<reflection::MapContainerClass*>(a_pVariableNode->getValueType());
    o_assert(pMapContainerClass);
    if(!a_pVariableNode->hasModifier(o_readonly))
    {
        vector<reflection::Variable*> groupedVariables;
        for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
        {
            groupedVariables.push_back(o_new(MapInsertPairVariable)(*it, pMapContainerClass));
        }
        a_pVariableNode->addChildNode(o_new(VariableNode)(groupedVariables));
    }

    struct map_key 
    {
        map_key() : m_pBuffer(0), m_pMapKeyType(0) {}
        map_key(reflection::Type* a_pMapKeyType)
            : m_pMapKeyType(a_pMapKeyType)
        {
            m_pBuffer = m_pMapKeyType->removeReference()->removeConst()->newInstance();
        }
        ~map_key()
        {
            if(m_pBuffer)
                m_pMapKeyType->removeReference()->removeConst()->deleteInstance(m_pBuffer);
        }
        map_key(const map_key& other)
            : m_pMapKeyType(other.m_pMapKeyType)
            , m_pBuffer(other.m_pMapKeyType->removeReference()->removeConst()->newInstance())
        {
            m_pMapKeyType->copy(m_pBuffer, other.m_pBuffer);
        }

        map_key& operator=(const map_key& other)
        {
            if(m_pBuffer == 0)
            {
                m_pMapKeyType = other.m_pMapKeyType;
                m_pBuffer = m_pMapKeyType->removeReference()->removeConst()->newInstance();
            }
            m_pMapKeyType->copy(m_pBuffer, other.m_pBuffer);
            return *this;
        }

        bool operator<(const map_key& other) const 
        {
            return m_pMapKeyType->less(m_pBuffer, other.m_pBuffer);
        }

        reflection::Type* m_pMapKeyType;
        void* m_pBuffer;
    };

    map<map_key, vector<reflection::Variable*>> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        vector<reflection::IteratorVariable*>   vars;
        pMapContainerClass->createIteratorVariables(*it, vars);
        size_t count = vars.size();
        for(size_t i = 0; i<count; ++i)
        {
            map_key key(pMapContainerClass->getKeyType());
            static_cast<reflection::MapValueIteratorVariable*>(vars[i])->getKeyValue(key.m_pBuffer);
            groupedVariables[key].push_back(vars[i]);
        }
    }
    size_t i = 0;
    for(auto it = groupedVariables.begin(); it != groupedVariables.end(); ++it)
    {
        VariableNode* pChildVariable = o_new(VariableNode)(it->second) ;
        a_pVariableNode->addChildNode(pChildVariable);
    }

}
}}
