/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeConstructor_h__
#define o_phantom_reflection_native_TNativeConstructor_h__



/* ****************** Includes ******************* */

/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

/* ************* t_Ty Declarations ************** */

/* *********************************************** */

template<typename t_Signature, bool t_is_default_constructible_or_not_polymorphic>
struct TNativeConstructorVTableHacks
{
    static void** getVTablePointer() { return nullptr; }
    static size_t getVTableSize() { return 0; }
};

template<typename t_Signature>
struct TNativeConstructorVTableHacks<t_Signature, false> 
{
    static void** getVTablePointer() { return NativeVTablePointerExtractor<t_Signature>::apply(); }
    static size_t getVTableSize() { return NativeVTableSizeComputer<t_Signature>::apply(); }
};

template<typename t_Signature>
class TNativeConstructor : public Constructor
{
public:
    typedef TNativeConstructor<t_Signature>    self_type;
    TNativeConstructor(const string& a_strName, const string& a_strSignature, modifiers_t a_Modifiers = 0)
        : Constructor(phantom::reflection::native::currentClassType(), a_strName, a_strSignature, a_Modifiers|o_native)
    {
        phantom::reflection::native::currentClassType()->addConstructor(this);
    }
    TNativeConstructor(const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers|o_native)
    {

    }
    virtual boolean      isNative() const { return true; }

    virtual void call(void* a_pAddress, void** a_pParams) const
    {
        constructor_caller<t_Signature>::apply(a_pAddress, a_pParams);
    }

    typedef typename boost::function_traits<t_Signature>::result_type result_type;
    typedef TNativeConstructorVTableHacks<t_Signature, !boost::is_polymorphic<result_type>::value OR std::is_default_constructible<result_type>::value> hacker;

    virtual void**  _getNativeVTablePointer() const { return hacker::getVTablePointer(); }
    virtual size_t  _getNativeVTableSize() const { return hacker::getVTableSize(); }
};

o_namespace_end(phantom, reflection, native)

#endif // TConstructor_h__