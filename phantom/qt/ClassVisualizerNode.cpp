/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ClassVisualizerNode.h"
#include "ClassVisualizerNode.hxx"
#include "VariableNode.h"
/* *********************************************** */
o_registerN((phantom, qt), ClassVisualizerNode);
 
namespace phantom { 
    namespace qt {

void ClassVisualizerNode::expand( VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions ) const
{
    reflection::Class* pClass = a_pVariableNode->getValueType()->asClass();
    o_assert(pClass);
    expand(a_pVariableNode, a_LeftExpressions, pClass);
}

void ClassVisualizerNode::expand( VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions, reflection::Class* a_pClass ) const
{
    VariableNode* pClassLayoutNode = o_new(VariableNode)(nameOf(a_pClass));
    pClassLayoutNode->setIcon(QIcon(iconOf(a_pClass).c_str()));
    a_pVariableNode->addChildNode(pClassLayoutNode);
    ClassTypeVisualizerNode::expand(pClassLayoutNode, a_LeftExpressions, a_pClass);
    if(a_pClass->isPublic())
    {
        for(size_t i = 0; i<a_pClass->getBaseClassCount(); ++i)
        {
            expand(a_pVariableNode, a_LeftExpressions, a_pClass->getBaseClass(i));
        }
    }
}
}}
