/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_LanguageElement_h__
#define o_phantom_reflection_LanguageElement_h__




/* ****************** Includes ******************* */
#include <phantom/reflection/Location.h>
#include <phantom/reflection/LanguageElementVisitor.h>
#include <phantom/reflection/Language.h>
#include <phantom/reflection/Precompiler.h>
#include <phantom/reflection/Compiler.h>
#include <phantom/reflection/Shaman.h>
/* **************** Declarations ***************** */
/* *********************************************** */


o_namespace_begin(phantom, reflection)

class Source;

#define o_language_element o_custom_language_element(phantom::reflection::LanguageElementVisitor, phantom::reflection::Language)

#define o_custom_language_element(Visitor_, Language_)\
    public:\
    friend class Visitor_;\
    friend class Language_;\
    virtual void visit(phantom::reflection::LanguageElementVisitor* a_pVisitor, visitor_data a_Data) \
    { static_cast<Visitor_*>(a_pVisitor)->visit(this, a_Data); }\
    private:

#define o_invalid_decl(class_)\
    public:\
    static class_* Invalid()      ; \
    private:\

#define o_invalid_def(class_, ...)\
    class_* class_::Invalid()                                                           \
{                                                                                   \
    static class_* instance = static_cast<class_*>(application()->invalid(o_new(class_)(__VA_ARGS__)));   \
    return instance;                                                                \
}      

#define o_invalid_custom_def(class_, newclass_, ...)\
    class_* class_::Invalid()                                                           \
{                                                                                   \
    static class_* instance = static_cast<class_*>(application()->invalid(o_new(newclass_)(__VA_ARGS__)));   \
    return instance;                                                                \
}     

class o_export LanguageElement
{
    o_language_element;

    o_invalid_decl(LanguageElement);

    friend class phantom::reflection::ClassType;
    friend class phantom::reflection::Class;
    friend class phantom::reflection::Scope;
    friend class phantom::reflection::TemplateSpecialization;
    friend class phantom::reflection::Module;
    friend class phantom::reflection::Application;
    friend class phantom::reflection::Source;
    friend class phantom::reflection::Namespace;
    friend class phantom::reflection::NamedElement;

public:
    LanguageElement();
    ~LanguageElement();

    o_terminate();

public:
    vector<LanguageElement*>::const_iterator beginElements() const;
    vector<LanguageElement*>::const_iterator endElements() const;

    vector<LanguageElement*>::const_iterator beginReferencedElements() const;
    vector<LanguageElement*>::const_iterator endReferencedElements() const;

    vector<LanguageElement*>::const_iterator beginReferencingElements() const;
    vector<LanguageElement*>::const_iterator endReferencingElements() const;

    size_t getReferencingElementCount() const { return m_pReferencingElements ? m_pReferencingElements->size() : 0; }

    virtual TemplateSpecialization*     getAscendantTemplateSpecialization() const 
    { 
        TemplateSpecialization* pOwnerSpec = m_pOwner ? m_pOwner->asTemplateSpecialization() : nullptr;
        return pOwnerSpec ? pOwnerSpec : nullptr; 
    }

    bool                                isTemplateElement() const;

    bool                                hasReferencedElement(LanguageElement* a_pLanguageElement) const;
    bool                                hasReferencingElement(LanguageElement* a_pLanguageElement) const;
    virtual bool                        isTemplateDependant() const;

