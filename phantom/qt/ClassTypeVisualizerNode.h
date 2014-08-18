#ifndef phantom_qt_ClassTypeVisualizerNode_h__
#define phantom_qt_ClassTypeVisualizerNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/TypeVisualizerNode.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ClassTypeVisualizerNode);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export ClassTypeVisualizerNode : public TypeVisualizerNode
{
public:
    ClassTypeVisualizerNode(const string& a_Condition = "")
        : TypeVisualizerNode(a_Condition)
    {
    }
    virtual void expand(VariableNode* a_pParent, const vector<reflection::Expression*>& a_ParentExpressions) const;

protected:
    void expand( VariableNode* a_pParentNode, const vector<reflection::Expression*>& a_LeftExpressions, reflection::ClassType* a_pClassType) const;

};

}}


#endif // phantom_qt_ClassTypeVisualizerNode_h__
