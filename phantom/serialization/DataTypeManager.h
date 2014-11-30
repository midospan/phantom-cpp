#ifndef o_phantom_moon_DataTypeManager_h__
#define o_phantom_moon_DataTypeManager_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), DataTypeManager)
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export DataTypeManager
{

public:
    DataTypeManager(DataBase* a_pDataBase) 
        : m_pDataBase(a_pDataBase)
    {

    }

protected:
    DataBase* m_pDataBase;
};

o_namespace_end(phantom, serialization)

#endif
