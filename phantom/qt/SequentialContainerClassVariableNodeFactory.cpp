/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "SequentialContainerClassVariableNodeFactory.h"
#include "SequentialContainerClassVariableNodeFactory.hxx"
#include "SequentialContainerPushBackVariable.h"
#include "VariableNode.h"
/* *********************************************** */
o_registerN((phantom, qt), SequentialContainerClassVariableNodeFactory);
 
namespace phantom { 
namespace qt {

void SequentialContainerClassVariableNodeFactory::addChildNodes(VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Type* a_pType) const 
{
    reflection::SequentialContainerClass* pSequentialContainerClass = as<reflection::SequentialContainerClass*>(a_pType);
    o_assert(pSequentialContainerClass);
    if(!a_pVariableNode->hasModifier(o_readonly))
    {
        vector<reflection::Variable*> groupedVariables;
        for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
        {
            groupedVariables.push_back(o_new(SequentialContainerPushBackVariable)(*it, pSequentialContainerClass));
        }
        a_pVariableNode->addChildNode(o_new(VariableNode)(groupedVariables));
    }
    vector<vector<reflection::Variable*>> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        vector<reflection::IteratorVariable*>   vars;
        pSequentialContainerClass->createIteratorVariables(*it, vars);
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
}}
