#ifndef phantom_qt_SetContainerVisualizerNode_h__
#define phantom_qt_SetContainerVisualizerNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/TypeVisualizerNode.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), SetContainerVisualizerNode);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export SetContainerVisualizerNode : public TypeVisualizerNode
{
public:
    SetContainerVisualizerNode(const string& a_Condition)
        : TypeVisualizerNode(a_Condition)
    {
    }
    virtual void expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const;

};

}}


#endif // phantom_qt_SetContainerVisualizerNode_h__
