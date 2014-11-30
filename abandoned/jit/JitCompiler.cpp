/* ******************* Includes ****************** */
#include "phantom/jit.h"
#include "JitCompiler.h"
#include "JitCompiler.hxx"
#include "phantom/reflection/SwitchStatement.h"
#include "phantom/reflection/WhileStatement.h"
#include "phantom/reflection/DoWhileStatement.h"
#include "phantom/reflection/ForStatement.h"
#include "phantom/reflection/IfStatement.h"
#include "phantom/reflection/LabelStatement.h"
#include "phantom/reflection/CaseStatement.h"
#include "phantom/reflection/ExpressionStatement.h"
#include "phantom/reflection/CallExpression.h"
#include "phantom/reflection/CastExpression.h"
#include "phantom/reflection/DereferenceExpression.h"
#include "phantom/reflection/AddressExpression.h"
#include "phantom/reflection/ConstantExpression.h"
#include "phantom/reflection/InstanceDataMemberAccess.h"
#include "phantom/reflection/InstanceDataMember.h"
#include "phantom/reflection/PropertyAccess.h"
#include "phantom/reflection/StaticVariableAccess.h"
#include "phantom/reflection/ArrayElementAccess.h"
#include "phantom/reflection/Property.h"
#include "JitCompiler.hpp"
#include "phantom/util/Message.h"
#include <stdarg.h>
/* *********************************************** */
o_namespace_begin(phantom, reflection) 

variant JitCompiler::compile( Block* a_pBlock )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    Block* pParentBlock = set("block").as<Block*>();

    o_assert(pParentBlock);

    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());

    for(auto it = a_pBlock->beginLocalVariables(); it != a_pBlock->beginLocalVariables(); ++it)
    {
        compileElement(*it);
    }

    for(auto it = a_pBlock->beginStatements(); it != a_pBlock->endStatements(); ++it)
    {
        compileElement(*it);
    }

    if(pParentBlock == pSubroutine->getBlock())
    {
        if(hasFailed())
        {
            set("subroutine", (void*)0);
            pJitSubroutine->abortCompilation();
        }
        else
        {
            jit_value v0 = pJitSubroutine->createIntConstant(1);
            jit_value v1 = pJitSubroutine->createIntConstant(2);
            int i = 0;
            while(i < 5)
            {
                v0 = pJitSubroutine->add(v0, v1);
                ++i;
            }
            pJitSubroutine->pushCodeLocation(a_pBlock->getCodeLocation());
            o_verify(pJitSubroutine->returnValue(0), "");
            pJitSubroutine->endCompilation();
        }
    }
    return variant();
}

variant JitCompiler::compile( ForStatement* a_pForStatement )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());

    for(auto it = a_pForStatement->beginInits(); it != a_pForStatement->endInits(); ++it)
    {
        o_assert(*it);
        compileElement(*it); // push the for initialization instruction (ex: int i = 0)
    }

    jit_label label_break ;
    jit_label label_continue ;
    jit_label label_condition ;

    // The first time we jump directly to the condition without updating (without ++i)
    o_verify(pJitSubroutine->branch(&label_condition), "jit compile error");

    // here is the continue address
    o_verify(pJitSubroutine->label(&label_continue), "jit compile error");

    // push the "++i" style update instruction 

    for(auto it = a_pForStatement->beginUpdates(); it != a_pForStatement->endUpdates(); ++it)
    {
        o_assert(*it);
        compileElement(*it); 
    }

    // here starts the condition test
    o_verify(pJitSubroutine->label(&label_condition), "jit compile error");

    // solve the for condition
    jit_value for_condition;
    if(a_pForStatement->getCondition())
    {
        compileElement(a_pForStatement->getCondition()).as(&for_condition);
    }
    else 
    {
        message(e_MessageType_Error, this->getCodeLocation(), "Invalid update statement");
    }

    // if for_condition exists and for_condition is false => break; 
    // (ex: i < 10)
    if(!for_condition.isNull())
    {
        // branch only if condition false
        o_verify(pJitSubroutine->branchIf(pJitSubroutine->eq(for_condition, pJitSubroutine->createIntConstant(0)), &label_break), "jit compile error");
    }

    // push break and continue labels for break and continue instruction solving
    set("break", &label_break);
    set("continue", &label_continue);

    // compile for block instructions
    compileElement(a_pForStatement->getBlock());

    // go back to continue
    o_verify(pJitSubroutine->branch(&label_continue), "jit compile error");

    // set break/out label position
    o_verify(pJitSubroutine->label(&label_break), "jit compile error");

    return variant();
}

