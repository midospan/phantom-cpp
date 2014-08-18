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

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ClassType.h>
#include <phantom/reflection/ClassType.hxx>
#include <phantom/reflection/Compiler.h>
#include <phantom/reflection/Expression.h>
#include <phantom/variant.h>
#include <phantom/reflection/ValueMember.hxx>
#include <phantom/reflection/CallExpression.h>
#include <phantom/reflection/StaticVariableAccess.h>
#include <phantom/reflection/SingleParameterFunctionExpression.h>
#include <phantom/reflection/ConstructorCallExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), ClassType);

o_namespace_begin(phantom, reflection) 

static vector<StaticDataMember*>      m_EmptyStaticDataMembers;
static vector<StaticMemberFunction*>  m_EmptyStaticMemberFunctions;
static vector<Collection*>            m_EmptyCollections;
static vector<Constructor*>           m_EmptyConstructors;

o_define_meta_type(ClassType);

ClassType::ClassType( extra_data* a_pExtraData, const string& a_strName, bitfield a_Modifiers /*= 0*/ ) 
    : Type(e_struct, a_strName, a_Modifiers)
    , m_pAttributes(nullptr)
    , m_pStaticMemberFunctions(nullptr)
    , m_pCollections(nullptr)
    , m_pConstructors(nullptr)
    , m_pStaticDataMembers(nullptr)
    , m_pExtraData(a_pExtraData)
{
    m_uiSerializedSize = m_uiResetSize = 0;
}

