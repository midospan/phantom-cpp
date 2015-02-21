/* TODO LICENCE HERE */
 
/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/BuiltInOperator.h>
#include <phantom/reflection/BuiltInOperator.hxx>
#include <phantom/reflection/BuiltInOperatorExpression.h>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/LabelStatement.h>
#include <phantom/reflection/Interpreter.h>
#include "BuiltInOperators.h"
/* *********************************************** */
o_registerN((phantom, reflection), BuiltInOperator);

o_namespace_begin(phantom, reflection) 

o_invalid_def(BuiltInOperator, e_Operator_Count);

BuiltInOperator::BuiltInOperator(EOperator a_eOperator)
    : NamedElement(OperatorName(a_eOperator))
    , m_eOperator(a_eOperator)
    , m_eType(OperatorType(a_eOperator))
{
    m_uiOperandCount = (m_eType == e_OperatorType_Binary) ? 2 : (m_eType == e_OperatorType_Ternary) ? 3 : 1; 
}

phantom::string BuiltInOperator::getQualifiedName() const
{
    return getName() ;
}

phantom::string BuiltInOperator::getQualifiedDecoratedName() const
{
    return getName();
}

phantom::string BuiltInOperator::getDecoratedName() const
{
    return getName();
}

EOperatorType BuiltInOperator::OperatorType( EOperator a_eOperator )
{
    switch(a_eOperator)
    {
    case e_Operator_Add:
    case e_Operator_Subtract:
    case e_Operator_Multiply:
    case e_Operator_Divide:
    case e_Operator_Equal:
    case e_Operator_NotEqual:
    case e_Operator_Greater:
    case e_Operator_Less:
    case e_Operator_GreaterEqual:
    case e_Operator_LessEqual:
    case e_Operator_LogicalAnd:
    case e_Operator_LogicalOr:
    case e_Operator_BitAnd:
    case e_Operator_BitOr:
    case e_Operator_ShiftLeft:
    case e_Operator_ShiftRight:
    case e_Operator_AssignmentAdd:
    case e_Operator_AssignmentSubtract:
    case e_Operator_AssignmentMultiply:
    case e_Operator_AssignmentDivide:
    case e_Operator_AssignmentBitAnd:
    case e_Operator_AssignmentBitOr:
    case e_Operator_AssignmentModulo:
    case e_Operator_AssignmentShiftLeft:
    case e_Operator_AssignmentShiftRight:
    case e_Operator_AssignmentXOr:
        return e_OperatorType_Binary;

    case e_Operator_ArrowStar:
    case e_Operator_Complement:
    case e_Operator_Not:
    case e_Operator_Address:
    case e_Operator_Dereference:
    case e_Operator_PreDecrement:
    case e_Operator_PreIncrement:
        return e_OperatorType_UnaryPrefixed;

    case e_Operator_PostDecrement:
    case e_Operator_PostIncrement:
    case e_Operator_Arrow:
        return e_OperatorType_UnaryPostfixed;
    }
    return e_OperatorType_Binary;
}

void BuiltInOperator::operandImplicitConversions( const vector<Expression*>& a_Expressions, conversions& out ) const
{
    vector<Type*> types;
    for(auto it = a_Expressions.begin(); it != a_Expressions.end(); ++it)
        types.push_back((*it)->getValueType());
}

void BuiltInOperator::fetchExtraOverloads(Type* a_pType, vector<overload>& a_Overloads) const
{
    a_pType = a_pType->removeQualifiers();
    switch(a_pType->getTypeId())
    {
    case e_pointer:
        if(a_pType->asDataPointerType())
        {
            fetchExtraOverloads(static_cast<DataPointerType*>(a_pType), a_Overloads);
        }
        else if(a_pType->asFunctionPointerType())
        {
            fetchExtraOverloads(static_cast<FunctionPointerType*>(a_pType), a_Overloads);
        }
        break;
    case e_member_pointer:
        fetchExtraOverloads(static_cast<MemberPointerType*>(a_pType), a_Overloads);
        break;
    case e_class:
        fetchExtraOverloads(static_cast<Class*>(a_pType), a_Overloads);
        break;
    case e_structure:
        fetchExtraOverloads(static_cast<ClassType*>(a_pType), a_Overloads);
        break;
    case e_reference:
        fetchExtraOverloads(static_cast<ReferenceType*>(a_pType), a_Overloads);
        break;
    case e_enum:
        fetchExtraOverloads(static_cast<Enum*>(a_pType), a_Overloads);
        break;
    }
}

