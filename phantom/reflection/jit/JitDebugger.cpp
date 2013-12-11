/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "phantom/def_jit_internal.h"
#include "JitDebugger.h"
#include "hwbrk.h"
/* *********************************************** */
o_registerN((phantom, reflection, jit), JitDebugger);


__declspec(naked) void phantom_moon_script_DebugDataBase_builtInBreak()
{
    // Astuce to go back exactly where we came from instead of the classic return address
    __asm 
    {
        PUSH        EBP                ; Save ebp
        MOV         EBP, ESP           ; Set stack frame pointer
        SUB         ESP, 32    ; Allocate space for locals
        PUSH EAX;
        PUSH EBX;
        PUSH ECX;
        PUSH EDX;
    }
    DWORD rebp;
    DWORD eip;
    rebp = 0;
    __asm 
    {
        MOV rebp, EBP
    }
    eip = *((DWORD*)((unsigned char*)rebp+4)) - BREAK_INSTRUCTION_SIZE;
    phantom::reflection::jit::JitDebugger::Instance()->handleSoftwareBreakPoint(0);
    *((DWORD*)((unsigned char*)rebp+4)) = eip;
    
    __asm 
    {
        POP EDX;
        POP ECX;
        POP EBX;
        POP EAX;
        MOV         ESP, EBP      ; Restore stack pointer
        POP         EBP           ; Restore ebp
        RET                     ; Return from function
    }
}

o_namespace_begin(phantom, reflection, jit)


JitDebugger* JitDebugger::Instance()
{
    static JitDebugger*                           sm_pInstance = nullptr;
    if(sm_pInstance == nullptr)
    {
        sm_pInstance = o_new(JitDebugger);
    }
    return sm_pInstance;
}

JitDebugger::JitDebugger( void ) 
    : m_pCurrentBreakPoint(nullptr)
    , m_DebuggedThread(0)
    , m_bDebuggerStarted(false)
    , m_EBP(nullptr)
    , m_bStepIntoEnabled(false)
    , m_RootEBP(nullptr)
    , m_iEnablingCounter(0)
    , m_StepByStepBreakPointHandle(0)
    , m_StepByStepEIP(nullptr)
    , m_StepByStepSubroutine(nullptr)
    , m_StepByStepLine(0)
    , m_StepByStepEBP(0)
    , m_Request(e_Request_None)
    , m_pMutex(nullptr)
    , m_pGenericContext(nullptr)
{
}

JitDebugger::~JitDebugger( void )
{
}

o_initialize_cpp(JitDebugger)
{
    collectDebuggableNativeSubroutines();
    o_connect(classOf<Subroutine>(), kindCreated(void*), this, subroutineCreated(void*));
    o_connect(classOf<Subroutine>(), kindDestroyed(void*), this, subroutineDestroyed(void*));
}

o_terminate_cpp(JitDebugger)
{
    o_disconnect(classOf<Subroutine>(), kindCreated(void*), this, subroutineCreated(void*));
    o_disconnect(classOf<Subroutine>(), kindDestroyed(void*), this, subroutineDestroyed(void*));
}

CodePosition JitDebugger::insertBreakPoint( const CodePosition& a_Position )
{
    CodePosition position = a_Position;
    position.column = 1;
    Instruction* pBreakpointInstruction = nullptr;
    for(auto it = m_DebuggableSubroutines.begin(); it != m_DebuggableSubroutines.end(); ++it)
    {
        Subroutine* pSubroutine = *it;
        if(pSubroutine->containsCodePosition(a_Position))
        {
            size_t count = pSubroutine->getInstructionCount();
            for(size_t i = 0; i < count; ++i)
            {
                Instruction* pInstruction = pSubroutine->getInstruction(i);
                if(pInstruction->getCodeLocation().getStart().line == a_Position.line)
                {
                    pBreakpointInstruction = pInstruction;
                    break;
                }
            }
            break;
        }
    }
    o_assert(pBreakpointInstruction == nullptr OR pBreakpointInstruction->getSubroutine()->containsMemoryAddress(pBreakpointInstruction->getMemoryStart()));
    if(pBreakpointInstruction == nullptr) return 0;
    BreakPoint* a_pBreakPoint = addBreakPoint(pBreakpointInstruction, BreakPoint::e_Flag_User);
    if(m_iEnablingCounter == 0 && m_bDebuggerStarted)
    {
        a_pBreakPoint->setEnabled(true);
    }
    return pBreakpointInstruction->getCodeLocation().getStart();
}

bool JitDebugger::removeBreakPoint( Instruction* a_pInstruction )
{
    BreakPoint* pBreakPoint = getBreakPoint(a_pInstruction);
    if(pBreakPoint)
    {
        removeBreakPoint(pBreakPoint, BreakPoint::e_Flag_User);
        return true;
    }
    return false;
}

bool JitDebugger::removeBreakPoint( const CodePosition& a_Position )
{
    Instruction* pInstruction = findInstructionAtCodePosition(a_Position);
    if(pInstruction)
        return removeBreakPoint(pInstruction);
    return false;
}