ClassType::ClassType( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers /*= 0*/ ) 
    : Type(e_struct, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    , m_pAttributes(nullptr)
    , m_pStaticMemberFunctions(nullptr)
    , m_pCollections(nullptr)
    , m_pConstructors(nullptr)
    , m_pStaticDataMembers(nullptr)
    , m_pExtraData(nullptr)
{
    m_uiSerializedSize = m_uiResetSize = 0;
}

ClassType::~ClassType( void )
{
    delete m_pExtraData;
    destroyContent();
}

void ClassType::destroyContent()
{
    if(m_pAttributes)
    {
        delete ((map<string, variant>*)m_pAttributes);
        m_pAttributes = nullptr;
    }
}

DataMember* ClassType::getDataMember( const string& a_strName) const
{
    DataMember* pDataMember = getInstanceDataMember(a_strName);
    if(pDataMember != NULL) return pDataMember;
    return getStaticDataMember(a_strName);
}

void ClassType::elementAdded(LanguageElement* a_pElement)
{
    Type::elementAdded(a_pElement);
}

void ClassType::elementRemoved(LanguageElement* a_pElement)
{
    Type::elementRemoved(a_pElement);
    if(a_pElement->asInstanceDataMember())
    {
        m_InstanceDataMembers.erase(std::find(m_InstanceDataMembers.begin(), m_InstanceDataMembers.end(), a_pElement->asInstanceDataMember()));
        m_ValueMembers.erase(std::find(m_ValueMembers.begin(), m_ValueMembers.end(), a_pElement->asValueMember()));
    }
    else if(a_pElement->asProperty())
    {
        m_Properties.erase(std::find(m_Properties.begin(), m_Properties.end(), a_pElement->asProperty()));
        m_ValueMembers.erase(std::find(m_ValueMembers.begin(), m_ValueMembers.end(), a_pElement->asValueMember()));
    } 
    else if(a_pElement->asInstanceMemberFunction())
    {
        m_InstanceMemberFunctions.erase(std::find(m_InstanceMemberFunctions.begin(), m_InstanceMemberFunctions.end(), a_pElement->asInstanceMemberFunction()));
    }
    else if(a_pElement->asStaticMemberFunction())
    {
        o_assert(m_pStaticMemberFunctions);
        m_pStaticMemberFunctions->erase(std::find(m_pStaticMemberFunctions->begin(), m_pStaticMemberFunctions->end(), a_pElement->asStaticMemberFunction()));
        if(m_pStaticMemberFunctions->empty())
        {
            delete m_pStaticMemberFunctions;
            m_pStaticMemberFunctions = nullptr;
        }
    }
    else if(a_pElement->asStaticDataMember())
    {
        o_assert(m_pStaticDataMembers);
        m_pStaticDataMembers->erase(std::find(m_pStaticDataMembers->begin(), m_pStaticDataMembers->end(), a_pElement->asStaticDataMember()));
        if(m_pStaticDataMembers->empty())
        {
            delete m_pStaticDataMembers;
            m_pStaticDataMembers = nullptr;
        }
    }
    else if(a_pElement->asCollection())
    {
        o_assert(m_pCollections);
        m_pCollections->erase(std::find(m_pCollections->begin(), m_pCollections->end(), a_pElement->asCollection()));
        if(m_pCollections->empty())
        {
            delete m_pCollections;
            m_pCollections = nullptr;
        }
    }
    else if(a_pElement->asValueMember())
    {
        m_ValueMembers.erase(std::find(m_ValueMembers.begin(), m_ValueMembers.end(), a_pElement->asValueMember()));
    } 
}
Property*           ClassType::getProperty(const string& a_strName) const
{
    ValueMember* pValueMember = getValueMember(a_strName);
    return pValueMember ? pValueMember->asProperty() : nullptr;
}

InstanceDataMember* ClassType::getInstanceDataMember( const string& a_strName) const
{
    auto it = m_ValueMembers.begin();
    auto end = m_ValueMembers.end();
    for(; it != end; ++it)
    {
        InstanceDataMember* pDataMember = (*it)->asInstanceDataMember();
        if(pDataMember && pDataMember->getName() == a_strName)
            return pDataMember;
    }
    return NULL;
}

Constructor* ClassType::getConstructor( const string& a_strDecoratedName) const
{
    LanguageElement* pElement = phantom::elementByName(a_strDecoratedName, const_cast<ClassType*>(this));
    return pElement ? pElement->asConstructor() : nullptr; 
}

Constructor* ClassType::getConstructor( const vector<Type*>& a_Types, vector<size_t>* a_pPartialMatchesIndexes, bitfield a_Modifiers ) const
{
    if(m_pConstructors) 
    {
        if(a_pPartialMatchesIndexes)
        {
            vector<std::pair<Constructor*, vector<size_t>>> matching;
            vector<size_t> partialMatches;
            partialMatches.reserve(a_Types.size());
            auto it = m_pConstructors->begin();
            auto end = m_pConstructors->end();
            for(; it != end; ++it)
            {
                partialMatches.clear();
                Constructor* pConstructor = *it;
                if(pConstructor->matches(m_strName, a_Types, &partialMatches, a_Modifiers))
                {
                    matching.push_back(std::pair<Constructor*, vector<size_t>>(pConstructor, partialMatches));
                }
            }
            if(matching.size() == 1)
            {
                a_pPartialMatchesIndexes->insert(a_pPartialMatchesIndexes->end(), matching.back().second.begin(), matching.back().second.end());
                return matching.back().first;
            }
        }
        else 
        {
            auto it = m_pConstructors->begin();
            auto end = m_pConstructors->end();
            for(; it != end; ++it)
            {
                Constructor* pConstructor = static_cast<Constructor*>((*it));
                if(pConstructor->matches(m_strName, a_Types, nullptr, a_Modifiers))
                {
                    return pConstructor;
                }
            }
        }
    }
    if(a_Types.empty() )
    {
        Constructor* pDefaultConstructor = createDefaultConstructor();
        if(pDefaultConstructor)
        {
            if(m_pConstructors == nullptr)
            {
                const_cast<vector<Constructor*>*&>(m_pConstructors) = new vector<Constructor*>;
            }
            const_cast<vector<Constructor*>*&>(m_pConstructors)->push_back(pDefaultConstructor);
            const_cast<ClassType*>(this)->addElement(pDefaultConstructor);
            return pDefaultConstructor;
        }
    }
    return nullptr;
}

Constructor* ClassType::getConstructor( Type* a_pType, vector<size_t>* a_pPartialMatches /*= nullptr*/, bitfield a_Modifiers /*= 0*/ ) const
{
    vector<Type*> types;
    types.push_back(a_pType);
    return getConstructor(types, a_pPartialMatches, a_Modifiers);
}

void ClassType::valueToString( string& s, const void* src ) const
{
    auto it = m_ValueMembers.begin();
    auto end = m_ValueMembers.end();
    if(it == end) 
        return;
    s += '{';
    int c = 0;
    for(; it != end; ++it)
    {
        if(c != 0)
        {
            s += ';';
            s += ' ';
        }
        ValueMember* pValueMember = static_cast<ValueMember*>((*it));
        s += pValueMember->getName();
        s += '=';
        void* buffer = pValueMember->getValueType()->newInstance();
        pValueMember->getValue(src, buffer);
        pValueMember->getValueType()->valueToString(s, buffer);
        pValueMember->getValueType()->deleteInstance(buffer);
        ++c;
    }
    s += '}';
}

void ClassType::valueFromString( const string& cs, void* dest ) const
{
    o_exception(exception::unsupported_member_function_exception, "TODO (not supported yet)");
}

InstanceMemberFunction* ClassType::getInstanceMemberFunction( const string& a_strIdentifierString ) const
{
    LanguageElement* pElement = phantom::elementByName(a_strIdentifierString, const_cast<ClassType*>(this));
    return pElement ? pElement->asInstanceMemberFunction() : nullptr; 
}

LanguageElement*            ClassType::solveElement(
    const string& a_strName 
    , const vector<TemplateElement*>* a_pTemplateSignature
    , const vector<LanguageElement*>* a_pFunctionSignature
    , bitfield a_Modifiers /*= 0*/) const 
{
    LanguageElement* pElement = nullptr;
    pElement = Type::solveElement(a_strName, a_pTemplateSignature, a_pFunctionSignature, a_Modifiers);
    if(pElement) return pElement;
    if(a_pFunctionSignature == nullptr AND a_pTemplateSignature == nullptr)
    {
        StaticDataMember* pStaticDataMember = getStaticDataMember(a_strName);
        if(pStaticDataMember)
        {
            return pStaticDataMember->asLanguageElement();
        }
        return getValueMember(a_strName);
    }
    if(a_pFunctionSignature)
    {
        vector<Type*> types;
        if(a_pFunctionSignature->empty())
        {
            if(a_strName == m_strName)
            {
                // Constructor
                return getConstructor(types, nullptr, a_Modifiers);
            }
            MemberFunction* pMemberFunction = getMemberFunction(a_strName, types, nullptr, a_Modifiers);
            if(pMemberFunction AND pMemberFunction->asStaticMemberFunction())
            {
                vector<Expression*> arguments;
                return o_new(CallExpression)(pMemberFunction->asStaticMemberFunction(), arguments);
            }
            return pMemberFunction ? pMemberFunction->asLanguageElement() : nullptr;
        }
        else 
        {
            Type* pType = a_pFunctionSignature->front()->asType();
            Expression* pExpression;
            if(pType)
            {
                types.push_back(pType);
                for(auto it = a_pFunctionSignature->begin()+1; it != a_pFunctionSignature->end(); ++it)
                {
                    pType = (*it)->asType();
                    if(pType == nullptr) return nullptr;
                    types.push_back(pType);
                }
                if(a_strName == m_strName)
                {
                    // Constructor
                    return getConstructor(types, nullptr, a_Modifiers);
                }
                // Don't accept member function with partial matches
                MemberFunction* pMemberFunction = getMemberFunction(a_strName, types, nullptr, a_Modifiers);
                return pMemberFunction ? pMemberFunction->asLanguageElement() : nullptr;
            }
            else if((pExpression = a_pFunctionSignature->front()->asExpression()))
            {
                vector<Expression*> expressions;
                vector<Expression*> arguments;
                expressions.push_back(pExpression);
                types.push_back(pExpression->getValueType());
                for(auto it = a_pFunctionSignature->begin()+1; it != a_pFunctionSignature->end(); ++it)
                {
                    pExpression = (*it)->asExpression();
                    if(pExpression == nullptr) 
                        return nullptr;
                    expressions.push_back(pExpression);
                    types.push_back(pExpression->getValueType());
                }
                vector<size_t> partialMatches;
                if(m_pNestedTypes)
                {
                    for(auto it = m_pNestedTypes->begin(); it != m_pNestedTypes->end(); ++it)
                    {
                        if((*it)->getName() == a_strName)
                        {
                            // Constructor
                            Constructor* pConstructor = getConstructor(types, &partialMatches, a_Modifiers);
                            if(pConstructor == nullptr)
                                return nullptr;
                            if(isCopyable())
                            {
                                return o_new(ConstructorCallExpression)(pConstructor, expressions);
                            }
                        }
                    }
                }
                // Accepts member function with partial matches
                StaticMemberFunction* pStaticMemberFunction = getStaticMemberFunction(a_strName, types, &partialMatches, a_Modifiers);
                if(pStaticMemberFunction)
                {
                    for(size_t i = 0; i<expressions.size(); ++i)
                    {
                        arguments.push_back(expressions[i]->implicitCast(pStaticMemberFunction->getParameterType(i)));
                    }

                    return o_new(CallExpression)(pStaticMemberFunction, arguments);
                }
            }
        }
    }
    return Type::solveElement(a_strName, a_pTemplateSignature, a_pFunctionSignature, a_Modifiers);
}

Expression* ClassType::solveExpression( Expression* a_pLeftExpression
    , const string& a_strName 
    , const vector<TemplateElement*>* a_pTemplateSignature
    , const vector<LanguageElement*>* a_pFunctionSignature
    , bitfield a_Modifiers /*= 0*/ ) const
{
    if((a_pLeftExpression->getValueType()->removeReference()->asConstType() != nullptr) != a_Modifiers.matchesMask(o_const))
    {
        o_exception(exception::reflection_runtime_exception, "Incoherency between const modifier and expression const type");
    }
    if(a_pLeftExpression->getValueType()->removeReference()->removeConst() != this) 
        return nullptr;
    if(NOT(a_pLeftExpression->hasEffectiveAddress())) 
        return nullptr;

    if(a_pTemplateSignature == nullptr && a_pFunctionSignature == nullptr)
    {
        StaticDataMember* pStaticDataMember = getStaticDataMember(a_strName);
        if(pStaticDataMember)
        {
            return o_new(StaticVariableAccess)(pStaticDataMember, a_pLeftExpression);
        }
        ValueMember* pValueMember = getValueMember(a_strName);
        if(pValueMember) 
        {
            return pValueMember->createAccessExpression(a_pLeftExpression->reference());
        }
        vector<Subroutine*> singleParameterMemberFunctions;
        for(auto it = m_InstanceMemberFunctions.begin(); it != m_InstanceMemberFunctions.end(); ++it)
        {
            if((*it)->getName() == a_strName && (*it)->getParameterCount() == 1)
            {
                singleParameterMemberFunctions.push_back(*it);
            }
        }
        if(m_pStaticMemberFunctions)
        {
            for(auto it = m_pStaticMemberFunctions->begin(); it != m_pStaticMemberFunctions->end(); ++it)
            {
                if((*it)->getName() == a_strName && (*it)->getParameterCount() == 1)
                {
                    singleParameterMemberFunctions.push_back(*it);
                }
            }
        }
        if(singleParameterMemberFunctions.size() == 1)
        {
            return o_new(SingleParameterFunctionExpression)(singleParameterMemberFunctions.back(), singleParameterMemberFunctions.back()->asInstanceMemberFunction() ? a_pLeftExpression->implicitCast(referenceType()) : nullptr);
        }
    }
    else if(a_pFunctionSignature)
    {
        vector<Type*> types;
        if(a_pFunctionSignature->empty())
        {
            MemberFunction* pMemberFunction = nullptr;
            if(a_pLeftExpression->isConstExpression()) 
            {
                pMemberFunction = getMemberFunction(a_strName, types, nullptr, a_Modifiers|o_const);
            }
            else 
            {
                pMemberFunction = getMemberFunction(a_strName, types, nullptr, a_Modifiers|o_noconst);
                if(pMemberFunction == nullptr)
                {
                    pMemberFunction = getMemberFunction(a_strName, types, nullptr, a_Modifiers|o_const);
                }
            }
            vector<Expression*> arguments;
            if(pMemberFunction)
            {
                if(pMemberFunction->asInstanceMemberFunction())
                {
                    arguments.push_back(a_pLeftExpression->reference());
                }
                return o_new(CallExpression)(pMemberFunction->asSubroutine(), arguments);
            }
        }
        else 
        {
            Type* pType = a_pFunctionSignature->front()->asType();
            Expression* pExpression = a_pFunctionSignature->front()->asExpression();
            if(pExpression)
            {
                vector<Expression*> expressions;
                vector<Expression*> arguments;
                types.push_back(pExpression->getValueType());
                expressions.push_back(pExpression);
                for(auto it = a_pFunctionSignature->begin()+1; it != a_pFunctionSignature->end(); ++it)
                {
                    pExpression = (*it)->asExpression();
                    if(pExpression == nullptr) 
                        return nullptr;
                    expressions.push_back(pExpression);
                    types.push_back(pExpression->getValueType());
                }
                // Accepts member function with partial matches
                vector<size_t> partialMatches;
                MemberFunction* pMemberFunction = nullptr;
                if(a_pLeftExpression->isConstExpression())
                {
                    pMemberFunction = getMemberFunction(a_strName, types, &partialMatches, a_Modifiers|o_const);
                }
                else 
                {
                    pMemberFunction = getMemberFunction(a_strName, types, &partialMatches, a_Modifiers|o_noconst);
                    if(pMemberFunction == nullptr)
                    {
                        pMemberFunction = getMemberFunction(a_strName, types, &partialMatches, a_Modifiers|o_const);
                    }
                }
                if(pMemberFunction) 
                {
                    for(size_t i = 0; i<expressions.size(); ++i)
                    {
                        arguments.push_back(expressions[i]->implicitCast(pMemberFunction->asSubroutine()->getParameterType(i)));
                    }
                    if(pMemberFunction->asInstanceMemberFunction())
                    {
                        arguments.insert(arguments.begin(), a_pLeftExpression->reference());
                    }
                    return o_new(CallExpression)(pMemberFunction->asSubroutine(), arguments);
                }
                return nullptr;
            }
        }
    }
    return Type::solveExpression(a_pLeftExpression, a_strName, a_pTemplateSignature, a_pFunctionSignature, a_Modifiers);
}

Expression* ClassType::solveOperator( const string& a_strOp, const vector<Expression*>& a_Expressions, bitfield a_Modifiers ) const
{
    o_assert(a_Expressions.size());
    vector<LanguageElement*> expressions;
    if(a_Expressions.size() == 2)
    {
        expressions.push_back(a_Expressions[1]);
    }
    Expression* pExpression = solveExpression(a_Expressions[0], "operator"+a_strOp, nullptr, &expressions, a_Modifiers);
    if(pExpression)
    {
        return pExpression;
    }
    return Type::solveOperator(a_strOp, a_Expressions, a_Modifiers);
}


InstanceMemberFunction* ClassType::getInstanceMemberFunction( const string& a_strName, const vector<Type*>& a_Types, vector<size_t>* a_pPartialMatchesIndexes, bitfield a_Modifiers /*= 0*/ ) const
{
    if(a_pPartialMatchesIndexes)
    {
        vector<std::pair<InstanceMemberFunction*, vector<size_t>>> matching;
        vector<size_t> partialMatches;
        partialMatches.reserve(a_Types.size());
        auto it = m_InstanceMemberFunctions.begin();
        auto end = m_InstanceMemberFunctions.end();
        for(; it != end; ++it)
        {
            partialMatches.clear();
            InstanceMemberFunction* pMemberFunction = static_cast<InstanceMemberFunction*>((*it));
            if(pMemberFunction->matches(a_strName, a_Types, &partialMatches, a_Modifiers))
            {
                matching.push_back(std::pair<InstanceMemberFunction*, vector<size_t>>(pMemberFunction, partialMatches));
            }
        }
        if(matching.size() == 1)
        {
            a_pPartialMatchesIndexes->insert(a_pPartialMatchesIndexes->end(), matching.back().second.begin(), matching.back().second.end());
            return matching.back().first;
        }
    }
    else 
    {
        auto it = m_InstanceMemberFunctions.begin();
        auto end = m_InstanceMemberFunctions.end();
        for(; it != end; ++it)
        {
            InstanceMemberFunction* pMemberFunction = static_cast<InstanceMemberFunction*>((*it));
            if(pMemberFunction->matches(a_strName, a_Types, nullptr, a_Modifiers))
            {
                return pMemberFunction;
            }
        }
    }
    return nullptr;
}

StaticMemberFunction* ClassType::getStaticMemberFunction( const string& a_strName, const vector<Type*>& a_Types, vector<size_t>* a_pPartialMatchesIndexes, bitfield a_Modifiers /*= 0*/  ) const
{
    if(m_pStaticMemberFunctions == nullptr) 
        return nullptr;
    if(a_pPartialMatchesIndexes)
    {
        vector<std::pair<StaticMemberFunction*, vector<size_t>>> matching;
        vector<size_t> partialMatches;
        partialMatches.reserve(a_Types.size());
        auto it = m_pStaticMemberFunctions->begin();
        auto end = m_pStaticMemberFunctions->end();
        for(; it != end; ++it)
        {
            partialMatches.clear();
            StaticMemberFunction* pMemberFunction = static_cast<StaticMemberFunction*>((*it));
            if(pMemberFunction->matches(a_strName, a_Types, &partialMatches, a_Modifiers))
            {
                matching.push_back(std::pair<StaticMemberFunction*, vector<size_t>>(pMemberFunction, partialMatches));
            }
        }
        if(matching.size() == 1)
        {
            a_pPartialMatchesIndexes->insert(a_pPartialMatchesIndexes->end(), matching.back().second.begin(), matching.back().second.end());
            return matching.back().first;
        }
        o_message(error, "ambiguity");
    }
    else 
    {
        auto it = m_pStaticMemberFunctions->begin();
        auto end = m_pStaticMemberFunctions->end();
        for(; it != end; ++it)
        {
            StaticMemberFunction* pMemberFunction = static_cast<StaticMemberFunction*>((*it));
            if(pMemberFunction->matches(a_strName, a_Types, nullptr, a_Modifiers))
            {
                return pMemberFunction;
            }
        }
    }
    return nullptr;
}

StaticMemberFunction* ClassType::getStaticMemberFunction( const string& a_strIdentifierString ) const
{
    LanguageElement* pElement = phantom::elementByName(a_strIdentifierString, const_cast<ClassType*>(this));
    return pElement ? pElement->asStaticMemberFunction() : nullptr; 
}

MemberFunction* ClassType::getMemberFunction(const string& a_strIdentifierString) const
{
    InstanceMemberFunction* pMemberFunction = getInstanceMemberFunction(a_strIdentifierString);
    if(pMemberFunction != NULL) return pMemberFunction;
    return getStaticMemberFunction(a_strIdentifierString);
}

MemberFunction* ClassType::getMemberFunction(const string& a_strName, const vector<Type*>& a_Types, vector<size_t>* a_pPartialMatchesIndexes, bitfield a_Modifiers /*= 0*/ ) const
{
    bitfield staticModifiers = a_Modifiers;
    staticModifiers &= ~o_noconst;
    staticModifiers &= ~o_const;
    if(a_pPartialMatchesIndexes)
    {
        vector<size_t> instancePartialMatches;
        InstanceMemberFunction* pMemberFunction = getInstanceMemberFunction(a_strName, a_Types, &instancePartialMatches, a_Modifiers);
        if(pMemberFunction == NULL) 
        {
            return getStaticMemberFunction(a_strName, a_Types, a_pPartialMatchesIndexes, staticModifiers);
        }
        else if(a_pPartialMatchesIndexes->size() == 0)
        {
            a_pPartialMatchesIndexes->insert(a_pPartialMatchesIndexes->end(), instancePartialMatches.begin(), instancePartialMatches.end());
            return pMemberFunction;
        } 
        else 
        {
            vector<size_t> staticPartialMatches;
            StaticMemberFunction* pStaticMemberFunction = getStaticMemberFunction(a_strName, a_Types, &staticPartialMatches, staticModifiers);
            if(pStaticMemberFunction)
            {
                if(staticPartialMatches.size() == 0)
                {
                    a_pPartialMatchesIndexes->insert(a_pPartialMatchesIndexes->end(), staticPartialMatches.begin(), staticPartialMatches.end());
                    return pStaticMemberFunction;
                }
                o_message(error, "ambiguity");
                return nullptr;
            }
        }
    }
    else 
    {
        InstanceMemberFunction* pMemberFunction = getInstanceMemberFunction(a_strName, a_Types, nullptr, a_Modifiers);
        if(pMemberFunction != NULL) return pMemberFunction;
        return getStaticMemberFunction(a_strName, a_Types, nullptr, staticModifiers);
    }
    return nullptr;
}
/*

phantom::string ClassType::getQualifiedName() const
{
    string        str ;
    if(m_pNamespace != NULL) 
    {
        m_pNamespace->getHierarchicalNameNoRoot(&str);
        if(NOT(str.empty()))
            str+=o_CC('.');
    }
    str += m_strName.substr(0, m_strName.find_first_of(o_CC('<'))) ;
    return str;
}*/


StaticDataMember* ClassType::getStaticDataMember( const string& a_strName) const
{
    if(m_pStaticDataMembers) 
    {
        auto it = m_pStaticDataMembers->begin();
        auto end = m_pStaticDataMembers->end();
        for(; it != end; ++it)
        {
            StaticDataMember* pDataMember = static_cast<StaticDataMember*>((*it));
            if(pDataMember->getName() == a_strName)
                return pDataMember;
        }
    }
    return nullptr;
}

void ClassType::getMembers( vector<LanguageElement*>& out ) const
{
    out.insert(out.end(), m_ValueMembers.begin(), m_ValueMembers.end());
    out.insert(out.end(), m_InstanceMemberFunctions.begin(), m_InstanceMemberFunctions.end());
    if(m_pStaticDataMembers) out.insert(out.end(), m_pStaticDataMembers->begin(), m_pStaticDataMembers->end());
    if(m_pStaticMemberFunctions) out.insert(out.end(), m_pStaticMemberFunctions->begin(), m_pStaticMemberFunctions->end());
    if(m_pCollections) out.insert(out.end(), m_pCollections->begin(), m_pCollections->end());
}

ValueMember* ClassType::getValueMember( const string& a_strName ) const
{
    auto it = m_ValueMembers.begin();
    auto end = m_ValueMembers.end();
    for(; it != end; ++it)
    {
        ValueMember* pValueMember = static_cast<ValueMember*>((*it));
        if(pValueMember->getName() == a_strName)
            return pValueMember;
    }
    return nullptr;
}

Collection* ClassType::getCollection( const string& a_strName ) const
{
    if(m_pCollections == nullptr) return nullptr;
    auto it = m_pCollections->begin();
    auto end = m_pCollections->end();
    for(; it != end; ++it)
    {
        if((*it)->getName() == a_strName)
            return (Collection*)(*it);
    }
    return nullptr;
}

void                    ClassType::addConstructor( Constructor* a_pConstructor )
{
    o_assert(getConstructor(a_pConstructor->getDecoratedName()));
    if(m_pExtraData)
    {
        if(m_pExtraData->m_iState < extra_data::e_State_MemberSetup)
        {
            m_pExtraData->m_iState = extra_data::e_State_MemberSetup;
        }
        else if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
        {
            o_exception(exception::reflection_runtime_exception, "Class finalized or compiled, you cannot add members anymore");
        }
    }
    if(m_pConstructors == nullptr) m_pConstructors = new vector<Constructor*>;
    m_pConstructors->push_back(a_pConstructor);
    addElement(a_pConstructor);
}

void                ClassType::addValueMember(ValueMember* a_pValueMember)
{
    o_assert(getValueMember(a_pValueMember->getName()) == NULL);
    if(a_pValueMember->asInstanceDataMember())
    {
        addInstanceDataMember(a_pValueMember->asInstanceDataMember());
    }
    else 
    {
        o_assert(a_pValueMember->asProperty());
        addProperty(a_pValueMember->asProperty());
    }
}

void                ClassType::addProperty( Property* a_pProperty )
{
    if(m_pExtraData)
    {
        if(m_pExtraData->m_iState < extra_data::e_State_MemberSetup)
        {
            m_pExtraData->m_iState = extra_data::e_State_MemberSetup;
        }
        else if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
        {
            o_exception(exception::reflection_runtime_exception, "Class finalized or compiled, you cannot add members anymore");
        }
    }

    o_assert(getValueMember(a_pProperty->getName()) == nullptr);
    if(a_pProperty->isReset())
    {
        m_uiResetSize += a_pProperty->getValueType()->getResetSize(); 
    }
    m_Properties.push_back(a_pProperty);
    m_ValueMembers.insert(m_ValueMembers.begin()+(m_Properties.size()-1), a_pProperty);
    addElement(a_pProperty);
}

void                ClassType::addInstanceDataMember(InstanceDataMember* a_pDataMember)
{
    if(m_pExtraData)
    {
        if(m_pExtraData->m_iState < extra_data::e_State_MemberSetup)
        {
            m_pExtraData->m_iState = extra_data::e_State_MemberSetup;
        }
        else if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
        {
            o_exception(exception::reflection_runtime_exception, "Class finalized or compiled, you cannot add members anymore");
        }
    }

    o_assert((asPOD() == nullptr OR (a_pDataMember->getValueType()->asPOD() != nullptr)), "POD structs can only store pod types");
    o_assert(getValueMember(a_pDataMember->getName()) == nullptr);
    if(a_pDataMember->isReset())
    {
        m_uiResetSize += a_pDataMember->getValueType()->getResetSize(); 
    }
    m_InstanceDataMembers.push_back(a_pDataMember);
    m_ValueMembers.push_back(a_pDataMember);
    addElement(a_pDataMember);
}

void                ClassType::addStaticDataMember(StaticDataMember* a_pDataMember)
{
    if(m_pStaticDataMembers == nullptr) m_pStaticDataMembers = new vector<StaticDataMember*>;
    m_pStaticDataMembers->push_back(a_pDataMember);
    addElement(a_pDataMember);
}

void                ClassType::addDataMember(DataMember* a_pDataMember)
{
    if(a_pDataMember->asInstanceDataMember())
    {
        addInstanceDataMember(a_pDataMember->asInstanceDataMember());
    }
    else 
    {
        o_assert(a_pDataMember->asStaticDataMember());
        addStaticDataMember(a_pDataMember->asStaticDataMember());
    }
}

void                ClassType::addCollection( Collection* a_pCollection)
{
    if(m_pExtraData)
    {
        if(m_pExtraData->m_iState < extra_data::e_State_MemberSetup)
        {
            m_pExtraData->m_iState = extra_data::e_State_MemberSetup;
        }
        else if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
        {
            o_exception(exception::reflection_runtime_exception, "Class finalized or compiled, you cannot add members anymore");
        }
    }
    if(m_pCollections == nullptr) m_pCollections = new vector<Collection*>;
    m_pCollections->push_back(a_pCollection);
    addElement(a_pCollection);
}

void                ClassType::addInstanceMemberFunction(InstanceMemberFunction* a_pInstanceMemberFunction)
{
    if(m_pExtraData)
    {
        if(m_pExtraData->m_iState < extra_data::e_State_MemberSetup)
        {
            m_pExtraData->m_iState = extra_data::e_State_MemberSetup;
        }
        else if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
        {
            o_exception(exception::reflection_runtime_exception, "Class finalized or compiled, you cannot add members anymore");
        }
    }
#if !defined(_NDEBUG)
    LanguageElement* pElement = phantom::elementByName(a_pInstanceMemberFunction->getDecoratedName(), const_cast<ClassType*>(this));
    o_assert(pElement == nullptr OR pElement->getOwner() != this OR pElement->isConst() != a_pInstanceMemberFunction->isConst());
#endif
    m_InstanceMemberFunctions.push_back(a_pInstanceMemberFunction);
    addElement(a_pInstanceMemberFunction);
}

void                ClassType::addStaticMemberFunction(StaticMemberFunction* a_pStaticMemberFunction)
{
#if !defined(_NDEBUG)
    LanguageElement* pElement = phantom::elementByName(a_pStaticMemberFunction->getDecoratedName(), const_cast<ClassType*>(this));
    o_assert(pElement == nullptr OR pElement->getOwner() != this);
#endif
    if(m_pStaticMemberFunctions == nullptr) m_pStaticMemberFunctions = new vector<StaticMemberFunction*>;
    m_pStaticMemberFunctions->push_back(a_pStaticMemberFunction);
    addElement(a_pStaticMemberFunction);
}

void ClassType::addMemberFunction( MemberFunction* a_pMemberFunction )
{
    if(a_pMemberFunction->asInstanceMemberFunction())
    {
        addInstanceMemberFunction(a_pMemberFunction->asInstanceMemberFunction());
    }
    else 
    {
        o_assert(a_pMemberFunction->asStaticMemberFunction());
        addStaticMemberFunction(a_pMemberFunction->asStaticMemberFunction());
    }
}

void                    ClassType::removeConstructor( Constructor* a_pConstructor )
{
    o_assert(getConstructor(""));
    removeElement(a_pConstructor);
}

void                ClassType::removeValueMember(ValueMember* a_pValueMember)
{
    removeElement(a_pValueMember);
}

void                ClassType::removeProperty( Property* a_pProperty )
{
    removeElement(a_pProperty);
}

void                ClassType::removeCollection( Collection* a_pCollection)
{
    removeElement(a_pCollection);
}

void                ClassType::removeDataMember(DataMember* a_pDataMember)
{
    removeElement(a_pDataMember->asLanguageElement());
}

void                ClassType::removeInstanceDataMember(InstanceDataMember* a_pDataMember)
{
    removeElement(a_pDataMember);
}

void                ClassType::removeStaticDataMember(StaticDataMember* a_pDataMember)
{
    removeElement(a_pDataMember);
}

void                ClassType::removeInstanceMemberFunction(InstanceMemberFunction* a_pInstanceMemberFunction)
{
    removeElement(a_pInstanceMemberFunction);
}

void                ClassType::removeStaticMemberFunction(StaticMemberFunction* a_pStaticMemberFunction)
{
    removeElement(a_pStaticMemberFunction);
}

void ClassType::removeMemberFunction( MemberFunction* a_pMemberFunction )
{
    removeElement(a_pMemberFunction->asLanguageElement());
}

void ClassType::interpolate( void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode /*= 0*/ ) const
{
    auto it = m_ValueMembers.begin();
    auto end = m_ValueMembers.end();
    byte scratch_start[phantom::max_type_size];
    byte scratch_end[phantom::max_type_size];
    byte scratch_result[phantom::max_type_size];
    for(; it != end; ++it)
    {
        ValueMember* pValueMember = static_cast<ValueMember*>((*it));
        pValueMember->getValue(a_src_start, scratch_start);
        pValueMember->getValue(a_src_end, scratch_end);
        pValueMember->getValueType()->interpolate(scratch_start, scratch_end, a_fPercent, scratch_result);
        pValueMember->setValue(a_pDest, scratch_result);
    }
}

void* ClassType::newInstance( Constructor* a_pConstructor, void** a_pArgs /*= NULL*/ ) const
{
    void* pInstance = o_dynamic_pool_allocate(m_uiSize);
    a_pConstructor->construct(pInstance, a_pArgs);
    return pInstance;
}

void* ClassType::newInstance() const
{
  void* pInstance = o_dynamic_pool_allocate(m_uiSize);
  construct(pInstance);
  return pInstance;
}

size_t ClassType::getValueMemberCount() const
{
    return m_ValueMembers.size();
}

size_t ClassType::getCollectionCount() const
{
    return m_pCollections ? m_pCollections->size() : 0;
}

size_t ClassType::getInstanceMemberFunctionCount() const
{
    return m_InstanceMemberFunctions.size();
}

size_t ClassType::getStaticMemberFunctionCount() const
{
    return m_pStaticMemberFunctions ? m_pStaticMemberFunctions->size() : 0;
}

void ClassType::findPublicValueMembersPointingValueType( Type* a_pType, vector<ValueMember*>& out ) const
{
    auto it = m_ValueMembers.begin();
    auto end = m_ValueMembers.end();
    for(; it != end; ++it)
    {
        ValueMember* pValueMember = static_cast<ValueMember*>((*it));
        DataPointerType* pPointerType = pValueMember->getValueType()->asDataPointerType();
        if(pPointerType AND pValueMember->isPublic() AND a_pType->isKindOf(pPointerType->getPointedType()))
        {
            out.push_back(pValueMember);
        }
    }
}

void        ClassType::smartCopy(void* a_pInstance, void const* a_pSource, Type* a_pSourceType) const
{
    ClassType* pSourceClassType = a_pSourceType->asClassType();
    o_assert(pSourceClassType);
    auto it = pSourceClassType->beginValueMembers();
    auto end = pSourceClassType->endValueMembers();
    for(; it!=end; ++it)
    {
        ValueMember* pOldValueMember = (ValueMember*)(*it);
        ValueMember* pNewValueMember = getValueMember(pOldValueMember->getName());
        Type* pOldValueMemberType = pOldValueMember->getValueType();
        Type* pNewValueMemberType = nullptr;
        if(pNewValueMember != nullptr 
            AND pOldValueMemberType->isImplicitlyConvertibleTo((pNewValueMemberType = pNewValueMember->getValueType())))
        {
            void* sourceBuffer = pOldValueMemberType->newInstance();
            pOldValueMember->getValue(a_pSource, sourceBuffer);
            void* newBuffer = pNewValueMemberType->newInstance();
            pOldValueMemberType->convertValueTo(pNewValueMemberType, newBuffer, sourceBuffer);
            pNewValueMember->setValue(a_pInstance, newBuffer);
            pOldValueMemberType->deleteInstance(pOldValueMember);
            pNewValueMemberType->deleteInstance(newBuffer);
        }
    }
}

InstanceMemberFunction* ClassType::getUniqueInstanceMemberFunctionWithName( const string& a_strName ) const
{
    InstanceMemberFunction* pInstanceMemberFunction = nullptr;
    auto it = m_InstanceMemberFunctions.begin();
    auto end = m_InstanceMemberFunctions.end();
    for(;it != end; ++it)
    {
        if(static_cast<InstanceMemberFunction*>((*it))->getName() == a_strName)
        {
            if(pInstanceMemberFunction) return nullptr;
            pInstanceMemberFunction = static_cast<InstanceMemberFunction*>((*it));
        }
    }
    return pInstanceMemberFunction;
}

void ClassType::getElements( vector<LanguageElement*>& out, Class* a_pClass ) const
{
    Type::getElements(out, a_pClass);
    o_assert(false, "deprecated");
    /*auto it = m_Members.begin();
    auto end = m_Members.end();
    if(a_pClass == nullptr)
    {
        for(;it != end; ++it)
        {
            out.push_back((*it));
        }
    }
    else 
    {
        Class* pCurrentClass = nullptr;
        bool bCurrentClassAccepted = false;
        for(;it != end; ++it)
        {
            if(pCurrentClass == nullptr OR pCurrentClass != it->first)
            {
                pCurrentClass = it->first;
                bCurrentClassAccepted = pCurrentClass->isKindOf(a_pClass);
            }
            if(bCurrentClassAccepted)
            {
                out.push_back((*it));
            }
            (*it)->getElements(out, a_pClass);
        }
    }*/
}

void ClassType::addAttribute( const string& a_strName, const variant& a_Variant )
{
    if(m_pAttributes == nullptr)
        m_pAttributes = new map<string, variant>;
    map<string, variant>* pAttributes = static_cast<map<string, variant>*>(m_pAttributes);
    (*pAttributes)[a_strName] = a_Variant;
}

void ClassType::removeAttribute( const string& a_strName )
{
    o_assert(m_pAttributes);
    map<string, variant>* pAttributes = static_cast<map<string, variant>*>(m_pAttributes);
    auto found = pAttributes->find(a_strName);
    o_assert(found != pAttributes->end());
    pAttributes->erase(found);
    if(pAttributes->empty())
    {
        delete ((map<string, variant>*)pAttributes);
        m_pAttributes = nullptr;
    }
}

const variant& ClassType::getAttribute( const string& a_strName ) const
{
    static variant null_variant;
    if(m_pAttributes == nullptr) return null_variant;
    map<string, variant>* pAttributes = static_cast<map<string, variant>*>(m_pAttributes);
    auto found = pAttributes->find(a_strName);
    if(found != pAttributes->end()) return found->second;
    return null_variant;
}

bool ClassType::canBeDestroyed() const
{
    return Type::canBeDestroyed();
}

vector<StaticDataMember*>::const_iterator ClassType::beginStaticDataMembers() const
{
    return m_pStaticDataMembers ? m_pStaticDataMembers->begin() : m_EmptyStaticDataMembers.begin();
}

vector<StaticDataMember*>::const_iterator ClassType::endStaticDataMembers() const
{
    return m_pStaticDataMembers ? m_pStaticDataMembers->end() : m_EmptyStaticDataMembers.end();
}

vector<StaticMemberFunction*>::const_iterator ClassType::beginStaticMemberFunctions() const
{
    return m_pStaticMemberFunctions ? m_pStaticMemberFunctions->begin() : m_EmptyStaticMemberFunctions.begin();
}

vector<StaticMemberFunction*>::const_iterator ClassType::endStaticMemberFunctions() const
{
    return m_pStaticMemberFunctions ? m_pStaticMemberFunctions->end() : m_EmptyStaticMemberFunctions.end();
}

vector<Collection*>::const_iterator ClassType::beginCollections() const
{
    return m_pCollections ? m_pCollections->begin() : m_EmptyCollections.begin();
}

vector<Collection*>::const_iterator ClassType::endCollections() const
{
    return m_pCollections ? m_pCollections->end() : m_EmptyCollections.end();
}

vector<Constructor*>::const_iterator ClassType::beginConstructors() const
{
    return m_pConstructors ? m_pConstructors->begin() : m_EmptyConstructors.begin();
}

vector<Constructor*>::const_iterator ClassType::endConstructors() const
{
    return m_pConstructors ? m_pConstructors->end() : m_EmptyConstructors.end();
}

bool ClassType::referencesData(const void* a_pInstance, const phantom::data& a_Data) const
{
    {
        auto it = m_ValueMembers.rbegin();
        auto end = m_ValueMembers.rend();
        for(; it != end; ++it)
        {
            ValueMember* pValueMember = *it;
            if(pValueMember->referencesData(a_pInstance, a_Data))
                return true;
        }
    }
    /*{
        auto it = beginCollections();
        auto end = endCollections();
        for(; it != end; ++it)
        {
            Collection* pCollection = *it;
            if(pCollection->referencesData(a_pInstance, a_Data))
                return true;
        }
    }*/
    return false;
}

void ClassType::fetchPointerReferenceExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, uint a_uiSerializationMask ) const
{
    {
        auto it = m_ValueMembers.rbegin();
        auto end = m_ValueMembers.rend();
        for(; it != end; ++it)
        {
            ValueMember* pValueMember = *it;
            pValueMember->getValueType()->fetchPointerReferenceExpressions(pValueMember->createAccessExpression(a_pInstanceExpression->clone()), out, a_uiSerializationMask);
        }
    }
    /*{
        auto it = beginCollections();
        auto end = endCollections();
        for(; it != end; ++it)
        {
            Collection* pCollection = *it;
            pCollection->fetchPointerReferenceExpressions(a_pInstance, out, a_uiSerializationMask);
        }
    }*/
}

