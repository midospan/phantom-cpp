/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "SequentialContainerVisualizerNode.h"
#include "SequentialContainerVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/Expression.h"
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
            vector<reflection::LanguageElement*> emptySignature;
            reflection::Expression* pSizeExpression = pLeftExpression->clone()->solveElement("size", nullptr, &emptySignature, 0)->asExpression();
            o_assert(pSizeExpression);
            bool ok;
            size_t count = pSizeExpression->get().as<size_t>(&ok);
            if(ok)
            {
                expressions.resize(std::max(expressions.size(), count));
                for(size_t i = 0; i<count; ++i)
                {
                    reflection::Expression* pIndexExpression = phantom::expressionByName(lexical_cast<string>(i));
                    vector<reflection::Expression*> signature;
                    signature.push_back(pIndexExpression);
                    reflection::Expression* pExpression = pLeftExpression->clone()->solveOperator("[]", signature);
                    o_assert(pExpression);
                    expressions[i].push_back(pExpression);
                }
            }
            phantom::deleteElement(pSizeExpression);
        }
        size_t i = 0;
        for(;i<expressions.size(); ++i)
        {
            a_pVariableNode->addChildNode(o_new(VariableNode)(lexical_cast<string>(i), expressions[i]));
        }
    }

}}
