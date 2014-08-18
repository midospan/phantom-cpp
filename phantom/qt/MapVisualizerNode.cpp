/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "MapVisualizerNode.h"
#include "MapVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/Expression.h"
/* *********************************************** */
o_registerN((phantom, qt), MapVisualizerNode);
 
namespace phantom { 
namespace qt {


    void MapVisualizerNode::expand( VariableNode* a_pParent, const vector<reflection::Expression*>& a_LeftExpressions ) const
    {
        map<string, vector<reflection::Expression*>> mapExpressions;
        for(auto it = a_LeftExpressions.begin(); it != a_LeftExpressions.end(); ++it)
        {
            reflection::Expression* pLeftExpression = *it;
            if(NOT(pLeftExpression->hasEffectiveAddress())) continue;
            void* pMapAddress = pLeftExpression->loadEffectiveAddress();
            reflection::MapContainerClass* pMapContainerClass = as<reflection::MapContainerClass*>(pLeftExpression->getValueType()->removeReference());
            o_assert(pMapContainerClass);
            reflection::MapIterator* pIterator = pMapContainerClass->begin(pMapAddress);
            o_assert(pMapContainerClass->getKeyType()->isCopyable());
            void* pKeyBuffer = pMapContainerClass->getKeyType()->newInstance();
            while(pIterator->hasNext())
            {
                pIterator->getKeyValue(pKeyBuffer);
                string lit;
                pMapContainerClass->getKeyType()->valueToLiteral(lit, pKeyBuffer);
                reflection::Expression* pLiteralExpression = phantom::expressionByName(lit);
                vector<reflection::Expression*> operatorSignature;
                operatorSignature.push_back(pLiteralExpression);
                reflection::Expression* pMapAccessExpression = pLeftExpression->clone()->solveOperator("[]", operatorSignature);
                o_assert(pMapAccessExpression);
                mapExpressions[lit].push_back(pMapAccessExpression);
                pIterator->advance();
            }
            pMapContainerClass->getKeyType()->deleteInstance(pKeyBuffer);
            pMapContainerClass->release(pIterator);
        }
        for(auto it = mapExpressions.begin(); it != mapExpressions.end(); ++it)
        {
            a_pParent->addChildNode(o_new(VariableNode)(it->first, it->second));
        }
    }

}}