variant JitCompiler::compile( WhileStatement* a_pWhileStatement )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();

    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());

    jit_label label_break ;
    jit_label label_continue ;
    jit_label label_first_instruction ;

    // set first instruction label position
    pJitSubroutine->label(&label_continue);

    jit_value while_condition;
    compileElement(a_pWhileStatement->getCondition()).as(&while_condition);
    if(while_condition.isNull())
    {
        return variant();
    }
    // if !while_condition => break;
    o_verify(pJitSubroutine->branchIf(pJitSubroutine->eq(while_condition.value, pJitSubroutine->createIntConstant(0) ), &label_break), "jit compile error");

    // push break and continue labels for break and continue instruction solving
    set("break", &label_break);
    set("continue", &label_continue);

    // compile while block instructions
    compileElement(a_pWhileStatement->getBlock());

    // branch continue
    pJitSubroutine->branch(&label_continue);

    // set break/out label position
    pJitSubroutine->label(&label_break);

    return variant();
}

variant JitCompiler::compile( IfStatement* a_pIfStatement )
{
    Subroutine* pJitSubroutine = get("subroutine").as<Subroutine*>();

    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    
    jit_label label_else ;
    jit_label label_end ;

    // solve the for condition
    jit_value if_condition;
    compileElement(a_pIfStatement->getCondition()).as(&if_condition);

    if(if_condition.isNull()) return variant();

    int result = pJitSubroutine->branchIfNot(if_condition, a_pIfStatement->getElseBlock() ? &label_else : &label_end);
    o_assert(result);
    
    // THEN (condition true)
    compileElement(a_pIfStatement->getThenBlock());

    if(a_pIfStatement->getElseBlock())
    {
        // ELSE (condition false)
        result = pJitSubroutine->label(&label_else);
        o_assert(result);
        compileElement(a_pIfStatement->getElseBlock());
    }
    result = pJitSubroutine->label(&label_end);
    o_assert(result);

    return variant();
}

variant JitCompiler::compile( SwitchStatement* a_pSwitchStatement )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();

    pJitSubroutine->pushCodeLocation(getCodeLocation());

    jit_value test_value;
    variant v = compileElement(a_pSwitchStatement->getTestValue());
    v.as(&test_value); 
    if(test_value.isNull())
    {
        message(e_MessageType_Error, a_pSwitchStatement->getCodeLocation(), "Invalid switch test value");
    }

    set("switch_value", test_value);

    // solve case labels

    jit_label label_break ;
    set("break", &label_break);

    vector<jit_label> case_labels;

    vector<uint> case_constant_values;

    set("case_constant_values", &case_constant_values);

    LabelStatement* pDefaultLabelStatement = nullptr;

    set("default_label_statement", &pDefaultLabelStatement);

    // Branch case labels

    auto itLabel = case_labels.begin();
    for(auto it = a_pSwitchStatement->beginCaseStatements(); it != a_pSwitchStatement->endCaseStatements(); ++it)
    {
        compileElement(*it);
    }

    if(pDefaultLabelStatement != nullptr)
    {
        pJitSubroutine->branch(&(pDefaultLabelStatement->getExtension()->as<JitCaseLabel*>()->m_jit_label));
    }
    else 
    {
        pJitSubroutine->branch(&label_break);
    }

    compileElement(a_pSwitchStatement->getBlock());

    pJitSubroutine->label(&label_break);
    pJitSubroutine->popCodeLocation();
    return variant();
}

