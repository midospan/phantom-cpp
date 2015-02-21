/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Placeholder_h__
#define o_phantom_reflection_Placeholder_h__

/* ****************** Includes ******************* */
#include "Expression.h"
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Placeholder 
{
public:
    virtual NamedElement*    asNamedElement() const = 0;

    virtual Placeholder*    asPlaceholder() const = 0;

    virtual PlaceholderType*    asPlaceholderType() const { return nullptr; }

    virtual PlaceholderConstant*    asPlaceholderConstant() const { return nullptr; }

    virtual PlaceholderClass*    asPlaceholderClass() const { return nullptr; }

    virtual TemplateDependantTemplateInstance* asTemplateDependantTemplateInstance() const { return nullptr; }

    virtual TemplateDependantArrayType*   asTemplateDependantArrayType() const { return nullptr; }

    virtual PlaceholderTemplate* asPlaceholderTemplate() const { return nullptr; }

    virtual bool accepts(LanguageElement* a_pLanguageElement) const { return false; }

};

class o_export PlaceholderType : public Type, public Placeholder
{
    o_type;

    o_declare_meta_type(PlaceholderType);

public:
    PlaceholderType(const string& a_strName, modifiers_t a_Modifiers = 0)
        : Type(e_placeholder, a_strName, 0, 0, a_Modifiers|o_template_dependant) 
        , m_pAsClass(nullptr)
        , m_pAsClassType(nullptr)
    {
    }

    virtual bool                accepts(LanguageElement* a_pLanguageElement) const { return a_pLanguageElement->asType() != nullptr; }
    virtual NamedElement*       asNamedElement() const { return (PlaceholderType*)this; }
    virtual Placeholder*        asPlaceholder() const { return (PlaceholderType*)this; }
    virtual Class*              asClass() const;
    virtual ClassType*          asClassType() const;
    virtual PlaceholderType*    asPlaceholderType() const { return (PlaceholderType*)this; }
    virtual bool                equals(LanguageElement* a_pOther) const 
    {
        return Type::equals(a_pOther) OR (a_pOther->asType() AND a_pOther->asPlaceholder());
    }

    virtual bool                isKindOf(Type* a_pType) const { return true; }

    virtual string getQualifiedDecoratedName() const { return m_strName; }
    virtual string getDecoratedName() const { return m_strName; }
    virtual string getQualifiedName() const { return m_strName; }
    virtual bool            isCopyable() const { return true; }

protected:
    mutable Class* m_pAsClass;
    mutable ClassType* m_pAsClassType;
};

class o_export PlaceholderClassType : public ClassType, public Placeholder
{
    o_type;

public:
    PlaceholderClassType(PlaceholderType* a_pPlaceholderType)
        : ClassType(e_placeholder, a_pPlaceholderType->getName(), 0, 0, a_pPlaceholderType->getModifiers()|o_template_dependant) 
    {
        addReferencedElement(a_pPlaceholderType);
    }

    virtual bool                    accepts(LanguageElement* a_pLanguageElement) const { return a_pLanguageElement->asClassType() != nullptr; }
    virtual NamedElement*           asNamedElement() const { return (PlaceholderClassType*)this; }
    virtual Placeholder*            asPlaceholder() const { return (PlaceholderClassType*)this; }
    virtual PlaceholderClassType*   asPlaceholderClassType() const { return (PlaceholderClassType*)this; }

    virtual bool                    isKindOf(Type* a_pType) const { return true; }
    virtual bool                    isKindOf(Class* a_pType) const { return true; }

    virtual Class*                  asClass() const { return m_pOwner->asClass(); }

    virtual bool                    equals(LanguageElement* a_pOther) const 
    {
        return Type::equals(a_pOther) OR (a_pOther->asType() AND a_pOther->asPlaceholder());
    }

    virtual string getQualifiedDecoratedName() const { return m_strName; }
    virtual string getDecoratedName() const { return m_strName; }
    virtual string getQualifiedName() const { return m_strName; }
    virtual bool            isCopyable() const { return true; }

};

class o_export PlaceholderClass : public Class, public Placeholder
{
    o_type;


public:
    PlaceholderClass(PlaceholderType* a_pPlaceholderType)
        : Class(a_pPlaceholderType->getName(), 0, 0, a_pPlaceholderType->getModifiers()|o_template_dependant) 
    {
        addReferencedElement(a_pPlaceholderType);
    }

    virtual bool                    accepts(LanguageElement* a_pLanguageElement) const { return a_pLanguageElement->asClass() != nullptr; }
    virtual NamedElement*           asNamedElement() const { return (PlaceholderClass*)this; }
    virtual Placeholder*            asPlaceholder() const { return (PlaceholderClass*)this; }
    virtual PlaceholderClass*       asPlaceholderClass() const { return (PlaceholderClass*)this; }

    virtual bool                    isKindOf(Type* a_pType) const { return true; }
    virtual bool                    isKindOf(Class* a_pType) const { return true; }

