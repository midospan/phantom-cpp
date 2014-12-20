/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Compiler.h"
#include "Compiler.hxx"
#include <phantom/reflection/LanguageElement.h>
#include "phantom/Message.h"
#include <stdarg.h>
/* *********************************************** */
o_registerN((phantom, reflection), Compiler);

o_namespace_begin(phantom, reflection) 

Compiler::Compiler( void )
: m_pCompiledElement(NULL)
, m_Flags(0)
, m_iCurrentPass(-1)
{
	m_QueuedInData.push(variant_map());
}

Compiler::~Compiler( void )
{
	m_QueuedInData.pop();
}

void Compiler::queueElement( int a_iPass, LanguageElement* a_pLanguageElement )
{
    o_assert(a_pLanguageElement);
	variant_map data = m_QueuedInData.empty()
        ? variant_map()
        : m_QueuedInData.top();
	getCompilationQueue(a_iPass).push_back(QueueNode(a_pLanguageElement, data));
    if(m_pCompiledElement)
    {
        incrementQueueWaitingCounter(m_pCompiledElement);
    }
}

void Compiler::set( const string& a_strId, const variant& a_Data )
{
	m_QueuedInData.top()[a_strId] = a_Data;
}

const variant& Compiler::get( const string& a_strId )
{
	return m_QueuedInData.top()[a_strId];
}

variant Compiler::compileElement( LanguageElement* a_pLanguageElement )
{
	return compile(a_pLanguageElement, m_QueuedInData.empty() ? variant_map() : m_QueuedInData.top());
}

variant Compiler::compile( LanguageElement* a_pLanguageElement, const variant_map& a_InData )
{
	LanguageElement* a_pASTOld = m_pCompiledElement;
	m_pCompiledElement = a_pLanguageElement;
	m_QueuedInData.push(a_InData);
    //a_pLanguageElement->compilationStart(this);

    preCompile(m_pCompiledElement);
    /*jit::JitSubroutine* pPreSubroutine = in("subroutine").as<jit::JitSubroutine*>();
    if(pPreSubroutine)
    {
        pPreSubroutine->pushCodeLocation(a_pLanguageElement->getLocation());
    }*/

    variant pResult = a_pLanguageElement->compile(this);

    // restore previous code location (if function still being compiled)
    /*jit::JitSubroutine* pPostSubroutine = in("subroutine").as<jit::JitSubroutine*>();
    if(pPostSubroutine && pPostSubroutine == pPreSubroutine)
    {
        pPreSubroutine->popCodeLocation();
    }*/
    postCompile(m_pCompiledElement);

    m_RememberedSolvingData[m_pCompiledElement] = m_QueuedInData.top();
	m_QueuedInData.pop();
	m_pCompiledElement = a_pASTOld;
	if(m_QueueWaitingCounter[a_pLanguageElement] == 0)
    {
        terminateElementCompilation(a_pLanguageElement);
    }
	return pResult;
}

void Compiler::terminateElementCompilation(LanguageElement* a_pLanguageElement)
{
    variant_map data = m_RememberedSolvingData[a_pLanguageElement];
    m_QueuedInData.push(data);
    //a_pLanguageElement->compilationEnd(this);
    m_QueuedInData.pop();
    m_QueueWaitingCounter[a_pLanguageElement] = -1; // means that it is completely solved
}

void Compiler::compile( int a_iPass )
{
    o_assert(NOT(hasFinished()));
    o_assert(a_iPass == m_iCurrentPass+1);
    m_iCurrentPass = a_iPass;
	while(NOT(getCompilationQueue(a_iPass).empty()))
	{
		QueueNode qn = getCompilationQueue(a_iPass).front();
		getCompilationQueue(a_iPass).pop_front();
		compile(qn.m_pLanguageElement, qn.m_InData);
        if(qn.m_pLanguageElement->getOwner())
        {
            decrementQueueWaitingCounter(qn.m_pLanguageElement->getOwner());
        }
	}

    bool queuesEmpty = true;
    for(auto it = m_CompilationQueues.begin(); it != m_CompilationQueues.end(); ++it)
    {
        if(!it->empty()) 
        {
            queuesEmpty = false;
            break;
        }
    }
    if(queuesEmpty)
    {
        m_Flags |= e_Flag_Finished;
    }
}

variant Compiler::compile( ClassType* a_pClassType )
{
    o_assert(a_pClassType->getExtraData());
    if(a_pClassType->getExtraData()->m_iState < ClassType::extra_data::e_State_Finalized)
    {
        a_pClassType->finalize();
    }
    o_assert(a_pClassType->getExtraData()->m_iState < ClassType::extra_data::e_State_Compiling);
    const_cast<ClassType::extra_data*>(a_pClassType->getExtraData())->m_iState = ClassType::extra_data::e_State_Compiling;
    return variant();
}

variant Compiler::compile( Class* a_pClass )
{
    compile(static_cast<ClassType*>(a_pClass));
    if(a_pClass->getStateMachine())
        compile(a_pClass->getStateMachine());
    return variant();
}

variant Compiler::compile( state::StateMachine* a_pStateMachine )
{
//     o_assert(a_pStateMachine->m_pCompilationData);
//     size_t i = 0;
//     size_t count = a_pStateMachine->getStateCount();
//     for(;i<count;++i)
//     {
//         static_cast<State*>(a_pStateMachine->m_States[i])->compile(this);
//     }
//     a_pStateMachine->m_pCompilationData->m_bCompiled = true;
    return variant();
}

void Compiler::message(EMessageType a_eType, const CodeLocation& a_Location, char* a_Format, ... )
{
    va_list args;
    va_start(args, a_Format);
	phantom::message(classOf(this)->getQualifiedDecoratedName(), a_eType, a_Location, a_Format, args);
    va_end(args);
}

void Compiler::pushMessage(EMessageType a_eType, const CodeLocation& a_Location, char* a_Format, ...)
{
    va_list args;
    va_start(args, a_Format);
    phantom::pushMessage(classOf(this)->getQualifiedDecoratedName(), a_eType, a_Location, a_Format, args);
    va_end(args);
}

void Compiler::popMessage()
{
    phantom::popMessage(classOf(this)->getQualifiedDecoratedName());
}

void Compiler::incrementQueueWaitingCounter( LanguageElement* a_pLanguageElement )
{
    m_QueueWaitingCounter[a_pLanguageElement]++;
    if(a_pLanguageElement->getOwner()) incrementQueueWaitingCounter(a_pLanguageElement->getOwner());
}

void Compiler::decrementQueueWaitingCounter( LanguageElement* a_pLanguageElement )
{
    if(--m_QueueWaitingCounter[a_pLanguageElement] == 0)
    {
        terminateElementCompilation(a_pLanguageElement);
    }
    if(a_pLanguageElement->getOwner()) 
        decrementQueueWaitingCounter(a_pLanguageElement->getOwner());
}

void Compiler::reset()
{
    m_QueuedForDestruction.clear();
    m_RememberedSolvingData.clear();
    m_QueueWaitingCounter.clear();
    m_CompilationQueues.clear(); 
    m_pCompiledElement = nullptr;
    m_iCurrentPass = -1;
    while(!m_QueuedInData.empty()) m_QueuedInData.pop();
    while(!m_QueuedOutData.empty()) m_QueuedOutData.pop();
    m_QueuedInData.push(variant_map());
    m_Flags = 0;
}

o_namespace_end(phantom, reflection)