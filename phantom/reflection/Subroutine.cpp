/* TODO LICENCE HERE */
 
/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Subroutine.h>
#include <phantom/reflection/Subroutine.hxx>
#include <phantom/reflection/CallExpression.h>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/LabelStatement.h>
#include <phantom/reflection/Interpreter.h>
/* *********************************************** */
o_registerN((phantom, reflection), Subroutine);

o_namespace_begin(phantom, reflection) 

o_invalid_def(Subroutine, "<unknown-subroutine>", Signature::Invalid(), e_unknowncall, o_invalid);

Subroutine::Subroutine()
    : NamedElement()
    , m_pSignature(nullptr)
    , m_pInstructions(nullptr)
    , m_pBlock(nullptr)
    , m_pClosure(nullptr)
    , m_uiFrameSize(0)
    , m_eABI(e_stdcall)
    , m_pLabelStatements(nullptr)
{

}

Subroutine::Subroutine( EABI a_eABI, modifiers_t a_Modifiers ) 
    : NamedElement("", a_Modifiers)
    , m_pSignature(nullptr)
    , m_pInstructions(nullptr)
    , m_pBlock(nullptr)
    , m_pClosure(nullptr)
    , m_uiFrameSize(0)
    , m_eABI(a_eABI)
    , m_pLabelStatements(nullptr)
{

}

Subroutine::Subroutine( const string& a_strName, EABI a_eABI, modifiers_t a_Modifiers ) 
    : NamedElement(a_strName, a_Modifiers)
    , m_pSignature(nullptr)
    , m_pInstructions(nullptr)
    , m_pBlock(nullptr)
    , m_pClosure(nullptr)
    , m_uiFrameSize(0)
    , m_eABI(a_eABI)
    , m_pLabelStatements(nullptr)
{

}

Subroutine::Subroutine( const string& a_strName, Signature* a_pSignature, EABI a_eABI, modifiers_t a_Modifiers /*= 0*/ ) 
    : NamedElement(a_strName, a_Modifiers)
    , m_pSignature(a_pSignature)
    , m_pInstructions(nullptr)
    , m_pBlock(nullptr)
    , m_pClosure(nullptr)
    , m_uiFrameSize(0)
    , m_eABI(a_eABI)
    , m_pLabelStatements(nullptr)
{
    if(m_pSignature)
    {
        if(m_pSignature->isShared())
        {
            addReferencedElement(a_pSignature);
        }
        else 
        {
            addElement(m_pSignature);
        }
    }
    else 
    {
        setInvalid();
    }
}

Subroutine::Subroutine( LanguageElement* a_pScope, const string& a_strName, const string& a_strSignature, EABI a_eABI, modifiers_t a_Modifiers /*= 0*/ )
    : NamedElement(a_strName, a_Modifiers)
    , m_pSignature(Signature::Create(a_Modifiers&(o_const|o_native)))
    , m_pInstructions(nullptr)
    , m_pBlock(nullptr)
    , m_pClosure(nullptr)
    , m_uiFrameSize(0)
    , m_eABI(a_eABI)
    , m_pLabelStatements(nullptr)
{
    o_assert(a_pScope);
    if(m_pSignature)
    {
        if(m_pSignature->isShared())
        {
            addReferencedElement(m_pSignature);
        }
        else 
        {
            addElement(m_pSignature);
        }
        m_pSignature->parse(a_strSignature, a_pScope);
    }
    else 
    {
        setInvalid();
    }
}

Subroutine::~Subroutine()
{
    if(m_pLabelStatements)
    {
        delete m_pLabelStatements;
    }
}

o_terminate_cpp(Subroutine)
{
    if(m_pInstructions)
    {
        for(auto it = m_pInstructions->begin(); it != m_pInstructions->end(); ++it)
        {
            delete *it;
        }
        delete m_pInstructions;
        m_pInstructions = nullptr;
    }
}

phantom::string Subroutine::getQualifiedName() const
{
    return m_pOwner ? (m_pOwner->getQualifiedName() + "::" + getName()) : getName() ;
}

phantom::string Subroutine::getQualifiedDecoratedName() const
{
    return m_pOwner ? (m_pOwner->getQualifiedDecoratedName() + "::" + getName() + (m_pSignature ? m_pSignature->getQualifiedDecoratedName() : "")) : getDecoratedName();
}

phantom::string Subroutine::getDecoratedName() const
{
    return getName() + (m_pSignature ? m_pSignature->getQualifiedDecoratedName() : nullptr);
}

