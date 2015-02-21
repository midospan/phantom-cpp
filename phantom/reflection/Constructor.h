/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Constructor_h__
#define o_phantom_reflection_Constructor_h__



/* ****************** Includes ******************* */


/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Constructor : public MemberFunction
{
public:
    template<typename t_Ty, bool t_is_default_constructible>
    friend struct phantom::reflection::native::detail::vtable_extractor_helper_default_constructible;
    template<typename t_Ty, bool t_is_default_constructible>
    friend struct phantom::reflection::native::detail::vtable_size_of_helper_default_constructible;

    friend class Class;
    static Class* const metaType;

public:
    Constructor();
    Constructor(const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers = 0);

    virtual void        construct(void* a_pInstance, void** a_pParams) const 
    {
        call(a_pInstance, a_pParams);
    }

    virtual void        construct(void* a_pChunk, void** a_pParams, size_t a_uiCount) 
    {
        size_t i = 0;
        while(a_uiCount--)
        {    
            call((byte*)a_pChunk+(i++)*getOwner()->asType()->getSize(), a_pParams);
        }
    }

    virtual Constructor* asConstructor() const { return (Constructor*)this; }

protected:
    Constructor(ClassType* a_pClassType, const string& a_strName, const string& a_strSignature, modifiers_t a_Modifiers = 0);
    virtual void**  getNativeVTablePointer() const { o_exception_no_implementation(); return nullptr; }
    virtual size_t  getNativeVTableSize() const { o_exception_no_implementation(); return 0; }

};

o_namespace_end(phantom, reflection)



#endif

