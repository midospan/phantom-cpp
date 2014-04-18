#ifndef phantom_qt_ClassTypeVariableNodeFactory_h__
#define phantom_qt_ClassTypeVariableNodeFactory_h__


/* ****************** Includes ******************* */
#include "phantom/qt/VariableNodeFactory.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ClassTypeVariableNodeFactory);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export ClassTypeVariableNodeFactory : public VariableNodeFactory
{
public:
    ClassTypeVariableNodeFactory(bool a_bExclusive = false)
        : VariableNodeFactory(a_bExclusive)
    {
    }
    virtual void addChildNodes(VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Type* a_pType) const;

protected:
    void addCollectionVariableNodes( VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Collection* a_pCollection ) const;

};

}}


#endif // phantom_qt_ClassTypeVariableNodeFactory_h__
