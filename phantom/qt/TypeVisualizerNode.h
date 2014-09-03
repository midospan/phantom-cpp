#ifndef phantom_qt_TypeVisualizerNode_h__
#define phantom_qt_TypeVisualizerNode_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_fwd(class, phantom, qt, VariableNode);
o_declareN(class, (phantom, qt), TypeVisualizerNode);
/* *********************************************** */

namespace phantom { namespace qt {

class Menu;

class o_qt_export TypeVisualizerNode
{
public:
    typedef std::pair<string, string> name_expression;

public:
    TypeVisualizerNode(const string& a_Condition = "")
        : m_Condition(a_Condition)
    {

    }
    void expand(VariableNode* a_pParent) const;

protected:
    virtual void expand(VariableNode* a_pParent, const vector<reflection::Expression*>& a_ParentExpressions) const = 0;

protected:
    string m_Condition;
};

}}


#endif // phantom_qt_TypeVisualizerNode_h__
