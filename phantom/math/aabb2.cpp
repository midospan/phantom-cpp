/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "aabb2.h"
#include "aabb2.hxx"
/* *********************************************** */
o_registerNT((phantom, math), (typename), (t_Ty), aabb2);
o_registerNTI((phantom, math), aabb2, (float));
o_registerNTI((phantom, math), aabb2, (double));

o_namespace_begin(phantom, math)

    template<>
const aabb2<float> aabb2<float>::NULL_BOUNDS(std::numeric_limits<float>::max()
                                                    , std::numeric_limits<float>::max()
                                                    , std::numeric_limits<float>::lowest()
                                                    , std::numeric_limits<float>::lowest());

template<>
const aabb2<double> aabb2<double>::NULL_BOUNDS(std::numeric_limits<double>::max()
                                                    , std::numeric_limits<double>::max()
                                                    , std::numeric_limits<double>::lowest()
                                                    , std::numeric_limits<double>::lowest());
o_namespace_end(phantom, math)