    virtual bool                    equals(LanguageElement* a_pOther) const 
    {
        return Type::equals(a_pOther) OR (a_pOther->asType() AND a_pOther->asPlaceholder());
    }

    virtual string getQualifiedDecoratedName() const { return m_strName; }
    virtual string getDecoratedName() const { return m_strName; }
    virtual string getQualifiedName() const { return m_strName; }
    virtual bool            isCopyable() const { return true; }

};

class o_export PlaceholderTemplate : public Template, public Placeholder
{
    o_language_element;

public:
    PlaceholderTemplate(const string& a_strName, TemplateSignature* a_pSignature)
        : Template(a_pSignature, a_strName, o_template_dependant) 
    {
    }

    virtual bool                    accepts(LanguageElement* a_pLanguageElement) const;
    virtual bool                    isKindOf(Type* a_pType) const { return true; }

    virtual NamedElement*           asNamedElement() const { return (PlaceholderTemplate*)this; }
    virtual Placeholder*            asPlaceholder() const { return (PlaceholderTemplate*)this; }
    virtual PlaceholderTemplate*    asPlaceholderTemplate() const { return (PlaceholderTemplate*)this; }

    virtual bool                    equals(LanguageElement* a_pOther) const 
    {
        if(Template::equals(a_pOther)) return true;
        Placeholder* pPH = a_pOther->asPlaceholder();
        PlaceholderTemplate* pPHT = pPH ? pPH->asPlaceholderTemplate() : nullptr;
        return pPHT AND pPHT->m_pTemplateSignature->equals(m_pTemplateSignature);
    }

    virtual string getQualifiedDecoratedName() const { return m_strName; }
    virtual string getDecoratedName() const { return m_strName; }
    virtual string getQualifiedName() const { return m_strName; }

};

class PlaceholderConstant : public Constant, public Placeholder
{
    o_language_element;

    o_declare_meta_type(PlaceholderConstant);

public:
    PlaceholderConstant(Type* a_pType, const string& a_strName, modifiers_t modifiers = 0)
        : Constant(a_strName, modifiers|o_template_dependant)
        , m_pType(a_pType)
    {

    }
    virtual bool                    accepts(LanguageElement* a_pLanguageElement) const;
    virtual NamedElement*           asNamedElement() const { return (PlaceholderConstant*)this; }
    virtual Placeholder*            asPlaceholder() const { return (PlaceholderConstant*)this; }
    virtual PlaceholderConstant*    asPlaceholderConstant() const { return (PlaceholderConstant*)this; }
    virtual void                    getValue(void* dest) const { o_exception_no_implementation(); }
    virtual Type*                   getValueType() const { return m_pType; }
    virtual bool                    hasValue(void* a_pSrc) const { o_exception_no_implementation(); return false; }
    virtual Constant*               clone() const;
    virtual bool                    isZero() const { o_exception_no_implementation(); return false; }
    virtual void                    toString(string& out) const { o_exception_no_implementation(); }
    virtual void                    toLiteral(string& out) const { o_exception_no_implementation(); }

    virtual string getQualifiedDecoratedName() const { return m_strName; }
    virtual string getDecoratedName() const { return m_strName; }
    virtual string getQualifiedName() const { return m_strName; }

    virtual bool                    equals(LanguageElement* a_pOther) const;

protected:
    Type* m_pType;
};

class o_export TemplateDependantArrayType : public ArrayType
{
    o_type;

public:
    TemplateDependantArrayType(Type* a_pType, Expression* a_pSize, PlaceholderConstant* a_pDeductibleConstant)
        : ArrayType(a_pType, 0, o_template_dependant) 
        , m_pItemCountExpression(a_pSize)
        , m_pDeductibleConstant(a_pDeductibleConstant)
    {
        if(!a_pSize->isCompileTime())
        {
            setInvalid();
        }
    }

    virtual bool                    isKindOf(Type* a_pType) const { return true; }
    virtual 
        TemplateDependantArrayType* asTemplateDependantArrayType() const { return (TemplateDependantArrayType*)this; }

    virtual string                  getQualifiedDecoratedName() const;
    virtual string                  getDecoratedName() const;
    virtual string                  getQualifiedName() const { return getItemType()->getQualifiedName(); }

    virtual bool                    isCopyable() const { return true; }

    virtual bool                    equals(LanguageElement* a_pOther) const;

    PlaceholderConstant*            getDeductibleConstant() const { return m_pDeductibleConstant; }

    Expression*                     getItemCountExpression() const { return m_pItemCountExpression; }

protected:
    Expression* m_pItemCountExpression;
    PlaceholderConstant* m_pDeductibleConstant;
};

class o_export TemplateDependantTemplateInstance : public ClassType
{
    o_type;

public:
    TemplateDependantTemplateInstance(TemplateSpecialization* a_pTemplateSpecialization, const map<Placeholder*, LanguageElement*>& a_Arguments);
    TemplateDependantTemplateInstance(Template* a_pTemplate, const map<Placeholder*, LanguageElement*>& a_Arguments);
    TemplateDependantTemplateInstance(Template* a_pTemplate, const vector<LanguageElement*>& a_Arguments);

