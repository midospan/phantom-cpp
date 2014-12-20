/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "LocalVariable.h"
#include "LocalVariable.hxx"
#include "LocalVariableExpression.h"
#include "Expression.h"
#include "Block.h"
#include <phantom/std/vector.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), LocalVariable);
o_registerNTI((phantom), vector, (phantom::reflection::LocalVariable*));

o_namespace_begin(phantom, reflection) 

o_define_meta_type(LocalVariable);

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
    , m_pInitializationExpression(nullptr)
{

}

LocalVariable::LocalVariable( Type* a_pValueType, const string& a_strName, Expression* a_pInitializer /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ ) 
    : LanguageElement(a_strName, a_Modifiers)
    , m_iFrameOffset(e_InvalidFrameOffset)
    , m_pValueType(a_pValueType)
    , m_uiIndexInBlock(~size_t(0))
    , m_pValueTypeName(nullptr)
    , m_pInitializationExpression(nullptr)
{
    if(m_pValueType == nullptr)
        setInvalid();
    if(a_pInitializer)
    {
        setInitializationExpression(a_pInitializer);
    }
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

Expression* LocalVariable::createExpression() const
{
    return o_new(LocalVariableExpression)(const_cast<LocalVariable*>(this));
}

LocalVariable* LocalVariable::clone() const
{
    return o_new(LocalVariable)(m_pValueType, m_strName, m_pInitializationExpression, m_Modifiers);
}

string LocalVariable::getQualifiedName() const
{
    return getQualifiedDecoratedName();
}

string LocalVariable::getQualifiedDecoratedName() const
{
    return (m_pValueType ? m_pValueType->getQualifiedDecoratedName() : "<null>")+" "+m_strName+(m_pInitializationExpression ? ("="+m_pInitializationExpression->translate()) : "");
}

void LocalVariable::setInitializationExpression( Expression* a_pInitializationExpression )
{
    o_assert(a_pInitializationExpression);
    if(m_pInitializationExpression)
    {
        removeElement(m_pInitializationExpression);
        o_assert(m_pInitializationExpression == nullptr);
        o_dynamic_delete m_pInitializationExpression;
    }
    m_pInitializationExpression = a_pInitializationExpression;
    addElement(m_pInitializationExpression);
    if(m_pValueType == nullptr 
        OR m_pInitializationExpression->getValueType() == nullptr 
        OR NOT(m_pInitializationExpression->getValueType()->isImplicitlyConvertibleTo(m_pValueType)))
    {
        setInvalid();
    }
}

void LocalVariable::setValueType( Type* a_pType )
{
    if(m_pValueType == a_pType) return;
    if(m_pValueType)
    {
        removeReferencedElement(m_pValueType);
    }
    m_pValueType = a_pType;
    if(m_pValueType)
    {
        addReferencedElement(m_pValueType);
    }
    else setInvalid();
}

o_namespace_end(phantom, reflection)