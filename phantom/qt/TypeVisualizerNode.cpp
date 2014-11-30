/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "TypeVisualizerNode.h"
#include "TypeVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/Expression.h"
/* *********************************************** */
o_registerN((phantom, qt), TypeVisualizerNode);
 
namespace phantom { 
namespace qt {

    void TypeVisualizerNode::expand( VariableNode* a_pParent ) const
    {
        vector<reflection::Expression*> validExpressions;
        for(auto it = a_pParent->beginExpressions(); it != a_pParent->endExpressions(); ++it)
        {
            reflection::Expression* pLeftExpression = *it;
            reflection::Expression* pCondition = m_Condition.empty() ? nullptr : phantom::expressionByName(m_Condition, pLeftExpression);
            bool bValue = true;
            if(pCondition != nullptr) 
            {
                reflection::Expression* pBoolCondition = pCondition->implicitCast(typeOf<bool>());
                if(pBoolCondition != nullptr)
                {
                    pBoolCondition->getValue(&bValue);
                    phantom::deleteElement(pBoolCondition);
                }
                else 
                {
                    phantom::deleteElement(pCondition);
                }
            }
            if(bValue)
            {
                validExpressions.push_back(pLeftExpression);
            }
        }
        expand(a_pParent, validExpressions);
    }

}}