#ifdef _WIN32
#define GENERIC_EIP ((unsigned char*)((LPCONTEXT)m_pGenericContext)->Eip)
#define GENERIC_EBP ((unsigned char*)((LPCONTEXT)m_pGenericContext)->Ebp)
#define GENERIC_ESP ((unsigned char*)((LPCONTEXT)m_pGenericContext)->Esp)
#define GENERIC_EAX ((unsigned char*)((LPCONTEXT)m_pGenericContext)->Eax)
#define GENERIC_EBX ((unsigned char*)((LPCONTEXT)m_pGenericContext)->Ebx)
#define GENERIC_ECX ((unsigned char*)((LPCONTEXT)m_pGenericContext)->Ecx)
#define GENERIC_EDX ((unsigned char*)((LPCONTEXT)m_pGenericContext)->Edx)
#endif

bool JitDebugger::handleHardwareBreakPoint(void* a_pGenericContext)
{
    printf("-------------------\n");
    printf("HARDWARE BREAKPOINT\n");
    printf("-------------------\n");
    m_pGenericContext = a_pGenericContext;
    m_bBroke = false;
    Instruction* pInstruction = findInstructionAtMemoryAddress(GENERIC_EIP);
    if(m_StepByStepBreakPointHandle != 0 && (GENERIC_EIP != m_StepByStepEIP))
    {
        // Step by step
        if(pInstruction != nullptr) 
        {
            if((m_StepByStepSubroutine != pInstruction->getSubroutine()) OR (m_StepByStepLine != pInstruction->getCodeLocation().getStart().line))
            {
                if(m_bStepIntoEnabled OR (m_StepByStepEBP != *((unsigned char**)(GENERIC_EBP+4))))
                {
                    m_pCurrentHardwareBreakpointInstruction = pInstruction;
                    m_bBroke = true;
                }
            }
        }
        RemoveHardwareBreakpoint(m_StepByStepBreakPointHandle);
    }
    else 
    {
        // Data break point

    }

    if(m_bBroke)
    {
        o_emit debuggerBroke();
        while(m_bBroke) Sleep(10);
        o_emit debuggerResumed();
    }

    m_pCurrentHardwareBreakpointInstruction = nullptr;
    return true;
}


bool JitDebugger::handleSoftwareBreakPoint(void* a_pGenericContext)
{
    bool result = true;
    if(m_pMutex) m_pMutex->lock();
    o_assert(m_iEnablingCounter == 0, "break points should have been disabled");
    m_pGenericContext = a_pGenericContext;
    printf("BREAKING at %x EBP:%x THIS:%x\n", GENERIC_EIP, GENERIC_EBP, *((void**)(GENERIC_EBP-4)));
    m_bBroke = true;
    BreakPoint* pBreakPoint = findBreakPointStartingAtMemoryAddress(GENERIC_EIP);
    if(pBreakPoint == nullptr) 
    {
        printf("NO BREAKPOINT at %x\n", GENERIC_EIP);
        auto out_of_script_found = m_BreakPoints.find(nullptr);
        if(out_of_script_found != m_BreakPoints.end() 
            AND GENERIC_EIP == out_of_script_found->second->getMemoryStart())
        {
            printf("OUT OF SCRIPT BREAKPOINT at %x\n", GENERIC_EIP);
            out_of_script_found->second->setEnabled(false);
            m_BreakPoints.erase(nullptr);
            m_bStepIntoEnabled = false;
            // some restorer breakpoints may be set on out-of-script code
            removeBreakPoints(BreakPoint::e_Flag_Restorer);
            removeBreakPoints(BreakPoint::e_Flag_StepOver);
            updateBreakPoints();
        }
        else
        {
            result = false;
        }
        if(m_pMutex) m_pMutex->unlock();
    }
    else
    {
        printf("BREAKPOINT FOUND with flags = %x\n", pBreakPoint->getFlags());
        fetchCallStack(GENERIC_EIP, GENERIC_EBP);
        m_pCurrentBreakPoint = pBreakPoint;
        o_assert(m_pCurrentBreakPoint);
        printf("INSTRUCTION PTR = %x\n", m_pCurrentBreakPoint->getInstruction());
        o_assert(m_pCurrentBreakPoint->getInstruction());
        m_pCurrentHardwareBreakpointInstruction = m_pCurrentBreakPoint->getInstruction();

        if(m_pCurrentBreakPoint->isFlagSet(BreakPoint::e_Flag_Restorer))
        {
            removeBreakPoint(m_pCurrentBreakPoint, BreakPoint::e_Flag_Restorer);

            printf("RESTORER BREAKPOINT\n");
            m_bBroke = false;
        }

        // If bypass set, we continue execution unless stronger flag is set
        if(m_pCurrentBreakPoint AND m_pCurrentBreakPoint->isByPassed())
        {
            printf("BY PASS\n");
            m_bBroke = false;
        }

        // Step over flag stronger than bypass
        if(m_pCurrentBreakPoint 
            AND (m_pCurrentBreakPoint->isFlagSet(BreakPoint::e_Flag_StepOver) 
            OR m_pCurrentBreakPoint->isFlagSet(BreakPoint::e_Flag_StepInto)))
        {
            printf("removeBreakPoints(BreakPoint::e_Flag_StepOver)\n");
            removeBreakPoints(BreakPoint::e_Flag_StepOver);
            m_bStepIntoEnabled = false;
            m_bBroke = true;
        }

        if(m_pCurrentBreakPoint AND m_pCurrentBreakPoint->isFlagSet(BreakPoint::e_Flag_User))
        {
            printf("addRestorerBreakPoint(m_pCurrentBreakPoint)\n");
            addRestorerBreakPoint(m_pCurrentBreakPoint);
            m_bBroke = true;
        }

        printf("updateBreakPoints()\n");
        updateBreakPoints();

        if(m_pMutex) m_pMutex->unlock();

        if(m_bBroke)
        {
            printf("m_bBroke\n");
            o_emit debuggerBroke();
            while(m_bBroke) 
            {
                if(m_pMutex) m_pMutex->lock();
                switch(m_Request)
                {
                case e_Request_StepInto:
                    printf("e_Request_StepInto\n");
                    applyStepInto();
                    break;
                case e_Request_StepOver:
                    printf("e_Request_StepOver\n");
                    applyStepOver();
                    break;
                }
                m_Request = e_Request_None;
                if(m_pMutex) m_pMutex->unlock();
                Sleep(10);
            }
            o_emit debuggerResumed();
        }
    }

    printf("RESUMED\n");
    m_CallStackFrames.clear();
    m_pCurrentBreakPoint = nullptr;
    m_pGenericContext = nullptr;
    m_pCurrentHardwareBreakpointInstruction = nullptr;
    m_EBP = nullptr;
    return true;
}

