/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "FlagsVisualizerNode.h"
#include "FlagsVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/ConstantExpression.h"
/* *********************************************** */
o_registerN((phantom, qt), FlagsVisualizerNode);
 
namespace phantom { 
namespace qt {


    void FlagsVisualizerNode::expand( VariableNode* a_pParent, const vector<reflection::Expression*>& a_LeftExpressions ) const
    {
        map<reflection::Constant*, vector<reflection::Expression*>> flagsExpressions;
        for(auto it = a_LeftExpressions.begin(); it != a_LeftExpressions.end(); ++it)
        {
            reflection::Expression* pLeftExpression = *it;
            if(NOT(pLeftExpression->hasEffectiveAddress())) continue;
            reflection::Enum* pEnum = pLeftExpression->getValueType()->removeReference()->removeConst()->getTemplateSpecialization()->getArgumentElement("Enum")->asLanguageElement()->asEnum();
            for(size_t i = 0; i<pEnum->getConstantCount(); ++i)
            {
                flagsExpressions[pEnum->getConstant(i)].push_back(pLeftExpression->clone()->solveBinaryOperator("[]", o_new(reflection::ConstantExpression)(pEnum->getConstant(i)))->solveElement("value", nullptr, nullptr, 0)->asExpression());
            }
        }
        for(auto it = flagsExpressions.begin(); it != flagsExpressions.end(); ++it)
        {
            VariableNode* pNode = o_new(VariableNode)(nameOf(it->first), it->second);
            pNode->setIcon(QIcon(iconOf(it->first).c_str()));
            a_pParent->addChildNode(pNode);
        }
    }

}}
