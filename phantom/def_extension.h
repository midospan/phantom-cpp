#ifndef o_def_extension_h__
#define o_def_extension_h__

#include "def_allocator.h"
#include "def_constructor.h"
#include "def_installer.h"
#include "def_initializer.h"

#include "def_string_convert.h"

#include "def_serializer.h"
#include "def_resetter.h"
#include "def_interpolator.h"
#include "def_copier.h"
#include "def_converter.h"
#include "def_new_delete.h"

o_namespace_begin(phantom)

/* these versions are the stable ones which are never specialized but inherits from the specilized/customized ones */


namespace detail 
{
    template<typename t_Ty, bool t_is_fundamental>
    struct default_promoter_helper
    {
        static reflection::Type* apply(reflection::Type*)
        {
            return typeOf<o_NESTED_TYPE boost::promote<t_Ty>::type>();
        }
    };
    template<typename t_Ty>
    struct default_promoter_helper<t_Ty, false>
    {
        static reflection::Type* apply(reflection::Type* a_pType)
        {
            return a_pType;
        }
    };
}

template<typename t_Ty>
struct promoter : public detail::default_promoter_helper<t_Ty, boost::is_fundamental<t_Ty>::value>
{
};

#define o_begin_extension(_extension_, ...)\
    o_namespace_begin(phantom)\
    template<>\
    struct _extension_##_ \
    {

#define o_end_extension()\
    };\
    o_namespace_end(phantom)\

o_namespace_end(phantom)


#endif // o_def_extension_h__