    virtual Type*                       asAddressType() const { return nullptr; }
    virtual Alias*                      asAlias() const { return nullptr; }
    virtual AnonymousSection*           asAnonymousSection() const { return nullptr; }
    virtual AnonymousStruct*            asAnonymousStruct() const { return nullptr; }
    virtual AnonymousUnion*             asAnonymousUnion() const { return nullptr; }
    virtual PrimitiveType*              asArithmeticType() const { return nullptr; }
    virtual ArrayType*                  asArrayType() const { return nullptr; }
    virtual Block*                      asBlock() const  { return nullptr; }
    virtual Callable*                   asCallable() const { return nullptr; }
    virtual Class*                      asClass() const { return nullptr; }
    virtual DataPointerType*            asClassDataPointerType() const { return nullptr; }
    virtual LValueReferenceType*        asClassLValueReferenceType() const { return nullptr; }
    virtual RValueReferenceType*        asClassRValueReferenceType() const { return nullptr; }
    virtual Type*                       asClassAddressType() const { return nullptr; }
    virtual ClassType*                  asClassType() const { return nullptr; }
    virtual Constant*                   asConstant() const { return nullptr; }
    virtual ConstantExpression*         asConstantExpression() const { return nullptr; }
    virtual ConstType*                  asConstClass() const { return nullptr; }
    virtual DataPointerType*            asConstClassDataPointerType() const { return nullptr; }
    virtual LValueReferenceType*        asConstClassLValueReferenceType() const { return nullptr; }
    virtual RValueReferenceType*        asConstClassRValueReferenceType() const { return nullptr; }
    virtual Type*                       asConstClassAddressType() const { return nullptr; }
    virtual Constructor*                asConstructor() const { return nullptr; }
    virtual ConstType*                  asConstType() const { return nullptr; }
    ReferenceType*                      asConstReferenceType() const;
    virtual ConstVolatileType*          asConstVolatileType() const { return nullptr; }
    virtual ContainerClass*             asContainerClass() const { return nullptr; }
    virtual DataMember*                 asDataMember() const { return nullptr; }
    virtual DataMemberPointerType*      asDataMemberPointerType() const { return nullptr; }
    virtual DataPointerType*            asDataPointerType() const { return nullptr; }
    virtual Ellipsis*                   asEllipsis() const { return nullptr; }
    virtual Enum*                       asEnum() const { return nullptr; }
    virtual Evaluable*                  asEvaluable() const { return nullptr; }
    virtual Event*                      asEvent() const { return nullptr; }
    virtual Expression*                 asExpression() const { return nullptr; }
    virtual PrimitiveType*              asFloatingPointType() const { return nullptr; }
    virtual Function*                   asFunction() const { return nullptr; }
    virtual FunctionPointerType*        asFunctionPointerType() const { return nullptr; }
    virtual PrimitiveType*              asFundamentalType() const { return nullptr; }
    virtual MemberFunction*             asMemberFunction() const { return nullptr; }
    virtual Import*                     asImport() const {return nullptr; }
    virtual PrimitiveType*              asIntegralType() const { return nullptr; }
    virtual LabelStatement*             asLabelStatement() const { return nullptr; }
    LanguageElement*                    asLanguageElement() const { return (LanguageElement*)this; }
    virtual LocalVariable*              asLocalVariable() const { return nullptr; }
    virtual LValueReferenceType*        asLValueReferenceType() const { return nullptr; }
    virtual MapContainerClass*          asMapContainerClass() const { return nullptr; }
    virtual Member*                     asMember() const { return nullptr; }
    virtual MemberAnonymousSection*     asMemberAnonymousSection() const { return nullptr; }
    virtual MemberAnonymousStruct*      asMemberAnonymousStruct() const { return nullptr; }
    virtual MemberAnonymousUnion*       asMemberAnonymousUnion() const { return nullptr; }
    virtual MemberFunctionPointerType*  asMemberFunctionPointerType() const { return nullptr; }
    virtual MemberPointerType*          asMemberPointerType() const { return nullptr; }
    virtual Module*                     asModule() const { return nullptr; }
    virtual NamedElement*               asNamedElement() const { return nullptr; }
    virtual Namespace*                  asNamespace() const { return nullptr; }
    virtual NamespaceAlias*             asNamespaceAlias() const { return nullptr; }
    virtual PrimitiveType*              asNullptrType() const { return nullptr; }
    virtual NumericConstant*            asNumericConstant() const { return nullptr; }
    virtual Package*                    asPackage() const { return nullptr; }
    virtual Parameter*                  asParameter() const { return nullptr; }
    virtual Placeholder*                asPlaceholder() const { return nullptr; }
    virtual Type*                       asPOD() const { return nullptr; }
    virtual PointerType*                asPointerType() const { return nullptr; }
    virtual PrimitiveType*              asPrimitiveType() const { return nullptr; }
    virtual Property*                   asProperty() const { return nullptr; }
    virtual Range*                      asRange() const { return nullptr; }
    virtual ReferenceType*              asReferenceType() const { return nullptr; }
    virtual RValueReferenceType*        asRValueReferenceType() const { return nullptr; }
    virtual Scope*                      asScope() const { return nullptr; }
    virtual SequentialContainerClass*   asSequentialContainerClass() const { return nullptr; }
    virtual SetContainerClass*          asSetContainerClass() const { return nullptr; }
    virtual Signal*                     asSignal() const  { return nullptr; }
    virtual PrimitiveType*              asSignalType() const { return nullptr; }
    virtual Signature*                  asSignature() const { return nullptr; }
    virtual MemberFunction*             asSlot() const  { return nullptr; }
    virtual Source*                     asSource() const { return nullptr; }
    virtual State*                      asState() const { return nullptr; }
    virtual StateMachine*               asStateMachine() const { return nullptr; }
    virtual StateMachineElement*        asStateMachineElement() const { return nullptr; }
    virtual Statement*                  asStatement() const { return nullptr; }
    virtual StaticDataMember*           asStaticDataMember() const  { return nullptr; }
    virtual StaticMemberFunction*       asStaticMemberFunction() const { return nullptr; }
    virtual Structure*                  asStructure() const { return nullptr; }
    virtual Subroutine*                 asSubroutine() const { return nullptr; }
    virtual Track*                      asTrack() const { return nullptr; }
    virtual Template*                   asTemplate() const { return nullptr; }
    virtual TemplateParameter*          asTemplateParameter() const { return nullptr; }
    virtual TemplateSignature*          asTemplateSignature() const { return nullptr; }
    virtual TemplateSpecialization*     asTemplateSpecialization() const { return nullptr; }
    virtual Type*                       asType() const { return nullptr; }
    virtual Union*                      asUnion() const { return nullptr; }
    virtual ValueMember*                asValueMember() const { return nullptr; }
    virtual Variable*                   asVariable() const  { return nullptr; }
    virtual VirtualMemberFunctionTable* asVirtualMemberFunctionTable() const { return nullptr; }
    virtual VolatileType*               asVolatileType() const  { return nullptr; }

