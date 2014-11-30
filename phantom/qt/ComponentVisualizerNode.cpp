/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ComponentVisualizerNode.h"
#include "ComponentVisualizerNode.hxx"
#include "VariableNode.h"
#include "ComponentVariableNodeDelegate.h"
/* *********************************************** */
o_registerN((phantom, qt), ComponentVisualizerNode);
 
namespace phantom { 
namespace qt {

void ComponentVisualizerNode::expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const 
{
    a_pVariableNode->setDelegate(o_new(ComponentVariableNodeDelegate));
    
}

}}
