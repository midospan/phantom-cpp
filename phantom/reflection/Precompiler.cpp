/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Precompiler.h"
#include "Precompiler.hxx"
// Fundamental expressions
#include <phantom/reflection/SingleParameterFunctionExpression.h>
#include <phantom/reflection/ConstructorCallExpression.h>
#include <phantom/reflection/LocalVariableExpression.h>
#include <phantom/reflection/StaticVariableExpression.h>
#include <phantom/reflection/AssignmentExpression.h>
#include <phantom/reflection/UnaryLogicalExpression.h>
#include <phantom/reflection/BinaryLogicalExpression.h>
#include <phantom/reflection/TUnaryBitExpression.h>
#include <phantom/reflection/TBinaryBitExpression.h>
#include <phantom/reflection/TBinaryIntegralExpression.h>
#include <phantom/reflection/TUnaryArithmeticExpression.h>
#include <phantom/reflection/TBinaryArithmeticExpression.h>
#include <phantom/reflection/TEqualityExpression.h>
#include <phantom/reflection/TBinaryBooleanExpression.h>
#include <phantom/reflection/TPreIncrementExpression.h>
#include <phantom/reflection/TPostIncrementExpression.h>
#include <phantom/reflection/TShiftExpression.h>
#include <phantom/reflection/PointerArithmeticExpression.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/LocalVariable.h>
#include <phantom/reflection/ArrayExpression.h>
#include <phantom/reflection/StringLiteralExpression.h>
#include <phantom/reflection/ConditionalExpression.h>
#include <phantom/reflection/PlacementConstructionExpression.h>
#include <phantom/reflection/AssignmentExpression.h>
#include <phantom/reflection/InstanceDataMemberExpression.h>
#include <phantom/reflection/AddressExpression.h>
#include <phantom/reflection/CallExpression.h>
#include <phantom/reflection/CastExpression.h>
#include <phantom/reflection/MemberFunctionPointerCallExpression.h>
#include <phantom/reflection/DataMemberPointerExpression.h>
#include <phantom/reflection/MemberFunctionPointerType.h>
#include <phantom/reflection/DataMemberPointerType.h>
#include <phantom/reflection/Enum.h>
#include <phantom/reflection/NumericConstant.h>
#include <phantom/reflection/LabelStatement.h>
#include <phantom/reflection/BranchIfStatement.h>
#include <phantom/reflection/BranchIfNotStatement.h>
#include <phantom/reflection/BranchStatement.h>
#include <phantom/reflection/Constant.h>
#include <phantom/reflection/Statement.h>
#include <phantom/reflection/ExpressionStatement.h>
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/BinaryOperationExpression.h>
#include <phantom/reflection/Parameter.h>
#include <phantom/reflection/AggregationClass.h>
#include <phantom/reflection/CompositionClass.h>
/* *********************************************** */
o_registerN((phantom, reflection), Precompiler);

o_namespace_begin(phantom, reflection) 

LanguageElement* Precompiler::precompileScope( LanguageElement* a_pScope, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    if(a_pScope->getTemplateSpecialization())
    {
        LanguageElement* pElement = a_pScope->getTemplateSpecialization()->getType(a_strName);
        if(pElement) return pElement;
    }
    return nullptr;
}

