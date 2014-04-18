#ifndef phantom_qt_MapContainerClassVariableNodeFactory_h__
#define phantom_qt_MapContainerClassVariableNodeFactory_h__


/* ****************** Includes ******************* */
#include "phantom/qt/VariableNodeFactory.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), MapContainerClassVariableNodeFactory);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export MapContainerClassVariableNodeFactory : public VariableNodeFactory
{
public:
    MapContainerClassVariableNodeFactory(bool a_bExclusive = false)
        : VariableNodeFactory(a_bExclusive)
    {
    }
    virtual void addChildNodes(VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Type* a_pType) const;

};

}}


#endif // phantom_qt_MapContainerClassVariableNodeFactory_h__
