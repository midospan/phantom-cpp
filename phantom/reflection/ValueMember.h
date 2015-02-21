/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_ValueMember_h__
#define o_phantom_reflection_ValueMember_h__

/* ****************** Includes ******************* */
#include <phantom/reflection/LanguageElement.h>

/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ValueMember : public NamedElement
{

public:
    ValueMember();
    ValueMember(Type* a_pValueType, const string& a_strName, Range* a_pRange, uint a_uiSerializationMask, modifiers_t a_Modifiers = 0);
    o_destructor ~ValueMember(void) {}

    virtual ValueMember*    asValueMember() const { return (ValueMember*)this; }

    Range*                  getRange() const { return m_pRange; }

    virtual void            getValue(void const* a_pObject, void* dest) const = 0;
    virtual void            setValue(void* a_pObject, void const* src) const = 0;

    virtual void            rememberValue(void const* a_pInstance, byte*& a_pOutBuffer) const;
    virtual void            rememberValue(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const;
    virtual void            resetValue(void* a_pInstance, byte const*& a_pInBuffer) const;
    virtual void            resetValue(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) const;

    virtual void            serializeValue(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            serializeValue(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            serializeValue(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            serializeValue(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            deserializeValue(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            deserializeValue(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            deserializeValue(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void            deserializeValue(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;

    Type*                   getValueType() const { return m_pValueType; }

    inline uint             getSerializationMask() const { return m_uiSerializationMask; }
                            
    virtual        void     copyValue(void* dest, void const* src) const 
    {
        void* sourceBuffer = getValueType()->newInstance();
        getValue(src, sourceBuffer);
        setValue(dest, sourceBuffer);
        getValueType()->deleteInstance(sourceBuffer);
    }

    inline ClassType*       getOwnerClassType() const { return m_pOwner->asClassType(); } 
    inline Class*           getOwnerClass() const { return m_pOwner->asClass(); }                  

    o_forceinline boolean   isSaved(uint a_uiSerializationFlag) const { return NOT(((m_Modifiers & o_transient) == o_transient)) AND ((m_uiSerializationMask & a_uiSerializationFlag) == a_uiSerializationFlag); }
    o_forceinline boolean   isReset() const { return ((m_Modifiers & o_reset) == o_reset); }
    o_forceinline boolean   isTransient() const { return ((m_Modifiers & o_transient) == o_transient); }

    virtual void*           getAddress(void const* a_pInstance) const { return NULL; }

    virtual bool            referencesData(const void* a_pInstance, const phantom::data& a_Data) const = 0;

protected:
    void                    referencedElementRemoved( LanguageElement* a_pElement );
    void                    setRange(Range* a_pRange);

protected:
    Type*   m_pValueType;
    Range*  m_pRange;
    uint    m_uiSerializationMask;
};

o_namespace_end(phantom, reflection)



#endif
