/*
    This file is part of PHANTOM
         P reprocessed
         H igh-level
         A llocator
         N ested state-machines and
         T emplate
         O riented
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

#ifndef o_phantom_reflection_LanguageElement_h__
#define o_phantom_reflection_LanguageElement_h__




/* ****************** Includes ******************* */
#include "phantom/reflection/Location.h"

/* **************** Declarations ***************** */
/* *********************************************** */


o_namespace_begin(phantom, reflection)

class SourceFile;

class o_export Extension
{
    
};

class o_export LanguageElement
{
    friend class ClassType;
    friend class Class;
	friend class Phantom;
    friend class Module;
    friend class TemplateSpecialization;


public:

    enum
    {
        eNativeFlag_Shared = 0x00000004,
    };

public:
    LanguageElement();
protected:
    LanguageElement(const string& a_strName, bitfield a_Modifiers = 0);
    LanguageElement(const string& a_strName, uint a_uiGuid, bitfield a_Modifiers = 0);

public:
    virtual void deleteNow();
    virtual void terminate();
    ~LanguageElement();

public:

    void                                setModifiers(bitfield a_Flags);
    o_forceinline bitfield              getModifiers() const { return m_Modifiers; }
    o_forceinline boolean               testModifiers(int a_uiModifiers) const { return ((m_Modifiers & a_uiModifiers) == a_uiModifiers); }

    void                                setTemplateSpecialization(TemplateSpecialization* a_pTemplateSpecialization);
    TemplateSpecialization*             getTemplateSpecialization() const { return m_pTemplateSpecialization; }
    Template*                           getTemplate() const;

    virtual bool                        matches(const string& a_strName, const vector<TemplateElement*>* a_TemplateSpecialization = NULL, bitfield a_Modifiers = 0) const;
    virtual bool                        matches(const vector<TemplateElement*>* a_pElements) const;

    o_forceinline void                  setShared()            { m_Modifiers |= o_shared; }
    o_forceinline boolean               isShared() const    { return ((m_Modifiers & o_shared) == o_shared); }

    o_forceinline const string&         getName() const { return m_strName; }
    virtual string                      getQualifiedName() const;
    virtual string                      getDecoratedName() const;
    virtual string                      getQualifiedDecoratedName() const;

	o_forceinline size_t				getGuid() const { return m_uiGuid; }

    virtual PrimitiveType*              asArithmeticType() const { return nullptr; }
    virtual ArrayType*                  asArrayType() const { return nullptr; }
    virtual Block*                      asBlock() const  { return nullptr; }
    virtual Class*                      asClass() const { return nullptr; }
    virtual ClassType*                  asClassType() const { return nullptr; }
    virtual Collection*                 asCollection() const { return nullptr; }
    virtual Constant*                   asConstant() const { return nullptr; }
    virtual Constructor*                asConstructor() const { return nullptr; }
    virtual ConstType*                  asConstType() const { return nullptr; }
    virtual ContainerClass*             asContainerClass() const { return nullptr; }
    virtual DataMember*                 asDataMember() const { return nullptr; }
    virtual DataPointerType*            asDataPointerType() const { return nullptr; }
    virtual Enum*                       asEnum() const { return nullptr; }
    virtual Evaluable*                  asEvaluable() const { return nullptr; }
    virtual state::Event*               asEvent() const { return nullptr; }
    virtual Expression*                 asExpression() const { return nullptr; }
    virtual ClassExtension*             asClassExtension() const { return nullptr; }
    virtual PrimitiveType*              asFloatingPointType() const { return nullptr; }
    virtual Function*                   asFunction() const { return nullptr; }
    virtual PrimitiveType*              asFundamentalType() const { return nullptr; }
    virtual InstanceDataMember*         asInstanceDataMember() const { return nullptr; }
    virtual InstanceMemberFunction*     asInstanceMemberFunction() const { return nullptr; }
    virtual PrimitiveType*              asIntegralType() const { return nullptr; }
    virtual LocalVariable*              asLocalVariable() const { return nullptr; }
    virtual MapContainerClass*          asMapContainerClass() const { return nullptr; }
    virtual MemberFunction*             asMemberFunction() const { return nullptr; }
    virtual Namespace*                  asNamespace() const { return nullptr; }
    virtual PrimitiveType*              asNullptrType() const { return nullptr; }
    virtual NumericConstant*            asNumericConstant() const { return nullptr; }
    virtual Type*                       asPOD() const { return nullptr; }
    virtual PointerType*                asPointerType() const { return nullptr; }
    virtual PrimitiveType*              asPrimitiveType() const { return nullptr; }
    virtual Property*                   asProperty() const { return nullptr; }
    virtual ReferenceType*              asReferenceType() const { return nullptr; }
    virtual SequentialContainerClass*   asSequentialContainerClass() const { return nullptr; }
    virtual SetContainerClass*          asSetContainerClass() const { return nullptr; }
    virtual Signal*                     asSignal() const  { return nullptr; }
    virtual PrimitiveType*              asSignalType() const { return nullptr; }
    virtual Signature*                  asSignature() const { return nullptr; }
    virtual InstanceMemberFunction*     asSlot() const  { return nullptr; }
    virtual state::State*               asState() const { return nullptr; }
    virtual state::StateMachine*        asStateMachine() const { return nullptr; }
    virtual Statement*                  asStatement() const { return nullptr; }
    virtual StaticDataMember*           asStaticDataMember() const  { return nullptr; }
    virtual StaticMemberFunction*       asStaticMemberFunction() const { return nullptr; }
    virtual StaticVariable*             asStaticVariable() const  { return nullptr; }
    virtual Subroutine*                 asSubroutine() const { return nullptr; }
    virtual state::Track*               asTrack() const { return nullptr; }
    virtual Template*                   asTemplate() const { return nullptr; }
    virtual TemplateElement*            asTemplateElement() const { return nullptr; }
    virtual TemplateSpecialization*     asTemplateSpecialization() const { return nullptr; }
    virtual Type*                       asType() const { return nullptr; }
    virtual ValueMember*                asValueMember() const { return nullptr; }
    virtual Variable*                   asVariable() const  { return nullptr; }
    virtual VirtualMemberFunctionTable* asVirtualMemberFunctionTable() const { return nullptr; }

