#ifndef phantom_qt_MapVisualizerNode_h__
#define phantom_qt_MapVisualizerNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/TypeVisualizerNode.h"
/* **************** Declarations ***************** */
o_fwd(class, phantom, qt, VariableNode);
o_declareN(class, (phantom, qt), MapVisualizerNode);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export MapVisualizerNode : public TypeVisualizerNode
{
public:
    MapVisualizerNode(const string& a_Condition)
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


#endif // phantom_qt_MapVisualizerNode_h__
