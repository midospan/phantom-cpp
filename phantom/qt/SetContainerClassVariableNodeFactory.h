#ifndef phantom_qt_SetContainerClassVariableNodeFactory_h__
#define phantom_qt_SetContainerClassVariableNodeFactory_h__


/* ****************** Includes ******************* */
#include "phantom/qt/VariableNodeFactory.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), SetContainerClassVariableNodeFactory);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export SetContainerClassVariableNodeFactory : public VariableNodeFactory
{
public:
    SetContainerClassVariableNodeFactory(bool a_bExclusive = false)
        : VariableNodeFactory(a_bExclusive)
    {
    }
    virtual void addChildNodes(VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Type* a_pType) const;

};

}}


#endif // phantom_qt_SetContainerClassVariableNodeFactory_h__
