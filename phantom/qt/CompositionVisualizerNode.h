#ifndef phantom_qt_CompositionVisualizerNode_h__
#define phantom_qt_CompositionVisualizerNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/TypeVisualizerNode.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CompositionVisualizerNode);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export CompositionVisualizerNode : public TypeVisualizerNode
{
public:
    CompositionVisualizerNode(const string& a_Condition)
        : TypeVisualizerNode(a_Condition)
    {
    }
    virtual void expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const;

};

}}


#endif // phantom_qt_CompositionVisualizerNode_h__
