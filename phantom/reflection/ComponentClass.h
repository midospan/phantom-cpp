#ifndef ComponentClass_h__
#define ComponentClass_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), ComponentClass);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ComponentClass : public Class
{
    o_declare_meta_type(ComponentClass);

public:
    ComponentClass(Class* a_pPointedClass, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : Class(a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
        , m_pPointedClass(a_pPointedClass) 
    {
    }

    virtual void        blockSignals(void* a_pComponent) const = 0;

    virtual void        unblockSignals(void* a_pComponent) const = 0;

    virtual void*       owner(const void* a_pComponent) const = 0;

    virtual void        set(void* a_pComponent, const void* a_pSrc) const = 0;

    virtual void        get(const void* a_pComponent, void* a_pDest) const = 0;
    
    Class*              getPointedClass() const { return m_pPointedClass; }

    virtual ComponentClass* asComponentClass() const { return const_cast<ComponentClass*>(this); }

    virtual Signal*     getAboutToBeChangedSignal() const = 0;
    virtual Signal*     getChangedSignal() const = 0;
    
    virtual bool referencesData( const void* a_pContainer, const phantom::data& a_Data ) const;

    virtual Expression* solveExpression( Expression* a_pLeftExpression , const string& a_strName , const vector<TemplateElement*>* a_pTS, const vector<LanguageElement*>* a_pFS, modifiers_t a_Modifiers ) const;

    virtual void fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const;

protected:
    Class*   m_pPointedClass;

};

o_namespace_end(phantom, reflection)

#endif
