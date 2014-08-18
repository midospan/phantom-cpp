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


/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Signature : public LanguageElement
{

public:
    static Signature* Create( void );
    static Signature* Create( const char* a_pText, TemplateSpecialization* a_pTemplateSpecialization, LanguageElement* a_pScope );
    
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

    Signature( void );
    Signature( Type* a_pType );
    Signature( const string& a_strSignature, TemplateSpecialization* a_pTemplateSpecialization = NULL, LanguageElement* a_pScope = (LanguageElement*)phantom::rootNamespace() );
    o_destructor ~Signature(void);

    virtual Signature* asSignature() const { return (Signature*)this; }

    virtual bool         equals(LanguageElement* a_pOther) const;

    virtual Signature*  clone() const;

    void            parse( const string& a_strSignature, TemplateSpecialization* a_pTemplateSpecialization = NULL, LanguageElement* a_pScope = (LanguageElement*)phantom::rootNamespace() );

    size_t          getParameterCount() const;
    void            addParameterType(Type* a_pParameterType);
    Type*           getParameterType(size_t a_uiParamIndex) const;
    void            setReturnType(Type* a_pType);
    Type*           getReturnType() const;

    virtual string  getQualifiedName() const;
    virtual string  getDecoratedName() const;
    virtual string  getQualifiedDecoratedName() const;

    bool            matches(const vector<Type*>& a_FunctionSignature, vector<size_t>* a_pPartialMatchesIndexes = nullptr) const;
    bool            compareParameterList( Signature* a_pOther ) const { return matches(a_pOther->m_ParametersTypes); }
    
protected:
    static boolean  SeparateParameterTypes(const string& a_strText, TemplateSpecialization* a_pTemplateSpecialization, vector<Type*>& a_OutParameterTypes, LanguageElement* a_pScope);
    static boolean  ParseParameterTypeList(const string& a_strText, TemplateSpecialization* a_pTemplateSpecialization, vector<Type*>& a_OutParameterTypes, LanguageElement* a_pScope);

    void updateName();
    void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    Type*               m_pReturnType;
    vector<Type*>       m_ParametersTypes;
    size_t              m_uiArgumentStorageSize;
};

o_namespace_end(phantom, reflection)



#endif