void JitDebugger::addRestorerBreakPoint(BreakPoint* a_pBreakPoint)
{
    Instruction* pInstructionToRestore = a_pBreakPoint->getInstruction();
    Instruction* pInstruction = findInstructionStartingAtMemoryAddress(pInstructionToRestore->getMemoryEnd());
    /*if(pInstruction == nullptr)
    {
        printf("ADD OUT-OF-SCRIPT RESTORER BREAKPOINT at %x\n", a_pBreakPoint->getInstruction()->getMemoryEnd());
        BreakPoint* pBreakPoint = setOutOfScriptBreakPoint(a_pBreakPoint->getInstruction()->getMemoryEnd(), BreakPoint::e_Flag_Restorer);
        pBreakPoint->setEnabled(true);
    }
    else
    {
        printf("ADD RESTORER BREAKPOINT at %x\n", pInstruction->getMemoryStart());
        BreakPoint* pBreakPoint = addBreakPoint(pInstruction, BreakPoint::e_Flag_Restorer);
        pBreakPoint->setEnabled(true);
    }*/

    if(pInstruction == nullptr)
    {
        byte* break_instruction_address = *((byte**)(m_EBP+4)) - CALL_INSTRUCTION_SIZE;
        Instruction* pUpInsn = findInstructionStartingAtMemoryAddress(break_instruction_address);
        if(pUpInsn != nullptr) 
        {
            pInstruction = findInstructionStartingAtMemoryAddress(pUpInsn->getMemoryEnd());
            if(pInstruction == nullptr) 
                pInstruction = findNextInstruction(pUpInsn, *((byte**)m_EBP));
        }
    }
    if(pInstruction == a_pBreakPoint->getInstruction())
        pInstruction = nullptr; 

    if(pInstruction)
    {
        byte* eip = GENERIC_EIP;

        if(pInstruction->getSubroutine() == pInstructionToRestore->getSubroutine())
        {
            //o_assert(pNext->getMemoryStart() > m_pCurrentHardwareBreakpointInstruction->getMemoryStart()); // ensure we are going forward (if not the case, its very weird...)
            if(pInstruction->getMemoryStart() <= pInstructionToRestore->getMemoryStart())
            {
                printf("RESTORE DIFFERENT FRAME\n");
            }
            for(byte* address = pInstructionToRestore->getMemoryStart(); address < pInstruction->getMemoryStart(); address++)
            {
                Instruction* pIntermediateInstruction = findInstructionAtMemoryAddress(address);
                if(pIntermediateInstruction == nullptr) 
                {
                    printf("RESTORE INSN SKIPPED %x\n", *address);
                    continue;
                }
                else 
                {
                    printf("RESTORE ACCEPTED %x\n", *address);
                }

                Instruction* pJumpDest = findInstructionJumpDestination(pIntermediateInstruction, address);

                if(pJumpDest AND pJumpDest != pInstructionToRestore)
                {
                    BreakPoint* pJmpBreakPoint = addBreakPoint(pJumpDest, BreakPoint::e_Flag_Restorer);
                    pJmpBreakPoint->setEnabled(true);
                    printf("STEP OVER : add jump dest break point\n");
                }
            }
        }

        BreakPoint* pNewBreakPoint = addBreakPoint(pInstruction, BreakPoint::e_Flag_Restorer);
        pNewBreakPoint->setEnabled(true);
        printf("RESTORE BREAKPOINT ADDED at %x\n", pNewBreakPoint->getInstruction()->getMemoryStart());
    }
    else 
    {
        printf("RESTORE OOS BREAKPOINT ADDED\n");
        BreakPoint* pNewBreakPoint = setOutOfScriptBreakPoint(pInstructionToRestore->getSubroutine()->getMemoryEnd(), BreakPoint::e_Flag_Restorer);
        pNewBreakPoint->setEnabled(true);
    }
}

