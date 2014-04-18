#ifndef phantom_qt_ClassVariableNodeFactory_h__
#define phantom_qt_ClassVariableNodeFactory_h__


/* ****************** Includes ******************* */
#include "phantom/qt/ClassTypeVariableNodeFactory.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ClassVariableNodeFactory);
/* *********************************************** */

namespace phantom { namespace qt {

    class o_qt_export ClassVariableNodeFactory : public ClassTypeVariableNodeFactory
    {
    public:
        ClassVariableNodeFactory(bool a_bExclusive = false)
            : ClassTypeVariableNodeFactory(a_bExclusive)
        {
        }
        virtual void addChildNodes(VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Type* a_pType) const;
    };

}}


#endif // phantom_qt_ClassVariableNodeFactory_h__
