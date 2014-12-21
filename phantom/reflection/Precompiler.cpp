/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Precompiler.h"
#include "Precompiler.hxx"
// Fundamental expressions
#include <phantom/reflection/Placeholder.h>
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
#include <phantom/reflection/ArrayExpression.h>
#include <phantom/reflection/PropertyExpression.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/LocalVariable.h>
#include <phantom/reflection/DereferenceExpression.h>
#include <phantom/reflection/AddressExpression.h>
#include <phantom/reflection/ReferenceExpression.h>
#include <phantom/reflection/DataExpression.h>
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
        else 
        {
            for(auto it = a_pScope->beginTemplates(); it != a_pScope->endTemplates(); ++it)
            {
            }
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

#define o_instanciateT(type, element)\
    (((element) == nullptr) ? nullptr : m_Templated[a_pSpec][element] ? m_Templated[a_pSpec][element]->as##type() : ((m_Templated[a_pSpec][element] = (element)->instanciateTemplate(this, a_pSpec))->as##type()))\


void Precompiler::instanciateTemplate( LanguageElement* a_pElement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( Namespace* a_pNamespace, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( Type* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( PrimitiveType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate(FunctionPointerType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate(MemberFunctionPointerType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate(DataMemberPointerType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate(DataPointerType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate(ReferenceType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate(ConstType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate(ArrayType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( Enum* a_pEnum, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( ClassType* a_pClassType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    instanciateTemplate(static_cast<Type*>(a_pClassType), a_pSpec, a_pInstanciated);
    ClassType* pClassType = a_pInstanciated->asClassType();
    for(auto it = a_pClassType->beginInstanceMemberFunctions(); it != a_pClassType->endInstanceMemberFunctions(); ++it)
    {
        InstanceMemberFunction* pInstanceMemberFunction = o_instanciateT(InstanceMemberFunction, *it);
        if(pInstanceMemberFunction->asSignal() == nullptr)
        {
            pClassType->addInstanceMemberFunction(pInstanceMemberFunction);
        }
    }
    for(auto it = a_pClassType->beginInstanceDataMembers(); it != a_pClassType->endInstanceDataMembers(); ++it)
    {
        pClassType->addInstanceDataMember(o_instanciateT(InstanceDataMember, *it));
    }
    for(auto it = a_pClassType->beginStaticDataMembers(); it != a_pClassType->endStaticDataMembers(); ++it)
    {
        pClassType->addStaticDataMember(o_instanciateT(StaticDataMember, *it));
    }
    for(auto it = a_pClassType->beginStaticMemberFunctions(); it != a_pClassType->endStaticMemberFunctions(); ++it)
    {
        pClassType->addStaticMemberFunction(o_instanciateT(StaticMemberFunction, *it));
    }
    for(auto it = a_pClassType->beginConstructors(); it != a_pClassType->endConstructors(); ++it)
    {
        pClassType->addConstructor(o_instanciateT(Constructor, *it));
    }
    for(auto it = a_pClassType->beginProperties(); it != a_pClassType->endProperties(); ++it)
    {
        pClassType->addProperty(o_instanciateT(Property, *it));
    }
}

void Precompiler::instanciateTemplate( Class* a_pClass, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) a_pInstanciated = o_new(Class)(a_pClass->getName(), a_pClass->getModifiers());
    Class* pClass = a_pInstanciated->asClass();
    o_assert(pClass);
    for(auto it = a_pClass->beginBaseClasses(); it != a_pClass->beginBaseClasses(); ++it)
    {
        pClass->addBaseClass(o_instanciateT(Class, it->m_pClass));
    }
    for(auto it = a_pClass->beginSignals(); it != a_pClass->endSignals(); ++it)
    {
        pClass->addSignal(o_instanciateT(Signal, *it));
    }
    instanciateTemplate(static_cast<ClassType*>(a_pClass), a_pSpec, a_pInstanciated);
}

void Precompiler::instanciateTemplate( Structure* a_pStructure, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) a_pInstanciated = o_new(Structure)(a_pStructure->getName(), a_pStructure->getModifiers());
    instanciateTemplate(static_cast<ClassType*>(a_pStructure), a_pSpec, a_pInstanciated);
}

void Precompiler::instanciateTemplate( Union* a_pUnion, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) a_pInstanciated = o_new(Union)(a_pUnion->getName(), a_pUnion->getModifiers());
    instanciateTemplate(static_cast<ClassType*>(a_pUnion), a_pSpec, a_pInstanciated);
}

void Precompiler::instanciateTemplate( PODUnion* a_pPODUnion, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) a_pInstanciated = o_new(PODUnion)(a_pPODUnion->getName(), a_pPODUnion->getModifiers());
    instanciateTemplate(static_cast<ClassType*>(a_pPODUnion), a_pSpec, a_pInstanciated);
}

void Precompiler::instanciateTemplate( AnonymousSection* a_pAnonymousSection, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( AnonymousStruct* a_pAnonymousStruct, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( AnonymousUnion* a_pAnonymousUnion, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( Template* a_pTemplate, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( TemplateSpecialization* a_pTemplateSpecialization, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) a_pInstanciated = o_new(TemplateSpecialization)(a_pTemplateSpecialization->getTemplate());
    TemplateSpecialization* pTemplateSpecialization = a_pInstanciated->asTemplateSpecialization();
    for(size_t i = 0; i<a_pTemplateSpecialization->getArgumentCount(); ++i)
    {
        pTemplateSpecialization->setArgument(i, o_instanciateT(LanguageElement, a_pTemplateSpecialization->getArgument(i)));
    }
}

void Precompiler::instanciateTemplate( Subroutine* a_pSubroutine, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    Subroutine* pSubroutine = a_pInstanciated->asSubroutine();
    o_assert(pSubroutine);
    if(a_pSubroutine->getBlock()) { o_instanciateT(Block, a_pSubroutine->getBlock()); }
}

void Precompiler::instanciateTemplate( Constructor* a_pConstructor, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(Constructor)(a_pConstructor->getName(), o_instanciateT(Signature, a_pConstructor->getSignature()), a_pConstructor->getModifiers());
    }
    instanciateTemplate(static_cast<Subroutine*>(a_pConstructor), a_pSpec, a_pInstanciated);
}

void Precompiler::instanciateTemplate( Function* a_pFunction, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(Function)(a_pFunction->getName(), o_instanciateT(Signature, a_pFunction->getSignature()), a_pFunction->getABI(), a_pFunction->getModifiers());
    }
    instanciateTemplate(static_cast<Subroutine*>(a_pFunction), a_pSpec, a_pInstanciated);
}

void Precompiler::instanciateTemplate( StaticMemberFunction* a_pStaticMemberFunction, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(StaticMemberFunction)(a_pStaticMemberFunction->getName(), o_instanciateT(Signature, a_pStaticMemberFunction->getSignature()), a_pStaticMemberFunction->getModifiers());
    }
    instanciateTemplate(static_cast<Subroutine*>(a_pStaticMemberFunction), a_pSpec, a_pInstanciated);
}

void Precompiler::instanciateTemplate( InstanceMemberFunction* a_pInstanceMemberFunction, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(InstanceMemberFunction)(a_pInstanceMemberFunction->getName(), o_instanciateT(Signature, a_pInstanceMemberFunction->getSignature()), a_pInstanceMemberFunction->getModifiers());
    }
    instanciateTemplate(static_cast<Subroutine*>(a_pInstanceMemberFunction), a_pSpec, a_pInstanciated);
}

void Precompiler::instanciateTemplate( Signal* a_pSignal, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(Signal)(a_pSignal->getName(), o_instanciateT(Signature, a_pSignal->getSignature()), a_pSignal->getModifiers());
    }
    instanciateTemplate(static_cast<Subroutine*>(a_pSignal), a_pSpec, a_pInstanciated);
}

void Precompiler::instanciateTemplate( StaticDataMember* a_pStaticDataMember, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(StaticDataMember)(o_instanciateT(Type, a_pStaticDataMember->getValueType())
                                                , a_pStaticDataMember->getName(), o_instanciateT(Range, a_pStaticDataMember->getRange()), a_pStaticDataMember->getModifiers());
    }
}

void Precompiler::instanciateTemplate( StaticVariable* a_pStaticVariable, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(StaticDataMember)(o_instanciateT(Type, a_pStaticVariable->getValueType())
            , a_pStaticVariable->getName(), o_instanciateT(Range, a_pStaticVariable->getRange()), a_pStaticVariable->getModifiers());
    }
}

void Precompiler::instanciateTemplate( InstanceDataMember* a_pInstanceDataMember, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(InstanceDataMember)(o_instanciateT(Type, a_pInstanceDataMember->getValueType())
            , a_pInstanceDataMember->getName(), o_instanciateT(Range, a_pInstanceDataMember->getRange()), a_pInstanceDataMember->getSerializationMask(), a_pInstanceDataMember->getModifiers());
    }
}

void Precompiler::instanciateTemplate( Property* a_pProperty, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(Property)(o_instanciateT(Type, a_pProperty->getValueType())
            , a_pProperty->getName()
            , o_instanciateT(InstanceMemberFunction, a_pProperty->getGetMemberFunction())
            , o_instanciateT(InstanceMemberFunction, a_pProperty->getGetMemberFunction())
            , o_instanciateT(Signal, a_pProperty->getSignal())
            , o_instanciateT(Range, a_pProperty->getRange())
            , a_pProperty->getSerializationMask()
            , a_pProperty->getModifiers());
    }
}

void Precompiler::instanciateTemplate( state::StateMachine* a_pStateMachine, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(state::StateMachine)(a_pStateMachine->getModifiers());
    }
    state::StateMachine* pStateMachine = a_pInstanciated->asStateMachine();
    pStateMachine->setRootTrack(o_instanciateT(Track, a_pStateMachine->getRootTrack()));
}

void Precompiler::instanciateTemplate( state::State* a_pState, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(state::State)(a_pState->getName(), a_pState->getModifiers());
    }
    state::State* pState = a_pInstanciated->asState();
    for(auto it = a_pState->beginTracks(); it != a_pState->endTracks(); ++it)
    {
        pState->addTrack(o_instanciateT(Track, *it));
    }
}

void Precompiler::instanciateTemplate( state::Track* a_pTrack, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(state::Track)(a_pTrack->getName(), a_pTrack->getSerializationMask(), a_pTrack->getModifiers());
    }
    state::Track* pTrack = a_pInstanciated->asTrack();
    for(auto it = a_pTrack->beginStates(); it != a_pTrack->endStates(); ++it)
    {
        pTrack->addState(o_instanciateT(State, *it));
    }
}

void Precompiler::instanciateTemplate( Block* a_pBlock, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        LocalVariable* pThis = a_pBlock->getLocalVariable("this");
        a_pInstanciated = a_pBlock->getBlock() ? o_new(Block)(a_pBlock->getBlock()) 
                                               : o_new(Block)(o_instanciateT(Subroutine, a_pBlock->getSubroutine()), pThis);
    }
    Block* pBlock = a_pInstanciated->asBlock();
    for(auto it = a_pBlock->beginLocalVariables(); it != a_pBlock->endLocalVariables(); ++it)
    {
        pBlock->addLocalVariable(o_instanciateT(LocalVariable, *it));
    }
    for(auto it = a_pBlock->beginStatements(); it != a_pBlock->endStatements(); ++it)
    {
        pBlock->addStatement(o_instanciateT(Statement, *it));
    }
    for(auto it = a_pBlock->beginRAIIDestructionStatements(); it != a_pBlock->endRAIIDestructionStatements(); ++it)
    {
        pBlock->addRAIIDestructionStatement(o_instanciateT(Statement, *it));
    }
}

