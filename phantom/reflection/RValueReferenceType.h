/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_RValueReferenceType_h__
#define o_phantom_reflection_RValueReferenceType_h__

/* ****************** Includes ******************* */
#include <phantom/reflection/ReferenceType.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export RValueReferenceType : public ReferenceType
{
    o_type;

    o_declare_meta_type(RValueReferenceType);

public:
    friend class Type;

protected:
    RValueReferenceType(Type* a_pType);

public:
    virtual RValueReferenceType*  asRValueReferenceType() const { return const_cast<RValueReferenceType*>(this); }
    virtual RValueReferenceType*  asClassRValueReferenceType() const { return (m_pReferencedType AND m_pReferencedType->asClass()) ? const_cast<RValueReferenceType*>(this) : nullptr; }
    virtual RValueReferenceType*  asConstClassRValueReferenceType() const { return (m_pReferencedType AND m_pReferencedType->asConstClass()) ? const_cast<RValueReferenceType*>(this) : nullptr; }
    
    virtual Type*   addLValueReference() const { return m_pReferencedType->lvalueReferenceType(); }

    virtual Type*   addRValueReference() const { return const_cast<RValueReferenceType*>(this); }

    virtual Type*   removeRValueReference() const { return m_pReferencedType; }

    virtual Type*   removeAllConst() const { return m_pReferencedType->removeAllConst()->rvalueReferenceType(); }

    virtual Type*   removeAllQualifiers() const { return m_pReferencedType->removeAllQualifiers()->rvalueReferenceType(); }

    virtual Type*   replicate(Type* a_pSource) const { return m_pReferencedType->replicate(a_pSource->removeReference())->addRValueReference(); }

    virtual string  getQualifiedName() const { return m_pReferencedType->getQualifiedName()+"&&"; }
    virtual string  getDecoratedName() const { return m_pReferencedType->getDecoratedName()+"&&"; }
    virtual string  getQualifiedDecoratedName() const { return m_pReferencedType->getQualifiedDecoratedName()+"&&"; }

    virtual bool    isCopyable() const { return true; }

    virtual bool    partialAccepts(Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_DeducedConstants) const;

    virtual bool    equals(LanguageElement* a_pOther) const 
    {
        return Type::equals(a_pOther) OR (a_pOther->asRValueReferenceType() AND m_pReferencedType->equals(static_cast<RValueReferenceType*>(a_pOther)->m_pReferencedType));
    }
};

o_namespace_end(phantom, reflection)



#endif