void BuiltInOperator::fetchExtraOverloads( ClassType* a_pClassType, vector<overload>& a_Overloads ) const
{
    // look for every conversion functions
    for(auto it = a_pClassType->beginMemberFunctions(); it != a_pClassType->endMemberFunctions(); ++it)
    {
        MemberFunction* pMemberFunction = *it;
        const string& name = pMemberFunction->getName();
        if(name.size() >= 8 AND name[8] == ' ') // TODO : find a faster way to distinguish conversion functions
        {
            fetchExtraOverloads(pMemberFunction->getReturnType(), a_Overloads);
        }
    }
}

void BuiltInOperator::fetchExtraOverloads( Class* a_pClass, vector<overload>& a_Overloads ) const
{
    fetchExtraOverloads(static_cast<ClassType*>(a_pClass), a_Overloads);
    // look for every base classes conversion functions
    for(auto it = a_pClass->beginBaseClasses(); it != a_pClass->endBaseClasses(); ++it)
    {
        Class* pBaseClass = it->m_pClass;
        fetchExtraOverloads(pBaseClass, a_Overloads);
    }
}

void BuiltInOperator::fetchExtraOverloads( MemberPointerType* a_pMemberPointerType, vector<overload>& a_Overloads ) const
{
    Type* pBoolType = typeOf<bool>();
    switch(m_eOperator)
    {
        /// standard 13.6.16
        /// ------------------------
        /// bool operator==(T , T );
    case e_Operator_Equal:
        a_Overloads.push_back(overload(pBoolType, a_pMemberPointerType, a_pMemberPointerType, operation_delegate_t(a_pMemberPointerType, &MemberPointerType::equal)));
        break;

        /// bool operator!=(T , T );
    case e_Operator_NotEqual:
        a_Overloads.push_back(overload(pBoolType, a_pMemberPointerType, a_pMemberPointerType, operation_delegate_t(a_pMemberPointerType, &MemberPointerType::notEqual)));
        break;

        /// standard 13.6.20
        /// ------------------------
        /// VQ T & operator=(VQ T &, T );
    case e_Operator_Assignment:
        a_Overloads.push_back(overload(a_pMemberPointerType->lvalueReferenceType(), a_pMemberPointerType->lvalueReferenceType(), a_pMemberPointerType, operation_delegate_t(a_pMemberPointerType, &MemberPointerType::assignment)));
        a_Overloads.push_back(overload(a_pMemberPointerType->volatileType()->lvalueReferenceType(), a_pMemberPointerType->volatileType()->lvalueReferenceType(), a_pMemberPointerType, operation_delegate_t(a_pMemberPointerType, &MemberPointerType::assignment)));
        break;
    }
}

void BuiltInOperator::fetchExtraOverloads( ReferenceType* a_pReferenceType, vector<overload>& a_Overloads ) const
{
    if(m_eOperator == e_Operator_Address)
    {
        a_Overloads.push_back(overload(a_pReferenceType->getReferencedType()->pointerType(), a_pReferenceType, nullptr, operation_delegate_t(a_pReferenceType, &ReferenceType::address)));
    }
    else fetchExtraOverloads(a_pReferenceType->removeReference(), a_Overloads);
}