void Precompiler::instanciateTemplate( LocalVariable* a_pLocalVariable, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(LocalVariable)(o_instanciateT(Type, a_pLocalVariable->getValueType())
                                                , a_pLocalVariable->getName()
                                                , o_instanciateT(Expression, a_pLocalVariable->getInitializationExpression())
                                                , a_pLocalVariable->getModifiers());
    }
}

void Precompiler::instanciateTemplate( Parameter* a_pParameter, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(Parameter)(o_instanciateT(Type, a_pParameter->getValueType())
            , a_pParameter->getName()
            , o_instanciateT(Expression, a_pParameter->getInitializationExpression())
            , a_pParameter->getModifiers());
    }
}

void Precompiler::instanciateTemplate( Signature* a_pSignature, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        vector<Parameter*> parameters;
        for(auto it = a_pSignature->beginParameters(); it != a_pSignature->endParameters(); ++it)
        {
            parameters.push_back(o_instanciateT(Parameter, *it));
        }
        a_pInstanciated = o_new(Signature)(o_instanciateT(Type, a_pSignature->getReturnType())
            , parameters
            , a_pSignature->getModifiers());
    }
}

void Precompiler::instanciateTemplate( BranchStatement* a_pBranchStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( BranchIfStatement* a_pBranchIfStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(BranchIfStatement)(o_instanciateT(Expression, a_pBranchIfStatement->getExpression()));
    }
}

