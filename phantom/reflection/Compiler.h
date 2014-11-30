

#ifndef o_reflection_Compiler_h__
#define o_reflection_Compiler_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
#include "phantom/Message.h"
#include <queue>
#include <stack>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Compiler);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class LanguageElement;
class InstanceDataMemberVariable;

class IncompleteStatement;
class BreakStatement;
class ContinueStatement;
class ForStatement;
class WhileStatement;
class DoWhileStatement;
class SwitchStatement;
class CaseStatement;
class LabelStatement;
class IfStatement;
class ExpressionStatement;

class Block;
class CallExpression;
class CastExpression;
class DereferenceExpression;
class AddressExpression;
class ConstantExpression;
class DataExpression;
class InstanceDataMemberAccess;
class PropertyAccess;
class StaticVariableAccess;
class ArrayElementAccess;
class StringLiteralExpression;

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
    typedef std::stack<variant_map, deque<variant_map>> stack;

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

    // User custom elements
    template<typename t_LanguageElement>
    variant compile(t_LanguageElement* a_pElement) 
    { 
        LanguageElement* pLanguageElementCastCompileTimeAssert = a_pElement;
        auto it = m_CompilationDelegates.find(typeOf<t_LanguageElement>());
        if(it == m_CompilationDelegates.end()) return variant();
        fastdelegate::FastDelegate1< variant, t_LanguageElement* > delegate;
        delegate.SetMemento(it->second); 
        return delegate(a_pElement);
    }

    template<typename t_LanguageElement>
    void registerCompilationDelegate(fastdelegate::FastDelegate1<variant, t_LanguageElement*> a_Delegate)
    {
        LanguageElement* pLanguageElementCastCompileTimeAssert = (t_LanguageElement*)nullptr;
        o_assert(typeOf<t_LanguageElement>()->isKindOf(typeOf<LanguageElement>()));
        m_CompilationDelegates[typeOf<t_LanguageElement>()] = a_Delegate.GetMemento();
    }

    // Default basic elements

    // Statements
    virtual variant compile(LanguageElement* a_pElement) { return variant(); }
    virtual variant compile(Block* a_pBlock) { return variant(); }
    virtual variant compile(ForStatement* a_pForStatement) { return variant(); }
    virtual variant compile(WhileStatement* a_pWhileStatement) { return variant(); }
    virtual variant compile(IfStatement* a_pIfStatement) { return variant(); }
    virtual variant compile(SwitchStatement* a_pSwitchStatement) { return variant(); }
    virtual variant compile(DoWhileStatement* a_pDoWhileStatement) { return variant(); }
    virtual variant compile(ExpressionStatement* a_pExpressionStatement) { return variant(); }
    virtual variant compile(IncompleteStatement* a_pIncompleteStatement) { return variant(); }
    virtual variant compile(BreakStatement* a_pBreakStatement) { return variant(); }
    virtual variant compile(ContinueStatement* a_pContinueStatement) { return variant(); }

    // Expressions
    virtual variant compile(CallExpression* a_pCallExpression) { return variant(); }
    virtual variant compile(CastExpression* a_pCastExpression) { return variant(); }
    virtual variant compile(DereferenceExpression* a_pDereferenceExpression) { return variant(); }
    virtual variant compile(AddressExpression* a_pAddressExpression) { return variant(); }
    virtual variant compile(ConstantExpression* a_pConstantExpression) { return variant(); }
    virtual variant compile(DataExpression* a_pDataExpression) { return variant(); }
    virtual variant compile(InstanceDataMemberAccess* a_pInstanceDataMemberAccess) { return variant(); }
    virtual variant compile(PropertyAccess* a_pPropertyAccess) { return variant(); }
    virtual variant compile(StaticVariableAccess* a_pStaticVariableAccess) { return variant(); }
    virtual variant compile(ArrayElementAccess* a_pArrayElementAccess) { return variant(); }
    virtual variant compile(StringLiteralExpression* a_pStringLiteralExpression) { return variant(); }

    // Elements 
    virtual variant compile(Structure* a_pStructure) { return variant(); }
    virtual variant compile(ClassType* a_pType) { return variant(); }
    virtual variant compile(Class* a_pClass) { return variant(); }
    virtual variant compile(InstanceMemberFunction* a_pInstanceMemberFunction) { return variant(); }
    virtual variant compile(Signal* a_pSignal) { return variant(); }
    virtual variant compile(state::StateMachine* a_pStateMachine) { return variant(); }
    virtual variant compile(state::State* a_pState) { return variant(); }
    virtual variant compile(state::Track* a_pTrack) { return variant(); }

protected:
    virtual void    preCompile(LanguageElement* a_pLanguageElement) {}
    virtual void    postCompile(LanguageElement* a_pLanguageElement) {}
    void            incrementQueueWaitingCounter(LanguageElement* a_pLanguageElement);
    void            decrementQueueWaitingCounter(LanguageElement* a_pLanguageElement);
    void	        terminateElementCompilation(LanguageElement* a_pLanguageElement);

protected:
	list<variant>				        m_QueuedForDestruction;
	vector<list<QueueNode>>	            m_CompilationQueues;
    int                                 m_iCurrentPass;
	stack	                            m_QueuedInData;
	stack	                            m_QueuedOutData;
    map<LanguageElement*, int>	        m_QueueWaitingCounter;
	map<LanguageElement*, variant_map>	m_RememberedSolvingData;
	uint 			                    m_Flags;
	LanguageElement*				    m_pCompiledElement;
    map<Class*, fastdelegate::DelegateMemento>        m_CompilationDelegates;
};

o_namespace_end(phantom, reflection)




#endif