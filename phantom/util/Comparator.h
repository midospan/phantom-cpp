/* TODO LICENCE HERE */

#ifndef util_Comparator_h__
#define util_Comparator_h__



/* ****************** Includes ******************* */
#include "phantom/def_export.h"

/* **************** Declarations ***************** */
o_declareN(class, (phantom), Comparator)
/* *********************************************** */


o_namespace_begin(phantom)


class o_export Comparator
{

public:

    struct std_adapter
    {
        std_adapter(Comparator* a_pComparator)
            : m_pComparator(a_pComparator){}
        
        inline bool        operator()(void* one, void* another) const
        {
            return m_pComparator->compare(one, another) > 0;
        }
        Comparator* m_pComparator;
    };
    struct std_reversed_adapter
    {
        std_reversed_adapter(Comparator* a_pComparator)
            : m_pComparator(a_pComparator) {}

        inline bool        operator()(void* one, void* another)  const
        {
            return m_pComparator->compare(another, one) > 0;
        }
        Comparator* m_pComparator;
    };
    virtual int32        compare(void*,void*) const = 0;

protected:
    
};

o_namespace_end(phantom)



#endif