void Precompiler::instanciateTemplate( BranchIfNotStatement* a_pBranchIfNotStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(BranchIfNotStatement)(o_instanciateT(Expression, a_pBranchIfNotStatement->getExpression()));
    }
}

void Precompiler::instanciateTemplate( ExpressionStatement* a_pExpressionStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(ExpressionStatement)(o_instanciateT(Expression, a_pExpressionStatement->getExpression()));
    }
}

void Precompiler::instanciateTemplate( ReturnStatement* a_pReturnStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        if(a_pReturnStatement->getExpression())
            a_pInstanciated = o_new(ReturnStatement)(o_instanciateT(Expression, a_pReturnStatement->getExpression()));
        else 
            { o_assert_no_implementation(); }
    }
}

void Precompiler::instanciateTemplate( LabelStatement* a_pLabelStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( CallExpression* a_pCallExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        vector<Expression*> arguments;
        bool bTemplateDependant = false;
        for(auto it = a_pCallExpression->beginArguments(); it != a_pCallExpression->endArguments(); ++it)
        {
            Expression* pExpression = o_instanciateT(Expression, *it);
            bTemplateDependant = bTemplateDependant OR pExpression->isTemplateDependant();
            arguments.push_back(pExpression);
        }
        Type* pConstrucionType = a_pCallExpression->getValueType() == a_pCallExpression->getSubroutine()->getReturnType() ? nullptr : a_pCallExpression->getValueType();
        if(bTemplateDependant OR a_pCallExpression->getSubroutine()->asPlaceholder() == nullptr)
        {
            a_pInstanciated = o_new(CallExpression)(o_instanciateT(Subroutine, a_pCallExpression->getSubroutine()), arguments, pConstrucionType);
        }
        else 
        {
            o_assert(a_pCallExpression->getSubroutine()->asPlaceholder());
            Expression* pThis = arguments[0];
            arguments.erase(arguments.begin());
            string name = a_pCallExpression->getSubroutine()->getName();
            size_t pos = 0;
            if((pos = name.find_last_of(":")) != string::npos)
            {
                Class* pClass = pThis->getValueType()->removeConstReference()->asClass();
                if(pClass == nullptr) 
                {
                    a_pInstanciated = o_new(CallExpression)(o_instanciateT(Subroutine, a_pCallExpression->getSubroutine()), arguments, pConstrucionType);
                    return; 
                }
                LanguageElement* pScope = phantom::elementByName(name.substr(0, pos-1), pClass);
                if(pScope == nullptr 
                    OR pScope->asClass() == nullptr 
                    OR NOT(pClass->hasBaseClassCascade(pScope->asClass())))
                {
                    a_pInstanciated = o_new(CallExpression)(o_instanciateT(Subroutine, a_pCallExpression->getSubroutine()), arguments, pConstrucionType);
                    return; 
                }
                a_pInstanciated = pClass->precompileExpression(this, pThis->implicitCast(pClass->referenceType()), name.substr(pos+1), nullptr, &arguments);
            }
            else a_pInstanciated = pThis->getValueType()->precompileExpression(this, pThis, name, nullptr, &arguments);
        }
    }
}

