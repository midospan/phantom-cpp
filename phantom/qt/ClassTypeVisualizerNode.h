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
    typedef fastdelegate::FastDelegate< bool (VariableNode*, reflection::ValueMember*) > filter;

    static bool NoFilter(VariableNode* a_pVariableNode, reflection::ValueMember* a_pValueMember);
    static bool NoProtectedOrPrivateFilter(VariableNode* a_pVariableNode, reflection::ValueMember* a_pValueMember);

public:
    ClassTypeVisualizerNode(filter a_Filter = filter(&ClassTypeVisualizerNode::NoFilter))
        : TypeVisualizerNode(""), m_Filter(a_Filter)
    {
    }
    virtual void expand(VariableNode* a_pParent, const vector<reflection::Expression*>& a_ParentExpressions) const;

protected:
    void expand( VariableNode* a_pParentNode, const vector<reflection::Expression*>& a_LeftExpressions, reflection::ClassType* a_pClassType) const;

protected:
    filter m_Filter;
};

}}


#endif // phantom_qt_ClassTypeVisualizerNode_h__