void BuiltInOperator::fetchExtraOverloads( Enum* a_pEnum, vector<overload>& a_Overloads ) const
{
    builtin_operation_delegate_selector selector;
    Type* pBoolType = typeOf<bool>();
    /// 13.6.15
    /// bool operator<(T , T );
    /// bool operator>(T , T );
    /// bool operator<=(T , T );
    /// bool operator>=(T , T );
    /// bool operator==(T , T );
    /// bool operator!=(T , T );
    Type* pUnderlyingType = a_pEnum->getIntType();

    switch(m_eOperator)
    {
    case e_Operator_Less:
        a_Overloads.push_back(overload(pBoolType, a_pEnum, a_pEnum, selector.delegate(e_Operator_Less, pUnderlyingType, pUnderlyingType)));
        break;
    case e_Operator_Greater:
        a_Overloads.push_back(overload(pBoolType, a_pEnum, a_pEnum, selector.delegate(e_Operator_Greater, pUnderlyingType, pUnderlyingType)));
        break;
    case e_Operator_LessEqual:
        a_Overloads.push_back(overload(pBoolType, a_pEnum, a_pEnum, selector.delegate(e_Operator_LessEqual, pUnderlyingType, pUnderlyingType)));
        break;
    case e_Operator_GreaterEqual:
        a_Overloads.push_back(overload(pBoolType, a_pEnum, a_pEnum, selector.delegate(e_Operator_GreaterEqual, pUnderlyingType, pUnderlyingType)));
        break;
    case e_Operator_Equal:
        a_Overloads.push_back(overload(pBoolType, a_pEnum, a_pEnum, selector.delegate(e_Operator_Equal, pUnderlyingType, pUnderlyingType)));
        break;
    case e_Operator_NotEqual:
        a_Overloads.push_back(overload(pBoolType, a_pEnum, a_pEnum, selector.delegate(e_Operator_NotEqual, pUnderlyingType, pUnderlyingType)));
        break;
        /// 13.6.19
        /// T *VQ & operator=(T *VQ &, T *);
    case e_Operator_Assignment:
        a_Overloads.push_back(overload(a_pEnum->lvalueReferenceType(), a_pEnum->lvalueReferenceType(), a_pEnum, selector.delegate(e_Operator_Assignment, pUnderlyingType, pUnderlyingType)));
        a_Overloads.push_back(overload(a_pEnum->volatileType()->lvalueReferenceType(), a_pEnum->volatileType()->lvalueReferenceType(), a_pEnum, selector.delegate(e_Operator_Assignment, pUnderlyingType, pUnderlyingType)));
        break;
    }
}

void BuiltInOperator::fetchExtraOverloads( PointerType* a_pPointerType, vector<overload>& a_Overloads ) const
{
    Type* pBoolType = typeOf<bool>();
    Type* pIntType = typeOf<int>();
    Type* ref = a_pPointerType->lvalueReferenceType(); 
    Type* Vref = a_pPointerType->volatileType()->lvalueReferenceType();
    Type* deref = a_pPointerType->removePointer()->lvalueReferenceType();
    switch(m_eOperator)
    {
    /// 13.6.15
    /// ---------------------- 
    /// bool operator<(T , T );
    /// bool operator>(T , T );
    /// bool operator<=(T , T );
    /// bool operator>=(T , T );
    /// bool operator==(T , T );
    /// bool operator!=(T , T );

    case e_Operator_Less:
        a_Overloads.push_back(overload(pBoolType, a_pPointerType, a_pPointerType, operation_delegate_t(a_pPointerType, &PointerType::less)));
        break;
    case e_Operator_Greater:
        a_Overloads.push_back(overload(pBoolType, a_pPointerType, a_pPointerType, operation_delegate_t(a_pPointerType, &PointerType::greater)));
        break;
    case e_Operator_LessEqual:
        a_Overloads.push_back(overload(pBoolType, a_pPointerType, a_pPointerType, operation_delegate_t(a_pPointerType, &PointerType::lessEqual)));
        break;
    case e_Operator_GreaterEqual:
        a_Overloads.push_back(overload(pBoolType, a_pPointerType, a_pPointerType, operation_delegate_t(a_pPointerType, &PointerType::greaterEqual)));
        break;
    case e_Operator_Equal:
        a_Overloads.push_back(overload(pBoolType, a_pPointerType, a_pPointerType, operation_delegate_t(a_pPointerType, &PointerType::equal)));
        break;
    case e_Operator_NotEqual:
        a_Overloads.push_back(overload(pBoolType, a_pPointerType, a_pPointerType, operation_delegate_t(a_pPointerType, &PointerType::notEqual)));
        break;

        /// 13.6.19
        /// T *VQ & operator=(T *VQ &, T *);
    case e_Operator_Assignment:
        a_Overloads.push_back(overload(ref, ref, a_pPointerType, operation_delegate_t(a_pPointerType, &PointerType::assignment)));
        a_Overloads.push_back(overload(Vref, Vref, a_pPointerType, operation_delegate_t(a_pPointerType, &PointerType::assignment)));
        break;

    }
}