void Precompiler::instanciateTemplate( CastExpression* a_pCastExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(CastExpression)(o_instanciateT(Type, a_pCastExpression->getValueType())
                                                , o_instanciateT(Expression, a_pCastExpression->getCastedExpression())
                                                , a_pCastExpression->getCastType());
    }
}

void Precompiler::instanciateTemplate( DereferenceExpression* a_pDereferenceExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(DereferenceExpression)(o_instanciateT(Expression, a_pDereferenceExpression->getDereferencedExpression()));
    }
}

void Precompiler::instanciateTemplate( AddressExpression* a_pAddressExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(AddressExpression)(o_instanciateT(Expression, a_pAddressExpression->getAddressedExpression()));
    }
}

void Precompiler::instanciateTemplate( ReferenceExpression* a_pReferenceExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(ReferenceExpression)(o_instanciateT(Expression, a_pReferenceExpression->getReferencedExpression()));
    }
}

void Precompiler::instanciateTemplate( ConstantExpression* a_pConstantExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(ConstantExpression)(o_instanciateT(Constant, a_pConstantExpression->getConstant()));
    }
}

void Precompiler::instanciateTemplate( DataExpression* a_pDataExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(DataExpression)(a_pDataExpression->getDataBase(), o_instanciateT(Expression, a_pDataExpression->getGuidExpression()));
    }
}

