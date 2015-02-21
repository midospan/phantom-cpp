/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "SequentialContainerVisualizerNode.h"
#include "SequentialContainerVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/Expression.h"
#include "phantom/reflection/ConstantExpression.h"
/* *********************************************** */
o_registerN((phantom, qt), SequentialContainerVisualizerNode);
 
namespace phantom { 
namespace qt {

    void SequentialContainerVisualizerNode::expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const 
    {
        vector<vector<reflection::Expression*>> expressions;
        for(auto it = a_LeftExpressions.begin(); it != a_LeftExpressions.end(); ++it)
        {
            reflection::Expression* pLeftExpression = *it;
            vector<reflection::Expression*> emptySignature;
            reflection::Expression* pSizeExpression = cplusplus()->qualifiedLookup(pLeftExpression->clone(), "size", nullptr, &emptySignature, 0)->asExpression();
            o_assert(pSizeExpression);
            bool ok;
            size_t count = pSizeExpression->get().as<size_t>(&ok);
            if(ok)
            {
                expressions.resize(std::max(expressions.size(), count));
                for(size_t i = 0; i<count; ++i)
                {
                    reflection::Expression* pIndexExpression = o_new(reflection::ConstantExpression)(constant<size_t>(i));
                    reflection::Expression* pExpression = cplusplus()->solveBinaryOperator("[]", pLeftExpression->clone(), pIndexExpression);
                    o_assert(pExpression);
                    expressions[i].push_back(pExpression);
                }
            }
            o_dynamic_delete pSizeExpression;
        }
        size_t i = 0;
        for(;i<expressions.size(); ++i)
        {
            a_pVariableNode->addChildNode(o_new(VariableNode)(lexical_cast<string>(i), expressions[i]));
        }
    }

}}
