#ifndef phantom_qt_CompositionClassVariableNodeFactory_h__
#define phantom_qt_CompositionClassVariableNodeFactory_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CompositionClassVariableNodeFactory);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export CompositionClassVariableNodeFactory : public VariableNodeFactory
{
public:
    CompositionClassVariableNodeFactory(bool a_bExclusive = false)
        : VariableNodeFactory(a_bExclusive)
    {
    }
    virtual void addChildNodes(VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Type* a_pType) const;

};

}}


#endif // phantom_qt_CompositionClassVariableNodeFactory_h__