void ClassType::construct( void* a_pInstance ) const
{
    o_assert(m_pExtraData);
    // Construct attributes
    size_t i = 0;
    Type::aligner aligner(reinterpret_cast<byte*>(a_pInstance)+m_pExtraData->m_uiDataMemberMemoryOffset);

    for(;i<m_pExtraData->m_DataMemberTypes.size();++i)
    {
        aligner.construct(m_pExtraData->m_DataMemberTypes[i]);
    }
}

void    ClassType::finalize()
{
    o_assert(m_pExtraData);
    if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
    {
        o_exception(exception::reflection_runtime_exception, "Class already finalized or compiled");
    }

    m_pExtraData->m_iState = extra_data::e_State_Finalized;
    size_t  memorySize = m_pExtraData->m_AlignmentComputer.compute();
    if(memorySize == 0 AND m_uiSize == 0)
    {
        memorySize = 4;
    }
    if(m_pExtraData->m_AlignmentComputer.maxAlignment() == 0 && memorySize == 0)
    {
        m_pExtraData->m_AlignmentComputer.setMaxAlignement(1);
    }
    size_t  modulo = m_uiSize ? m_uiSize % m_pExtraData->m_AlignmentComputer.maxAlignment() : 0;
    if(modulo)
        m_pExtraData->m_uiAlignmentFixingOffset = m_pExtraData->m_AlignmentComputer.maxAlignment() - modulo;
    m_pExtraData->m_uiDataMemberMemoryOffset = m_uiSize+m_pExtraData->m_uiAlignmentFixingOffset;

    m_uiSize = m_pExtraData->m_uiDataMemberMemoryOffset+memorySize;
    m_uiAlignment = m_pExtraData->m_AlignmentComputer.maxAlignment();

    Type::aligner aligner((byte*)(m_pExtraData->m_uiDataMemberMemoryOffset));

    auto it = m_InstanceDataMembers.begin();
    auto end = m_InstanceDataMembers.end();
    for(;it != end; ++it)
    {
        InstanceDataMember* pDataMember = static_cast<InstanceDataMember*>(*it);
        // Finalize attribute offset
        if(pDataMember)
        {
            pDataMember->setOffset((size_t)aligner.address()); // we convert from relative to absolute attribute offset
            aligner.skip(pDataMember->getValueType());
        }
    }
}

