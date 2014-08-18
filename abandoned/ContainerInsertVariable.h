#ifndef phantom_qt_ContainerInsertVariable_h__
#define phantom_qt_ContainerInsertVariable_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ContainerInsertVariable);
/* *********************************************** */

namespace phantom { namespace qt {

    class o_qt_export ContainerInsertVariable : public reflection::Variable
    {
    public:
        ContainerInsertVariable(const string& name, bitfield modifiers = bitfield())
            : Variable(name, modifiers) {}

    };

}}


#endif // phantom_qt_ContainerInsertVariable_h__