void JitDebugger::resume()
{
    printf("RESUME\n");
    m_bBroke = false;
}

void JitDebugger::stepOver()
{
    m_Request = e_Request_StepOver;
}

void JitDebugger::stepInto()
{
    m_Request = e_Request_StepInto;
}

Instruction* JitDebugger::findInstructionJumpDestination(Instruction* a_pInstruction, byte* a_pAddress)
{
    Instruction* pJmpDest = nullptr;
    int opcode = a_pInstruction->getOpCode();
    if(opcode >= JIT_OP_BR && opcode <= JIT_OP_BR_NFGE_INV)
    {
        unsigned char op = *a_pAddress;
        // branch => handle jumps
        // X86
        if(op == 0xEB OR op == 0xE3 OR (op >= 0x71 AND op <= 0x7F))
        {
            // JMP relative short
            char offset = *(a_pAddress+1);
            printf("STEP OVER : JMP short offset %d\n", offset);
            pJmpDest = findInstructionAtMemoryAddress(a_pAddress+2+offset);
        }
        else if(op == 0xE9)
        {
            // JMP relative long
            long offset = *((long*)(a_pAddress+1));
            printf("STEP OVER : JMP long offset %d\n", offset);
            pJmpDest = findInstructionAtMemoryAddress(a_pAddress+5+offset);
        }
        else if(op == 0x0F)
        {
            long offset = *((long*)(a_pAddress+2));
            printf("STEP OVER : JMP IF long offset %d\n", offset);
            pJmpDest = findInstructionAtMemoryAddress(a_pAddress+6+offset);
        }
        else if(op == 0xEA)
        {
            byte* absolute_address = *((byte**)(a_pAddress+1));
            printf("STEP OVER : JMP absolute %x\n", absolute_address);
            pJmpDest = findInstructionAtMemoryAddress(absolute_address);
        }
    }
    return pJmpDest;
}

void JitDebugger::applyStepOver()
{
    o_assert(m_bDebuggerStarted);
    
    if(m_pCurrentHardwareBreakpointInstruction == nullptr OR m_pGenericContext == nullptr OR m_DebuggedThread == 0) 
    {
        printf("STEP OVER CANCELLED : %x %x %x\n", m_pCurrentHardwareBreakpointInstruction, m_pGenericContext, m_DebuggedThread);
        return;
    }
    /*
    m_StepByStepBreakPointHandle = SetHardwareBreakpoint(m_DebuggedThread, HWBRK_TYPE_CODE, HWBRK_SIZE_1, 0);
    m_StepByStepEBP = GENERIC_EBP;
    m_StepByStepEIP = GENERIC_EIP;
    m_StepByStepLine = m_pCurrentInstruction->line;
    m_StepByStepMemberFunction = m_pCurrentMemberFunction;*/

    printf("STEP OVER\n");  

    // pure step by step break point => remove it on disabling 
    int currentLine = m_pCurrentHardwareBreakpointInstruction->getCodeLocation().getEnd().line;
    
    Instruction* pNext = m_pCurrentHardwareBreakpointInstruction;
    do 
    {
        pNext = findInstructionStartingAtMemoryAddress(pNext->getMemoryEnd());  
    }
    while(pNext && pNext->getCodeLocation().getStart().line == currentLine);

    if(pNext == nullptr)
    {
        byte* break_instruction_address = *((byte**)(m_EBP+4)) - CALL_INSTRUCTION_SIZE;
        Instruction* pUpInsn = findInstructionStartingAtMemoryAddress(break_instruction_address);
        if(pUpInsn != nullptr) 
        {
            pNext = findInstructionStartingAtMemoryAddress(pUpInsn->getMemoryEnd());
            if(pNext == nullptr) 
                pNext = findNextInstruction(pUpInsn, *((byte**)m_EBP));
        }
    }
    if(pNext == m_pCurrentHardwareBreakpointInstruction)
        pNext = nullptr; 

    if(pNext)
    {
        byte* eip = GENERIC_EIP;

        if(pNext->getSubroutine() == m_pCurrentHardwareBreakpointInstruction->getSubroutine())
        {
            //o_assert(pNext->getMemoryStart() > m_pCurrentHardwareBreakpointInstruction->getMemoryStart()); // ensure we are going forward (if not the case, its very weird...)
            if(pNext->getMemoryStart() <= m_pCurrentHardwareBreakpointInstruction->getMemoryStart())
            {
                printf("STEP OVER IN DIFFERENT FRAME\n");
            }
            for(byte* address = m_pCurrentHardwareBreakpointInstruction->getMemoryStart(); address < pNext->getMemoryStart(); address++)
            {
                Instruction* pIntermediateInstruction = findInstructionAtMemoryAddress(address);
                if(pIntermediateInstruction == nullptr) 
                {
                    printf("STEP OVER INSN SKIPPED %x\n", *address);
                    continue;
                }
                else 
                {
                    printf("STEP OVER INSN ACCEPTED %x\n", *address);
                }

                Instruction* pJumpDest = findInstructionJumpDestination(pIntermediateInstruction, address);
                
                if(pJumpDest AND pJumpDest != m_pCurrentHardwareBreakpointInstruction)
                {
                    BreakPoint* pJmpBreakPoint = addBreakPoint(pJumpDest, BreakPoint::e_Flag_StepOver);
                    pJmpBreakPoint->setEnabled(true);
                    printf("STEP OVER : add jump dest break point\n");
                }
            }
        }
        
        BreakPoint* pNewBreakPoint = addBreakPoint(pNext, BreakPoint::e_Flag_StepOver);
        pNewBreakPoint->setEnabled(true);
        printf("STEP OVER BREAKPOINT ADDED at %x\n", pNewBreakPoint->getInstruction()->getMemoryStart());
    }
    else 
    {
        printf("STEP OVER OFS BREAKPOINT ADDED\n");
        BreakPoint* pNewBreakPoint = setOutOfScriptBreakPoint(m_pCurrentHardwareBreakpointInstruction->getSubroutine()->getMemoryEnd(), BreakPoint::e_Flag_StepOver);
        pNewBreakPoint->setEnabled(true);
    }
    resume();
}

