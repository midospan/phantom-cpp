/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "CompositionVisualizerNode.h"
#include "CompositionVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/CompositionClass.h"
#include "phantom/reflection/CompositionClass.hxx"
#include "UndoCommandAction.h"
#include "UndoCommand.h"
#include "VariableModel.h"
#include "CompositionVariableNodeDelegate.h"
#include "CompositionComponentVariableNodeDelegate.h"
#include "Menu.h"
/* *********************************************** */
o_registerN((phantom, qt), CompositionVisualizerNode);
 
namespace phantom { 
namespace qt {

void CompositionVisualizerNode::expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const 
{
    a_pVariableNode->setDelegate(o_new(CompositionVariableNodeDelegate));
    vector<vector<reflection::Expression*>> groupedVariables;
    for(size_t i = 0; i<a_LeftExpressions.size(); ++i)
    {
        reflection::Expression* pLeftExpression = a_LeftExpressions[i];
        reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pLeftExpression->getValueType()->removeReference());
        o_assert(pCompositionClass);
        vector<reflection::Expression*> signature;
        reflection::Expression* pSizeExpression = cplusplus()->qualifiedLookup(pLeftExpression->clone(), "count", nullptr, &signature)->asExpression();
        bool ok;
        size_t count = pSizeExpression->get().as<size_t>(&ok);
        o_assert(ok);

        groupedVariables.resize(std::max(groupedVariables.size(), count));
        for(size_t i = 0; i<count; ++i)
        {
            reflection::Expression* pIndexExpression = phantom::expressionByName(lexical_cast<string>(i));
            reflection::Expression* pExpression = cplusplus()->solveBinaryOperator("[]", pLeftExpression->clone(), pIndexExpression);
            pExpression = pExpression->getValueType()->removeReference()->asClass()->getProperty("value")->toExpression(pExpression);
            o_assert(pExpression);
            groupedVariables[i].push_back(pExpression);
        }
        o_dynamic_delete pSizeExpression;
    }
    size_t i = 0;
    for(;i<groupedVariables.size(); ++i)
    {
        VariableNode* pChild = o_new(VariableNode)(lexical_cast<string>(i), groupedVariables[i]);
        pChild->setDelegate(o_new(CompositionComponentVariableNodeDelegate)(i, groupedVariables.size()));
        a_pVariableNode->addChildNode(pChild);
    }
}

}}