    void                                setInvalid() { m_Modifiers |= o_invalid; }
    bool                                isInvalid() const ;
    virtual bool                        isDeclared() const { return true; }
    virtual bool                        isDefined() const { return true; }
    virtual bool                        isLinked() const { return true; }
    virtual bool                        isMemberPointerType() const { return false; }
    virtual bool                        isFunctionPointerType() const { return false; }
    virtual bool                        isDataMemberPointerType() const { return false; }
    virtual bool                        isMemberFunctionPointerType() const { return false; }
    virtual bool                        isTemplateInstance() const { return m_pTemplateSpecialization != NULL; }
    virtual bool                        isPOD() const { return false; }
    o_forceinline bool                  isStatic() const  { return ((m_Modifiers & o_static) == o_static); }
    o_forceinline bool                  isProtected() const { return ((m_Modifiers & o_protected) == o_protected) ; }
    o_forceinline bool                  isPrivate() const { return (m_Modifiers & (o_protected|o_public)) == 0; }
    o_forceinline bool                  isPublic() const { return ((m_Modifiers & o_public) == o_public); }
    o_forceinline bool                  isUnionAlternative() const { return ((m_Modifiers & o_union_alternative) == o_union_alternative) ; }
    o_forceinline bool                  isComponent() const { return ((m_Modifiers & o_component) == o_component) ; }
    o_forceinline bool                  isOwner() const { return ((m_Modifiers & o_owner) == o_owner) ; }
    o_forceinline bool                  isAbstract() const { return ((m_Modifiers & o_abstract) == o_abstract); }
    o_forceinline bool                  isSingleton() const { return ((m_Modifiers & o_singleton) == o_singleton); }    
    o_forceinline bool                  isVirtual() const { return ((m_Modifiers & o_virtual) == o_virtual); }
    o_forceinline bool                  isConst() const { return ((m_Modifiers & o_const) == o_const); }

    virtual boolean                     isNative() const;
   

    virtual boolean                     isCustom() const { return false; }

    o_forceinline LanguageElement*      getOwner() const { return m_pOwner; }
	
    virtual LanguageElement*            solveElement(
                                            const string& a_strName
                                            , const vector<TemplateElement*>*
                                            , const vector<LanguageElement*>*
                                            , bitfield a_Modifiers = 0) const;

    virtual Expression*                 solveOperator(const string& a_strOp, const vector<Expression*>& a_Expressions, bitfield a_Modifiers) const 
    { 
        return nullptr; 
    }