void Subroutine::addInstruction( Instruction* a_pInstruction )
{
    if(m_pInstructions == nullptr)
    {
        m_pInstructions = new vector<Instruction*>;
    }
    m_pInstructions->push_back(a_pInstruction);
    a_pInstruction->m_pSubroutine = this;
    struct InstructionSorter
    {
        bool operator()(Instruction* a_pI0, Instruction* a_pI1) const 
        {
            return *a_pI0 < *a_pI1;
        }
    };
    std::sort(m_pInstructions->begin(), m_pInstructions->end(), InstructionSorter());
}

Instruction* Subroutine::findInstructionAtCodePosition( const CodePosition& position ) const
{
//     if(m_pInstructions == nullptr) return nullptr;
//     if(NOT(containsCodePosition(position))) return nullptr;
//     for(auto it = m_pInstructions->begin(); it != m_pInstructions->end(); ++it)
//     {
//         Instruction* pInstruction = *it;
//         if(pInstruction->containsCodePosition(position)) 
//             return pInstruction;
//     }
    return nullptr;
}

Instruction* Subroutine::findInstructionAtMemoryAddress( byte* a_pAddress ) const
{
    if(m_pInstructions == nullptr) return nullptr;
    for(auto it = m_pInstructions->begin(); it != m_pInstructions->end(); ++it)
    {
        Instruction* pInstruction = *it;
        if(pInstruction->getMemoryStart() == a_pAddress)
            return pInstruction;
    }
    return nullptr;
}

Instruction* Subroutine::findInstructionStartingAtMemoryAddress( byte* a_pAddress ) const
{
    if(m_pInstructions == nullptr) return nullptr;
    for(auto it = m_pInstructions->begin(); it != m_pInstructions->end(); ++it)
    {
        Instruction* pInstruction = *it;
        if(pInstruction->getMemoryStart() == a_pAddress)
            return pInstruction;
    }
    return nullptr;
}

Block* Subroutine::findBlockAtCodePosition( const CodePosition& a_Position ) const
{
//     if(m_pBlock AND m_pBlock->containsCodePosition(a_Position))
//         return m_pBlock->findBlockAtCodePosition(a_Position);
    return nullptr;
}

void Subroutine::setBlock( Block* a_pBlock )
{
    if(m_pBlock)
    {
        removeElement(m_pBlock);
    }
    m_pBlock = a_pBlock;
    if(m_pBlock)
    {
        addElement(m_pBlock);
    }
}

bool Subroutine::containsMemoryAddress( const byte* a_pAddress )
{
    return m_MemoryLocation.containsMemoryAddress(a_pAddress);
}

void Subroutine::referencedElementRemoved( LanguageElement* a_pElement )
{
    LanguageElement::referencedElementRemoved(a_pElement);
    if(m_pBlock == a_pElement)
        m_pBlock = nullptr;
    else if(m_pSignature == a_pElement)
        m_pSignature = nullptr;
}

bool Subroutine::matches( const string& a_strName, const vector<Type*>& a_FunctionSignature, modifiers_t a_Qualifiers /*= 0*/ ) const
{
    return m_strName == a_strName
        AND matches(a_FunctionSignature, a_Qualifiers);
}

bool Subroutine::matches( const vector<Type*>& a_ParameterTypes, modifiers_t a_Qualifiers ) const
{
    o_assert(a_Qualifiers == (a_Qualifiers & o_member_function_qualifiers_mask));
    return m_pSignature ? m_pSignature->matches(a_ParameterTypes, a_Qualifiers) : nullptr;
}

bool Subroutine::matches( const vector<LanguageElement*>& templateArguments, const vector<Type*>& parameterTypes, modifiers_t a_Qualifiers ) const
{
    o_assert(a_Qualifiers == (a_Qualifiers & o_member_function_qualifiers_mask));
    o_assert_no_implementation(); /// template function not supported yet
    return false; 
}

void Subroutine::call( void** a_pArgs ) const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Subroutine is invalid");
    }
    if(getReturnType() != typeOf<void>())
    {
        o_exception(exception::reflection_runtime_exception, "Missing return address for non-void call");
    }
    call(a_pArgs, m_pSignature->getParameterCount()+(m_eABI==e_thiscall), nullptr);
}

void Subroutine::call( void** a_pArgs, void* a_pReturnAddress ) const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Subroutine is invalid");
    }
    if(getReturnType() != typeOf<void>() AND a_pReturnAddress == nullptr)
    {
        o_exception(exception::reflection_runtime_exception, "Null return address passed to non-void call");
    }
    call(a_pArgs, m_pSignature->getParameterCount()+(m_eABI==e_thiscall), a_pReturnAddress);
}

void Subroutine::placementCall( void** a_pArgs, void* a_pReturnAddress ) const
{
    call(a_pArgs, a_pReturnAddress);
}

