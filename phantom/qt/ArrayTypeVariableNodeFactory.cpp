/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ArrayTypeVariableNodeFactory.h"
#include "ArrayTypeVariableNodeFactory.hxx"
#include "ArrayElementVariable.h"
#include "VariableNode.h"
/* *********************************************** */
o_registerN((phantom, qt), ArrayTypeVariableNodeFactory);
 
namespace phantom { 
namespace qt {

void ArrayTypeVariableNodeFactory::addChildNodes(VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Type* a_pType) const 
{
    reflection::ArrayType* pArrayType = as<reflection::ArrayType*>(a_pType);
    o_assert(pArrayType);
    vector<vector<reflection::Variable*>> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        size_t i = 0;
        size_t count = pArrayType->getCount();
        groupedVariables.resize(std::max(groupedVariables.size(), count));
        for(;i<count;++i)
        {
            groupedVariables[i].push_back(o_new(ArrayElementVariable)(*it, pArrayType, i));
        }
    }
    size_t i = 0;
    for(auto it = groupedVariables.begin(); it != groupedVariables.end(); ++it)
    {
        a_pVariableNode->addChildNode(o_new(VariableNode)(*it));
    }
}
}}