void Precompiler::instanciateTemplate( InstanceDataMemberExpression* a_pInstanceDataMemberExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        o_assert(a_pInstanceDataMemberExpression->getInstanceDataMember()->asPlaceholder());
        Expression* pExpression = o_instanciateT(Expression, a_pInstanceDataMemberExpression->getLeftExpression());
        if(pExpression->isTemplateDependant())
        {
            a_pInstanciated = o_new(InstanceDataMemberExpression)(pExpression
                , o_instanciateT(InstanceDataMember, a_pInstanceDataMemberExpression->getInstanceDataMember()));
        }
        else 
        {
            // no more dependencies, resolve instance data member access
            a_pInstanciated = precompileScope(pExpression, a_pInstanceDataMemberExpression->getName(), nullptr, nullptr, a_pInstanceDataMemberExpression->getModifiers());
        }
    }
}

void Precompiler::instanciateTemplate( LocalVariableExpression* a_pLocalVariableExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(LocalVariableExpression)(o_instanciateT(LocalVariable, a_pLocalVariableExpression->getLocalVariable()));
    }
}

void Precompiler::instanciateTemplate( PropertyExpression* a_pPropertyExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(PropertyExpression)(o_instanciateT(Expression, a_pPropertyExpression->getLeftExpression())
            , o_instanciateT(Property, a_pPropertyExpression->getProperty()));
    }
}

void Precompiler::instanciateTemplate( StaticVariableExpression* a_pStaticVariableExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(StaticVariableExpression)(o_instanciateT(StaticVariable, a_pStaticVariableExpression->getStaticVariable()));
    }
}

void Precompiler::instanciateTemplate( ArrayExpression* a_pArrayExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(ArrayExpression)(o_instanciateT(Expression, a_pArrayExpression->getLeftExpression())
                                                , o_instanciateT(Expression, a_pArrayExpression->getIndexExpression()));
    }
}

void Precompiler::instanciateTemplate( StringLiteralExpression* a_pStringLiteralExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( MemberFunctionPointerCallExpression* a_pMemberFunctionPointerCallExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        vector<Expression*> arguments;
        for(auto it = a_pMemberFunctionPointerCallExpression->beginArguments(); it != a_pMemberFunctionPointerCallExpression->endArguments(); ++it)
        {
            arguments.push_back(o_instanciateT(Expression, *it));
        }
        a_pInstanciated = o_new(MemberFunctionPointerCallExpression)(
              o_instanciateT(MemberFunctionPointerType, a_pMemberFunctionPointerCallExpression->getMemberFunctionPointerType())
            , o_instanciateT(Expression, a_pMemberFunctionPointerCallExpression->getObjectExpression())
            , o_instanciateT(Expression, a_pMemberFunctionPointerCallExpression->getMemberExpression())
            , arguments
        );
    }
}

void Precompiler::instanciateTemplate( DataMemberPointerExpression* a_pDataMemberPointerExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    if(a_pInstanciated == nullptr) 
    {
        a_pInstanciated = o_new(DataMemberPointerExpression)(
            o_instanciateT(DataMemberPointerType, a_pDataMemberPointerExpression->getDataMemberPointerType())
            , o_instanciateT(Expression, a_pDataMemberPointerExpression->getObjectExpression())
            , o_instanciateT(Expression, a_pDataMemberPointerExpression->getMemberExpression())
            );
    }
}

void Precompiler::instanciateTemplate( AssignmentExpression* a_pAssignmentExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    a_pInstanciated = o_new(AssignmentExpression)(o_instanciateT(Expression, a_pAssignmentExpression->getLeftExpression())
        , o_instanciateT(Expression, a_pAssignmentExpression->getRightExpression()));
}

void Precompiler::instanciateTemplate( ConstructorCallExpression* a_pConstructorCallExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    vector<Expression*> arguments;
    for(auto it = a_pConstructorCallExpression->beginArguments(); it != a_pConstructorCallExpression->endArguments(); ++it)
    {
        arguments.push_back(o_instanciateT(Expression, *it));
    }
    a_pInstanciated = o_new(ConstructorCallExpression)(
        o_instanciateT(Constructor, a_pConstructorCallExpression->getSubroutine())
        , arguments
        );
}

