/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "CompositionVisualizerNode.h"
#include "CompositionVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/CompositionClass.h"
#include "phantom/reflection/CompositionClass.hxx"
/* *********************************************** */
o_registerN((phantom, qt), CompositionVisualizerNode);
 
namespace phantom { 
namespace qt {

void CompositionVisualizerNode::expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const 
{
    /*if(!a_pVariableNode->hasModifier(o_readonly))
    {
        vector<reflection::Expression*> groupedVariables;
        for(auto it = a_LeftExpressions.begin(); it != a_LeftExpressions.end(); ++it)
        {
            groupedVariables.push_back((*it)+".add");
        }
        a_pVariableNode->addChildNode(o_new(VariableNode)("<add>", groupedVariables));
    }*/
    vector<vector<reflection::Expression*>> groupedVariables;
    for(auto it = a_LeftExpressions.begin(); it != a_LeftExpressions.end(); ++it)
    {
        reflection::Expression* pLeftExpression = *it;
        reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pLeftExpression->getValueType()->removeReference());
        o_assert(pCompositionClass);
        vector<reflection::LanguageElement*> signature;
        reflection::Expression* pSizeExpression = pLeftExpression->clone()->solveElement("size", nullptr, &signature)->asExpression();
        bool ok;
        size_t count = pSizeExpression->get().as<size_t>(&ok);
        o_assert(ok);
        groupedVariables.resize(std::max(groupedVariables.size(), count));
        for(size_t i = 0; i<count; ++i)
        {
            reflection::Expression* pIndexExpression = phantom::expressionByName(lexical_cast<string>(i));
            reflection::Expression* pExpression = pLeftExpression->clone()->solveBinaryOperator("[]", pIndexExpression);
            o_assert(pExpression);
            groupedVariables[i].push_back(pExpression);
        }
        phantom::deleteElement(pSizeExpression);
    }
    size_t i = 0;
    for(;i<groupedVariables.size(); ++i)
    {
        a_pVariableNode->addChildNode(o_new(VariableNode)(lexical_cast<string>(i), groupedVariables[i]));
    }
}

}}
