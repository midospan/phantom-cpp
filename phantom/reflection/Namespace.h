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

#ifndef o_phantom_reflection_Namespace_h__
#define o_phantom_reflection_Namespace_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/LanguageElement.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Namespace.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */


o_h_begin

class o_export Namespace : public LanguageElement
{
public:
    typedef map<string, Type*>  typedef_map;
    typedef map<string, Namespace*> namespace_alias_map;
    typedef vector<Namespace*>  namespace_container;
    typedef vector<Function*>   function_container;
    typedef vector<Type*>       type_container;
    typedef vector<Template*>   template_container;

    o_friend(class, phantom, Phantom)

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    Namespace(void);
    Namespace(const string& a_strName);
    o_destructor ~Namespace(void);


    /** @name Signals
     *
     */
    //@{
protected:
    o_signal_data(typeAdded, Type*)
    o_signal_data(typeRemoved, Type*)
    o_signal_data(namespaceAdded, Namespace*)
    o_signal_data(namespaceRemoved, Namespace*)
    o_signal_data(templateAdded, Template*)
    o_signal_data(templateRemoved, Template*)
    //@}

public:
    virtual Namespace*  asNamespace() const { return (Namespace*)this; }
    void                addType(Type* a_pType);
    void                addTemplate(Template* a_pTemplate);
    void                removeTemplate( Template* a_pTemplate );
    void                addNamespace(Namespace* a_pNamespace);
    void                removeType(Type* a_pType);
    void                removeNamespace(Namespace* a_pNamespace);
    void                getHierarchicalName(string* a_OutString);
    void                getHierarchicalNameNoRoot(string* a_OutString);

    Type*               getType( uint index ) const {return m_Types[index]; }
    Type*               getType( const string& a_strName ) const;
    void                getAllTypesCascade( const string& a_strName, vector<Type*>& a_Out ) const;
	Type*               getTypeByGuid( uint a_uiGuid ) const;
	Type*               getTypeByGuidCascade( uint a_uiGuid ) const;
    uint                getTypeCount() const {return m_Types.size(); }

    PrimitiveType*      getPrimitiveType(const string& a_strName) const;
    Class*              getPolymorphicType(const string& a_strName) const;
    Class*              getPolymorphicType(uint index) const;
    uint                getPolymorphicTypeCount() const;

    Template*           getTemplate( const string& a_strName ) const ;

    Namespace*          findTypeNamespace(Type* a_pType) const;


    Namespace*          getRootNamespace() const;
    Namespace*          getNamespace(const string& a_strName) const;
    Namespace*          getNamespaceCascade(list<string>* a_HierarchyWords) const;
    Namespace*          getNamespaceCascade(const string& qualifiedName) const;
    o_forceinline
    Namespace*          getParentNamespace() const { return static_cast<Namespace*>(m_pOwner); }
    Namespace*          findOrCreateNamespaceCascade(const string& a_strNamespaceName);
    Namespace*          findOrCreateNamespaceCascade(list<string>* a_HierarchyWords);

    Namespace*          getNamespace(uint i) const { return m_Namespaces[i]; }
    uint                getNamespaceCount() const { return m_Namespaces.size(); }

    void                destroyAllCascade();
    void                destroyAllNamespaceCascade();

    boolean             searchAndDestroy(Type* a_pType);
    boolean             searchAndDestroyCascade(Type* a_pType);

    boolean             searchAndDestroy(Namespace* a_pNamespace);
    boolean             searchAndDestroyCascade(Namespace* a_pNamespace);

    boolean             searchAndRemove(Type* a_pType);
    boolean             searchAndRemoveCascade(Type* a_pType);

    void                removeAllTypeCascade();

    void                addTypedef( const string& a_strTypedef, Type* a_pType );

    void                removeTypedef( const string& a_strTypedef, Type* a_pType );

    inline Type*        getTypedef(const string& a_strTypedef) const;

    void                addNamespaceAlias( const string& a_strAlias, Namespace* a_pNamespace );

    void                removeNamespaceAlias( const string& a_strAlias, Namespace* a_pNamespace );

    inline Namespace*   getNamespaceAlias(const string& a_strAlias) const;

    DataPointerType*    getDataPointerType(Type* a_pPointedType) const;
    ReferenceType*      getReferenceType(Type* a_pPointedType) const;
    Type*               getConstType(Type* a_pPointedType) const;
    ArrayType*          getArrayType(Type* a_pPointedType, size_t a_uiCount) const;
    virtual
    LanguageElement*    getElement(
        const char* a_strQualifiedName
        , template_specialization const*
        , function_signature const*
        , bitfield a_Modifiers = 0) const;

    virtual void    getElements(vector<LanguageElement*>& out, Class* a_pClass = nullptr) const;

protected:
    void                setParentNamespace(Namespace* a_pNamespace) { m_pOwner = a_pNamespace; }
    Class*              polymorphicArrayClassOf(Class* a_pType, uint a_uiArrayLevel = 1) ;
    Type*               pointerTypeOf(Type* a_pType, uint a_uiPointerLevel = 1) ;
    Type*               referenceTypeOf(Type* a_pType, uint a_uiPointerLevel = 1) ;
    Type*               constTypeOf(Type* a_pType);
    Type*               arrayTypeOf(Type* a_pType, size_t a_uiCount);
    
    virtual void        teardownMetaDataCascade(size_t count)
    {
        {
            type_container::const_iterator it = m_Types.begin();
            type_container::const_iterator end = m_Types.end();
            for(;it != end; ++it)
            {
                (*it)->teardownMetaDataCascade(count);
            }
        }
        {
            namespace_container::const_iterator it = m_Namespaces.begin();
            namespace_container::const_iterator end = m_Namespaces.end();
            for(;it != end; ++it)
            {
                (*it)->teardownMetaDataCascade(count);
            }
        }
        {
            function_container::const_iterator it = m_Functions.begin();
            function_container::const_iterator end = m_Functions.end();
            for(;it != end; ++it)
            {
                (*it)->teardownMetaDataCascade(count);
            }
        }
        LanguageElement::teardownMetaDataCascade(count);
    }

protected:
    namespace_container m_Namespaces;
    mutable
    function_container  m_Functions;
    type_container      m_Types;
    template_container  m_Templates;
    typedef_map         m_Typedefs;
    namespace_alias_map m_NamespaceAliases;

private:
    friend phantom::reflection::DataPointerType*         phantom::pointerTypeOf(phantom::reflection::Type* a_pType);
    friend phantom::reflection::ReferenceType*           phantom::referenceTypeOf(phantom::reflection::Type* a_pType);
    friend phantom::reflection::Type*                    phantom::constTypeOf(phantom::reflection::Type* a_pType);
    friend phantom::reflection::ArrayType*               phantom::arrayTypeOf(phantom::reflection::Type* a_pType,size_t);
    void release(vector<Type*>& out_types);
};

inline Type* Namespace::getTypedef( const string& a_strTypedef ) const
{
    auto found = m_Typedefs.find(a_strTypedef);
    if( found != m_Typedefs.end() ) return found->second;
    return nullptr;
}

inline Namespace* Namespace::getNamespaceAlias( const string& a_strAlias ) const
{
    auto found = m_NamespaceAliases.find(a_strAlias);
    if( found != m_NamespaceAliases.end() ) return found->second;
    return nullptr;
}

o_h_end


#else // o_phantom_reflection_Namespace_h__
#include "Namespace.classdef.h"
#endif
