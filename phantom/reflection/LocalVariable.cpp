/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "LocalVariable.h"
#include "LocalVariable.hxx"
#include "LocalVariableAccess.h"
#include "Expression.h"
#include "Block.h"
#include <phantom/std/vector.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), LocalVariable);
o_registerNTI((phantom), vector, (phantom::reflection::LocalVariable*));

o_namespace_begin(phantom, reflection) 

bool LocalVariable::Parse(const string& a_strCode, Type*& a_OutType, string& a_OutName, Expression*& a_OutExpression, LanguageElement* a_pScope)
{
    Type* pType = phantom::typeByName(a_strCode, a_pScope);
    if(pType)
    {
        a_OutType = pType;
        a_OutName = "";
        a_OutExpression = nullptr;
        return true;
    }
    size_t j = a_strCode.size();
    string word;
    string decl;
    while(j--)
    {
        char c = a_strCode[j];
        if(o_char_is_blank(c))
        {
            if(!word.empty())
            {
                Type* pType = phantom::typeByName(a_strCode.substr(0, j), a_pScope);
                if(pType != nullptr)
                {
                    decl = string(word.rbegin(), word.rend());
                    size_t equalPos = decl.find_first_of("=");
                    if(equalPos != string::npos)
                    {
                        Expression* pExpression = expressionByName(decl.substr(equalPos+1));
                        if(pExpression == nullptr OR NOT(pExpression->getValueType()->isImplicitlyConvertibleTo(pType)))
                        {
                            return false;
                        }
                        a_OutExpression = pExpression;
                        a_OutName = decl.substr(0, equalPos);
                    }
                    else 
                    {
                        a_OutExpression = nullptr;
                        a_OutName = decl;
                    }
                    a_OutType = pType;
                    return true;
                }
            }
        }
        word += c;
    }
    if(!word.empty())
    {
        Type* pType = phantom::typeByName(string(word.rbegin(), word.rend()), a_pScope);
        if(pType != nullptr)
        {
            a_OutType = pType;
            a_OutName = "";
            a_OutExpression = nullptr;
            return true;
        }
    }
    return false;
}

LocalVariable::LocalVariable()
    : LanguageElement()
    , m_iFrameOffset(e_InvalidFrameOffset)
    , m_pValueType(nullptr)
    , m_uiIndexInBlock(~size_t(0))
    , m_pValueTypeName(nullptr)
{

}

LocalVariable::LocalVariable( Type* a_pValueType, const string& a_strName, modifiers_t a_Modifiers /*= 0*/ ) 
    : LanguageElement(a_strName, a_Modifiers)
    , m_iFrameOffset(e_InvalidFrameOffset)
    , m_pValueType(a_pValueType)
    , m_uiIndexInBlock(~size_t(0))
    , m_pValueTypeName(nullptr)
{
    if(m_pValueType == nullptr)
        setInvalid();
}

bool LocalVariable::isAccessibleAtCodePosition( const CodePosition& position ) const
{
    if(getBlock() == nullptr) 
        return nullptr;
    return (position.line > getCodeLocation().getStart().line) AND (position.line <= getBlock()->getCodeLocation().getEnd().line);
}

Block* LocalVariable::getBlock() const
{
    return static_cast<Block*>(m_pOwner);
}

LanguageElement* LocalVariable::solveElement( const string& a_strName , const vector<TemplateElement*>* a_pTS, const vector<LanguageElement*>* a_pFS, modifiers_t a_Modifiers /*= 0*/ ) const
{
    return nullptr;
}

void LocalVariable::restore()
{
    if(m_pValueTypeName)
    {
        m_pValueType = phantom::typeByName(*m_pValueTypeName);
        delete m_pValueTypeName;
        m_pValueTypeName = nullptr;
    }
}

void LocalVariable::setValueTypeName( string name )
{
    if(name.size())
    {
        m_pValueTypeName = new string(name);
    }
}

void LocalVariable::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(a_pElement == m_pValueType)
    {
        m_pValueType = nullptr;
    }
}

Expression* LocalVariable::createAccess() const
{
    return o_new(LocalVariableAccess)(const_cast<LocalVariable*>(this));
}

o_namespace_end(phantom, reflection)