variant JitCompiler::compile( CaseStatement* a_pCaseStatement )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();

    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());

    SwitchStatement* pSwitchStatement = a_pCaseStatement->getSwitchStatement();

    LabelStatement** ppDefaultLabelStatement = set("default_label_statement").as<LabelStatement**>(); 

    jit_value switch_value;
    vector<ulonglong>* case_constant_values = set("case_constant_values").as<vector<ulonglong>*>();
    if(case_constant_values == nullptr 
        OR pSwitchStatement == nullptr 
        OR ppDefaultLabelStatement == nullptr 
        OR NOT(set("switch_value").as(&switch_value)))
    {
        message(e_MessageType_Error, a_pSwitchStatement->getCodeLocation(), "Case label outside switch statement");
    }

    if(a_pCaseStatement->getValue())
    {
        jit_value case_value;
        compileElement(a_pCaseStatement->getValue()).as(&case_value);

        if(case_value.isNull())
        {
            message(e_MessageType_Error, a_pCaseStatement->getCodeLocation(), "Invalid case value");
            pJitSubroutine->popCodeLocation();
            return variant();
        }
        if(case_value.isConstant() == 0)
        {
            message(e_MessageType_Error, a_pCaseStatement->getCodeLocation(), "Case value must be an integer constant");
            pJitSubroutine->popCodeLocation();
            return variant();
        }
        jit_constant constant;
        jit_constant case_constant = case_value.getConstant();
        jit_value::convertConstant(&constant, &case_constant, switch_value.type, 0);

        for(size_t k = 0; k<case_constant_values->size(); ++k)
        {
            bool equals = false;
            Type* pType = constant.getType();
            if(pType == typeOf<int>())
                equals = (*case_constant_values)[k] == constant.getIntValue();
            else if(pType == typeOf<uint>())
                equals = (*case_constant_values)[k] == constant.getUIntValue();
            else if(pType == typeOf<longlong>())
                equals = (*case_constant_values)[k] == constant.getLongLongValue();
            else if(pType == typeOf<ulonglong>())
                equals = (*case_constant_values)[k] == constant.getULongLongValue();
            else o_assert(false);

            if(equals)
            {
                message(e_MessageType_Error, a_pCaseStatement->getCodeLocation(), "Case label with constant value '%ull' already defined", (*case_constant_values)[k]);
                pJitSubroutine->popCodeLocation();
                return variant();
            }
        }
        JitCaseLabel* pJitCaseLabel = o_new(JitCaseLabel)(a_pCaseStatement->getLabelStatement());
        a_pCaseStatement->getLabelStatement()->setExtension(pJitCaseLabel);

        jit_constant jit_nuint_constant;
        jit_value::convertConstant(&jit_nuint_constant, &constant, typeOf<ulonglong>(), 0);
        case_constant_values.push_back(jit_nuint_constant.getULongLongValue());

        pJitSubroutine->branchIf(pJitSubroutine->eq(case_value.value, switch_value.value), &pJitCaseLabel->m_jit_Label);
    }
    else 
    {
        if(*ppDefaultLabelStatement)
        {
            pushMessage(e_MessageType_Error, a_pCaseStatement->getCodeLocation(), "Label 'default' already defined");
            message(e_MessageType_Error, (*ppDefaultLabelStatement)->getCodeLocation(), "see previous definition of label 'default'");
            popMessage();
            pJitSubroutine->popCodeLocation();
            return variant();
        }
        JitCaseLabel* pJitCaseLabel = o_new(JitCaseLabel)(a_pCaseStatement->getLabelStatement());
        a_pCaseStatement->getLabelStatement()->setExtension(pJitCaseLabel);
        *ppDefaultLabelStatement = a_pCaseStatement->getLabelStatement();
    }
    return variant();
}

variant JitCompiler::compile( LabelStatement* a_pLabelStatement )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();

    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());

    if(a_pLabelStatement->getLabelName().empty()) // anonymous label => switch case label
    {
        JitCaseLabel* pLabel = a_pLabelStatement->getExtension().as<JitCaseLabel*>();
        if(pLabel == nullptr)
        {
            return variant();
        }
        pJitSubroutine->label(&pLabel->m_jit_Label);
        return variant();
    }
    else 
    {
        map<string, jit_label>* labels = set("labels").as<map<string, jit_label>*>();
        if(labels == nullptr) 
        {
            message(e_MessageType_Error, a_pLabelStatement->getCodeLocation(), "No label")
            return variant();
        }
        {
            // Look for existing labels with this name (used by goto)
            auto found = labels->find(a_pLabelStatement->getLabelName());
            if(found != labels->end())
            {
                // If found, define it to the current code position
                if(found->second.isUndefined())
                {
                    pJitSubroutine->label(&found->second);
                }
                else 
                {
                    message(e_MessageType_Error, a_pLabelStatement->getCodeLocation(), "Label '%s' already defined", found->first.c_str());
                    return variant();
                }
                return variant();
            }
        }
        // No label exists, we create one and define it to the current code position
        pJitSubroutine->label(&(*labels)[a_pLabelStatement->getLabelName()]);
    }
    return variant();
}

