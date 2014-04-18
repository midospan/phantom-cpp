/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "aabb2.h"
/* *********************************************** */
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