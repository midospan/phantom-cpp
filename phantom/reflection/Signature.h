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

#ifndef o_phantom_reflection_Signature_h__
#define o_phantom_reflection_Signature_h__



/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Signature.classdef.h"
/* **************** Declarations ***************** */
o_declare(class, phantom, reflection, Type)
o_declare(class, phantom, reflection, TemplateSpecialization)
/* *********************************************** */

o_h_begin

class o_export Signature : public LanguageElement
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:

    enum EState
    {
        eState_Virgin = 0,
        eState_UnderConstruction,
        eState_Final,
    };

    struct ElementParsingInfo
    {
        ElementParsingInfo()
            : m_pType(NULL)
            , m_uiPointingLevel(0)
        {

        }
        ElementParsingInfo(Type* a_pType)
            : m_pType(a_pType)
            , m_uiPointingLevel(0)
        {

        }
        enum EProperties
        {
            eConst = 0,
            eReference,
        };
        Type*                m_pType;
        uint                m_uiPointingLevel;
        flags<EProperties>    m_Properties;
    };

    typedef phantom::vector<Type*> parameter_type_list;

    Signature( void )
        : m_pReturnType(NULL)
        , m_uiArgumentStorageSize(0)
    {
    }
    o_destructor ~Signature(void);

    boolean         equals(Object* other) const
    {
        if(NOT(phantom::is<Signature>(other))) return false;
        Signature*    pOther = static_cast<Signature*>(other);
        if(NOT(compareParameterList(pOther))) return false;
        return m_pReturnType == pOther->m_pReturnType;
    }

    virtual Signature*  clone() const 
    {
        Signature* pSignature = o_new(Signature);
        o_foreach(Type* pParameterType, m_ParametersTypes)
        {
            pSignature->addParameterType(pParameterType);
        }
        pSignature->setReturnType(m_pReturnType);
        return pSignature;
    }

    void            parse( const string& a_strSignature, TemplateSpecialization* a_pTemplateSpecialization = NULL, LanguageElement* pScope = (LanguageElement*)phantom::rootNamespace() );

    uint            getParameterCount() const;
    void            addParameterType(Type* a_pParameterType);
    Type*           getParameterType(uint a_uiParamIndex) const;
    void            setReturnType(Type* a_pType);
    Type*           getReturnType() const;

    virtual string  getQualifiedName() const;
    virtual string  getDecoratedName() const;
    virtual string  getQualifiedDecoratedName() const;

    boolean         matches(function_signature const* a_FunctionSignature) const;
    boolean         compareParameterList( Signature* a_pOther ) const { return matches(&a_pOther->m_ParametersTypes); }
    
protected:
    static boolean  SeparateParameterTypes(const string& a_strText, TemplateSpecialization* a_pTemplateSpecialization, function_signature& a_OutParameterTypes, LanguageElement* a_pScope);
    static boolean  ParseParameterTypeList(const string& a_strText, TemplateSpecialization* a_pTemplateSpecialization, function_signature& a_OutParameterTypes, LanguageElement* a_pScope);

    void updateName();

protected:
    Type*               m_pReturnType;
    function_signature  m_ParametersTypes;
    size_t              m_uiArgumentStorageSize;
};

o_h_end


#else // o_phantom_reflection_Signature_h__
#include "Signature.classdef.h"
#endif