variant JitCompiler::compile( DoWhileStatement* a_pDoWhileStatement )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();

    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());

    jit_label label_do ;
    jit_label label_break ;
    jit_label label_continue ;
    jit_label label_first_instruction ;

    // set first instruction label position
    pJitSubroutine->label(&label_do);

    // push break and continue labels for break and continue instruction solving
    set("break", &label_break);
    set("continue", &label_continue);

    // compile do block instructions
    compileElement(a_pDoWhileStatement->getBlock());

    // set continue position
    pJitSubroutine->label(&label_continue);

    jit_value while_condition;
    compileElement(a_pDoWhileStatement->getCondition()).as(&while_condition);
    if(while_condition.isNull())
    {
        return variant();
    }
    // if !while_condition => do;
    o_verify(pJitSubroutine->branchIfNot(pJitSubroutine->eq(while_condition, pJitSubroutine->createIntConstant(0)), &label_do), "jit compile error");

    // set break/out label position
    pJitSubroutine->label(&label_break);

    return variant();
}

variant JitCompiler::compile( ExpressionStatement* a_pExpressionStatement )
{
    return compileElement(a_pExpressionStatement->getExpression());
}

variant JitCompiler::compile( BreakStatement* a_pBreakStatement )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    jit_label* label_break;
    if(pJitSubroutine == nullptr OR NOT(set("break").as(&label_break)))
    {
        message(e_MessageType_Error, a_pBreakStatement->getCodeLocation(), "'break' not allowed here");
        return variant();
    }
    o_verify(pJitSubroutine->branch(label_break), "");
    return variant();
}

variant JitCompiler::compile( ContinueStatement* a_pContinueStatement )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    jit_label* label_continue;
    if(pJitSubroutine == nullptr OR NOT(set("continue").as(&label_continue)))
    {
        message(e_MessageType_Error, a_pContinueStatement->getCodeLocation(), "'continue' not allowed here");
        return variant();
    }
    o_verify(pJitSubroutine->branch(label_continue), "");
    return variant();
}

variant JitCompiler::compile( CastExpression* a_pCastExpression )
{ 
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    
	Type* pType = a_pCastExpression->getValueType();
	if(pType == NULL) 
        return variant();
	jit_value value;
    compileElement(a_pCastExpression->getCastedExpression()).as(&value);
	if(value.isNull()) 
        return variant();
	jit_value	casted_value = pJitSubroutine->cast(value, pType);
	if(casted_value.isNull())
	{
		message(e_MessageType_Error, a_pCastExpression->getCodeLocation(), "Cannot cast from '%s' to '%s'"
			, value.type->getName().c_str()
			, pType->getName().c_str()
			);
		return variant();
	}
	return casted_value;
}

typedef std::pair<PropertyAccess*, jit_value> property_access_pair;
typedef vector<property_access_pair> property_access_pairs;

variant JitCompiler::compile( CallExpression* a_pCallExpression )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    property_access_pairs* pPropertyAccessPairs = set("property_access_pairs").as<property_access_pairs*>();

    vector<PropertyAccess*> propertyAccessPairs;
    set("property_access_pairs", &propertyAccessPairs);
    
    vector<jit_value> arguments;

    // Evaluate arguments from right to left
    for(auto it = a_pCallExpression->rbeginArguments(); it != a_pCallExpression->rendArguments(); ++it)
    {
        jit_value argumentValue;
        if(NOT(compileElement(*it).as(&argumentValue)))
        {
            return variant();
        }
        arguments.push_back(argumentValue);
    }
    jit_value returnValue = pJitSubroutine->callSubroutine(a_pCallExpression->getSubroutine(), arguments.data(), arguments.size(), 0);
    
    // Flush property accesses
    
    for(auto it = propertyAccessPairs.begin(); it != propertyAccessPairs.end(); ++it)
    {
        flush(it->first, it->second);
    }

    return returnValue;
}

