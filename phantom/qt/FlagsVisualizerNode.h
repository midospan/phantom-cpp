#ifndef phantom_qt_FlagsVisualizerNode_h__
#define phantom_qt_FlagsVisualizerNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/TypeVisualizerNode.h"
/* **************** Declarations ***************** */
o_fwd(class, phantom, qt, VariableNode);
o_declareN(class, (phantom, qt), FlagsVisualizerNode);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export FlagsVisualizerNode : public TypeVisualizerNode
{
public:
    FlagsVisualizerNode(const string& a_Condition)
        : TypeVisualizerNode(a_Condition)
    {

    }

    virtual void expand(VariableNode* a_pParent, const vector<reflection::Expression*>& a_LeftExpressions) const;

protected:
    string m_Head;
    string m_Right;
    string m_Left;

};

}}


#endif // phantom_qt_FlagsVisualizerNode_h__
