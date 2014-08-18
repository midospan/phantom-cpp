#ifndef phantom_qt_VariableNodeFactory_h__
#define phantom_qt_VariableNodeFactory_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), VariableModel);
o_fwd(class, phantom, qt, VariableNode);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export VariableNodeFactory
{
public:
    VariableNodeFactory(bool a_bExclusive = false)
        : m_bExclusive(a_bExclusive) {}

    virtual void addChildNodes(VariableNode* a_pVariableNode, const vector<string>& a_LeftExpressions, reflection::Type* a_pType) const = 0;
    virtual void addChildNodes(VariableNode* a_pVariableNode) const;
    bool isExclusive() const { return m_bExclusive; }

protected:
    bool m_bExclusive;
};

}}


#endif // phantom_qt_VariableNodeFactory_h__