LanguageElement* Precompiler::precompileScope( Namespace* a_pScope, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    LanguageElement* pUsing = a_pScope->getUsing(a_strName);
    if(pUsing)
    {
        if(a_pTemplate AND pUsing->asTemplate())
        {
            return pUsing->getOwner()->precompileScope(this, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
        }
        else if(a_pTemplate == nullptr)
        {
            return pUsing;
        }
    }
    if(a_pFuncSignature)
    {
        vector<Expression*> expressions;
        vector<Type*> types;
        bool bTypes = true;
        bool bExpressions = true;
        for( auto it = a_pFuncSignature->begin(); it != a_pFuncSignature->end(); ++it)
        {
            LanguageElement* pElement = (*it);
            if(pElement)
            {
                Expression* pExpression = pElement->asExpression();
                Type* pType = pElement->asType();
                if(pExpression AND bExpressions)
                {
                    bTypes = false;
                    expressions.push_back(pExpression);
                    types.push_back(pExpression->getValueType());
                }
                else if(pType AND bTypes)
                {
                    bExpressions = false;
                    types.push_back(pType);
                }
                else return nullptr;
            }
            else return nullptr;
        }

        if(bExpressions)
        {
            for(auto it = a_pScope->beginTypes(); it != a_pScope->endTypes(); ++it)
            {
                Type* pType = *it;
                if(pType->getName() == a_strName AND pType->asClassType())
                {
                    vector<size_t> partialMatches;
                    Constructor* pConstructor = pType->asClassType()->getConstructor(types, &partialMatches, a_Modifiers);
                    if(pConstructor == nullptr)
                        return nullptr;
                    if(pType->isCopyable())
                    {
                        return o_new(ConstructorCallExpression)(pConstructor, expressions);
                    }
                }
            }
            map<Function*, vector<size_t>> functionsPartialMatches;
            for(auto it = a_pScope->beginFunctions(); it != a_pScope->endFunctions(); ++it)
            {
                Function* pFunction = *it;
                vector<size_t> partialMatches;
                if(pFunction->matches(a_strName, types, &partialMatches, a_Modifiers))
                {
                    if(partialMatches.empty()) 
                        return o_new(CallExpression)(pFunction, expressions); 
                    functionsPartialMatches[pFunction] = partialMatches;
                }
            }
            if(functionsPartialMatches.size() == 1)
            {
                return o_new(CallExpression)(functionsPartialMatches.begin()->first, expressions);
            }
            return nullptr;
        }
        if(bTypes)
        {
            for(auto it = a_pScope->beginFunctions(); it != a_pScope->endFunctions(); ++it)
            {
                Function* pFunction = *it;
                if(pFunction->matches(a_strName, types, nullptr, a_Modifiers))
                {
                    return pFunction;
                }
            }
        }
    }
    else 
    {
        if(a_pTemplate == nullptr)
        {
            Type* pTypedef = a_pScope->getTypedef(a_strName);
            if(pTypedef != nullptr) return pTypedef;
            Namespace* pNamespaceAlias = a_pScope->getNamespaceAlias(a_strName);
            if(pNamespaceAlias != nullptr) return pNamespaceAlias;
            Template* pTemplate = a_pScope->getTemplate(a_strName);
            if(pTemplate != nullptr) return pTemplate;
        }
        for(auto it = a_pScope->beginTypes(); it != a_pScope->endTypes(); ++it)
        {
            Type* pType = *it;
            if(pType->matches(a_strName, a_pTemplate, a_Modifiers))
            {
                return pType;
            }
            else if(pType->asEnum())
            {
                LanguageElement* pEnumConstant = pType->precompileScope(this, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
                if(pEnumConstant) return pEnumConstant;
            }
        }
        for(auto it = a_pScope->beginVariables(); it != a_pScope->endVariables(); ++it)
        {
            StaticVariable* pVariable = *it;
            if(pVariable->getName() == a_strName)
            {
                return pVariable;
            }
        }
    }
    if(a_pTemplate != nullptr) 
        return nullptr;
    for(auto it = a_pScope->beginNamespaces(); it != a_pScope->endNamespaces(); ++it)
    {
        Namespace* pNamespace = *it;
        if(pNamespace->getName() == a_strName )
            return pNamespace;
    }
    return nullptr;
}

LanguageElement* Precompiler::precompileScope( Type* a_pScope, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    LanguageElement* pElement = precompileScope(static_cast<LanguageElement*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
    if(pElement) return pElement;
    Type* pNestedTypedef = a_pScope->getNestedTypedef(a_strName);
    if(pNestedTypedef) return pNestedTypedef;
    if(a_pScope->getNestedTypeCount())  
    {
        size_t i = 0;
        size_t count = a_pScope->getNestedTypeCount();
        for(;i<count;++i)
        {
            Type* pNestedType = a_pScope->getNestedType(i);
            if(pNestedType->matches(a_strName, a_pTemplate, a_Modifiers))
            {
                return pNestedType;
            }
            else if(pNestedType->asEnum())
            {
                LanguageElement* pConstant = pNestedType->precompileScope(this, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
                if(pConstant) return pConstant;
            }
        }
    }
    return nullptr;
}

LanguageElement* Precompiler::precompileScope( ConstType* a_pType, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    return a_pType->getConstedType()->precompileScope(this, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
}

LanguageElement* Precompiler::precompileScope( Enum* a_pScope, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    if(a_pTemplate) return precompileScope(static_cast<LanguageElement*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
    if(a_pFuncSignature) return precompileScope(static_cast<LanguageElement*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
    Constant* pConstant = a_pScope->getConstant(a_strName);
    return pConstant ? o_new(ConstantExpression)(pConstant) : nullptr;
}

LanguageElement* Precompiler::precompileScope( ClassType* a_pScope, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    LanguageElement* pElement = precompileScope(static_cast<Type*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
    if(pElement) return pElement;
    if(a_pFuncSignature == nullptr AND a_pTemplate == nullptr)
    {
        StaticDataMember* pStaticDataMember = a_pScope->getStaticDataMember(a_strName);
        if(pStaticDataMember)
        {
            return pStaticDataMember->asLanguageElement();
        }
        return a_pScope->getValueMember(a_strName);
    }
    if(a_pFuncSignature)
    {
        vector<Type*> types;
        if(a_pFuncSignature->empty())
        {
            if(a_strName == a_pScope->getName())
            {
                // Constructor
                return a_pScope->getConstructor(types, nullptr, a_Modifiers);
            }
            MemberFunction* pMemberFunction = a_pScope->getMemberFunction(a_strName, types, nullptr, a_Modifiers);
            if(pMemberFunction AND pMemberFunction->asStaticMemberFunction())
            {
                vector<Expression*> arguments;
                return o_new(CallExpression)(pMemberFunction->asStaticMemberFunction(), arguments);
            }
            return pMemberFunction ? pMemberFunction->asLanguageElement() : nullptr;
        }
        else 
        {
            LanguageElement* pElem = a_pFuncSignature->front();
            Type* pType = pElem ? pElem->asType() : nullptr;
            Expression* pExpression;
            // If the first element is a type, we look for a signature, not a call
            if(pType)
            {
                types.push_back(pType);
                for(auto it = a_pFuncSignature->begin()+1; it != a_pFuncSignature->end(); ++it)
                {
                    pElem = *it;
                    pType = pElem ? pElem->asType() : nullptr;
                    if(pType == nullptr) return precompileScope(static_cast<LanguageElement*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
                    types.push_back(pType);
                }
                if(a_strName == a_pScope->getName())
                {
                    // Constructor
                    return a_pScope->getConstructor(types, nullptr, a_Modifiers);
                }
                // Don't accept member function with partial matches
                MemberFunction* pMemberFunction = a_pScope->getMemberFunction(a_strName, types, nullptr, a_Modifiers);
                return pMemberFunction ? pMemberFunction->asLanguageElement() : nullptr;
            }
            // If the first element is an expression, we look for a call
            else if((pExpression = pElem ? pElem->asExpression() : nullptr))
            {
                vector<Expression*> expressions;
                vector<Expression*> arguments;
                expressions.push_back(pExpression);
                types.push_back(pExpression->getValueType());
                for(auto it = a_pFuncSignature->begin()+1; it != a_pFuncSignature->end(); ++it)
                {
                    pExpression = (*it) ? (*it)->asExpression() : nullptr;
                    if(pExpression == nullptr) 
                        return precompileScope(static_cast<LanguageElement*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
                    expressions.push_back(pExpression);
                    types.push_back(pExpression->getValueType());
                }
                vector<size_t> partialMatches;
                if(a_pScope->getNestedTypeCount())
                {
                    for(size_t i = 0 ;i<a_pScope->getNestedTypeCount(); ++i)
                    {
                        Type* pType = a_pScope->getNestedType(i);
                        if(pType->getName() == a_strName)
                        {
                            // Constructor
                            Constructor* pConstructor = a_pScope->getConstructor(types, &partialMatches, a_Modifiers);
                            if(pConstructor == nullptr)
                                return precompileScope(static_cast<LanguageElement*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
                            if(a_pScope->isCopyable())
                            {
                                return o_new(ConstructorCallExpression)(pConstructor, expressions);
                            }
                        }
                    }
                }
                // Accepts member function with partial matches
                StaticMemberFunction* pStaticMemberFunction = a_pScope->getStaticMemberFunction(a_strName, types, &partialMatches, a_Modifiers);
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
    return nullptr;
}

LanguageElement* Precompiler::precompileScope( Class* a_pScope, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    LanguageElement* pElement = precompileScope(static_cast<ClassType*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
    if(pElement) return pElement;
    auto it = a_pScope->beginBaseClasses();
    auto end = a_pScope->endBaseClasses();
    for(;it != end; ++it)
    {
        if(it->m_pClass->matches(a_strName, a_pTemplate))
        {
            return it->m_pClass;
        }
        if(pElement = it->m_pClass->precompileScope(this, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers))
        {
            if(pElement->asConstructor() == nullptr)
            {
                return pElement;
            }
        }
    }
    return nullptr;
}

LanguageElement* Precompiler::precompileScope( state::StateMachine* a_pScope, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileScope(static_cast<LanguageElement*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
}

LanguageElement* Precompiler::precompileScope( state::State* a_pScope, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileScope(static_cast<LanguageElement*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
}

LanguageElement* Precompiler::precompileScope( state::Track* a_pScope, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileScope(static_cast<LanguageElement*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
}

LanguageElement* Precompiler::precompileScope( Block* a_pScope, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    LocalVariable* pLocal = a_pScope->getLocalVariable(a_strName);
    if(pLocal) return o_new(LocalVariableExpression)(pLocal);
    int blockIndex = -1;
    sscanf(a_strName.c_str(), "%d", &blockIndex);
    if(blockIndex >= 0 AND blockIndex < (int)a_pScope->getStatementCount())
    {
        size_t c = 0;
        for(auto it = a_pScope->beginStatements(); it != a_pScope->endStatements(); ++it)
        {
            Block* pChildBlock = (*it)->asBlock();
            if(pChildBlock)
            {
                if(c == blockIndex)
                {
                    return pChildBlock;
                }
                ++c;
            }
        }
    }
    pLocal = a_pScope->getLocalVariable("this");
    if(pLocal)
    {
        LocalVariableExpression* pThis = o_new(LocalVariableExpression)(pLocal);
        Expression* pThisDereferenced = pThis->dereference();
        LanguageElement* pElement = pThisDereferenced->precompileScope(this, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
        if(pElement) return pElement;
        o_dynamic_delete pThisDereferenced;
    }
    return precompileScope(static_cast<LanguageElement*>(a_pScope), a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
}

LanguageElement* Precompiler::precompileScope( Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<LanguageElement*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    if(a_pExpression->getValueType() == nullptr)
    {
        return nullptr;
    }
    if(a_pExpression->hasEffectiveAddress())
    {
        if(a_pFuncSignature)
        {
            vector<Expression*> expressions;
            for(auto it = a_pFuncSignature->begin(); it != a_pFuncSignature->end(); ++it)
            {
                LanguageElement* pElement = *it;
                if(pElement)
                {
                    Expression* pExpression = pElement->asExpression();
                    if(pExpression == nullptr)
                    {
                        //o_semantic_error("invalid parameter expression");
                    }
                    expressions.push_back(pExpression);
                }
                else 
                {
                    expressions.push_back(nullptr);
                }
            }
            return a_pExpression->getValueType()->precompileExpression(this, a_pExpression->reference(), a_strName, a_pTemplate, &expressions, a_Modifiers);
        }
        else return a_pExpression->getValueType()->precompileExpression(this, a_pExpression->reference(), a_strName, a_pTemplate, nullptr, a_Modifiers);
    }
    return nullptr;
}

Expression* Precompiler::precompileExpression( ReferenceType* a_pType, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<Expression*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    return a_pType->getReferencedType()->precompileExpression(this, a_pExpression, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
}

Expression* Precompiler::precompileExpression( ConstType* a_pType, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<Expression*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    return a_pType->getConstedType()->precompileExpression(this, a_pExpression, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers | o_const);
}

Expression* Precompiler::precompileExpression( ClassType* a_pType, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<Expression*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    if((a_pExpression->getValueType()->removeReference()->asConstType() != nullptr) != ((a_Modifiers & o_const) == o_const))
    {
        // o_exception(exception::reflection_runtime_exception, "Incoherency between const modifier and expression const type");
        return nullptr;
    }
    if(a_pExpression->getValueType()->removeReference()->removeConst() != a_pType) 
    {
        // o_exception(exception::reflection_runtime_exception, "LHS Expression type doesn't match current class");
        return nullptr;
    }
    if(NOT(a_pExpression->hasEffectiveAddress())) 
    {
        return nullptr;
    }

    if(a_pTemplate == nullptr && a_pFuncSignature == nullptr)
    {
        StaticDataMember* pStaticDataMember = a_pType->getStaticDataMember(a_strName);
        if(pStaticDataMember)
        {
            return o_new(StaticVariableExpression)(pStaticDataMember, a_pExpression);
        }
        ValueMember* pValueMember = a_pType->getValueMember(a_strName);
        if(pValueMember) 
        {
            return pValueMember->createExpression(a_pExpression->reference());
        }
        vector<Subroutine*> singleParameterMemberFunctions;
        for(auto it = a_pType->beginInstanceMemberFunctions(); it != a_pType->endInstanceMemberFunctions(); ++it)
        {
            if((*it)->getName() == a_strName && (*it)->getParameterCount() == 1)
            {
                singleParameterMemberFunctions.push_back(*it);
            }
        }
        for(auto it = a_pType->beginStaticMemberFunctions(); it != a_pType->endStaticMemberFunctions(); ++it)
        {
            if((*it)->getName() == a_strName && (*it)->getParameterCount() == 1)
            {
                singleParameterMemberFunctions.push_back(*it);
            }
        }
        if(singleParameterMemberFunctions.size() == 1)
        {
            return o_new(SingleParameterFunctionExpression)(singleParameterMemberFunctions.back(), singleParameterMemberFunctions.back()->asInstanceMemberFunction() ? a_pExpression->implicitCast(a_pType->referenceType()) : nullptr);
        }
    }
    else if(a_pFuncSignature)
    {
        vector<Type*> types;
        if(a_pFuncSignature->empty())
        {
            MemberFunction* pMemberFunction = nullptr;
            if(a_pExpression->isConstExpression()) 
            {
                pMemberFunction = a_pType->getMemberFunction(a_strName, types, nullptr, a_Modifiers|o_const);
            }
            else 
            {
                pMemberFunction = a_pType->getMemberFunction(a_strName, types, nullptr, a_Modifiers|o_noconst);
                if(pMemberFunction == nullptr)
                {
                    pMemberFunction = a_pType->getMemberFunction(a_strName, types, nullptr, a_Modifiers|o_const);
                }
            }
            vector<Expression*> arguments;
            if(pMemberFunction)
            {
                if(pMemberFunction->asInstanceMemberFunction())
                {
                    arguments.push_back(a_pExpression->reference());
                }
                return o_new(CallExpression)(pMemberFunction->asSubroutine(), arguments);
            }
        }
        else 
        {
            Type* pType = a_pFuncSignature->front()->asType();
            Expression* pExpression = a_pFuncSignature->front()->asExpression();
            if(pExpression)
            {
                vector<Expression*> expressions;
                vector<Expression*> arguments;
                types.push_back(pExpression->getValueType());
                expressions.push_back(pExpression);
                for(auto it = a_pFuncSignature->begin()+1; it != a_pFuncSignature->end(); ++it)
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
                if(a_pExpression->isConstExpression())
                {
                    pMemberFunction = a_pType->getMemberFunction(a_strName, types, &partialMatches, a_Modifiers|o_const);
                }
                else 
                {
                    pMemberFunction = a_pType->getMemberFunction(a_strName, types, &partialMatches, a_Modifiers|o_noconst);
                    if(pMemberFunction == nullptr)
                    {
                        pMemberFunction = a_pType->getMemberFunction(a_strName, types, &partialMatches, a_Modifiers|o_const);
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
                        arguments.insert(arguments.begin(), a_pExpression->reference());
                    }
                    return o_new(CallExpression)(pMemberFunction->asSubroutine(), arguments);
                }
                return nullptr;
            }
        }
    }
    return precompileExpression(static_cast<Type*>(a_pType), a_pExpression, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
}

Expression* Precompiler::precompileExpression( Class* a_pType, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<Expression*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    if((a_pExpression->getValueType()->removeReference()->asConstType() != nullptr) != ((a_Modifiers & o_const) == o_const))
    {
        o_exception(exception::reflection_runtime_exception, "Incoherency between const modifier and expression const type");
    }
    if(a_pExpression->getValueType()->removeReference()->removeConst() != a_pType)
    {
        o_exception(exception::reflection_runtime_exception, "LHS Expression type doesn't match current class");
    }
    Expression* pExpression = precompileExpression(static_cast<ClassType*>(a_pType), a_pExpression, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
    if(pExpression) return pExpression;
    a_pExpression->detach();
    auto it = a_pType->beginBaseClasses();
    auto end = a_pType->endBaseClasses();
    for(;it != end; ++it)
    {
        Expression* pCast = a_pExpression->implicitCast(it->m_pClass->referenceType());
        if(pExpression = it->m_pClass->precompileExpression(this, pCast, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers))
        {
            return pExpression;
        }
        else
        {
            a_pExpression->detach(); // ensure left expression is detached from owner before destroying pCast
            o_dynamic_delete (pCast);
        }
    }
    return nullptr;
}

Expression* Precompiler::precompileExpression( AggregationClass* a_pType, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<Expression*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    if(a_strName == "operator[]" AND a_pFuncSignature AND a_pFuncSignature->size() == 1 && a_pFuncSignature->back()->asExpression() && a_pFuncSignature->back()->asExpression()->getValueType()->isImplicitlyConvertibleTo(typeOf<size_t>()))
    {
        return o_new(AggregationGetSetExpression)(a_pExpression, a_pFuncSignature->back()->asExpression()->implicitCast(typeOf<size_t>()), a_pType);
    }
    else if(a_strName == "operator()" AND a_pFuncSignature AND a_pFuncSignature->size() == 1 && a_pFuncSignature->back()->asExpression() && a_pFuncSignature->back()->asExpression()->getValueType()->isImplicitlyConvertibleTo(typeOf<size_t>()))
    {
        return o_new(AggregationInsertRemoveExpression)(a_pExpression, a_pFuncSignature->back()->asExpression()->implicitCast(typeOf<size_t>()), a_pType);
    }
    return precompileExpression(static_cast<Class*>(a_pType), a_pExpression, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
}

Expression* Precompiler::precompileExpression( CompositionClass* a_pType, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<Expression*>* a_pFuncSignature /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
{
    if(a_strName == "operator[]" AND a_pFuncSignature AND a_pFuncSignature->size() == 1 && a_pFuncSignature->back()->asExpression() && a_pFuncSignature->back()->asExpression()->getValueType()->isImplicitlyConvertibleTo(typeOf<size_t>()))
    {
        return o_new(CompositionGetSetExpression)(a_pExpression, a_pFuncSignature->back()->asExpression()->implicitCast(typeOf<size_t>()), a_pType);
    }
    else if(a_strName == "operator()" AND a_pFuncSignature AND a_pFuncSignature->size() == 1 && a_pFuncSignature->back()->asExpression() && a_pFuncSignature->back()->asExpression()->getValueType()->isImplicitlyConvertibleTo(typeOf<size_t>()))
    {
        return o_new(CompositionInsertRemoveExpression)(a_pExpression, a_pFuncSignature->back()->asExpression()->implicitCast(typeOf<size_t>()), a_pType);
    }
    return precompileExpression(static_cast<Class*>(a_pType), a_pExpression, a_strName, a_pTemplate, a_pFuncSignature, a_Modifiers);
}

Expression* Precompiler::precompileOperator( PointerType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    if(a_strOperator.size() == 1 && a_Arguments.size() == 2)
    {
        Expression* pRightExpression = a_Arguments[1];
        ConstantExpression* pConstantRightExpression = pRightExpression->asConstantExpression();
        if(pConstantRightExpression AND pConstantRightExpression->getConstant()->isIntegralZero())
        {
            pRightExpression = pConstantRightExpression->cast(a_Arguments[0]->getValueType()->removeReference());
        }
        switch(a_strOperator[0])
        {
        case '=': // Assignment operation
            {
                if(pRightExpression->getValueType()->isImplicitlyConvertibleTo(a_Arguments[0]->getValueType()->removeReference()))
                {
                    return o_new(AssignmentExpression)(a_Arguments[0], pRightExpression);
                }
            }
        }
    }
    return nullptr;
}

Expression* Precompiler::precompileOperator( MemberPointerType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    if(a_strOperator.size() == 1 && a_Arguments.size() == 2)
    {
        Expression* pRightExpression = a_Arguments[1];
        switch(a_strOperator[0])
        {
        case '=': // Assignment operation
            {
                if(pRightExpression->getValueType()->isImplicitlyConvertibleTo(a_Arguments[0]->getValueType()->removeReference()))
                {
                    return o_new(AssignmentExpression)(a_Arguments[0], pRightExpression);
                }
            }
        }
    }
    return nullptr;
}

Expression* Precompiler::precompileOperator( DataPointerType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    o_assert(a_Arguments[0]->getValueType()->removeReference()->removeConst() == a_pType);
    if(a_strOperator == "*" && a_Arguments.size() == 1)
    {
        return a_Arguments.back()->dereference();
    }
    if(a_strOperator == "->")
    {
        if(a_Arguments.size() != 1) return nullptr;
        return a_Arguments.back()->dereference();
    }
    else if(a_strOperator.size() == 2 && a_Arguments.size() == 2)
    {
        if(a_strOperator == "&&" OR a_strOperator == "||")
        {
            return o_new(BinaryLogicalExpression)(a_strOperator, a_Arguments[0], a_Arguments[1]);
        }/*
        else if(a_strOperator == ">>" OR a_strOperator == "<<")
        {
            return o_new(TBinaryBitExpression<void*>)(a_strOperator, a_Arguments[0], a_Arguments[1]);
        }*/
        else if(a_strOperator[1] == '=') // Assignment operation
        {
            Expression* pSubExpression = nullptr;
            switch(a_strOperator[0])
            {
            case '+':
            case '-':
                if(a_Arguments[1]->getValueType()->isImplicitlyConvertibleTo(typeOf<int>()))
                {
                    pSubExpression = o_new(PointerArithmeticExpression)(a_strOperator.substr(0, 1), a_Arguments[0], a_Arguments[1]);
                }
                break;
            case '=':
            case '!':
            case '<':
            case '>':
                return o_new(TBinaryBooleanExpression<void*>)(a_strOperator, a_Arguments[0], a_Arguments[1]);
            /*case '|':
            case '&':
            case '^':
                pSubExpression = o_new(TBinaryBitExpression<void*>)(a_strOperator.substr(0, 1), a_Arguments[0], a_Arguments[1]);
                break;*/

            }
            if(pSubExpression)
            {
                return o_new(AssignmentExpression)(a_Arguments[0], pSubExpression);
            }
        }
    }
    else if(a_strOperator.size() == 1 && a_Arguments.size() == 2)
    {
        Expression* pRightExpression = a_Arguments[1];
        ConstantExpression* pConstantRightExpression = pRightExpression->asConstantExpression();
        if(pConstantRightExpression AND pConstantRightExpression->getValueType()->asIntegralType())
        {
            pRightExpression = pConstantRightExpression->cast(a_Arguments[0]->getValueType()->removeReference());
        }
        switch(a_strOperator[0])
        {
        case '=': // Assignment operation
            {
                if(pRightExpression->getValueType()->isImplicitlyConvertibleTo(a_Arguments[0]->getValueType()->removeReference()))
                {
                    return o_new(AssignmentExpression)(a_Arguments[0], pRightExpression);
                }
            }
    
        case '<':
        case '>':
            return o_new(TBinaryBooleanExpression<void*>)(a_strOperator, a_Arguments[0], pRightExpression);
        }
    }
    return precompileOperator(static_cast<PointerType*>(a_pType), a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( ReferenceType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    if(a_strOperator == "&" && a_Arguments.size() == 1)
    {
        return a_Arguments.back()->address();
    }
    else 
    {
        return a_pType->getReferencedType()->precompileOperator(this, a_strOperator, a_Arguments, a_Modifiers);
    }
}

Expression* Precompiler::precompileOperator( ConstType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return a_pType->getConstedType()->precompileOperator(this, a_strOperator, a_Arguments, a_Modifiers|o_const);
}

Expression* Precompiler::precompileOperator( ArrayType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    if(a_strOperator == "[]" AND a_Arguments.size() == 2)
    {
        if(a_Arguments[0]->getValueType()->removeReference()->removeConst() == a_pType)
        {
            if(a_Arguments[1]->getValueType()->isConvertibleTo(typeOf<size_t>()))
            {
                if(a_Modifiers & o_const)
                {
                    return o_new(ArrayExpression)( a_pType->constType(), a_Arguments[0], a_Arguments[1]);
                }
                else 
                {
                    return o_new(ArrayExpression)( a_pType, a_Arguments[0], a_Arguments[1]);
                }
            }
        }
    }
    return precompileOperator(static_cast<Type*>(a_pType), a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( Enum* a_pEnum, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return a_pEnum->getIntType()->precompileOperator(this, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( ClassType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    o_assert(a_Arguments.size());
    vector<Expression*> expressions;
    if(a_Arguments.size() == 2)
    {
        expressions.push_back(a_Arguments[1]);
    }
    Expression* pExpression = a_pType->precompileExpression(this, a_Arguments[0], "operator"+a_strOperator, nullptr, &expressions, a_Modifiers);
    if(pExpression)
    {
        return pExpression;
    }
    if(a_strOperator == "=" AND a_Arguments[1]->getValueType()->isImplicitlyConvertibleTo(a_pType))
    {
        return o_new(AssignmentExpression)(a_Arguments[0], a_Arguments[1]);
    }
    return precompileOperator(static_cast<Type*>(a_pType), a_strOperator, a_Arguments, a_Modifiers);
}

template<typename t_Ty>
Expression* Precompiler::precompileArithmeticOperator(native::TArithmeticType<t_Ty>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/)
{
    o_assert(a_Arguments.size());
    o_assert(a_Arguments[0]->getValueType()->isImplicitlyConvertibleTo(((Type*)a_pType)));
    if(a_Arguments.size() == 2)
    {
        if(a_strOperator.size() == 2)
        {
            if(a_strOperator == "==" OR a_strOperator == "!=")
            {
                return o_new(TEqualityExpression<t_Ty>)(a_strOperator, a_Arguments[0], a_Arguments[1]);
            }
            else if(a_strOperator[1] == '=') // Assignment operation or equality test
            {
                Expression* pSubExpression = nullptr;
                switch(a_strOperator[0])
                {
                case '+':
                case '-':
                case '*':
                case '/':
                    pSubExpression = o_new(TBinaryArithmeticExpression<t_Ty>)(a_strOperator.substr(0, 1), a_Arguments[0], a_Arguments[1]);
                    break;

                case '=':
                case '!':
                case '<':
                case '>':
                    return o_new(TBinaryBooleanExpression<t_Ty>)(a_strOperator, a_Arguments[0], a_Arguments[1]);

                }
                if(pSubExpression)
                {
                    return o_new(AssignmentExpression)(a_Arguments[0], pSubExpression);
                }
            }
        }
        else if(a_strOperator.size() == 1)
        {
            switch(a_strOperator[0])
            {
            case '=':
                {
                    return o_new(AssignmentExpression)(a_Arguments[0], a_Arguments[1]);
                }
            case '+':
            case '-':
            case '*':
            case '/':
                {
                    return o_new(TBinaryArithmeticExpression<t_Ty>)(a_strOperator, a_Arguments[0], a_Arguments[1]);
                }
            case '<':
            case '>':
                {
                    return o_new(TBinaryBooleanExpression<t_Ty>)(a_strOperator, a_Arguments[0], a_Arguments[1]);
                }
            }
        }
    }
    else if(a_Arguments.size() == 1)
    {
        if(a_strOperator.size() == 1)
        {
            if(a_strOperator[0] == '+' OR a_strOperator[0] == '-')
            {
                return o_new(TUnaryArithmeticExpression<t_Ty>)(a_strOperator, a_Arguments[0]);
            }
        }
    }
    return precompileOperator(reinterpret_cast<PrimitiveType*>(a_pType), a_strOperator, a_Arguments, a_Modifiers);
}

template<typename t_Ty>
Expression* Precompiler::precompileFloatingPointOperator(native::TFloatingPointType<t_Ty>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/)
{
    return precompileArithmeticOperator<t_Ty>(reinterpret_cast<native::TArithmeticType<t_Ty>*>(a_pType), a_strOperator, a_Arguments, a_Modifiers);
}

template<typename t_Ty>
Expression* Precompiler::precompileIntegralOperator(native::TIntegralType<t_Ty>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/)
{
    o_assert(a_Arguments.size());
    o_assert(a_Arguments[0]->getValueType()->isImplicitlyConvertibleTo((Type*)a_pType));
    if(a_strOperator.size() == 3)
    {
        if((a_strOperator == ">>=" OR a_strOperator == "<<=") AND a_Arguments.size() == 2)
        {
            return o_new(AssignmentExpression)(a_Arguments[0], o_new(TShiftExpression<t_Ty>)(a_strOperator, a_Arguments[0], a_Arguments[1]));
        }
    }
    else if(a_strOperator.size() == 2)
    {
        if(a_Arguments.size() == 2)
        {
            if(a_strOperator == "&&" OR a_strOperator == "||")
            {
                return o_new(BinaryLogicalExpression)(a_strOperator, a_Arguments[0], a_Arguments[1]);
            }
            else if(a_strOperator == "++" OR a_strOperator == "--")
            {
                if(a_Arguments[0]->getValueType() == ((Type*)a_pType)->referenceType())
                {
                    return o_new(TPostIncrementExpression<t_Ty>)(a_strOperator, a_Arguments[0]);
                }
            }
            else if(a_strOperator == ">>" OR a_strOperator == "<<")
            {
                return o_new(TShiftExpression<t_Ty>)(a_strOperator, a_Arguments[0], a_Arguments[1]);
            }
            else if(a_strOperator[1] == '=') // Assignment operation
            {
                Expression* pSubExpression = nullptr;
                switch(a_strOperator[0])
                {
                case '|':
                case '&':
                case '^':
                    pSubExpression = o_new(TBinaryBitExpression<t_Ty>)(a_strOperator.substr(0, 1), a_Arguments[0], a_Arguments[1]);
                    break;

                case '%':
                    pSubExpression = o_new(TBinaryIntegralExpression<t_Ty>)(a_strOperator.substr(0, 1), a_Arguments[0], a_Arguments[1]);
                    break;
                }
                if(pSubExpression)
                {
                    return o_new(AssignmentExpression)(a_Arguments[0], pSubExpression);
                }
            }
        }
        else
        {
            if(a_strOperator == "++" OR a_strOperator == "--")
            {
                if(a_Arguments[0]->getValueType() == ((Type*)a_pType)->referenceType())
                {
                    return o_new(TPreIncrementExpression<t_Ty>)(a_strOperator, a_Arguments[0]);
                }
            }
        }
    }
    else if(a_strOperator.size() == 1)
    {
        if(a_Arguments.size() == 2)
        {
            if(a_strOperator[0] == '&' OR a_strOperator[0] == '|' OR a_strOperator[0] == '^')
            {
                return o_new(TBinaryBitExpression<t_Ty>)(a_strOperator, a_Arguments[0], a_Arguments[1]);
            }
            else if(a_strOperator[0] == '%')
            {
                return o_new(TBinaryIntegralExpression<t_Ty>)(a_strOperator, a_Arguments[0], a_Arguments[1]);
            }
        }
        else if(a_Arguments.size() == 1)
        {
            if(a_strOperator[0] == '!' )
            {
                return o_new(UnaryLogicalExpression)(a_strOperator, a_Arguments[0]);
            }
            else if(a_strOperator[0] == '~')
            {
                return o_new(TUnaryBitExpression<t_Ty>)(a_strOperator, a_Arguments[0]);
            }
            else if(a_strOperator[0] == '@')
            {
                if(phantom::getCurrentDataBase())
                {
                    return o_new(DataExpression)(phantom::getCurrentDataBase(), a_Arguments.back());
                }
            }
        }
    }
    return precompileArithmeticOperator<t_Ty>(reinterpret_cast<native::TArithmeticType<t_Ty>*>(a_pType), a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TFundamentalType<void>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return nullptr;
}

Expression* Precompiler::precompileOperator( native::TIntegralType<bool>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TIntegralType<char>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TIntegralType<uchar>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}
#if o_HAS_BUILT_IN_WCHAR_T
Expression* Precompiler::precompileOperator( native::TIntegralType<wchar_t>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}
#endif
Expression* Precompiler::precompileOperator( native::TIntegralType<short>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TIntegralType<ushort>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TIntegralType<int>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TIntegralType<uint>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TIntegralType<long>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TIntegralType<ulong>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TIntegralType<longlong>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TIntegralType<ulonglong>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileIntegralOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TFloatingPointType<float>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileFloatingPointOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TFloatingPointType<double>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileFloatingPointOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( native::TFloatingPointType<longdouble>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    return precompileFloatingPointOperator(a_pType, a_strOperator, a_Arguments, a_Modifiers);
}

Expression* Precompiler::precompileOperator( Expression* a_pExpression, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ )
{
    vector<Expression*> newExpressions;
    newExpressions.push_back(a_pExpression);
    if(a_Arguments.size() > 0)
    {
        newExpressions.insert(newExpressions.end(), a_Arguments.begin(), a_Arguments.end());

        Type* pEffectiveType = a_pExpression->getValueType()->removeReference();
        // Use 'strongest' type to solve operation
        if((pEffectiveType->getTypeId() >= e_struct) OR (pEffectiveType->getTypeId() >= a_Arguments.back()->getValueType()->removeReference()->getTypeId()))
        {
            return a_pExpression->getValueType()->precompileOperator(this, a_strOperator, newExpressions, a_Modifiers);
        }
        else 
        {
            return a_Arguments.back()->getValueType()->precompileOperator(this, a_strOperator, newExpressions, a_Modifiers);
        }
    }
    else 
    {
        return a_pExpression->getValueType()->precompileOperator(this, a_strOperator, newExpressions, a_Modifiers);
    }
}


/// TEMPLATE INSTANCIATION



LanguageElement* Precompiler::instanciateTemplate( LanguageElement* a_pElement, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Namespace* a_pNamespace, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Type* a_pType, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( PrimitiveType* a_pType, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate(FunctionPointerType* a_pType, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate(MemberFunctionPointerType* a_pType, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate(DataMemberPointerType* a_pType, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate(DataPointerType* a_pType, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate(ReferenceType* a_pType, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate(ConstType* a_pType, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate(ArrayType* a_pType, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Enum* a_pEnum, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( ClassType* a_pClassType, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Class* a_pClass, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Structure* a_pStructure, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Union* a_pUnion, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( PODUnion* a_pPODUnion, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( AnonymousSection* a_pAnonymousSection, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( AnonymousStruct* a_pAnonymousStruct, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( AnonymousUnion* a_pAnonymousUnion, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Template* a_pTemplate, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( TemplateSpecialization* a_pTemplateSpecialization, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Subroutine* a_pSubroutine, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Constructor* a_pConstructor, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Function* a_pFunction, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( StaticMemberFunction* a_pStaticMemberFunction, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( InstanceMemberFunction* a_pInstanceMemberFunction, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Signal* a_pSignal, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( StaticDataMember* a_pStaticDataMember, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( StaticVariable* a_pStaticVariable, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( InstanceDataMember* a_pInstanceDataMember, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Property* a_pProperty, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( state::StateMachine* a_pStateMachine, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( state::State* a_pState, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( state::Track* a_pTrack, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Block* a_pBlock, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( LocalVariable* a_pLocalVariable, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Parameter* a_pParameter, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Signature* a_pSignature, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( BranchStatement* a_pBranchStatement, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( BranchIfStatement* a_pBranchIfStatement, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( BranchIfNotStatement* a_pBranchIfNotStatement, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( ExpressionStatement* a_pExpressionStatement, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( ReturnStatement* a_pReturnStatement, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( LabelStatement* a_pLabelStatement, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( CallExpression* a_pCallExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( CastExpression* a_pCastExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( DereferenceExpression* a_pDereferenceExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( AddressExpression* a_pAddressExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( ReferenceExpression* a_pReferenceExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( ConstantExpression* a_pConstantExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( DataExpression* a_pDataExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( InstanceDataMemberExpression* a_pInstanceDataMemberExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( LocalVariableExpression* a_pLocalVariableExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( PropertyExpression* a_pPropertyExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( StaticVariableExpression* a_pStaticVariableExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( ArrayExpression* a_pArrayExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( StringLiteralExpression* a_pStringLiteralExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( MemberFunctionPointerCallExpression* a_pMemberFunctionPointerCallExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( DataMemberPointerExpression* a_pDataMemberPointerExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( AssignmentExpression* a_pAssignmentExpression, TemplateSpecialization* a_pSpec )
{
    return o_new(AssignmentExpression)(instanciateTemplate(a_pAssignmentExpression->getLeftExpression(), a_pSpec)
        , instanciateTemplate(a_pAssignmentExpression->getRightExpression(), a_pSpec));
}

LanguageElement* Precompiler::instanciateTemplate( ConstructorCallExpression* a_pConstructorCallExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( PlacementConstructionExpression* a_pPlacementConstructionExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( BinaryOperationExpression* a_pBinaryOperatorExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( PreUnaryOperationExpression* a_pPreUnaryOperationExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( PostUnaryOperationExpression* a_pPostUnaryOperationExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( CompositionGetSetExpression* a_pCompositionGetSetExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( AggregationGetSetExpression* a_pAggregationGetSetExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( CompositionInsertRemoveExpression* a_pCompositionInsertRemoveExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( AggregationInsertRemoveExpression* a_pAggregationInsertRemoveExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( SingleParameterFunctionExpression* a_pSingleParameterFunctionExpression, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}

LanguageElement* Precompiler::instanciateTemplate( Constant* a_pConstant, TemplateSpecialization* a_pSpec )
{
    o_assert_no_implementation(); return nullptr;
}







o_namespace_end(phantom, reflection)