

#ifndef o_reflection_Compiler_h__
#define o_reflection_Compiler_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
#include <queue>
#include <stack>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Compiler);
/* *********************************************** */

o_namespace_begin(phantom, reflection)
    
struct CompilerData
{
    CompilerData(LanguageElement* a_pElement) : m_pElement(a_pElement) {}
    virtual ~CompilerData() {}
    LanguageElement* m_pElement;
};

class Compiler 
{
public:
    typedef map<string, variant>                        variant_map;
    typedef std::stack<variant_map, deque<variant_map> > stack;

    struct QueueNode
    {
        QueueNode(LanguageElement*	a_pLanguageElement, const variant_map& a_InData)
            : m_pLanguageElement(a_pLanguageElement)
            , m_InData(a_InData)
        {

        }
        LanguageElement*	m_pLanguageElement;
        variant_map	m_InData;
    };

	enum EFlag
	{
		e_Flag_Failed = 0x1,
        e_Flag_Warned = 0x2,
        e_Flag_Finished = 0x4,
	};

	Compiler(void);
	~Compiler(void);

    void reset();

    bool hasFinished() const { return (m_Flags & e_Flag_Finished) == e_Flag_Finished; }
	bool hasFailed() const { return (m_Flags & e_Flag_Failed) == e_Flag_Failed; }
	bool hasWarned() const { return (m_Flags & e_Flag_Warned) == e_Flag_Warned; }

	void set(const string& a_strId, const variant& a_Data);
    
	const variant& get(const string& a_strId);

	void    pushMessage(EMessageType a_eType, const CodeLocation& m_Location, char* a_Format, ...);
    void    popMessage();

    void	message(EMessageType a_eType, const CodeLocation& m_Location, char* a_Format, ...);

	void	checkQueueAccumulatorFor(LanguageElement* a_pLanguageElement);
	
	void	queueElement( int a_iPass, LanguageElement* a_pLanguageElement );

	variant compileElement( LanguageElement* a_pLanguageElement );

	variant compile( LanguageElement* a_pLanguageElement, const variant_map& a_InData );

    int getCurrentPass() const { return m_iCurrentPass; }

    bool    stepCompile()
    {
        if(!hasFinished())
        {
            compile(m_iCurrentPass+1);
        }
        return hasFinished();
    }

	void	compile(int a_uiPass);

    bool    hasQueuedDescendant(LanguageElement* a_pLanguageElement) const;

    list<QueueNode>& getCompilationQueue(int a_iPass)
    {
        if(int(m_CompilationQueues.size()) <= a_iPass)
        {
            m_CompilationQueues.resize(a_iPass+1);
        }
        return m_CompilationQueues[a_iPass];
    }

    // Default cplusplus like elements
    virtual variant compile(LanguageElement* a_pElement) { return variant(); }

    // Namespace
    virtual variant compile(Namespace* a_pNamespace) { return variant(); }

    // Types 
    virtual variant compile(Type* a_pType) { return variant(); }
    virtual variant compile(PrimitiveType* a_pType) { return variant(); }
    virtual variant compile(FunctionPointerType* a_pType) { return variant(); }
    virtual variant compile(MemberFunctionPointerType* a_pType) { return variant(); }
    virtual variant compile(DataMemberPointerType* a_pType) { return variant(); }
    virtual variant compile(DataPointerType* a_pType) { return variant(); }
    virtual variant compile(ReferenceType* a_pType) { return variant(); }
    virtual variant compile(ConstType* a_pType) { return variant(); }
    virtual variant compile(ArrayType* a_pType) { return variant(); }
    virtual variant compile(Enum* a_pEnum) { return variant(); }
    virtual variant compile(ClassType* a_pClassType);
    virtual variant compile(Class* a_pClass);
    virtual variant compile(Structure* a_pStructure) { return variant(); }
    virtual variant compile(Union* a_pUnion) { return variant(); }
    virtual variant compile(PODUnion* a_pPODUnion) { return variant(); }
    virtual variant compile(AnonymousSection* a_pAnonymousSection) { return variant(); }
    virtual variant compile(AnonymousStruct* a_pAnonymousStruct) { return variant(); }
    virtual variant compile(AnonymousUnion* a_pAnonymousUnion) { return variant(); }
    virtual variant compile(Template* a_pTemplate) { return variant(); }
    virtual variant compile(TemplateSpecialization* a_pTemplateSpecialization) { return variant(); }

    // Subroutines
    virtual variant compile(Subroutine* a_pSubroutine) { return variant(); }
    virtual variant compile(Constructor* a_pConstructor) { return variant(); }
    virtual variant compile(Function* a_pFunction) { return variant(); }
    virtual variant compile(StaticMemberFunction* a_pStaticMemberFunction) { return variant(); }
    virtual variant compile(InstanceMemberFunction* a_pInstanceMemberFunction) { return variant(); }
    virtual variant compile(Signal* a_pSignal) { return variant(); }

