/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ClassTypeVisualizerNode.h"
#include "ClassTypeVisualizerNode.hxx"
#include "VariableNode.h"
#include "phantom/reflection/Expression.h"
/* *********************************************** */
o_registerN((phantom, qt), ClassTypeVisualizerNode);
 
namespace phantom { 
namespace qt {

void ClassTypeVisualizerNode::expand( VariableNode* a_pParentNode, const vector<reflection::Expression*>& a_LeftExpressions, reflection::ClassType* a_pClassType) const
{
    // Public Value Members (Properties and InstanceAttributes
    {
        auto it = a_pClassType->beginValueMembers();
        auto end = a_pClassType->endValueMembers();
        for(;it != end;++it)
        {
            reflection::ValueMember* pValueMember = *it;
            if(pValueMember->isProtected() OR pValueMember->isPrivate()) 
                continue;
            vector<reflection::Expression*> expressions;
            for(auto it = a_LeftExpressions.begin(); it != a_LeftExpressions.end(); ++it)
            {
                reflection::Expression* pLeftExpression = *it;
                expressions.push_back(pLeftExpression->clone()->solveElement(pValueMember->getName(), nullptr, nullptr, 0)->asExpression());
            }
            VariableNode* pVariableNode = o_new(VariableNode)(nameOf(pValueMember), expressions);
            pVariableNode->setRange(pValueMember->getRange());
            pVariableNode->setModifiers(pValueMember->getModifiers());
            a_pParentNode->addChildNode(pVariableNode);
        }
    }
/*

    // Public Collections
    {
        auto it = pClassType->beginCollections();
        auto end = pClassType->endCollections();
        for(;it != end;++it)
        {
            reflection::Collection* pCollection = static_cast<reflection::Collection*>(*it);
            if(pCollection->isProtected() OR pCollection->isPrivate()) continue;
            string name = pCollection->getMetaDataValue(getNameMetaDataIndex());
            if(name.empty()) name = pCollection->getName();
            VariableNode* pCollectionNode = o_new(VariableNode)(name.c_str());
            expandCollection(pCollectionNode, a_LeftExpressions, pCollection); 
        }
    }*/
}


void ClassTypeVisualizerNode::expand( VariableNode* a_pParentNode, const vector<reflection::Expression*>& a_LeftExpressions) const
{
    reflection::ClassType* pClassType = as<reflection::ClassType*>(a_pParentNode->getValueType());
    o_assert(pClassType);
    expand(a_pParentNode, a_LeftExpressions, pClassType);
}
/*

void ClassTypeVisualizerNode::expandCollection( VariableNode* a_pVariableNode, const vector<Expression*>& a_LeftExpressions, reflection::Collection* a_pCollection) const
{
    if(a_LeftExpressions.empty()) 
        return;
    // Create group for insert variables
    vector<string> groupedInsertVariables;
    for(auto it = a_LeftExpressions.begin(); it != a_LeftExpressions.end(); ++it)
    {
        groupedInsertVariables.push_back((*it)->solveElement(a_pCollection->getName()+".add");
    }
    a_pVariableNode->addChildNode(o_new(VariableNode)("<insert>", groupedInsertVariables));

    // Elements variables
    vector<vector<string>> groupedVariables;
    for(auto it = a_LeftExpressions.begin(); it != a_LeftExpressions.end(); ++it)
    {
        string sizeExp = (*it)+a_pCollection->getName()+".count";
        reflection::LanguageElement* pElement = phantom::elementByName(sizeExp);
        if(pElement == nullptr) continue;
        reflection::Expression* pExpression = pElement->asExpression();
        if(pExpression == nullptr) 
            continue;
        bool ok;
        size_t count = pExpression->get().as<size_t>(&ok);
        if(ok)
        {
            groupedVariables.resize(std::max(groupedVariables.size(), count));
            for(size_t i = 0; i<count; ++i)
            {
                groupedVariables[i].push_back((*it)+"["+lexical_cast<string>(i)+"]");
            }
        }
        pExpression->terminate();
        pExpression->deleteNow();
    }
    size_t i = 0;
    for(;i<groupedVariables.size(); ++i)
    {
        a_pVariableNode->addChildNode(o_new(VariableNode)(lexical_cast<string>(i), groupedVariables[i]));
    }
}*/

}}
