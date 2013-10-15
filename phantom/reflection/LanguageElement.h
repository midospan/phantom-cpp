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
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "LanguageElement.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */


o_h_begin

class SourceFile;

class o_export LanguageElement : public Object
{
    friend class ClassType;
    friend class Class;
	friend class Phantom;

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:

    enum
    {
        eNativeFlag_Shared = 0x00000004,
    };

protected:
    LanguageElement();
    LanguageElement(const string& a_strName, bitfield a_bfModifiers = bitfield());
    LanguageElement(const string& a_strName, uint a_uiGuid, bitfield a_bfModifiers = bitfield());

public:
    ~LanguageElement();

public:

    void                                setModifiers(uint a_Flags);
    o_forceinline bitfield              getModifiers() const { return m_bfModifiers; }
    o_forceinline boolean               testModifiers(uint a_uiModifiers) const { return m_bfModifiers.matchesMask(a_uiModifiers); }

    o_forceinline void                  setShared()            { m_bfModifiers.setMask(o_shared); }
    o_forceinline boolean               isShared() const    { return m_bfModifiers.matchesMask(o_shared); }

    o_forceinline const string&         getName() const { return m_strName; }
    virtual string                      getQualifiedName() const;
    virtual string                      getDecoratedName() const { return getName(); }
    virtual string                      getQualifiedDecoratedName() const { return getQualifiedName(); }

	o_forceinline size_t				getGuid() const { return m_uiGuid; }

    // Util methods to get the type of element
    boolean                             isClass() const { return asClass() != nullptr; }
    boolean                             isClassType() const { return asClassType() != nullptr; }
    virtual boolean                     isArithmeticType() const { return false; }
    virtual boolean                     isIntegralType() const { return false; }
    virtual boolean                     isMemberPointerType() const { return false; }
    virtual boolean                     isFunctionPointerType() const { return false; }
            boolean                     isPrimitiveType() const { return asPrimitiveType() != nullptr; }
    virtual boolean                     isReferenceType() const { return false; }
    virtual boolean                     isAttributePointerType() const { return false; }
    virtual boolean                     isMethodPointerType() const { return false; }
    virtual boolean                     isDataPointerType() const { return false; }
    virtual boolean                     isPointerType() const { return false; }
    virtual boolean                     isFunction() const { return false; }
    virtual boolean                     isMember() const { return false; }
    virtual boolean                     isNamespace() const { return false; }
    virtual boolean                     isMethod() const { return false; }
    virtual boolean                     isInstanceMethod() const { return false; }
    virtual boolean                     isStaticMethod() const { return false; }
    virtual boolean                     isSignal() const { return false; }
    virtual boolean                     isSlot() const { return false; }
    virtual boolean                     isAttribute() const { return false; }
    virtual boolean                     isInstanceAttribute() const { return false; }
    virtual boolean                     isProperty() const { return false; }
    virtual boolean                     isAccessor() const { return false; }
    virtual boolean                     isConstructor() const { return false; }
    virtual boolean                     isExtension() const { return false; }
    virtual boolean                     isConstType() const { return false; }
    virtual boolean                     isArrayType() const { return false; }
    virtual boolean                     isEnum() const { return false; }
    virtual boolean                     isPOD() const { return false; }

    virtual Method*                     asMethod() const { return nullptr; }
    virtual Enum*                       asEnum() const { return nullptr; }
    virtual Type*                       asType() const { return nullptr; }
    virtual ClassType*                  asClassType() const { return nullptr; }
    virtual ReferenceType*              asReferenceType() const { return nullptr; }
    virtual Class*                      asClass() const { return nullptr; }
    virtual ContainerClass*             asContainerClass() const { return nullptr; }
    virtual PrimitiveType*              asPrimitiveType() const { return nullptr; }
    virtual DataPointerType*            asDataPointerType() const { return nullptr; }
    virtual Subroutine*                 asSubroutine() const { return nullptr; }
    virtual InstanceMethod*             asInstanceMethod() const { return nullptr; }
    virtual StaticMethod*               asStaticMethod() const { return nullptr; }
    virtual InstanceAttribute*          asInstanceAttribute() const { return nullptr; }
    virtual StaticAttribute*            asStaticAttribute() const  { return nullptr; }
    virtual Signal*                     asSignal() const  { return nullptr; }
    virtual InstanceMethod*             asSlot() const  { return nullptr; }
    virtual Namespace*                  asNamespace() const { return nullptr; }

    o_forceinline boolean               isStatic() const  { return m_bfModifiers.matchesMask(o_static); }
    o_forceinline boolean               isPublic() const { return m_bfModifiers.matchesMask(o_public); }
    o_forceinline boolean               isProtected() const { return m_bfModifiers.matchesMask(o_protected) ; }
    o_forceinline boolean               isPrivate() const { return NOT(m_bfModifiers.matchesOneOfMask(o_protected|o_public)); }
    o_forceinline boolean               isUnionAlternative() const { return m_bfModifiers.matchesMask(o_union_alternative) ; }
    o_forceinline boolean               isComponent() const { return m_bfModifiers.matchesMask(o_component) ; }
    o_forceinline boolean               isOwner() const { return m_bfModifiers.matchesMask(o_owner) ; }
    o_forceinline boolean               isAbstract() const { return m_bfModifiers.matchesMask(o_abstract); }

    virtual boolean                     isNative() const { return false ; }
    virtual boolean                     isRuntime() const { return false; }
    
    virtual boolean                     isCustom() const { return false; }

    o_forceinline LanguageElement*      getOwner() const { return m_pOwner; }
	
    virtual Class*                      getSortingCategoryClass() const;

    virtual LanguageElement*            getElement(
                                            const char* a_strQualifiedName
                                            , template_specialization const*
                                            , function_signature const*
                                            , bitfield a_bfModifiers = bitfield()) const;

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

    const CodeLocation& getCodeLocation(size_t index) const;

    bool containsCodePosition(const CodePosition& position) const;
    
    void            setMetaDataValue(size_t index, const string& value);

    const string&   getMetaDataValue(size_t index) const;

    virtual void    teardownMetaDataCascade(size_t count);

    LanguageElement*getElement(size_t a_uiIndex) const 
    { 
        o_assert(m_pElements);
        return (*m_pElements)[a_uiIndex];
    }
    size_t          getElementCount() const 
    { 
        return m_pElements ? m_pElements->size() : 0;
    }

protected:
    void setupMetaData(size_t count);
    void addElement(LanguageElement* a_pElement);
    void removeElement(LanguageElement* a_pElement);
    void setGuid(uint a_uiGuid);

protected:
    string              m_strName;
    vector<LanguageElement*>* m_pElements;
    vector<CodeLocation>*   m_DeclarationCodeLocations;
    vector<CodeLocation>*   m_ReferenceCodeLocations;
    vector<CodeLocation>*   m_CodeLocations;
    uint                m_uiGuid;
    LanguageElement*    m_pOwner;
    bitfield            m_bfModifiers;
    mutable string*     m_pMetaData;

};

// Check if the trait 'has_virtual_destructor_cascade' works well
BOOST_STATIC_ASSERT(has_virtual_destructor_cascade<LanguageElement>::value);

o_h_end


#else // o_phantom_reflection_LanguageElement_h__
#include "LanguageElement.classdef.h"
#endif