    Expression*                         toExpression() const { return toExpression(nullptr); }

    Expression*                         toExpression(Expression* a_pOptExpression) const;

    virtual bool                        hasAccessTo(NamedElement* a_pOther, NamedElement* a_pAccessContext = nullptr) const;
    virtual bool                        hasFriend(LanguageElement* a_pElement) const { return false; }
    bool                                hasElement(LanguageElement* a_pElement) const { return a_pElement->m_pOwner == this; }
    bool                                hasFriendCascade(LanguageElement* a_pElement) const { return hasFriend(a_pElement) OR (m_pOwner AND m_pOwner->hasFriendCascade(a_pElement)); }
    bool                                hasOwnerCascade(LanguageElement* a_pElement) const { return (m_pOwner == a_pElement) OR (m_pOwner AND m_pOwner->hasOwnerCascade(a_pElement)); }
    bool                                hasElementCascade(LanguageElement* a_pElement) const { return hasElement(a_pElement) OR (m_pOwner AND m_pOwner->hasElementCascade(a_pElement)); }

    virtual bool                        isCompileTime() const { return false; }
    bool                                isInvalid() const;
    virtual bool                        isAlwaysValid() const { return isNative(); }
    void                                setInvalid();
    Message*                            error(const char* a_Format, ...);
    Message*                            subError(const char* a_Format, ...);

    virtual bool                        isNative() const;
    virtual bool                        isCustom() const { return false; }

    o_forceinline LanguageElement*      getOwner() const { return m_pOwner; }

    void getElementsCascade(vector<LanguageElement*>& out, Class* a_pClass = nullptr) const;
    void getElements(vector<LanguageElement*>& out, Class* a_pClass = nullptr) const;

    LanguageElement*getElement(size_t a_uiIndex) const
    {
        o_assert(m_pElements);
        return (*m_pElements)[a_uiIndex];
    }
    size_t          getElementCount() const
    {
        return m_pElements ? m_pElements->size() : 0;
    }

    virtual Source* getSource() const { return m_pOwner ? m_pOwner->getSource() : nullptr; }

    Language*       getLanguage() const;

    bool            isInsideTemplate() const { return m_pOwner ? m_pOwner->asTemplate() ? true : m_pOwner->isInsideTemplate() : false; }