void JitDebugger::applyStepInto()
{
    o_assert(m_bDebuggerStarted);
    if(m_pCurrentHardwareBreakpointInstruction == nullptr) 
    {
        printf("STEP INTO CANCELLED\n");
        return;
    }
    printf("STEP INTO\n");
    m_bStepIntoEnabled = true;
    updateBreakPoints();
    applyStepOver();
}

BreakPoint* JitDebugger::setOutOfScriptBreakPoint(byte* start, int flags)
{
    BreakPoint* new_bp = m_BreakPoints[nullptr];
    if(new_bp == nullptr)
    {
        new_bp = m_BreakPoints[nullptr] = new BreakPoint;
    }
    new_bp->setHardCodedMemoryAddress(start);
    new_bp->setFlags(flags);
    return new_bp;
}

BreakPoint* JitDebugger::addBreakPoint( Instruction* a_pInstruction, int flags )
{
    BreakPoint* new_bp = m_BreakPoints[a_pInstruction];
    if(new_bp == nullptr)
    {
        new_bp = m_BreakPoints[a_pInstruction] = new BreakPoint(a_pInstruction);
    }

    a_pInstruction->setUserData(new_bp);
    new_bp->setFlags(flags);

    return new_bp;
}

void JitDebugger::removeBreakPoint( BreakPoint* a_pBreakPoint, BreakPoint::EFlag flag )
{
    a_pBreakPoint->unsetFlag(flag);
    if(a_pBreakPoint->getFlags() == 0)
    {
        a_pBreakPoint->setEnabled(false);

        if(m_pCurrentBreakPoint == a_pBreakPoint)
        {
            printf("CURRENT BREAKPOINT REMOVED/NULLIFIED\n");
            m_pCurrentBreakPoint = nullptr;
        }

        printf("START a_pBreakPoint->getInstruction()->setUserData(nullptr);\n");
        if(a_pBreakPoint->getInstruction())
            a_pBreakPoint->getInstruction()->setUserData(nullptr);

        printf("m_BreakPoints.erase(a_pBreakPoint->getInstruction());\n");
        m_BreakPoints.erase(a_pBreakPoint->getInstruction());

        printf("delete a_pBreakPoint;\n");
        delete a_pBreakPoint;
    }
}

void BreakPoint::setEnabled( bool value )
{
    if(isEnabled() == value) return;
    
    if(value)
    {
        //printf("BP ENABLED with %x\n", m_iFlags);
        // enable
        m_iStates |= e_State_Enabled; 

        // save instruction code
        memcpy(m_ReplacementCode, getMemoryStart(), BREAK_INSTRUCTION_SIZE);

        unsigned char call_code[BREAK_INSTRUCTION_SIZE] = {0xCC}; //{ 0xe8, rp.relative_pos_bytes[0], rp.relative_pos_bytes[1], rp.relative_pos_bytes[2], rp.relative_pos_bytes[3]};

        // replace instruction code
        memcpy(getMemoryStart(), call_code, BREAK_INSTRUCTION_SIZE);

    }
    else 
    {
        //printf("BP DISABLED with %x\n", m_iFlags);
        m_iStates &= ~e_State_Enabled; 
        // restore instruction code
        memcpy(getMemoryStart(), m_ReplacementCode, BREAK_INSTRUCTION_SIZE);
    }

    o_verify(FlushInstructionCache(GetCurrentProcess(), getMemoryStart(), BREAK_INSTRUCTION_SIZE), "");
}

BreakPoint* JitDebugger::findBreakPointStartingAtMemoryAddress( byte* start ) 
{
    Instruction* pInstruction = findInstructionStartingAtMemoryAddress(start);
    return pInstruction 
            ? (BreakPoint*)(pInstruction->getUserData())
            : nullptr;
}

void JitDebugger::enableMemberFunctionEntryBreakPoint( Subroutine* a_pSubroutine )
{
    o_assert(std::find(m_DebuggableSubroutines.begin(), m_DebuggableSubroutines.end(), a_pSubroutine) != m_DebuggableSubroutines.end());
    m_BreakPoints[a_pSubroutine->getInstruction(0)]->setEnabled(true);
}