void Subroutine::call( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Subroutine is invalid");
    }
    if(m_eABI!=e_thiscall)
    {
        o_exception(exception::reflection_runtime_exception, "no caller expected for other convention than __thiscall");
    }
    size_t argCount = m_pSignature->getParameterCount()+1;
    void** newArgs = (void**)o_malloc(argCount*sizeof(void*));
    newArgs[0] = &a_pCallerAddress;
    memcpy(&newArgs[1], a_pArgs, (argCount-1)*sizeof(void*));
    call(newArgs, argCount, a_pReturnAddress);
    o_free(newArgs);
}

void Subroutine::placementCall( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const
{
    call(a_pCallerAddress, a_pArgs, a_pReturnAddress);
}

void Subroutine::call( void* a_pCallerAddress, void** a_pArgs ) const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Subroutine is invalid");
    }
    if(m_eABI!=e_thiscall)
    {
        o_exception(exception::reflection_runtime_exception, "no caller expected for other convention than __thiscall");
    }
    size_t argCount = m_pSignature->getParameterCount()+1;
    void** newArgs = (void**)o_malloc(argCount*sizeof(void*));
    newArgs[0] = &a_pCallerAddress;
    memcpy(&newArgs[1], a_pArgs, (argCount-1)*sizeof(void*));
    call(newArgs, argCount, nullptr);
    o_free(newArgs);
}

void Subroutine::call( void** a_pArgs, size_t a_uiCount, void* a_pReturnAddress ) const
{
    o_assert(!testModifiers(o_native));
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Subroutine is invalid");
    }
    void* pTemporary = getReturnType()->allocate();
    if(!m_ClosureCallDelegate.empty() && m_pClosure)
    {
        m_ClosureCallDelegate(m_pClosure, a_pArgs, a_uiCount, a_pReturnAddress);
    }
    else 
    {
        phantom::interpreter()->call(const_cast<Subroutine*>(this), a_pArgs, a_uiCount, pTemporary);
    }
    getReturnType()->copy(a_pReturnAddress, pTemporary);
    getReturnType()->deleteInstance(pTemporary);
}

void Subroutine::placementCall( void** a_pArgs, size_t a_uiCount, void* a_pReturnAddress ) const
{
    o_assert(!testModifiers(o_native));
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Subroutine is invalid");
    }
    if(!m_ClosureCallDelegate.empty() && m_pClosure)
    {
        m_ClosureCallDelegate(m_pClosure, a_pArgs, a_uiCount, a_pReturnAddress);
    }
    else 
    {
        phantom::interpreter()->call(const_cast<Subroutine*>(this), a_pArgs, a_uiCount, a_pReturnAddress);
    }
}

void Subroutine::registerLabelStatement( LabelStatement* a_pLabelStatement )
{
    if(m_pLabelStatements == nullptr)
    {
        m_pLabelStatements = new vector<LabelStatement*>;
    }
    a_pLabelStatement->m_uiIndex = m_pLabelStatements->size();
    m_pLabelStatements->push_back(a_pLabelStatement);
}

void Subroutine::unregisterLabelStatement( LabelStatement* a_pLabelStatement )
{
    o_assert(m_pLabelStatements);
    a_pLabelStatement->m_uiIndex = 0xffffffff;
    m_pLabelStatements->erase(std::find(m_pLabelStatements->begin(), m_pLabelStatements->end(), a_pLabelStatement));
    if(m_pLabelStatements->empty())
    {
        delete m_pLabelStatements;
        m_pLabelStatements = nullptr;
    }
}

void Subroutine::finalize()
{
    if(m_pSignature)
    {
        m_pSignature->setFinalized();
    }
}

Block* Subroutine::createBlock( LocalVariable* a_pThis )
{
    if(isNative())
    {
        o_exception(exception::reflection_runtime_exception, "Cannot create block on native subroutine");
    }
    if(testModifiers(o_pure_virtual))
    {
        o_exception(exception::reflection_runtime_exception, "Cannot create block on pure virtual subroutine");
    }
    return o_new(Block)(this, a_pThis);
}

