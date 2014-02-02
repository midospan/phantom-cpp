#ifndef o_phantom_reflection_jit_JitEnum_h__
#define o_phantom_reflection_jit_JitEnum_h__


/* ****************** Includes ******************* */
#include <phantom/jit.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection, jit), JitEnum);
/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)

class o_jit_export JitEnum : public Enum
{
public:
	JitEnum(const string& a_strName, reflection::Type* a_pIntTypeRef, bitfield modifiers = bitfield()) 
        : Enum(a_strName, a_pIntTypeRef->getSize(), a_pIntTypeRef->getAlignment(), modifiers)
        , m_pIntTypeRef(a_pIntTypeRef)
    {
    }
	~JitEnum(void) {}
	void*allocate(size_t n) const { return m_pIntTypeRef->allocate(n); }
	void*allocate(void) const { return m_pIntTypeRef->allocate(); }
	void deallocate(void * a_pInstance,size_t n) const { m_pIntTypeRef->deallocate(a_pInstance, n); }
	void deallocate(void * a_pInstance) const { m_pIntTypeRef->deallocate(a_pInstance); }
	void construct(void * a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) const { m_pIntTypeRef->construct(a_pInstance, a_uiCount, a_uiChunkSectionSize); }
	void construct(void * a_pInstance) const { m_pIntTypeRef->construct(a_pInstance); }
	void destroy(void * a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) const { m_pIntTypeRef->destroy(a_pInstance, a_uiCount, a_uiChunkSectionSize); }
	void destroy(void * a_pInstance) const { m_pIntTypeRef->destroy(a_pInstance); }
    void serialize(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntTypeRef->serialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    void serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntTypeRef->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    void serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntTypeRef->serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    void serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntTypeRef->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    void deserialize(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntTypeRef->deserialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    void deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntTypeRef->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    void deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntTypeRef->deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    void deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntTypeRef->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase); }

    void remember(void const* a_pInstance, byte*& a_pBuffer) const { m_pIntTypeRef->remember(a_pInstance, a_pBuffer); }
    void remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer) const { m_pIntTypeRef->remember(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }
    void reset(void* a_pInstance, byte const*& a_pBuffer) const { m_pIntTypeRef->reset(a_pInstance, a_pBuffer); }
    void reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer) const { m_pIntTypeRef->reset(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }
	void valueFromString(const phantom::string & a_src, void * a_dest) const { m_pIntTypeRef->valueFromString(a_src, a_dest); }
	void valueToString(phantom::string & a_dest,void * a_src) const { m_pIntTypeRef->valueToString(a_dest, a_src); }
    void interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const
    {
        m_pIntTypeRef->interpolate(a_src_start, a_src_end, a_fPercent, a_pDest, mode );
    }
	Type * createConstType(void) const 
    {
        o_warning(false, "JitEnum const version has not been implemented");
        return const_cast<JitEnum*>(this);//o_new(native::TConstType<JitClass>)();
    }
    virtual void copy(void* a_pDest, void const* a_pSrc) const 
    { 
        m_pIntTypeRef->copy(a_pDest, a_pSrc); 
    }

protected:
    reflection::Type* m_pIntTypeRef;
};

o_namespace_end(phantom, reflection, jit)

#endif