BreakPoint* JitDebugger::getBreakPoint( Instruction* insn )
{
    auto found = m_BreakPoints.find(insn);
    return (found != m_BreakPoints.end()) ? (found->second) : nullptr;
}

// TODO : implement this in LanguageElement as 'getRootOwner'
LanguageElement* JitDebugger::getSubroutineRootOwner(Subroutine* a_pSubroutine) const 
{
    LanguageElement* pOwner = a_pSubroutine->getOwner();
    while(pOwner && pOwner->getOwner())
    {
        pOwner = pOwner->getOwner();
    }
    return pOwner;
}

bool JitDebugger::isSubroutineReadyForDebug(Subroutine* a_pSubroutine) const
{
    return a_pSubroutine->getInstructionCount() > 0 
        && getSubroutineRootOwner(a_pSubroutine) == phantom::rootNamespace(); 
}

void JitDebugger::startDebugger()
{
    for(auto it = m_DebuggableSubroutines.begin(); it != m_DebuggableSubroutines.end(); ++it)
    {
        if(isSubroutineReadyForDebug(*it))
        {
            // add step into break point
            addBreakPoint((*it)->getInstruction(0), BreakPoint::e_Flag_StepInto);
        }
        else 
        {
            m_DebuggableSubroutinesNotReady.push_back(*it);
        }
    }
    printf("startDebugger\n");
    o_assert(!m_bDebuggerStarted);
    m_bDebuggerStarted = true;
    updateBreakPoints();
}


void JitDebugger::endDebugger()
{
    if(m_bBroke)
    {
        resume();
    }
    while(m_pGenericContext) 
    {
        Yield(); // wait for resume completed
    }

    printf("endDebugger\n");
    o_assert(m_bDebuggerStarted);
    auto it = m_BreakPoints.begin();
    auto end = m_BreakPoints.end();
    for(;it!=end;++it)
    {
        it->second->setEnabled(false);
    }
    m_bDebuggerStarted = false;
    m_DebuggableSubroutinesNotReady.clear();
}

void JitDebugger::fetchCallStack( byte* eip, byte* ebp )
{
    bool currentFrame = false;
    if(m_EBP == nullptr) 
    {
        m_EBP = ebp;
        currentFrame = true;
    }
    Instruction* pInstruction = findInstructionStartingAtMemoryAddress(eip);
    if(pInstruction == nullptr) pInstruction = findInstructionAtMemoryAddress(eip);
    if((pInstruction == nullptr) AND (m_RootEBP == nullptr)) return;
    byte* up_eip = *((byte**)(ebp+4)) - CALL_INSTRUCTION_SIZE;
    byte* up_ebp = *((byte**)ebp);

    m_CallStackFrames.push_back(FrameInfo(pInstruction, ebp, (void*)(ebp-4)));
    if(up_ebp == m_RootEBP) return;
    fetchCallStack(up_eip, up_ebp);
}

SourceFile* JitDebugger::getCallStackSourceFile( size_t i ) const
{
    if(m_CallStackFrames[i].getInstruction() == nullptr) return nullptr;
    return m_CallStackFrames[i].getInstruction()->getSourceFile();
}


Instruction* JitDebugger::findNextInstruction( Instruction* insn, unsigned char* ebp )
{
    o_assert(ebp);
    Instruction* pNext = findInstructionStartingAtMemoryAddress(insn->getMemoryEnd());
    if(pNext) return pNext;
    byte* break_instruction_address = *((byte**)(ebp+4)) - CALL_INSTRUCTION_SIZE;
    Instruction* pUpInsn = findInstructionStartingAtMemoryAddress(break_instruction_address);
    if(pUpInsn == nullptr) return nullptr;
    pNext = findInstructionStartingAtMemoryAddress(pUpInsn->getMemoryEnd());
    if(pNext) return pNext;
    return findNextInstruction(pUpInsn, *((byte**)ebp));
}

bool JitDebugger::doesBreakPointMustBeEnabled(BreakPoint* a_pBreakPoint) const
{
    return (a_pBreakPoint != m_pCurrentBreakPoint) 
        AND (a_pBreakPoint->isFlagSet(BreakPoint::e_Flag_User) 
        OR a_pBreakPoint->isFlagSet(BreakPoint::e_Flag_StepOver)
        OR a_pBreakPoint->isFlagSet(BreakPoint::e_Flag_Restorer) 
        OR (a_pBreakPoint->isFlagSet(BreakPoint::e_Flag_StepInto) AND m_bStepIntoEnabled))
        ;
}


void JitDebugger::updateBreakPoints()
{
    printf("UPDATE BREAKPOINTS:\n");
    // Enabling/Disabling pass
    {
        auto it = m_BreakPoints.begin();
        auto end = m_BreakPoints.end();
        for(;it!=end;++it)
        {
            BreakPoint* a_pBreakPoint = it->second;
            // TODO : clean debug code
            bool enabled = doesBreakPointMustBeEnabled(a_pBreakPoint);
            if(enabled)
            {
                printf("+++ BREAKPOINT ENABLED ADDRESS: %x LOCATION: %d %d\n", a_pBreakPoint->getMemoryStart(), a_pBreakPoint->getInstruction() ? a_pBreakPoint->getInstruction()->getCodeLocation().getStart().line : 0);
            }
            a_pBreakPoint->setEnabled(enabled);
        }
    }
    
}

