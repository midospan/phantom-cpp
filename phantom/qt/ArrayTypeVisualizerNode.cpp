/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ArrayTypeVisualizerNode.h"
#include "ArrayTypeVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/Expression.h"
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
        size_t count = pArrayType->getElementCount();
        groupedVariables.resize(std::max(groupedVariables.size(), count));
        reflection::Expression* pIndexExpression = phantom::expressionByName(lexical_cast<string>(i));
        for(;i<count;++i)
        {
            reflection::Expression* pExpression = pLeftExpression->solveBinaryOperator("[]", pIndexExpression);
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