    virtual bool    canBeDestroyed() const;

    virtual void    checkCompleteness() const;

    virtual bool    equals(LanguageElement* a_pOther) const;

    virtual LanguageElement* hatch();

    virtual LanguageElement* getHatchedElement() const;

    Statement* getEnclosingStatement() const;

    Block* getEnclosingBlock() const;

    Scope* getEnclosingScope() const;

    Namespace*  getEnclosingNamespace() const;

    virtual Module* getModule() const;

    virtual bool partialAccepts( LanguageElement* a_pLanguageElement, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const;

    void        addReferencedElement(LanguageElement* a_pElement);
    void        removeReferencedElement(LanguageElement* a_pElement);

    void        addScopedElement(LanguageElement* a_pElement);
    void        removeScopedElement(LanguageElement* a_pElement);

    void        fetchReferencedModules( set<Module*>& a_Modules ) const;
    void        fetchReferencingModules( set<Module*>& a_Modules ) const;

    void        fetchReferencedModulesCascade( set<Module*>& a_Modules ) const;
    void        fetchReferencingModulesCascade( set<Module*>& a_Modules ) const;

    void        fetchElements( vector<LanguageElement*>& a_Elements ) const;
    void        fetchElementsCascade( vector<LanguageElement*>& a_Elements ) const;

    void        addElement(LanguageElement* a_pElement);
    void        addNamedElement( NamedElement* a_pElement );
    void        removeElement(LanguageElement* a_pElement);

    string      translate(int a_TranslationType = e_translation_definition, LanguageElement* a_pScope = (LanguageElement*)globalNamespace()) const;
    void        translate(string& out, int a_TranslationType = e_translation_definition, LanguageElement* a_pScope = (LanguageElement*)globalNamespace()) const;

    NamedElement* getUniqueElement(const string& name, modifiers_t modifiers = 0) const;

    size_t      getElementIndex(LanguageElement* a_pElement) const
    {
        if(m_pElements)
        {
            size_t count = m_pElements->size();
            for(size_t i = 0; i<count; ++i)
            {
                if((*m_pElements)[i] == a_pElement) return i;
            }
        }
        return ~size_t(0);
    }

    void        dumpElementList(ostream& out) const;

    void        dumpElementListCascade(ostream& out) const;

    virtual string getQualifiedName() const { return ""; }
    virtual string getDecoratedName() const { return ""; }
    virtual string getQualifiedDecoratedName() const { return ""; }
    virtual string getUniqueName() const { return ""; }
    virtual string getUniqueDecoratedName() const { return ""; }
    virtual Scope* getNamingScope() const { return m_pOwner ? m_pOwner->asScope() : nullptr; }
    bool hasNamingScopeCascade(Scope* a_pScope) const;

protected:
    void setOwner(LanguageElement* a_pOwner);
    void internalAncestorChanged(LanguageElement* a_pOwner);
    virtual void ancestorChanged(LanguageElement* a_pOwner);
    virtual void invalidated();

protected:
    void replaceElement(LanguageElement* a_pOld, LanguageElement* a_pNew);
    void registerReferencingElement(LanguageElement* a_pElement);
    void unregisterReferencingElement(LanguageElement* a_pElement);
    virtual void elementRemoved(LanguageElement* a_pElement);
    virtual void elementInvalidated(LanguageElement* a_pElement);
    virtual void elementDefined(LanguageElement* a_pElement);
    virtual void referencedElementAdded(LanguageElement* a_pElement);
    virtual void referencedElementRemoved(LanguageElement* a_pElement);
    virtual void referencedElementInvalidated(LanguageElement* a_pElement);

protected:
    LanguageElement*            m_pOwner;   /// Owner represents the real container of the element, for example a global function is owned by its source
    vector<LanguageElement*>*   m_pElements;
    vector<LanguageElement*>*   m_pReferencingElements;
    vector<LanguageElement*>*   m_pReferencedElements;
    Message*                    m_pStatusMessage;

private:
    static void Register(LanguageElement*);
    static void Unregister(LanguageElement*);
    static vector<LanguageElement*> sm_Elements;
};

o_namespace_end(phantom, reflection)

#endif