CodePosition JitDebugger::getCallStackCodePosition( size_t i ) const
{
    return m_CallStackFrames[i].getInstruction() ? m_CallStackFrames[i].getInstruction()->getCodeLocation().getStart() : CodePosition();
}

Subroutine* JitDebugger::getCallStackSubroutine( size_t i ) const
{
    return m_CallStackFrames[i].getInstruction() ? m_CallStackFrames[i].getInstruction()->getSubroutine() : nullptr;
}

Block* JitDebugger::getCallStackBlock( size_t i ) const
{
    return m_CallStackFrames[i].getInstruction() ? m_CallStackFrames[i].getInstruction()->getSubroutine()->findBlockAtCodePosition(getCallStackCodePosition(i)) : nullptr;
}

void* JitDebugger::getCallStackThisPointerAddress( size_t i ) const
{
    return m_CallStackFrames[i].getThisAddress();
}

void JitDebugger::setRootBasePointer( unsigned char* ebp )
{
    m_RootEBP = ebp;
}

void JitDebugger::clear()
{
    printf("CLEAR DEBUGGER\n");
    o_assert(!m_bDebuggerStarted);
    m_BreakPoints.clear();
    m_CallStackFrames.clear();
    m_pCurrentBreakPoint = nullptr;
    m_EBP = nullptr;
    m_RootEBP = nullptr;
    m_bBroke = false;
    m_bStepIntoEnabled = false;
}

unsigned char* JitDebugger::getCallStackBasePointer( size_t i ) const
{
    return m_CallStackFrames[i].getEBP();
}

void JitDebugger::enableBreakPoints()
{
    //printf("ENABLE BREAKPOINTS\n");
    o_assert(m_iEnablingCounter > 0);
    m_iEnablingCounter--;
    if(m_iEnablingCounter == 0)
    {
        auto it = m_RememberedBreakPoints.begin();
        auto end = m_RememberedBreakPoints.end();
        for(;it!=end;++it)
        {
            (*it)->setEnabled(true);
        }
        m_RememberedBreakPoints.clear();
    }
}

void JitDebugger::disableBreakPoints()
{
    //printf("DISABLE BREAKPOINTS\n");
    o_assert(m_iEnablingCounter >= 0);
    if(m_iEnablingCounter == 0)
    {
        o_assert(m_RememberedBreakPoints.empty());
        auto it = m_BreakPoints.begin();
        auto end = m_BreakPoints.end();
        for(;it!=end;++it)
        {
            BreakPoint* a_pBreakPoint = it->second;
            if(a_pBreakPoint->isEnabled())
            {
                a_pBreakPoint->setEnabled(false);
                m_RememberedBreakPoints.push_back(a_pBreakPoint);
            }
        }
    }
    m_iEnablingCounter++;
}

void JitDebugger::removeBreakPoints( BreakPoint::EFlag flag )
{
    vector<BreakPoint*> to_remove;
    for(auto it = m_BreakPoints.begin(); it != m_BreakPoints.end(); ++it)
    {
        if(it->second->isFlagSet(flag))
            to_remove.push_back(it->second);
    }
    printf("START REMOVING\n");
    for(auto it = to_remove.begin(); it != to_remove.end(); ++it)
    {
        removeBreakPoint(*it, flag);
    }
}

void JitDebugger::collectDebuggableNativeSubroutines()
{
    o_assert(m_DebuggableSubroutines.empty());
    vector<LanguageElement*> subRoutines;
    phantom::elementsByClass(classOf<Subroutine>(), subRoutines, phantom::rootNamespace());
    m_DebuggableSubroutines.reserve(subRoutines.size());
    for(size_t i = 0; i<subRoutines.size(); ++i)
    {
        Subroutine* pSubroutine = static_cast<Subroutine*>(subRoutines[i]);
        if(pSubroutine->getInstructionCount())
        {
            registerSubroutine(pSubroutine);
        }
    }
}

void JitDebugger::startDebuggingSubroutines()
{
    for(auto it = m_DebuggableSubroutines.begin(); it != m_DebuggableSubroutines.end(); ++it)
    {
        Subroutine* pSubroutine = *it;
        if(isSubroutineReadyForDebug(pSubroutine))
        {
            // add step into break point
            addBreakPoint(pSubroutine->getInstruction(0), BreakPoint::e_Flag_StepInto);
        }
    }
}

void JitDebugger::endDebuggingSubroutines()
{
    for(auto it = m_DebuggableSubroutines.begin(); it != m_DebuggableSubroutines.end(); ++it)
    {
        Subroutine* pSubroutine = *it;
        if(isSubroutineReadyForDebug(pSubroutine))
        {
            // add step into break point
            removeBreakPoint((BreakPoint*)pSubroutine->getInstruction(0)->getUserData(), BreakPoint::e_Flag_StepInto);
        }
    }
}

