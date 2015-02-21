/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ArrayTypeVisualizerNode.h"
#include "ArrayTypeVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/ConstantExpression.h"
/* *********************************************** */
o_registerN((phantom, qt), ArrayTypeVisualizerNode);
 
namespace phantom { 
namespace qt {

void ArrayTypeVisualizerNode::expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const 
{
    vector<vector<reflection::Expression*>> groupedVariables;
    for(auto it = a_LeftExpressions.begin(); it != a_LeftExpressions.end(); ++it)
    {
        reflection::Expression* pLeftExpression = *it;
        reflection::ArrayType* pArrayType = pLeftExpression->getValueType()->removeReference()->asArrayType();
        o_assert(pArrayType);
        size_t i = 0;
        size_t count = pArrayType->getItemCount();
        groupedVariables.resize(std::max(groupedVariables.size(), count));
        for(;i<count;++i)
        {
            reflection::Expression* pIndexExpression = o_new(reflection::ConstantExpression)(constant<size_t>(i));
            reflection::Expression* pExpression = cplusplus()->solveBinaryOperator("[]", pLeftExpression->clone(), pIndexExpression);
            o_assert(pExpression);
            groupedVariables[i].push_back(pExpression);
        }
    }
    size_t i = 0;
    for(;i<groupedVariables.size(); ++i)
    {
        a_pVariableNode->addChildNode(o_new(VariableNode)(lexical_cast<string>(i), groupedVariables[i]));
    }
}

}}
