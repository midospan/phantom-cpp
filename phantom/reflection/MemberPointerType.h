/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_MemberPointerType_h__
#define o_phantom_reflection_MemberPointerType_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export MemberPointerType : public PrimitiveType
{
    o_type;

    o_declare_meta_type(MemberPointerType);

public:
    friend class Type;

protected:
    MemberPointerType(ClassType* a_pObjectType, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0);

public:
    o_destructor ~MemberPointerType(void);

    virtual Type*               asPOD() const { return (MemberPointerType*)this; }
    virtual MemberPointerType*  asMemberPointerType() const { return (MemberPointerType*)this; }

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
    
    virtual void        interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_dest, uint mode) const 
    {
        o_exception(exception::unsupported_member_function_exception, "interpolation is not supported for any pointer type");
    }

    ClassType*          getObjectType() const { return m_pObjectType; }

    /// built-in delegates
    void        assignment(void** a_pArgs, void* a_pOutput) 
    {
        memcpy(a_pArgs[0], a_pArgs[1], m_uiSize);
        *(void**)a_pOutput = a_pArgs[0];
    }
    void        equal(void** a_pArgs, void* a_pOutput)
    {
        *(bool*)a_pOutput = memcmp(a_pArgs[0], a_pArgs[1], m_uiSize) == 0;
    }
    void        notEqual(void** a_pArgs, void* a_pOutput)
    {
        *(bool*)a_pOutput = memcmp(a_pArgs[0], a_pArgs[1], m_uiSize) != 0;
    }

protected:
    ClassType* m_pObjectType;
};

o_namespace_end(phantom, reflection)



#endif