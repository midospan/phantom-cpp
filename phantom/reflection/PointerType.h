/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_PointerType_h__
#define o_phantom_reflection_PointerType_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */


/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export PointerType : public PrimitiveType
{
    o_type;

    o_declare_meta_type(PointerType);

public:
    friend class Type;

protected:
    PointerType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0) 
        : PrimitiveType(e_pointer, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)    
    {

    }

public:
    o_destructor ~PointerType(void)     {}

    virtual Type*           asPOD() const { return (PointerType*)this; }
    virtual PointerType*    asPointerType() const { return (PointerType*)this; }

    virtual void        safeConstruct(void* a_pBuffer) const 
    {
        *reinterpret_cast<void**>(a_pBuffer) = NULL;
    }
    virtual void        safeConstruct(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const 
    {
        memset(a_pBuffer, 0, a_uiCount*a_uiChunkSectionSize*m_uiSize);
    }

    virtual void        construct(void* a_pBuffer) const 
    {
        // trivial
    }
    virtual void        destroy(void* a_pBuffer) const 
    {
        // trivial
    }
    virtual void        construct(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const 
    {
        // trivial
    }
    virtual void        destroy(void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize) const 
    {
        // trivial
    }
    
    virtual void    interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_dest, uint mode) const 
    {
        o_exception(exception::unsupported_member_function_exception, "interpolation is not supported for any pointer type");
    }

    /// 13.6.15
    /// ---------------------- 
    /// bool operator<(T , T );
    /// bool operator>(T , T );
    /// bool operator<=(T , T );
    /// bool operator>=(T , T );
    /// bool operator==(T , T );
    /// bool operator!=(T , T );
    void                less(void** a_pArgs, void* a_pOutput);
    void                greater(void** a_pArgs, void* a_pOutput);
    void                lessEqual(void** a_pArgs, void* a_pOutput);
    void                greaterEqual(void** a_pArgs, void* a_pOutput);
    void                equal(void** a_pArgs, void* a_pOutput);
    void                notEqual(void** a_pArgs, void* a_pOutput);

    /// 13.6.19
    /// ---------------------- 
    /// T *VQ & operator=(T *VQ &, T *);
    void                assignment(void** a_pArgs, void* a_pOutput);

protected:
};

o_namespace_end(phantom, reflection)



#endif