void BuiltInOperator::fetchExtraOverloads( DataPointerType* a_pDataPointerType, vector<overload>& a_Overloads ) const
{
    Type* std_ptrdiff_t = typeOf<std::ptrdiff_t>();
    Type* pBoolType = typeOf<bool>();
    Type* pIntType = typeOf<int>();
    bool is_void = a_pDataPointerType->getPointedType()->removeAllQualifiers() == typeOf<void>();
    Type* ref = a_pDataPointerType->lvalueReferenceType(); 
    Type* Vref = a_pDataPointerType->volatileType()->lvalueReferenceType();
    Type* deref = a_pDataPointerType->removePointer()->lvalueReferenceType();

    switch(m_eOperator)
    {
        /// 13.6.5
        /// T *VQ & operator++(T *VQ &);
        /// T *VQ & operator--(T *VQ &);
        /// T * operator++(T *VQ &, int);
        /// T * operator--(T *VQ &, int);
    case e_Operator_PreIncrement:
        if(!is_void)
        {
            a_Overloads.push_back(overload(ref, a_pDataPointerType, nullptr, operation_delegate_t(a_pDataPointerType, &DataPointerType::preIncrement)));
            a_Overloads.push_back(overload(Vref, a_pDataPointerType, nullptr, operation_delegate_t(a_pDataPointerType, &DataPointerType::preIncrement)));
        }
        break;
    case e_Operator_PreDecrement:
        if(!is_void)
        {
            a_Overloads.push_back(overload(ref, a_pDataPointerType, nullptr, operation_delegate_t(a_pDataPointerType, &DataPointerType::preDecrement)));
            a_Overloads.push_back(overload(Vref, a_pDataPointerType, nullptr, operation_delegate_t(a_pDataPointerType, &DataPointerType::preDecrement)));
        }
        break;
    case e_Operator_PostIncrement:
        if(!is_void)
        {
            a_Overloads.push_back(overload(ref, a_pDataPointerType, pIntType, operation_delegate_t(a_pDataPointerType, &DataPointerType::postIncrement)));
            a_Overloads.push_back(overload(Vref, a_pDataPointerType, pIntType, operation_delegate_t(a_pDataPointerType, &DataPointerType::postIncrement)));
        }
        break;
    case e_Operator_PostDecrement:
        if(!is_void)
        {
            a_Overloads.push_back(overload(ref, a_pDataPointerType, pIntType, operation_delegate_t(a_pDataPointerType, &DataPointerType::postDecrement)));
            a_Overloads.push_back(overload(Vref, a_pDataPointerType, pIntType, operation_delegate_t(a_pDataPointerType, &DataPointerType::postDecrement)));
        }
        break;

        /// 13.6.6
        /// T & operator*(T *);
        // 
    case e_Operator_Dereference:
        if(!is_void)
        {
            a_Overloads.push_back(overload(deref, a_pDataPointerType, nullptr, operation_delegate_t(a_pDataPointerType, &DataPointerType::dereference)));
        }
        break;

        /// 13.6.8
        /// T * operator+(T *);
        // 
    case e_Operator_Plus:
        a_Overloads.push_back(overload(a_pDataPointerType, a_pDataPointerType, nullptr, operation_delegate_t(a_pDataPointerType, &DataPointerType::plus)));
        break;

        /// 13.6.13
        /// T * operator+(T *, std::ptrdiff_t);
        /// T & operator[](T *, std::ptrdiff_t);
        /// T * operator-(T *, std::ptrdiff_t);
        /// T * operator+(std::ptrdiff_t, T *);
        /// T & operator[](std::ptrdiff_t, T *);

    case e_Operator_Add:
        if(!is_void)
        {
            a_Overloads.push_back(overload(a_pDataPointerType, std_ptrdiff_t, a_pDataPointerType, operation_delegate_t(a_pDataPointerType, &DataPointerType::addRev)));
            a_Overloads.push_back(overload(a_pDataPointerType, a_pDataPointerType, std_ptrdiff_t, operation_delegate_t(a_pDataPointerType, &DataPointerType::add)));
        }
        break;

    case e_Operator_Subtract:
        if(!is_void)
        {
            a_Overloads.push_back(overload(a_pDataPointerType, a_pDataPointerType, std_ptrdiff_t, operation_delegate_t(a_pDataPointerType, &DataPointerType::subtract)));
        }
        /// 13.6.14
        /// std::ptrdiff_t operator-(T , T );
        a_Overloads.push_back(overload(std_ptrdiff_t, a_pDataPointerType, a_pDataPointerType, operation_delegate_t(a_pDataPointerType, &DataPointerType::subtractPointer)));
        break;

    case e_Operator_Bracket:
        if(!is_void)
        {
            a_Overloads.push_back(overload(deref, std_ptrdiff_t, a_pDataPointerType, operation_delegate_t(a_pDataPointerType, &DataPointerType::bracketRev)));
            a_Overloads.push_back(overload(deref, a_pDataPointerType, std_ptrdiff_t, operation_delegate_t(a_pDataPointerType, &DataPointerType::bracket)));
        }
        break;


        /// 13.6.21
        /// T *VQ & operator+=(T *VQ &, std::ptrdiff_t);
        /// T *VQ & operator-=(T *VQ &, std::ptrdiff_t);
    case e_Operator_AssignmentAdd:
        if(!is_void)
        {
            a_Overloads.push_back(overload(ref, ref, std_ptrdiff_t, operation_delegate_t(a_pDataPointerType, &DataPointerType::assignmentAdd)));
            a_Overloads.push_back(overload(Vref, Vref, std_ptrdiff_t, operation_delegate_t(a_pDataPointerType, &DataPointerType::assignmentAdd)));
        }
        break;

    case e_Operator_AssignmentSubtract:
        if(!is_void)
        {
            a_Overloads.push_back(overload(ref, ref, std_ptrdiff_t, operation_delegate_t(a_pDataPointerType, &DataPointerType::assignmentSubtract)));
            a_Overloads.push_back(overload(Vref, Vref, std_ptrdiff_t, operation_delegate_t(a_pDataPointerType, &DataPointerType::assignmentSubtract)));
        }
        break;
    }
}