Instruction* JitDebugger::findInstructionStartingAtMemoryAddress( byte* a_pAddress )
{
    for(auto it = m_DebuggableSubroutines.begin(); it != m_DebuggableSubroutines.end(); ++it)
    {
        Subroutine* pSubroutine = *it;
        if(pSubroutine->containsMemoryAddress(a_pAddress))
        {
            return pSubroutine->findInstructionStartingAtMemoryAddress(a_pAddress);
        }
    }
    return nullptr;
}

Instruction* JitDebugger::findInstructionAtMemoryAddress( byte* a_pAddress )
{
    for(auto it = m_DebuggableSubroutines.begin(); it != m_DebuggableSubroutines.end(); ++it)
    {
        Subroutine* pSubroutine = *it;
        if(pSubroutine->containsMemoryAddress(a_pAddress))
        {
            printf("SUB ROUTINE %s FOUND AT %x\n", pSubroutine->getName().c_str(), a_pAddress);
            return pSubroutine->findInstructionStartingAtMemoryAddress(a_pAddress);
        }
    }
    return nullptr;
}

Instruction* JitDebugger::findInstructionAtCodePosition(const CodePosition& a_Position) const 
{
    for(auto it = m_DebuggableSubroutines.begin(); it != m_DebuggableSubroutines.end(); ++it)
    {
        Subroutine* pSubroutine = *it;
        if(pSubroutine->containsCodePosition(a_Position))
        {
            Instruction* pFoundInstruction = pSubroutine->findInstructionAtCodePosition(a_Position);
            if(pFoundInstruction == nullptr)
            {
                size_t count = pSubroutine->getInstructionCount();
                Instruction* pClosestInstruction = nullptr;
                CodePosition closestStartPos;
                for(size_t i = 0; i<count; ++i)
                {
                    Instruction* pInstruction = pSubroutine->getInstruction(i);
                    CodePosition startPos = pInstruction->getCodeLocation().getStart();
                    if((a_Position < startPos  OR startPos == a_Position)
                        AND (pClosestInstruction == nullptr 
                            OR startPos < closestStartPos))
                    {
                        pClosestInstruction = pInstruction;
                        closestStartPos = startPos;
                    }
                }
                pFoundInstruction = pClosestInstruction;
            }
            if(pFoundInstruction)
            {
                return pFoundInstruction;
            }
        }
    }
    return nullptr;
}

void JitDebugger::subroutineCreated( void* a_pSubroutine )
{
    registerSubroutine(as<Subroutine*>(a_pSubroutine));
}

void JitDebugger::subroutineDestroyed( void* a_pSubroutine )
{
    unregisterSubroutine(as<Subroutine*>(a_pSubroutine));
}

void JitDebugger::registerSubroutine( Subroutine* a_pSubroutine )
{
    if(m_bDebuggerStarted)
    {
        if(isSubroutineReadyForDebug(a_pSubroutine))
        {
            addBreakPoint(a_pSubroutine->getInstruction(0), BreakPoint::e_Flag_StepInto);
        }
        else 
        {
            m_DebuggableSubroutinesNotReady.push_back(a_pSubroutine);
        }
    }
    m_DebuggableSubroutines.push_back(a_pSubroutine);
}

void JitDebugger::unregisterSubroutine( Subroutine* a_pSubroutine )
{
    if(m_bDebuggerStarted)
    {
        auto found = std::find(m_DebuggableSubroutinesNotReady.begin()
            , m_DebuggableSubroutinesNotReady.end()
            , a_pSubroutine);
        if(found != m_DebuggableSubroutinesNotReady.end())
        {
            m_DebuggableSubroutinesNotReady.erase(found);
        }
        /*for(size_t i = 0; i < a_pSubroutine->getInstructionCount(); ++i)
        {
            BreakPoint* pBreakPoint = (BreakPoint*)a_pSubroutine->getInstruction(i)->getUserData();
            if(pBreakPoint)
            {
                printf("CLEAR BREAKPOINT ON SUBROUTINE DELETION\n");
                removeBreakPoint(pBreakPoint, BreakPoint::e_Flag_StepInto);
                removeBreakPoint(pBreakPoint, BreakPoint::e_Flag_User);
                removeBreakPoint(pBreakPoint, BreakPoint::e_Flag_StepOver);
                removeBreakPoint(pBreakPoint, BreakPoint::e_Flag_Restorer);
            }
        }*/
    }
    m_DebuggableSubroutines.erase(std::find(m_DebuggableSubroutines.begin(), m_DebuggableSubroutines.end(), a_pSubroutine));
}

void JitDebugger::updateDebugger()
{
    vector<Subroutine*> stillWithoutInstructions;
    for(auto it = m_DebuggableSubroutinesNotReady.begin(); it != m_DebuggableSubroutinesNotReady.end(); ++it)
    {
        Subroutine* pSubroutine = *it;
        if(isSubroutineReadyForDebug(pSubroutine))
        {
            m_DebuggableSubroutines.push_back(pSubroutine);
            addBreakPoint(pSubroutine->getInstruction(0), BreakPoint::e_Flag_StepInto);
        }
        else 
        {
            stillWithoutInstructions.push_back(pSubroutine);
        }
    }
    m_DebuggableSubroutinesNotReady = stillWithoutInstructions;
}



o_namespace_end(phantom, reflection, jit)
