/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "CompositionClassVariableNodeFactory.h"
#include "CompositionClassVariableNodeFactory.hxx"
#include "CompositionAddVariable.h"
#include "VariableNode.h"
#include "phantom/reflection/CompositionClass.h"
#include "phantom/reflection/CompositionClass.hxx"
/* *********************************************** */
o_registerN((phantom, qt), CompositionClassVariableNodeFactory);
 
namespace phantom { 
namespace qt {

void CompositionClassVariableNodeFactory::addChildNodes(VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Type* a_pType) const 
{
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(a_pVariableNode->getValueType());
    o_assert(pCompositionClass);
    if(!a_pVariableNode->hasModifier(o_readonly))
    {
        vector<reflection::Variable*> groupedVariables;
        for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
        {
            groupedVariables.push_back(o_new(CompositionAddVariable)(*it, pCompositionClass));
        }
        a_pVariableNode->addChildNode(o_new(VariableNode)(groupedVariables));
    }
    vector<vector<reflection::Variable*>> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        size_t count = pCompositionClass->count(*it);
        groupedVariables.resize(std::max(groupedVariables.size(), count));
        for(size_t i = 0; i<count; ++i)
        {
            groupedVariables[i].push_back(o_new(ComponentVariable)(*it, pCompositionClass, i));
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