void BuiltInOperator::fetchExtraOverloads( FunctionPointerType* a_pFunctionPointerType, vector<overload>& a_Overloads ) const
{
    fetchExtraOverloads(static_cast<PointerType*>(a_pFunctionPointerType), a_Overloads);
}

void BuiltInOperator::implicitConversions( Type** a_ppTypes, vector<conversions>& a_Conversions, vector<overload>& a_Overloads ) const
{
    Language* pLanguage = cplusplus();
    vector<overload> extraOverloads;
    for(size_t i = 0; i<m_uiOperandCount; ++i)
        fetchExtraOverloads(a_ppTypes[i], extraOverloads);
    a_Conversions.resize(extraOverloads.size()+m_Overloads.size());
    for(size_t i = 0; i<extraOverloads.size(); ++i)
    {
        conversions& conv = a_Conversions[i];
        extraOverloads[i].implicitConversions(pLanguage, a_ppTypes, conv);
        a_Overloads.push_back(extraOverloads[i]);
    }

    for(size_t i = 0; i<m_Overloads.size(); ++i)
    {
        conversions& conv = a_Conversions[i];
        m_Overloads[i].implicitConversions(pLanguage, a_ppTypes, conv);
        a_Overloads.push_back(m_Overloads[i]);
    }
}

void BuiltInOperator::implicitConversions( Expression** a_ppExpressions, vector<conversions>& a_Conversions, vector<overload>& a_Overloads ) const
{
    Type* types[3];
    for(size_t i = 0; i<m_uiOperandCount; ++i)
        types[i] = a_ppExpressions[i]->getValueType();
    implicitConversions(types, a_Conversions, a_Overloads);
}

void BuiltInOperator::editOverload( bool a_bAdd, Type* a_pResult, Type* a_pOp0, Type* a_pOp1, operation_delegate_t a_Delegate )
{
    if(a_bAdd)
        addOverload(a_pResult, a_pOp0, a_pOp1, a_Delegate);
    else 
        removeOverload(a_pResult, a_pOp0, a_pOp1, a_Delegate);
}

