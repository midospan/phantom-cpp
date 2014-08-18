#ifndef phantom_qt_SequentialContainerVisualizerNode_h__
#define phantom_qt_SequentialContainerVisualizerNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/TypeVisualizerNode.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), SequentialContainerVisualizerNode);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export SequentialContainerVisualizerNode : public TypeVisualizerNode
{
public:
    SequentialContainerVisualizerNode(const string& a_Condition = "")
        : TypeVisualizerNode(a_Condition)
    {
    }
    virtual void expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const;

};

}}


#endif // phantom_qt_SequentialContainerVisualizerNode_h__