    // Variables
    virtual variant compile(StaticDataMember* a_pStaticDataMember) { return variant(); }
    virtual variant compile(StaticVariable* a_pStaticVariable) { return variant(); }
    virtual variant compile(InstanceDataMember* a_pInstanceDataMember) { return variant(); }
    virtual variant compile(Property* a_pProperty) { return variant(); }

    // Statechart
    virtual variant compile(state::StateMachine* a_pStateMachine);
    virtual variant compile(state::State* a_pState) { return variant(); }
    virtual variant compile(state::Track* a_pTrack) { return variant(); }

    // Statements
    virtual variant compile(Block* a_pBlock) { return variant(); }
    virtual variant compile(LocalVariable* a_pLocalVariable) { return variant(); }
    virtual variant compile(Parameter* a_pParameter) { return variant(); }
    virtual variant compile(Signature* a_pSignature) { return variant(); }
    virtual variant compile(BranchStatement* a_pBranchStatement) { return variant(); }
    virtual variant compile(BranchIfStatement* a_pBranchIfStatement) { return variant(); }
    virtual variant compile(BranchIfNotStatement* a_pBranchIfNotStatement) { return variant(); }
    virtual variant compile(ExpressionStatement* a_pExpressionStatement) { return variant(); }
    virtual variant compile(ReturnStatement* a_pReturnStatement) { return variant(); }
    virtual variant compile(LabelStatement* a_pLabelStatement) { return variant(); }

    // Expressions
    virtual variant compile(CallExpression* a_pCallExpression) { return variant(); }
    virtual variant compile(CastExpression* a_pCastExpression) { return variant(); }
    virtual variant compile(DereferenceExpression* a_pDereferenceExpression) { return variant(); }
    virtual variant compile(AddressExpression* a_pAddressExpression) { return variant(); }
    virtual variant compile(ReferenceExpression* a_pReferenceExpression) { return variant(); }
    virtual variant compile(ConstantExpression* a_pConstantExpression) { return variant(); }
    virtual variant compile(DataExpression* a_pDataExpression) { return variant(); }
    virtual variant compile(InstanceDataMemberExpression* a_pInstanceDataMemberExpression) { return variant(); }
    virtual variant compile(LocalVariableExpression* a_pLocalVariableExpression) { return variant(); }
    virtual variant compile(PropertyExpression* a_pPropertyExpression) { return variant(); }
    virtual variant compile(StaticVariableExpression* a_pStaticVariableExpression) { return variant(); }
    virtual variant compile(ArrayExpression* a_pArrayExpression) { return variant(); }
    virtual variant compile(StringLiteralExpression* a_pStringLiteralExpression) { return variant(); }
    virtual variant compile(MemberFunctionPointerCallExpression* a_pMemberFunctionPointerCallExpression) { return variant(); }
    virtual variant compile(DataMemberPointerExpression* a_pDataMemberPointerExpression) { return variant(); }
    virtual variant compile(AssignmentExpression* a_pAssignmentExpression) { return variant(); }
    virtual variant compile(ConstructorCallExpression* a_pConstructorCallExpression) { return variant(); }
    virtual variant compile(PlacementConstructionExpression* a_pPlacementConstructionExpression) { return variant(); }
    virtual variant compile(BinaryOperationExpression* a_pBinaryOperatorExpression) { return variant(); }
    virtual variant compile(PreUnaryOperationExpression* a_pPreUnaryOperationExpression) { return variant(); }
    virtual variant compile(PostUnaryOperationExpression* a_pPostUnaryOperationExpression) { return variant(); }
    virtual variant compile(SingleParameterFunctionExpression* a_pSingleParameterFunctionExpression) { return variant(); }

    virtual variant compile(Constant* a_pConstant) { return variant(); }

protected:
    virtual void    preCompile(LanguageElement* a_pLanguageElement) {}
    virtual void    postCompile(LanguageElement* a_pLanguageElement) {}
    void            incrementQueueWaitingCounter(LanguageElement* a_pLanguageElement);
    void            decrementQueueWaitingCounter(LanguageElement* a_pLanguageElement);
    void	        terminateElementCompilation(LanguageElement* a_pLanguageElement);

protected:
	list<variant>				        m_QueuedForDestruction;
	vector<list<QueueNode> >	            m_CompilationQueues;
    int                                 m_iCurrentPass;
	stack	                            m_QueuedInData;
	stack	                            m_QueuedOutData;
    map<LanguageElement*, int>	        m_QueueWaitingCounter;
	map<LanguageElement*, variant_map>	m_RememberedSolvingData;
	uint 			                    m_Flags;
	LanguageElement*				    m_pCompiledElement;
    // map<Class*, fastdelegate::DelegateMemento>        m_CompilationDelegates;
};

o_namespace_end(phantom, reflection)




#endif