void BuiltInOperator::editOverload( bool a_bAdd, Type* a_pResult, Type* a_pOp0, operation_delegate_t a_Delegate )
{
    if(a_bAdd)
        addOverload(a_pResult, a_pOp0, 0, a_Delegate);
    else 
        removeOverload(a_pResult, a_pOp0, 0, a_Delegate);
}

void BuiltInOperator::addOverload( Type* a_pResult, Type* a_pOp0, Type* a_pOp1, operation_delegate_t a_Delegate )
{
    m_Overloads.push_back(overload(a_pResult, a_pOp0, a_pOp1, a_Delegate));
}

void BuiltInOperator::removeOverload( Type* a_pResult, Type* a_pOp0, Type* a_pOp1, operation_delegate_t a_Delegate )
{
    overload ov(a_pResult, a_pOp0, a_pOp1, a_Delegate);
    for(auto it = m_Overloads.begin(); it != m_Overloads.end(); ++it)
    {
        if(*it == ov)
        {
            m_Overloads.erase(it);
            return;
        }
    }
    o_assert(false);
}

const char* BuiltInOperator::OperatorName( EOperator a_eOperator )
{
    static map<EOperator, const char*> s_OperatorNames;
    if(s_OperatorNames.empty())
    {
        s_OperatorNames[e_Operator_Plus] = "+";
        s_OperatorNames[e_Operator_Minus] = "-";
        s_OperatorNames[e_Operator_Add] = "+";
        s_OperatorNames[e_Operator_Subtract] = "-";
        s_OperatorNames[e_Operator_Multiply] = "*";
        s_OperatorNames[e_Operator_Divide] = "/";
        s_OperatorNames[e_Operator_Address] = "&";
        s_OperatorNames[e_Operator_Dereference] = "*";
        s_OperatorNames[e_Operator_Arrow] = "->";
        s_OperatorNames[e_Operator_ArrowStar] = "->*";
        s_OperatorNames[e_Operator_PreDecrement] = "--";
        s_OperatorNames[e_Operator_PreIncrement] = "++";
        s_OperatorNames[e_Operator_PostDecrement] = "--";
        s_OperatorNames[e_Operator_PostIncrement] = "++";
        s_OperatorNames[e_Operator_Equal] = "==";
        s_OperatorNames[e_Operator_NotEqual] = "!=";
        s_OperatorNames[e_Operator_Greater] = ">";
        s_OperatorNames[e_Operator_Less] = "<";
        s_OperatorNames[e_Operator_GreaterEqual] = ">=";
        s_OperatorNames[e_Operator_LessEqual] = "<=";
        s_OperatorNames[e_Operator_LogicalAnd] = "&&";
        s_OperatorNames[e_Operator_LogicalOr] = "||";
        s_OperatorNames[e_Operator_XOr] = "^";
        s_OperatorNames[e_Operator_Not] = "!";
        s_OperatorNames[e_Operator_BitAnd] = "&";
        s_OperatorNames[e_Operator_BitOr] = "|";
        s_OperatorNames[e_Operator_Complement] = "~";
        s_OperatorNames[e_Operator_Modulo] = "%";
        s_OperatorNames[e_Operator_ShiftLeft] = "<<";
        s_OperatorNames[e_Operator_ShiftRight] = ">>";
        s_OperatorNames[e_Operator_Assignment] = "=";
        s_OperatorNames[e_Operator_AssignmentAdd] = "+=";
        s_OperatorNames[e_Operator_AssignmentSubtract] = "-=";
        s_OperatorNames[e_Operator_AssignmentMultiply] = "*=";
        s_OperatorNames[e_Operator_AssignmentDivide] = "/=";
        s_OperatorNames[e_Operator_AssignmentBitAnd] = "&=";
        s_OperatorNames[e_Operator_AssignmentBitOr] = "|=";
        s_OperatorNames[e_Operator_AssignmentModulo] = "%=";
        s_OperatorNames[e_Operator_AssignmentShiftLeft] = "<<=";
        s_OperatorNames[e_Operator_AssignmentShiftRight] = ">>=";
        s_OperatorNames[e_Operator_AssignmentXOr] = "^=";
        s_OperatorNames[e_Operator_Bracket] = "[]";
    }
    return s_OperatorNames[a_eOperator];
}

o_namespace_end(phantom, reflection)