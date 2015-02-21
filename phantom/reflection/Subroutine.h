/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Subroutine_h__
#define o_phantom_reflection_Subroutine_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

typedef fastdelegate::FastDelegate4<void*, void**, size_t, void*> closure_call_delegate;

struct MemoryLocation
{
    MemoryLocation() : m_pStart(0), m_pEnd(0) {}
    MemoryLocation(byte* start, byte* end) 
        : m_pStart(start), m_pEnd(end) 
    {
        o_assert(m_pStart && m_pEnd && (m_pStart < m_pEnd));
    }
    bool operator==(const MemoryLocation& other) const 
    {
        return m_pStart == other.m_pStart AND m_pEnd == other.m_pEnd;
    }

    bool operator<(const MemoryLocation& other) const 
    {
        return m_pStart < other.m_pStart;
    }

    bool isValid() const { return m_pStart && m_pEnd; }

    byte* getStart() const { return m_pStart; }
    byte* getEnd() const { return m_pEnd; }

    void setStart(byte* a_pAddress);
    void setEnd(byte* a_pAddress);

    bool containsMemoryAddress(const byte* a_pAddress) const;

    inline size_t getRange() const { return m_pEnd-m_pStart; }

protected:
    byte* m_pStart;
    byte* m_pEnd;
};

class Instruction
{
    friend class Subroutine;

public:
    Instruction(int a_iOpcode
        , const CodeLocation& a_CodeLocation
        , const MemoryLocation& a_MemoryLocation) 
        : m_pSubroutine(nullptr)
        , m_iOpcode(a_iOpcode)
        , m_CodeLocation(a_CodeLocation)
        , m_MemoryLocation(a_MemoryLocation)
        , m_pUserData(nullptr)
    {

    }

    bool operator<(const Instruction& other) const 
    {
        return m_MemoryLocation < other.m_MemoryLocation;
    }

    Subroutine* getSubroutine() const { return m_pSubroutine; }
    void setUserData(void* a_pUserData) const { m_pUserData = a_pUserData; }
    void* getUserData() const { return m_pUserData; }
    int getOpCode() const { return m_iOpcode; }
    const CodeLocation&     getCodeLocation() const { return m_CodeLocation; }
    const MemoryLocation&   getMemoryLocation() const { return m_MemoryLocation; }
    Source* getSource() const { return m_CodeLocation.getSource(); }

    byte* getMemoryStart() const { return m_MemoryLocation.getStart(); }
    byte* getMemoryEnd() const { return m_MemoryLocation.getEnd(); }

    inline bool containsCodePosition(const CodePosition& position)
    {
        return m_CodeLocation.containsCodePosition(position);
    }

    inline bool containsMemoryAddress(const byte* a_pAddress)
    {
        return m_MemoryLocation.containsMemoryAddress(a_pAddress);
    }

protected:
    Subroutine*     m_pSubroutine;
    int             m_iOpcode;
    CodeLocation    m_CodeLocation;
    MemoryLocation  m_MemoryLocation;
    mutable void*   m_pUserData;
};

enum ESignatureRelation
{
    e_SignatureRelation_None = 0,
    e_SignatureRelation_Equal,
    e_SignatureRelation_Covariant,
    e_SignatureRelation_Contravariant,
    e_SignatureRelation_Forbidden,
};

class o_export Subroutine : public NamedElement, public Callable
{
    o_language_element;

    o_invalid_decl(Subroutine);

    friend class Block;
    friend class LabelStatement;
    friend class ClassType;
    friend class Class;

public:
    Subroutine();
    Subroutine(const string& a_strName, EABI a_eABI, modifiers_t a_Modifiers = 0);
    Subroutine(const string& a_strName, Signature* a_pSignature, EABI a_eABI, modifiers_t a_Modifiers = 0);
    Subroutine(LanguageElement* a_pScope, const string& a_strName, const string& a_strSignature, EABI a_eABI, modifiers_t a_Modifiers = 0);
    o_destructor ~Subroutine();

    o_terminate();

    EABI                getABI() const { return m_eABI; }


    virtual LanguageElement* asLanguageElement() const { return const_cast<Subroutine*>(this); }
    virtual Callable*   asCallable() const { return const_cast<Subroutine*>(this); }
    virtual Subroutine* asSubroutine() const { return const_cast<Subroutine*>(this); }

    inline Signature*   getSignature() const { return m_pSignature; }
    void                setSignature(Signature* a_pSignature) { m_pSignature = a_pSignature; }

    ESignatureRelation  getSignatureRelationWith( const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers ) const;
    ESignatureRelation  getSignatureRelationWith( Subroutine* a_pSubroutine ) const;
    ESignatureRelation  getSignatureRelationWith( Type* a_pReturnType, const string& a_strName, const vector<Type*>& a_Types, modifiers_t a_Modifiers ) const;

    virtual string      getDecoratedName() const;
    virtual string      getQualifiedName() const;
    virtual string      getQualifiedDecoratedName() const;

