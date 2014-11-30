#ifndef phantom_qt_ClassVisualizerNode_h__
#define phantom_qt_ClassVisualizerNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/ClassTypeVisualizerNode.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ClassVisualizerNode);
/* *********************************************** */

namespace phantom { namespace qt {

    class o_qt_export ClassVisualizerNode : public ClassTypeVisualizerNode
    {
    public:
        ClassVisualizerNode(filter a_Filter = filter(&ClassTypeVisualizerNode::NoFilter))
            : ClassTypeVisualizerNode(a_Filter)
        {
        }
        virtual void expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions) const;

    protected:
        void expand(VariableNode* a_pVariableNode, const vector<reflection::Expression*>& a_LeftExpressions, reflection::Class* a_pClass) const;
    };

}}


#endif // phantom_qt_ClassVisualizerNode_h__
