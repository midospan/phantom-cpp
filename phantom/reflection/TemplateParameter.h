

#ifndef o_reflection_TemplateParameter_h__
#define o_reflection_TemplateParameter_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
#include <phantom/reflection/LanguageElement.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), TemplateParameter);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export TemplateParameter : public NamedElement
{
    o_language_element;

    o_declare_meta_type(TemplateParameter);

public:
    TemplateParameter();
    TemplateParameter(Placeholder* a_pPlaceholder, LanguageElement* a_pDefaultArgument = nullptr, modifiers_t modifiers = 0);
	~TemplateParameter(void) 	{}

    virtual TemplateParameter*  asTemplateParameter() const { return (TemplateParameter*)this; }

    size_t getIndex() const;

    virtual TemplateParameter* clone() const;

    Template* getTemplate() const { return m_pOwner ? m_pOwner->asTemplate() : nullptr; }

    LanguageElement* getDefaultArgument() const { return m_pDefaultArgument; }

    void setDefaultArgument( LanguageElement* a_pElement );

    Placeholder* getPlaceholder() const { return m_pPlaceholder; }

    virtual bool            partialAccepts(LanguageElement* a_pLanguageElement, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions) const;

    bool acceptsArgument(LanguageElement* a_pLanguageElement) const;

    virtual string getQualifiedDecoratedName() const { return m_strName; }
    virtual string getDecoratedName() const { return m_strName; }
    virtual string getQualifiedName() const { return m_strName; }

    virtual bool        equals(LanguageElement* a_pLanguageElement) const 
    {
        TemplateParameter* pTP = a_pLanguageElement->asTemplateParameter();
        return pTP AND equals(pTP);
    }

    bool                equals(TemplateParameter* a_pOther) const;

protected:
    void elementRemoved( LanguageElement* a_pElement );
    void referencedElementRemoved( LanguageElement* a_pElement );

protected:
    Placeholder*     m_pPlaceholder;
    LanguageElement* m_pDefaultArgument;
};

o_namespace_end(phantom, reflection)
    
#endif