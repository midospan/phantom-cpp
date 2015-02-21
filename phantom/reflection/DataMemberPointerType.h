/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_DataMemberPointerType_h__
#define o_phantom_reflection_DataMemberPointerType_h__


/* ****************** Includes ******************* */

/* ************* Class Declarations ************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)


class o_export DataMemberPointerType : public MemberPointerType
{
    o_type;

    o_invalid_decl(DataMemberPointerType);

public:
    static Class* const metaType;

public:
    DataMemberPointerType(ClassType* a_pObjectType, Type* a_pValueType, modifiers_t a_uiModifiers = 0);

protected:
    DataMemberPointerType(ClassType* a_pObjectType, Type* a_pValueType, size_t a_uiSize, size_t a_uiAlignment, modifiers_t a_uiModifiers = 0);

public:
    o_destructor ~DataMemberPointerType()
    {

    }

    virtual DataMemberPointerType* asDataMemberPointerType() const { return (DataMemberPointerType*)this; }

    virtual size_t  getOffset(void* a_pPointer) const;

    virtual void    setValue( void* a_pPointer, void* a_pObject, void const* src ) const;

    virtual void    getValue( void* a_pPointer, void const* a_pObject, void* dest ) const;

    virtual void*   getAddress( void* a_pPointer, void const* a_pObject ) const;

    inline Type*    getValueType() const { return m_pValueType; }
    
    virtual void    referencedElementRemoved(LanguageElement* a_pElement);

protected:
    Type*  m_pValueType;

};

o_namespace_end(phantom, reflection)



#endif
