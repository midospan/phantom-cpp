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

bool ClassTypeVisualizerNode::NoProtectedOrPrivateFilter( VariableNode* a_pVariableNode, reflection::ValueMember* a_pValueMember )
{
    if(a_pValueMember->isProtected() OR a_pValueMember->isPrivate()) 
        return false;
    return true;
}

bool ClassTypeVisualizerNode::NoFilter( VariableNode* a_pVariableNode, reflection::ValueMember* a_pValueMember )
{
    return true;
}

void ClassTypeVisualizerNode::expand( VariableNode* a_pParentNode, const vector<reflection::Expression*>& a_LeftExpressions, reflection::ClassType* a_pClassType) const
{
    // Public Value Members (Properties and InstanceAttributes
    {
        auto it = a_pClassType->beginValueMembers();
        auto end = a_pClassType->endValueMembers();
        for(;it != end;++it)
        {
            reflection::ValueMember* pValueMember = *it;
            if(!m_Filter(a_pParentNode, pValueMember)) 
                continue;
            vector<reflection::Expression*> expressions;
            for(auto it = a_LeftExpressions.begin(); it != a_LeftExpressions.end(); ++it)
            {
                reflection::Expression* pLeftExpression = *it;
                expressions.push_back(cplusplus()->qualifiedLookup(pLeftExpression->clone(), pValueMember->getName(), nullptr, nullptr, 0)->asExpression());
            }
            VariableNode* pVariableNode = o_new(VariableNode)(nameOf(pValueMember), expressions);
            pVariableNode->setIcon(QIcon(iconOf(pValueMember).c_str()));
            pVariableNode->setRange(pValueMember->getRange());
            pVariableNode->setModifiers(pValueMember->getModifiers());
            a_pParentNode->addChildNode(pVariableNode);
        }
    }
}


void ClassTypeVisualizerNode::expand( VariableNode* a_pParentNode, const vector<reflection::Expression*>& a_LeftExpressions) const
{
    reflection::ClassType* pClassType = as<reflection::ClassType*>(a_pParentNode->getValueType());
    o_assert(pClassType);
    expand(a_pParentNode, a_LeftExpressions, pClassType);
}

}}