ESignatureRelation Subroutine::getSignatureRelationWith( const string& a_strName, Signature* a_pSignature, modifiers_t a_Qualifiers ) const
{
    if(a_strName != getName()) return e_SignatureRelation_None;
    if((a_Qualifiers&o_member_function_qualifiers_mask) != (m_Modifiers&o_member_function_qualifiers_mask)) return e_SignatureRelation_None;

    if(getSignature()->getParameterCount() != a_pSignature->getParameterCount())
    {
        return e_SignatureRelation_None;
    }
    uint i = 0;
    for(;i<getSignature()->getParameterCount();++i)
    {
        if(NOT(getSignature()->getParameterType(i)->equals(a_pSignature->getParameterType(i))))
        {
            return e_SignatureRelation_None;
        }
    }

    // here, to sum, we have :
    // ¤ same name, 
    // ¤ same parameter count
    // ¤ same parameter types, 

    // We now look at the return types
    Type* thisReturnType = getSignature()->getReturnType()->removeConst();
    Type* otherReturnType = a_pSignature->getReturnType()->removeConst();
    if(thisReturnType->equals(otherReturnType)) 
    {
        return e_SignatureRelation_Equal;
    }

    // Only (const) class pointer/reference types can postulate to covariance and contravariance
    // We filter them by using address type implicit conversion
    if((thisReturnType->asDataPointerType() AND otherReturnType->asDataPointerType())
        OR (thisReturnType->asLValueReferenceType() AND otherReturnType->asLValueReferenceType())
        OR (thisReturnType->asRValueReferenceType() AND otherReturnType->asRValueReferenceType()))
    {
        // Covariance and Contravariance test
        if(thisReturnType->getUnderlyingType()->isKindOf(otherReturnType->getUnderlyingType()))
        {
            return e_SignatureRelation_Covariant;
        }
        else if(otherReturnType->getUnderlyingType()->isKindOf(thisReturnType->getUnderlyingType()))
        {
            // In the majority of case contravariance would be a forbidden case
            // We return a specific value for this result in case of ...
            return e_SignatureRelation_Contravariant;
        }
    }

    // Return types don't have any inheritance relation
    return e_SignatureRelation_Forbidden;
}

ESignatureRelation Subroutine::getSignatureRelationWith( Type* a_pReturnType, const string& a_strName, const vector<Type*>& a_Types, modifiers_t a_Qualifiers ) const
{
    if(a_strName != getName()) return e_SignatureRelation_None;
    if((a_Qualifiers&o_member_function_qualifiers_mask) != (m_Modifiers&o_member_function_qualifiers_mask)) return e_SignatureRelation_None;

    if(getSignature()->getParameterCount() != a_Types.size())
    {
        return e_SignatureRelation_None;
    }
    uint i = 0;
    for(;i<getSignature()->getParameterCount();++i)
    {
        if(NOT(getSignature()->getParameterType(i)->equals(a_Types[i])))
        {
            return e_SignatureRelation_None;
        }
    }

    // here, to sum, we have :
    // ¤ same name, 
    // ¤ same parameter count
    // ¤ same parameter types, 

    // We now look at the return types
    Type* thisReturnType = getSignature()->getReturnType();
    Type* otherReturnType = a_pReturnType;
    if(thisReturnType->equals(otherReturnType)) 
    {
        return e_SignatureRelation_Equal;
    }

    // Only (const) class pointer/reference types can postulate to covariance and contravariance
    // We filter them by using address type implicit conversion
    if((thisReturnType->asDataPointerType() AND otherReturnType->asDataPointerType())
        OR (thisReturnType->asLValueReferenceType() AND otherReturnType->asLValueReferenceType())
        OR (thisReturnType->asRValueReferenceType() AND otherReturnType->asRValueReferenceType()))
    {
        // Covariance and Contravariance test
        if(thisReturnType->getUnderlyingType()->isKindOf(otherReturnType->getUnderlyingType()))
        {
            return e_SignatureRelation_Covariant;
        }
        else if(otherReturnType->getUnderlyingType()->isKindOf(thisReturnType->getUnderlyingType()))
        {
            // In the majority of case contravariance would be a forbidden case
            // We return a specific value for this result in case of ...
            return e_SignatureRelation_Contravariant;
        }
    }

    // Return types don't have any inheritance relation
    return e_SignatureRelation_Forbidden;
}

ESignatureRelation Subroutine::getSignatureRelationWith( Subroutine* a_pSubroutine ) const
{
    return getSignatureRelationWith(a_pSubroutine->getName(), a_pSubroutine->getSignature(), a_pSubroutine->getModifiers());
}

Expression* Subroutine::createCallExpression( const vector<Expression*>& arguments ) const
{
    return o_new(CallExpression)(const_cast<Subroutine*>(this), arguments);
}

void MemoryLocation::setStart( byte* a_pAddress )
{
    o_assert(a_pAddress);
    o_assert(m_pEnd == 0 || a_pAddress < m_pEnd); 
    m_pStart = a_pAddress;
}

void MemoryLocation::setEnd( byte* a_pAddress )
{
    o_assert(a_pAddress);
    o_assert(m_pStart == 0 || a_pAddress > m_pStart); 
    m_pEnd = a_pAddress;
}

bool MemoryLocation::containsMemoryAddress( const byte* a_pAddress ) const
{
    return a_pAddress >= m_pStart && a_pAddress < m_pEnd;
}


o_namespace_end(phantom, reflection)