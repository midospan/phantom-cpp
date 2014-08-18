#ifndef o_reflection_eval_cpp_cpp_h__
#define o_reflection_eval_cpp_cpp_h__

#include "phantom/reflection/Location.h"

o_namespace_begin(phantom, reflection)

namespace cpp {

    struct hex_t 
    { 
        hex_t() : val(0) {}
        explicit hex_t(unsigned long long x) : val(x) {} 
        operator unsigned long long() const { return val; } 
        unsigned long long val; 
    } ;

    inline std::ostream&  operator<<(std::ostream& stream, const hex_t& expr)
    {
        return stream;
    }
}

o_namespace_end(phantom, reflection)

namespace std 
{
    inline std::ostream&  operator<<(std::ostream& stream, const std::nullptr_t expr)
    {
        stream << "nullptr";
        return stream;
    }
}

#endif // tokens_h__