variant     ClassType::compile(Compiler* a_pCompiler)
{
    o_assert(m_pExtraData);
    if(m_pExtraData->m_iState < extra_data::e_State_Finalized)
    {
        finalize();
    }
    o_assert(m_pExtraData->m_iState < extra_data::e_State_Compiling);
    m_pExtraData->m_iState = extra_data::e_State_Compiling;
    return a_pCompiler->compile(this);
}

Constructor* ClassType::createDefaultConstructor() const
{
    o_assert(m_pExtraData);
    return nullptr;
}

InstanceMemberFunction* ClassType::getDestructor() const
{
    InstanceMemberFunction* pDestructor = getInstanceMemberFunction("~"+m_strName+"()");
    if(pDestructor == nullptr)
    {
        pDestructor = createDestructor();
        o_assert(pDestructor->getDecoratedName() == "~"+m_strName+"()");
        const_cast<ClassType*>(this)->addInstanceMemberFunction(pDestructor);
    }
    return pDestructor;
}

InstanceMemberFunction* ClassType::createDestructor() const
{
    Signature* pSignature = o_new(Signature);
    pSignature->setReturnType(typeOf<void>());
    return o_new(InstanceMemberFunction)("~"+m_strName, pSignature, 0);
}

o_namespace_end(phantom, reflection)