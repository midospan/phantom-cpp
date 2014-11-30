/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "AggregationVisualizerNode.h"
#include "AggregationVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/AggregationClass.h"
#include "phantom/reflection/AggregationClass.hxx"
#include "phantom/reflection/ConstantExpression.h"
#include "UndoCommandAction.h"
#include "UndoCommand.h"
#include "VariableModel.h"
#include "AggregationVariableNodeDelegate.h"
#include "AggregationAggregateVariableNodeDelegate.h"
#include "Menu.h"
/* *********************************************** */
o_registerN((phantom, qt), AggregationVisualizerNode);
 
namespace phantom { 
namespace qt {

void AggregationVisualizerNode::expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const 
{
    a_pVariableNode->setDelegate(o_new(AggregationVariableNodeDelegate));
    vector<vector<reflection::Expression*>> groupedVariables;
    for(size_t i = 0; i<a_LeftExpressions.size(); ++i)
    {
        reflection::Expression* pLeftExpression = a_LeftExpressions[i];
        reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pLeftExpression->getValueType()->removeReference());
        o_assert(pAggregationClass);
        vector<reflection::LanguageElement*> signature;
        reflection::Expression* pSizeExpression = pLeftExpression->clone()->solveElement("count", nullptr, &signature)->asExpression();
        bool ok;
        size_t count = pSizeExpression->get().as<size_t>(&ok);
        o_assert(ok);

        groupedVariables.resize(std::max(groupedVariables.size(), count));
        for(size_t i = 0; i<count; ++i)
        {
            reflection::Expression* pIndexExpression = o_new(reflection::ConstantExpression)(constant<size_t>(i));
            reflection::Expression* pExpression = pLeftExpression->clone()->solveBinaryOperator("[]", pIndexExpression);
            o_assert(pExpression);
            groupedVariables[i].push_back(pExpression);
        }
        phantom::deleteElement(pSizeExpression);
    }
    size_t i = 0;
    for(;i<groupedVariables.size(); ++i)
    {
        VariableNode* pChild = o_new(VariableNode)(lexical_cast<string>(i), groupedVariables[i]);
        pChild->setDelegate(o_new(AggregationAggregateVariableNodeDelegate)(i, groupedVariables.size()));
        a_pVariableNode->addChildNode(pChild);
    }
}

}}