    virtual bool                    isKindOf(Type* a_pType) const { return true; }

    virtual TemplateDependantTemplateInstance* asTemplateDependantTemplateInstance() const { return (TemplateDependantTemplateInstance*)this; }

    Template*                       getTemplate() const { return m_pTemplate; }
    TemplateSpecialization*         getTemplateSpecialization() const { return m_pTemplateSpecialization; }

    map<Placeholder*, LanguageElement*>::const_iterator beginArguments() const { return m_Arguments.begin(); }
    map<Placeholder*, LanguageElement*>::const_iterator endArguments() const { return m_Arguments.end(); }

    LanguageElement*                getArgument(Placeholder* a_pPlaceholder) const;
    size_t                          getArgumentCount() const { return m_Arguments.size(); }

    virtual string                  getQualifiedDecoratedName() const { return m_strName; }
    virtual string                  getDecoratedName() const { return m_strName; }
    virtual string                  getQualifiedName() const { return m_strName; }

    virtual bool                    equals(LanguageElement* a_pOther) const;

protected:
    Template*                       m_pTemplate;
    TemplateSpecialization*         m_pTemplateSpecialization;
    map<Placeholder*, LanguageElement*> m_Arguments;
};

class TemplateDependantElement : public NamedElement
{
    o_language_element;

public:
    TemplateDependantElement(LanguageElement* a_pLeft, const string& a_strName, const vector<LanguageElement*>* a_pTemplateArguments = 0, const vector<LanguageElement*>* a_pFunctionArguments = 0, modifiers_t modifiers = 0)
        : NamedElement(a_strName, modifiers|o_template_dependant)
        , m_pLeft(a_pLeft)
        , m_pAsType(nullptr) 
        , m_pTemplateArguments(a_pTemplateArguments ? new vector<LanguageElement*>(*a_pTemplateArguments) : nullptr)
        , m_pFunctionArguments(a_pFunctionArguments ? new vector<LanguageElement*>(*a_pFunctionArguments) : nullptr)
    {

    }

    ~TemplateDependantElement() { delete m_pTemplateArguments; delete m_pFunctionArguments; }

    virtual Type*               asType() const;
    virtual Expression*         asExpression() const;

    LanguageElement*            getLeft() const { return m_pLeft; }

    virtual string getQualifiedDecoratedName() const { return m_strName; }
    virtual string getDecoratedName() const { return m_strName; }
    virtual string getQualifiedName() const { return m_strName; }

    vector<LanguageElement*>* getTemplateArguments() const { return m_pTemplateArguments; }
    vector<LanguageElement*>* getFunctionArguments() const { return m_pFunctionArguments; }

protected:
    mutable Type* m_pAsType;
    LanguageElement* m_pLeft;
    vector<LanguageElement*>* m_pTemplateArguments;
    vector<LanguageElement*>* m_pFunctionArguments;
};


/// example : typename boost::unsigned_type<t_Ty>::type 
class o_export TemplateDependantType : public Type
{
    o_type;

public:
    TemplateDependantType()
        : Type(e_template_dependant, "", 0, 0, 0) 
    {
    }
    TemplateDependantType(TemplateDependantElement* a_pElement)
        : Type(e_template_dependant, a_pElement->getName(), 0, 0, a_pElement->getModifiers()) 
    {
    }

    virtual bool                    isKindOf(Type* a_pType) const { return true; }

    virtual TemplateDependantType*  asTemplateDependantType() const { return (TemplateDependantType*)this; }

    virtual string getQualifiedDecoratedName() const { return m_strName; }
    virtual string getDecoratedName() const { return m_strName; }
    virtual string getQualifiedName() const { return m_strName; }

};

/// example : boost::is_abstract<t_Ty>::value
class o_export TemplateDependantExpression : public Expression
{
    o_language_element;

public:
    TemplateDependantExpression(TemplateDependantElement* a_pElement);

    virtual TemplateDependantExpression*  asTemplateDependantExpression() const { return (TemplateDependantExpression*)this; }
    
    virtual void internalEval(void* a_pDest) const 
    {
        o_exception_no_implementation();
    }

    virtual TemplateDependantExpression* clone() const { o_assert_no_implementation(); return nullptr; }

protected:
    string m_strName;
};

class o_export TemplateDependantDotExpression : public Expression
{
    o_language_element;

public:
    TemplateDependantDotExpression(Expression* a_pElement, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<Expression*>* a_pArguments = nullptr);

    virtual TemplateDependantDotExpression*  asTemplateDependantDotExpression() const { return (TemplateDependantDotExpression*)this; }

    virtual void internalEval(void* a_pDest) const 
    {
        o_exception_no_implementation();
    }

    virtual TemplateDependantDotExpression* clone() const { o_assert_no_implementation(); return nullptr; }

protected:
    string m_strName;
    vector<LanguageElement*>* m_pTemplate;
    vector<Expression*>* m_pArguments;
};

o_namespace_end(phantom, reflection)



#endif