variant JitCompiler::compile( DereferenceExpression* a_pDereferenceExpression )
{
    jit_value value;
    if(NOT(compileElement(a_pDereferenceExpression->getDereferencedExpression()).as(&value)))
    {
        return variant();
    }
    if(value.isNull())
    {
        return variant();
    }
    if(value.type->asDataPointerType() == nullptr) 
    {
        message(e_MessageType_Error, a_pDereferenceExpression->getCodeLocation(), "Expression is not deferenceable");
        return variant();
    }
    return jit_value(value.value, value.type->removePointer()->referenceType());
}

variant JitCompiler::compile( AddressExpression* a_pAddressExpression )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    jit_value value;
    if(NOT(compileElement(a_pAddressExpression->getAddressedExpression()).as(&value)))
    {
        return variant();
    }
    if(value.isNull())
    {
        return variant();
    }
    if(value.type->asReferenceType())
    {
        return jit_value(value.value, value.type->removeReference()->pointerType());
    }
    if(NOT(value.isAddressable()))
    {
        return variant();
    }
    return pJitSubroutine->addressOf(value);
}

variant JitCompiler::compile( ConstantExpression* a_pConstantExpression )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    jit_constant constant;
    constant.type = a_pConstantExpression->getValueType();
    a_pConstantExpression->getConstant()->getValue(&constant.un.int_value);
    return pJitSubroutine->createConstant(&constant);
}

variant JitCompiler::compile( InstanceDataMemberAccess* a_pInstanceDataMemberAccess )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    jit_value left;
    compileElement(a_pInstanceDataMemberAccess->getLeftExpression()).as(&left);
    if(left.isNull())
    {
        return nullptr;
    }
    left.setAddressable();
    left = pJitSubroutine->implicitCast(left, left.type->asReferenceType());
    if(left.isNull())
    {
        message(e_MessageType_Error, a_pInstanceDataMemberAccess->getLeftExpression()->getCodeLocation(), "Expression is not a l-value");
        return variant();
    }
    return pJitSubroutine->loadRelative(left, a_pInstanceDataMemberAccess->getInstanceDataMember()->getOffset()
        , a_pInstanceDataMemberAccess->getInstanceDataMember()->getValueType());
}

void JitCompiler::flush( PropertyAccess* a_pPropertyAccess, jit_value a_PointerValue )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    jit_value left;
    compileElement(a_pPropertyAccess->getLeftExpression()).as(&left);
    if(left.isNull())
    {
        return;
    }
    left.setAddressable();
    left = pJitSubroutine->addressOf(left);
    if(left.isNull())
    {
        message(e_MessageType_Error, a_pPropertyAccess->getLeftExpression()->getCodeLocation(), "Expression is not a l-value");
        return variant();
    }
    jit_value arg_value = pJitSubroutine->loadRelative(a_PointerValue, 0, a_PointerValue.type->removePointer());
    jit_value args[2] = { left, pJitSubroutine->implicitCast(arg_value, a_pPropertyAccess->getProperty()->getValueType()) };
    pJitSubroutine->callSubroutine(a_pPropertyAccess->getProperty()->getSetMemberFunction(), args, 2, 0);
}

variant JitCompiler::compile( PropertyAccess* a_pPropertyAccess )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    property_access_pairs* pPropertyAccessPairs = set("property_access_pairs").as<property_access_pairs*>();
    size_t propertyAccessIndex = 0; 

    if(pPropertyAccessPairs)
    {
        propertyAccessIndex = pPropertyAccessPairs->size();
        pPropertyAccessPairs->push_back(property_access_pair(a_pPropertyAccess, jit_value()));
    }
    jit_value left;
    compileElement(a_pPropertyAccess->getLeftExpression()).as(&left);
    if(left.isNull())
    {
        return nullptr;
    }
    left.setAddressable();
    left = pJitSubroutine->implicitCast(left, left.type->asReferenceType());
    left = pJitSubroutine->implicitCast(left, left.type->removeReference()->pointerType())
    if(left.isNull())
    {
        message(e_MessageType_Error, a_pPropertyAccess->getLeftExpression()->getCodeLocation(), "Expression is not a l-value");
        return variant();
    }
    jit_value call_result = pJitSubroutine->callSubroutine(a_pPropertyAccess->getProperty()->getGetMemberFunction(), &left, 1, 0);
    jit_value casted_value = pJitSubroutine->implicitCast(call_result, a_pPropertyAccess->getValueType()->removeReference()->removeConst()); 
    jit_value property_value = pJitSubroutine->createValue(casted_value.type);
    pJitSubroutine->store(property_value, casted_value);
    property_value.setAddressable();
    if(pPropertyAccessPairs)
    {
        (*pPropertyAccessPairs)[propertyAccessIndex].second = pJitSubroutine->addressOf(property_value);
    }
}

