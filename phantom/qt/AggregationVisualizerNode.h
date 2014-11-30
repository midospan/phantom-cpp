#ifndef phantom_qt_AggregationVisualizerNode_h__
#define phantom_qt_AggregationVisualizerNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/TypeVisualizerNode.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), AggregationVisualizerNode);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export AggregationVisualizerNode : public TypeVisualizerNode
{
public:
    AggregationVisualizerNode(const string& a_Condition)
        : TypeVisualizerNode(a_Condition)
    {
    }
    virtual void    expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const;
};

}}


#endif // phantom_qt_AggregationVisualizerNode_h__
