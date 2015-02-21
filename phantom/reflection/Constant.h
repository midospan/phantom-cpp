/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Constant_h__
#define o_phantom_reflection_Constant_h__

/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Constant : public NamedElement
{
    o_language_element;

public:
    static Class* const metaType;

public:
    Constant()
    {

    }
    Constant(const string& a_strName, modifiers_t modifiers = 0)
        : NamedElement(a_strName, modifiers)
    {

    }

    virtual Type*                   getValueType() const = 0;
    virtual void                    getValue(void* dest) const = 0;
    virtual bool                    hasValue(void* a_pSrc) const = 0;
    virtual Constant*               asConstant() const { return const_cast<Constant*>(this); }

    virtual Expression*             toExpression() const;

    virtual string                  getQualifiedName() const { return m_strName.empty() ? "" : NamedElement::getQualifiedName(); }
    virtual string                  getQualifiedDecoratedName() const { return m_strName.empty() ? "" : NamedElement::getQualifiedDecoratedName(); }
    virtual string                  getDecoratedName() const { return m_strName.empty() ? "" : NamedElement::getDecoratedName(); }

    virtual Constant*               clone() const = 0;

    virtual bool                    isIntegral() const { return getValueType()->asIntegralType() != nullptr; }
    virtual bool                    isZero() const = 0;

    inline  bool                    isIntegralZero() const { return isIntegral() AND isZero(); }

    virtual void                    toString(string& out) const = 0;

    virtual void                    toLiteral(string& out) const = 0;

protected:
};

o_namespace_end(phantom, reflection)



#endif
