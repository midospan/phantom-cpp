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
                reflection::Expression* pMapAccessExpression = cplusplus()->solveBinaryOperator("[]", pLeftExpression->clone(), pLiteralExpression);
                o_assert(pMapAccessExpression);
                mapExpressions[lit].push_back(pMapAccessExpression);
                pIterator->advance();
            }
            pMapContainerClass->getKeyType()->deleteInstance(pKeyBuffer);
            pMapContainerClass->release(pIterator);
        }
        for(auto it = mapExpressions.begin(); it != mapExpressions.end(); ++it)
        {
            reflection::Expression* pLiteralExpression = phantom::expressionByName(it->first);
            reflection::LanguageElement* pElement = pLiteralExpression->hatch();
            VariableNode* pNode = o_new(VariableNode)(nameOf(pElement->asNamedElement()), it->second);
            pNode->setIcon(QIcon(iconOf(pElement->asNamedElement()).c_str()));
            a_pParent->addChildNode(pNode);
            if(pElement == pLiteralExpression)
                o_dynamic_delete pElement;
        }
    }

}}