void Precompiler::instanciateTemplate( PlacementConstructionExpression* a_pPlacementConstructionExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    vector<Expression*> arguments;
    for(auto it = a_pPlacementConstructionExpression->beginArguments(); it != a_pPlacementConstructionExpression->endArguments(); ++it)
    {
        arguments.push_back(o_instanciateT(Expression, *it));
    }
    a_pInstanciated = o_new(PlacementConstructionExpression)(
        o_instanciateT(Constructor, a_pPlacementConstructionExpression->getSubroutine())
        , o_instanciateT(Expression, a_pPlacementConstructionExpression->getPlaceExpression())
        , arguments
        );
}

void Precompiler::instanciateTemplate( BinaryOperationExpression* a_pBinaryOperatorExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    Expression* pLeft = o_instanciateT(Expression, a_pBinaryOperatorExpression->getLeftExpression());
    Expression* pRight = o_instanciateT(Expression, a_pBinaryOperatorExpression->getRightExpression());
    if(NOT(pLeft->isTemplateDependant()) AND NOT(pRight->isTemplateDependant()))
    {
        // No more template dependencies in expressions, we can re-precompile them
        a_pInstanciated = pLeft->precompileBinaryOperator(this, a_pBinaryOperatorExpression->getOperator(), pRight, a_pBinaryOperatorExpression->getModifiers());
    }
    else 
    {
        a_pInstanciated = o_new(BinaryOperationExpression)(a_pBinaryOperatorExpression->getValueType(), a_pBinaryOperatorExpression->getOperator(), pLeft, pRight);
    }
}

void Precompiler::instanciateTemplate( PreUnaryOperationExpression* a_pPreUnaryOperationExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    Expression* pExpr = o_instanciateT(Expression, a_pPreUnaryOperationExpression->getExpression());
    if(NOT(pExpr->isTemplateDependant()))
    {
        // No more template dependencies in expressions, we can re-precompile them
        a_pInstanciated = pExpr->precompilePreUnaryOperator(this, a_pPreUnaryOperationExpression->getOperator(), a_pPreUnaryOperationExpression->getModifiers());
    }
    else 
    {
        a_pInstanciated = o_new(PreUnaryOperationExpression)(a_pPreUnaryOperationExpression->getValueType(), a_pPreUnaryOperationExpression->getOperator(), pExpr);
    }
}

void Precompiler::instanciateTemplate( PostUnaryOperationExpression* a_pPostUnaryOperationExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    Expression* pExpr = o_instanciateT(Expression, a_pPostUnaryOperationExpression->getExpression());
    if(NOT(pExpr->isTemplateDependant()))
    {
        // No more template dependencies in expressions, we can re-precompile them
        a_pInstanciated = pExpr->precompilePostUnaryOperator(this, a_pPostUnaryOperationExpression->getOperator(), a_pPostUnaryOperationExpression->getModifiers());
    }
    else 
    {
        a_pInstanciated = o_new(PostUnaryOperationExpression)(a_pPostUnaryOperationExpression->getValueType(), a_pPostUnaryOperationExpression->getOperator(), pExpr);
    }
}

void Precompiler::instanciateTemplate( CompositionGetSetExpression* a_pCompositionGetSetExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( AggregationGetSetExpression* a_pAggregationGetSetExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( CompositionInsertRemoveExpression* a_pCompositionInsertRemoveExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( AggregationInsertRemoveExpression* a_pAggregationInsertRemoveExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( SingleParameterFunctionExpression* a_pSingleParameterFunctionExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( Constant* a_pConstant, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}

void Precompiler::instanciateTemplate( PlaceholderConstant* a_pPlaceholderConstant, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    a_pInstanciated = a_pSpec->getArgument(a_pPlaceholderConstant->getName());
    if(a_pInstanciated == nullptr) return;
    if(a_pInstanciated->asConstant() == nullptr) { a_pInstanciated = nullptr; return; }
}

void Precompiler::instanciateTemplate( PlaceholderType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    a_pInstanciated = a_pSpec->getArgument(a_pType->getName());
    if(a_pInstanciated == nullptr OR a_pInstanciated->asType() == nullptr) 
    {
        a_pInstanciated = nullptr;
    }
}

void Precompiler::instanciateTemplate( PlaceholderClass* a_pPlaceholderClass, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    a_pInstanciated = a_pSpec->getArgument(a_pPlaceholderClass->getName());
    if(a_pInstanciated == nullptr OR a_pInstanciated->asClass() == nullptr) 
    {
        a_pInstanciated = nullptr;
    }
}

void Precompiler::instanciateTemplate( PlaceholderInstanceDataMember* a_pPlaceholderInstanceDataMember, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated )
{
    o_assert_no_implementation();
}







o_namespace_end(phantom, reflection)