    virtual vector<Type*> getParameterTypes() const { return m_pSignature->getParameterTypes(); }
    virtual Type*         getParameterType(size_t i) const { return m_pSignature ? m_pSignature->getParameterType(i) : nullptr; }
    virtual Parameter*    getParameter(size_t i) const { return m_pSignature ? m_pSignature->getParameter(i) : nullptr; }
    virtual size_t        getParameterCount() const { return m_pSignature ? m_pSignature->getParameterCount() : 0; }
    virtual size_t        getMinimumNeededParameterCount() const { return m_pSignature ?m_pSignature->getMinimumNeededParameterCount() : 0; }

    virtual bool        matches(const vector<Type*>& parameterTypes, modifiers_t a_Modifiers) const;
    virtual bool        matches(const vector<LanguageElement*>& templateArguments, const vector<Type*>& parameterTypes, modifiers_t a_Modifiers) const;
    bool                matches(const string& a_strName, const vector<Type*>& a_FunctionSignature, modifiers_t a_Qualifiers = 0 ) const;

    Type*               getReturnType() const    { return m_pSignature ? m_pSignature->getReturnType() : nullptr; }

    virtual void        call( void* a_pCallerAddress, void** a_pArgs ) const;
    virtual void        call( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const;
    virtual void        placementCall( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const;

    virtual void        call( void** a_pArgs ) const;
    virtual void        call( void** a_pArgs, void* a_pReturnAddress ) const;
    virtual void        placementCall( void** a_pArgs, void* a_pReturnAddress ) const;

    void                call( void** a_pArgs, size_t a_uiCount, void* a_pReturnAddress ) const;
    void                placementCall( void** a_pArgs, size_t a_uiCount, void* a_pReturnAddress ) const;

    void                setMemoryLocation(const MemoryLocation& a_MemoryLocation ) { m_MemoryLocation = a_MemoryLocation; }
    const MemoryLocation& getMemoryLocation() const { return m_MemoryLocation; }
    byte*               getMemoryStart() const { return m_MemoryLocation.getStart(); }
    byte*               getMemoryEnd() const { return m_MemoryLocation.getEnd(); }
    void                setMemoryStart(byte* b) 
    {
        m_MemoryLocation.setStart(b);
    }
    void                setMemoryEnd(byte* b) 
    {
        m_MemoryLocation.setEnd(b);
    }

    void                addInstruction(Instruction* a_pInstruction);

    Instruction*        getInstruction(size_t i) const 
    { 
        o_assert(m_pInstructions && m_pInstructions->size() > i);
        return (*m_pInstructions)[i]; 
    }

    size_t              getInstructionCount() const { return m_pInstructions ? m_pInstructions->size() : 0; }

    Instruction*        findInstructionAtCodePosition(const CodePosition& position) const;
    Instruction*        findInstructionAtMemoryAddress(byte* a_pAddress) const;
    Instruction*        findInstructionStartingAtMemoryAddress(byte* a_pAddress) const;

    Block*              findBlockAtCodePosition(const CodePosition& a_Position) const;

    Block*              getBlock() const { return m_pBlock; }
    void                setBlock(Block* a_pBlock);

    virtual Block*      createBlock() { return createBlock(nullptr); }

    virtual Expression* createCallExpression(const vector<Expression*>& arguments) const;

    bool                containsMemoryAddress(const byte* a_pAddress);

    virtual void*       getAddress(void* a_pObject, void** a_pParams) const
    {
        return nullptr;
    }

    virtual void*       getAddress(void** a_pParams) const
    {
        return nullptr;
    }

    virtual bool        isAddressable() const { return getReturnType() ? getReturnType()->removeConst()->asLValueReferenceType() != nullptr : false; }

    virtual void*       getClosure() const { return m_pClosure; }

    void                setClosure(void* a_pClosure) 
    { 
        o_assert(!testModifiers(o_native));
        m_pClosure = a_pClosure; 
    }

    size_t              getFrameSize() const { return m_uiFrameSize; }

    LabelStatement*     getLabelStatement(size_t a_uiIndex) const { return m_pLabelStatements ? (*m_pLabelStatements)[a_uiIndex] : nullptr; }

protected:
    Subroutine(EABI a_eABI, modifiers_t a_Modifiers = 0);
    virtual void        referencedElementRemoved(LanguageElement* a_pElement);
    void                registerLabelStatement(LabelStatement* a_pLabelStatement);
    void                unregisterLabelStatement(LabelStatement* a_pLabelStatement);
    virtual void        finalize();
    Block*              createBlock(LocalVariable* a_pThis);
protected:
    Signature*                      m_pSignature;
    EABI                            m_eABI;
    vector<Instruction*>*           m_pInstructions;
    vector<LabelStatement*>*        m_pLabelStatements;
    Block*                          m_pBlock;
    MemoryLocation                  m_MemoryLocation;
    void*                           m_pClosure;
    closure_call_delegate           m_ClosureCallDelegate;
    size_t                          m_uiFrameSize;
};

o_namespace_end(phantom, reflection)


    o_declareN((phantom, reflection), EABI);


#endif
