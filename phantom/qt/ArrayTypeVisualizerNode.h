#ifndef phantom_qt_ArrayTypeVisualizerNode_h__
#define phantom_qt_ArrayTypeVisualizerNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/TypeVisualizerNode.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ArrayTypeVisualizerNode);
o_fwd(class, phantom, qt, VariableNode);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export ArrayTypeVisualizerNode : public TypeVisualizerNode
{
public:
    ArrayTypeVisualizerNode(const string& a_Condition)
        : TypeVisualizerNode(a_Condition)
    {
    }
    virtual void expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const;

};

}}


#endif // phantom_qt_ArrayTypeVisualizerNode_h__