variant JitCompiler::compile( StaticVariableAccess* a_pStaticVariableAccess )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    jit_value value = pJitSubroutine->createVoidPtrConstant(a_pStaticVariableAccess->getAddress());
    value.type = value.type->removePointer()->referenceType();
    return value;
}

variant JitCompiler::compile( ArrayElementAccess* a_pArrayElementAccess )
{
    Subroutine* pSubroutine = get("subroutine").as<Subroutine*>();
    JitSubroutine* pJitSubroutine = as<JitSubroutine*>(pSubroutine->getExtension());
    jit_value left;
    compileElement(a_pArrayElementAccess->getLeftExpression()).as(&left);
    if(left.isNull())
        return variant();
    jit_value index;
    compileElement(a_pArrayElementAccess->getIndexExpression()).as(&index);
    if(index.isNull())
        return variant();
    left.setAddressable();
    left = pJitSubroutine->implicitCast(left, left.type->asReferenceType());
    left = pJitSubroutine->implicitCast(left, left.type->removeReference()->pointerType())
    return pJitSubroutine->loadElem(left, index, a_pArrayElementAccess->getValueType());
}

variant JitCompiler::compile( InstanceMemberFunction* a_pInstanceMemberFunction )
{
    set("subroutine", a_pInstanceMemberFunction); // push member function to data map
    JitInstanceMemberFunction* pJitInstanceMemberFunction = o_new(JitInstanceMemberFunction)(a_pInstanceMemberFunction);
    o_assert(a_pInstanceMemberFunction->getOwnerClassType());
    vector<InstanceMemberFunction*> originalOverriddenMemberFunctions;
    a_pInstanceMemberFunction->getOriginalOverriddenMemberFunctions(originalOverriddenMemberFunctions);
    if(originalOverriddenMemberFunctions.size() > 1) // more than one root overridden method => thunk adjustor needed
    {
        // MSVC convention : generate thunks if more than 1 override (because ambiguity on how to adjust this pointer in last override)
        for(auto it = originalOverriddenMemberFunctions.begin(); it != originalOverriddenMemberFunctions.end(); ++it)
        {
            InstanceMemberFunction* pOverridden = *it;
            size_t uiOffset = a_pInstanceMemberFunction->getOwnerClass()->getSuperClassOffsetCascade(pOverridden->getOwnerClass());
            if(uiOffset != 0)
            {
                pJitInstanceMemberFunction->compileThisAdjustementThunk(uiOffset);
            }
        }
    }
    else if(originalOverriddenMemberFunctions.size() == 1)
    {
        // MSVC convention : readjust this pointer inside the function code if only one override
        if(originalOverriddenMemberFunctions.back() != a_pInstanceMemberFunction)
        {
            size_t uiOffset = a_pInstanceMemberFunction->getOwnerClass()->getSuperClassOffsetCascade(originalOverriddenMemberFunctions.back()->getOwnerClass());
            if(uiOffset != 0)
            {
                pJitInstanceMemberFunction->store(
                    pJitInstanceMemberFunction->getThis()
                    , pJitInstanceMemberFunction->sub(pJitInstanceMemberFunction->getThis(), pJitInstanceMemberFunction->createIntConstant((int)uiOffset))
                    );
            }
        }
    }
    a_pInstanceMemberFunction->setExtension(pJitInstanceMemberFunction);
    queueElement(e_Pass_Definitions, a_pInstanceMemberFunction->getBlock());
    return variant();
}

variant JitCompiler::compile( Signal* a_pSignal )
{
    set("subroutine", a_pSignal); // push member function to data map
    JitSignal* pJitSignal = o_new(pJitSignal)(a_pSignal);
    a_pSignal->setExtension(pJitSignal);
    queueElement(e_Pass_Definitions, a_pSignal->getBlock());
}

o_namespace_end(phantom, reflection)