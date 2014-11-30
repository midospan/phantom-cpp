#include "phantom/phantom.h"
#include "boost.h"
#include "boost_thread.h"

#if o__int__reflection_template_use_level != 3
#include "boost.hxx"
#endif

o_static_assert(phantom::has_reflection<boost::details::pool::null_mutex>::value);

o_registerN((boost, details, pool), null_mutex);
o_registerN((boost), mutex);