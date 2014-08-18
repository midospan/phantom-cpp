/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "SetContainerVisualizerNode.h"
#include "SetContainerVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/Expression.h"
/* *********************************************** */
o_registerN((phantom, qt), SetContainerVisualizerNode);
 
namespace phantom { 
namespace qt {

    void SetContainerVisualizerNode::expand( VariableNode* a_pParent, const vector<reflection::Expression*>& a_LeftExpressions ) const
    {
        map<string, vector<reflection::Expression*>> setExpressions;
        for(auto it = a_LeftExpressions.begin(); it != a_LeftExpressions.end(); ++it)
        {
            reflection::Expression* pLeftExpression = *it;
            if(NOT(pLeftExpression->hasEffectiveAddress())) continue;
            void* pMapAddress = pLeftExpression->loadEffectiveAddress();
            reflection::SetContainerClass* pSetContainerClass = pLeftExpression->getValueType()->removeReference()->asSetContainerClass();
            o_assert(pSetContainerClass);
            reflection::Iterator* pIterator = pSetContainerClass->begin(pMapAddress);
            void* pKeyBuffer = pSetContainerClass->getKeyType()->newInstance();
            while(pIterator->hasNext())
            {
                pIterator->getValue(pKeyBuffer);
                string lit;
                pSetContainerClass->getKeyType()->valueToLiteral(lit, pKeyBuffer);
                reflection::Expression* pLiteralExpression = phantom::expressionByName(lit);
                vector<reflection::LanguageElement*> operatorSignature;
                operatorSignature.push_back(pLiteralExpression);
                reflection::Expression* pFindExpression = pLeftExpression->clone()->solveElement("find", nullptr, &operatorSignature, o_const)->asExpression();
                o_assert(pFindExpression);
                operatorSignature.clear();
                reflection::Expression* pDereferenceExpression = pFindExpression->solveElement("operator*", nullptr, &operatorSignature, o_const)->asExpression();
                o_assert(pDereferenceExpression);
                setExpressions[lit].push_back(pDereferenceExpression);
                pIterator->advance();
            }
            pSetContainerClass->getKeyType()->deleteInstance(pKeyBuffer);
        }
        for(auto it = setExpressions.begin(); it != setExpressions.end(); ++it)
        {
            a_pParent->addChildNode(o_new(VariableNode)(it->first, it->second));
        }
    }

}}
