/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Language.h"
#include "Language.hxx"
#include "Application.h"
#include "Package.h"
#include "Source.h"
#include "Expression.h"
/* *********************************************** */
o_registerN((phantom, reflection), Language);

o_namespace_begin(phantom, reflection)

void Language::translate( LanguageElement* a_pElement, string& a_Out, int a_TranslationType, LanguageElement* a_pScope )
{
    visitor_data data;
    data.id = e_Function_Translate;
    const void* in[2] = {&a_TranslationType, &a_pScope};
    void* out[1] = {&a_Out};
    data.in = in;
    data.out = out;
    a_pElement->visit(this, data);
}

const string& Language::name( NamedElement* a_pElement, int options )
{
    static string null_name_str = "<null>";
    return a_pElement ? a_pElement->getName() : null_name_str;
}

void Language::name( NamedElement* a_pElement, string& translation, int options )
{
    translation += a_pElement ? a_pElement->getName() : "<null>";
}

string Language::qualifiedName( NamedElement* a_pElement, int options )
{
    return a_pElement ? a_pElement->getQualifiedName() : "<null>";
}

void Language::qualifiedName( NamedElement* a_pElement, string& translation, int options /*= 0*/ )
{
    translation += a_pElement ? a_pElement->getQualifiedName() : "<null>";
}

string Language::qualifiedDecoratedName( NamedElement* a_pElement, int options )
{
    return a_pElement ? a_pElement->getQualifiedDecoratedName() : "<null>";
}

void Language::qualifiedDecoratedName( NamedElement* a_pElement, string& translation, int options )
{
    translation += a_pElement ? a_pElement->getQualifiedDecoratedName() : "<null>";
}

Source* Language::precompile( const string& a_strSourceName, const string& a_strCode ) const
{
    size_t colonpos = a_strSourceName.find_first_of(":");
    size_t packagePos = a_strSourceName.find_last_of(".");
    string packageName;
    Module* pModule = nullptr;
    if(colonpos != string::npos)
    {
        string moduleName = a_strSourceName.substr(0, colonpos);
        pModule = moduleByName(moduleName);
        if(pModule == nullptr)
        {
            o_warning(false, "module not found");
            return nullptr;
        }
        if(pModule->isNative() AND NOT(application()->isNativeModuleLoaded(pModule)))
        {
            o_warning(false, "native module not loaded");
            return nullptr;
        }
        packageName = a_strSourceName.substr(colonpos+1, packagePos-(colonpos+1));
    }
    else 
    {
        packageName = a_strSourceName.substr(0, packagePos);
    }
    if(packagePos == string::npos)
    {
        o_warning(false, "missing source name in '%s', only package provided; reminder source full name must be of the form 'module:package.source'", a_strSourceName.c_str());
        return nullptr;
    }
    Package* pPackage = phantom::package(packageName);
    if(pPackage == nullptr)
    {
        o_warning(false, "package cannot be found or already belongs to another module");
        return nullptr;
    }
    if(pPackage == nullptr)
        pPackage = phantom::package(pModule, packageName);
    
    string sourceName = a_strSourceName.substr(packagePos+1);
    Source* pSource = pPackage->getSource(sourceName);
    if(pSource == nullptr)
        pSource = pPackage->addSource(const_cast<Language*>(this), sourceName);
    pSource->addInputStream(new istringstream(a_strCode));
    pSource->precompile();

    return pSource;
}

Source* Language::compile( Compiler* a_pCompiler, const string& a_strPackage, const string& a_strCode ) const
{
    Source* pSource = precompile(a_strPackage, a_strCode);
    if(pSource == nullptr)
        return nullptr;/*
    if(a_pCompiler->compile(pSource).isNull())
    {
        o_dynamic_delete pSource;
        return nullptr;
    }*/
    return pSource;
}

Expression* Language::expressionByName( const string& a_strName, LanguageElement* a_pScope /*= (LanguageElement*)phantom::globalNamespace()*/, modifiers_t a_Modifiers /*= 0*/ ) const
{
    LanguageElement* pElement = elementByName(a_strName, a_pScope, a_Modifiers);
    if(pElement)
    {
        Expression* pExpression = pElement->toExpression();
        if(pExpression->isInvalid())
        {
            if(pExpression != Expression::Invalid()) 
                o_dynamic_delete pExpression;
            return nullptr;
        }
        return pExpression;
    }
    return nullptr;
}

Type* Language::typeByName( const string& a_strName, LanguageElement* a_pScope /*= phantom::globalNamespace()*/, modifiers_t a_Modifiers /*= 0*/ ) const
{
    LanguageElement* pElement = elementByName(a_strName, a_pScope, a_Modifiers);
    return pElement ? pElement->asType() : nullptr;
}

bool conversion::isIdentity() const
{
    return input->removeQualifiers()->equals(output->removeQualifiers());
}

conversion* Language::typeConversion( Type* a_pInput, Type* a_pOutput, int a_iConversionType, LanguageElement* a_pContextScope, int a_iUserDefinedAllowedConversions  )
{
    conversion* conv = 0;
    visitor_data data;
    data.id = e_Function_Conversion;
    const void* in[4] = { &a_pOutput, &a_iConversionType, &a_iUserDefinedAllowedConversions, &a_pContextScope };
    void* out [1] = {&conv};
    data.in = in;
    data.out = out;
    a_pInput->visit(this, data);
    return conv;
}

Expression* Language::toExpression( LanguageElement* a_pElement, Expression* a_pLeft )
{
    Expression* pResult = nullptr;
    visitor_data data;
    data.id = e_Function_ToExpression;
    const void* in[1] = {&a_pLeft};
    void* out[1] = {&pResult};
    data.in = in;
    data.out = out;
    a_pElement->visit(this, data);
    return pResult;
}

o_namespace_end(phantom, reflection)