    void getElementsCascade(vector<LanguageElement*>& out, Class* a_pClass = nullptr) const;
    void getElements(vector<LanguageElement*>& out, Class* a_pClass = nullptr) const;

    virtual LanguageElement* getLeafElementAt(const CodePosition& a_Position) const;
    virtual void getAccessibleElementsAt(const CodePosition& a_Position, vector<LanguageElement*>& a_Elements) const;
    
    void addCodeLocation(const CodeLocation& a_Location); // Generally only one (except for namespaces)
    void removeCodeLocation(const CodeLocation& a_Location);

    void addDeclarationCodeLocation(const CodeLocation& a_Location);
    void removeDeclarationCodeLocation(const CodeLocation& a_Location);

    void addReferenceCodeLocation(const CodeLocation& a_Location);
    void removeReferenceCodeLocation(const CodeLocation& a_Location);

    const CodeLocation& getCodeLocation() const 
    { 
        return getCodeLocation(0);
    }

    void setCodeLocation(const CodeLocation& a_Location)
    {
        if(m_CodeLocations == nullptr) addCodeLocation(a_Location);
        else (*m_CodeLocations)[0] = a_Location;
    }

    const CodeLocation& getCodeLocation(size_t index) const;

    bool containsCodePosition(const CodePosition& position) const;
    
    void            setMetaDataValue(size_t index, const string& value);

    const string&   getMetaDataValue(size_t index) const;

    void            teardownMetaDataCascade(size_t count);

    LanguageElement*getElement(size_t a_uiIndex) const 
    { 
        o_assert(m_pElements);
        return (*m_pElements)[a_uiIndex];
    }
    size_t          getElementCount() const 
    { 
        return m_pElements ? m_pElements->size() : 0;
    }

    Module*         getModule() const { return m_pModule; }

    virtual bool    canBeDestroyed() const;

    virtual void    checkCompleteness() const;

    virtual bool    equals(LanguageElement* a_pOther) const { return this == a_pOther; }

    virtual variant compile(Compiler* a_pCompiler);

    virtual LanguageElement* hatch() { return this; }

    Extension*  getExtension() const { return m_pExtension; }

    void        setExtension(Extension* a_pExtension) { m_pExtension = a_pExtension; }

    void        setLanguage(Language* a_pLanguage) { o_assert(a_pLanguage); m_pLanguage = a_pLanguage; }
    Language*   getLanguage() const { return m_pLanguage; }

    virtual Block* getBlock() const;

protected:
    void setGuid(uint a_uiGuid);
    void setName(const string& a_strName) { m_strName = a_strName; }
    void setOwner(LanguageElement* a_pOwner);
    void internalAncestorChanged(LanguageElement* a_pOwner);
    virtual void ancestorChanged(LanguageElement* a_pOwner);

protected:
    void setModule(Module* a_pModule);
    virtual void moduleChanged(Module* a_pModule);
    void setupMetaData(size_t count);
    void addElement(LanguageElement* a_pElement);
    void removeElement(LanguageElement* a_pElement);
    void addReferencedElement(LanguageElement* a_pElement);
    void removeReferencedElement(LanguageElement* a_pElement);
    void registerReferencingElement(LanguageElement* a_pElement);
    void unregisterReferencingElement(LanguageElement* a_pElement);
    virtual void elementAdded(LanguageElement* a_pElement);
    virtual void elementRemoved(LanguageElement* a_pElement);
    virtual void referencedElementAdded(LanguageElement* a_pElement);
    virtual void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    string                      m_strName;
    Language*                   m_pLanguage;
    vector<LanguageElement*>*   m_pElements;
    vector<LanguageElement*>*   m_pReferencingElements;
    vector<LanguageElement*>*   m_pReferencedElements;
    vector<CodeLocation>*       m_DeclarationCodeLocations;
    vector<CodeLocation>*       m_ReferenceCodeLocations;
    vector<CodeLocation>*       m_CodeLocations;
    LanguageElement*            m_pOwner;
    Extension*                  m_pExtension;
    TemplateSpecialization*     m_pTemplateSpecialization;
    uint                        m_uiGuid;
    bitfield                    m_Modifiers;
    mutable string*             m_pMetaData;
    Module*                     m_pModule;

};

o_namespace_end(phantom, reflection)

//#include "LanguageElement.hxx"

#endif
