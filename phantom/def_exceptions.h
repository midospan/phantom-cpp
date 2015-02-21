/* TODO LICENCE HERE */

#ifndef o_phantom_exceptions_h__
#define o_phantom_exceptions_h__



/* ****************** Includes ******************* */
#include <exception>
/* *********************************************** */

o_namespace_begin(phantom, exception)

#if (o_COMPILER == o_COMPILER_VISUAL_STUDIO)
typedef std::exception base_exception;
#else
class base_exception : public std::exception
{
public:
    base_exception(void) {}
    base_exception(const char * const & _What)
    {

    }
};
#endif


class invalid_argument_exception : public base_exception
{
public:
    invalid_argument_exception(void) : base_exception("Invalid argument") {}
    invalid_argument_exception(const char * const & _What)
        : base_exception(_What)
    {

    }
};

class invalid_parsing_exception : public base_exception
{
public:
    invalid_parsing_exception(void) {}
    invalid_parsing_exception(const char * const & _What)
        : base_exception(_What)
    {

    }
};

class reflection_runtime_exception : public base_exception
{
public:
    reflection_runtime_exception(void) {}
    reflection_runtime_exception(const char * const & _What)
        : base_exception(_What)
    {

    }
};

class unknown_reflection_type_exception : public reflection_runtime_exception
{
public:
    unknown_reflection_type_exception(void) {}
    unknown_reflection_type_exception(const char * const & _What)
        : reflection_runtime_exception((string("Unknown type '") + _What + '\'').c_str())
    {

    }
};

template<typename t_Ty>
class t_unknown_reflection_type_exception : public unknown_reflection_type_exception
{
public:
    t_unknown_reflection_type_exception(void) {}
    t_unknown_reflection_type_exception(const char * const & _What)
        : unknown_reflection_type_exception(_What)
    {

    }
};


class unsupported_member_function_exception : public base_exception
{
public:
    unsupported_member_function_exception(void) {}
    unsupported_member_function_exception(const char * const & _What)
        : base_exception(_What)
    {

    }
};

class unserializable_exception : public base_exception
{
public:
    unserializable_exception(void) {}
    unserializable_exception(const char * const & _What)
        : base_exception(_What)
    {

    }
};

o_namespace_end(phantom, exception)

#endif // o_phantom_exceptions_h__
