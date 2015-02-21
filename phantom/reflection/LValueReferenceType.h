/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_LValueReferenceType_h__
#define o_phantom_reflection_LValueReferenceType_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export LValueReferenceType : public ReferenceType
{
    o_type;

    o_declare_meta_type(LValueReferenceType);

public:
    friend class Type;

protected:
    LValueReferenceType(Type* a_pType);

public:
    virtual LValueReferenceType*  asLValueReferenceType() const { return const_cast<LValueReferenceType*>(this); }
    virtual LValueReferenceType*  asClassLValueReferenceTypeType() const { return (m_pReferencedType AND m_pReferencedType->asClass()) ? const_cast<LValueReferenceType*>(this) : nullptr; }
    virtual LValueReferenceType*  asConstClassLValueReferenceType() const { return (m_pReferencedType AND m_pReferencedType->asConstClass()) ? const_cast<LValueReferenceType*>(this) : nullptr; }

    virtual Type*   addLValueReference() const { return const_cast<LValueReferenceType*>(this); }

    virtual Type*   addRValueReference() const { return const_cast<LValueReferenceType*>(this); }

    virtual Type*   removeLValueReference() const { return m_pReferencedType; }

    virtual Type*   removeAllConst() const { return m_pReferencedType->removeAllConst()->lvalueReferenceType(); }

    virtual Type*   removeAllQualifiers() const { return m_pReferencedType->removeAllQualifiers()->lvalueReferenceType(); }

    virtual Type*   replicate(Type* a_pSource) const { return m_pReferencedType->replicate(a_pSource->removeReference())->addLValueReference(); }

    virtual string  getQualifiedName() const { return m_pReferencedType->getQualifiedName()+'&'; }
    virtual string  getDecoratedName() const { return m_pReferencedType->getDecoratedName()+'&'; }
    virtual string  getQualifiedDecoratedName() const { return m_pReferencedType->getQualifiedDecoratedName()+'&'; }

    virtual bool    isCopyable() const { return true; }

    virtual bool    partialAccepts(Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_DeducedConstants) const;

    virtual bool    equals(LanguageElement* a_pOther) const 
    {
        return Type::equals(a_pOther) OR (a_pOther->asLValueReferenceType() AND m_pReferencedType->equals(static_cast<LValueReferenceType*>(a_pOther)->m_pReferencedType));
    }
};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_LValueReferenceType_h__