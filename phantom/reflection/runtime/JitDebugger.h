#ifndef o_phantom_moon_script_DebugDataBase_h__
#define o_phantom_moon_script_DebugDataBase_h__


/* ****************** Includes ******************* */
#include "phantom/def_runtime.h"
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection, runtime)

#define BREAK_INSTRUCTION_SIZE 1
#define CALL_INSTRUCTION_SIZE 5

struct BreakPoint
{
    enum EFlag
    {
        e_Flag_User = 0x1,
        e_Flag_StepOver = 0x4,
        e_Flag_StepInto = 0x8,
        e_Flag_Restorer = 0x20
    };

    enum EState 
    {
        e_State_Enabled = 0x1,
        e_State_Bypass = 0x2,
    };

    BreakPoint(Instruction* a_pInstruction)
        : m_pInstruction(a_pInstruction)
        , m_pRestoredBreakPoint(0)
        , m_iFlags(0)
        , m_iStates(0)
        , m_pHardCodedMemoryAddress(nullptr)
    {

    }
    BreakPoint()
        : m_pInstruction(0)
        , m_pRestoredBreakPoint(0)
        , m_iFlags(0)
        , m_iStates(0)
        , m_pHardCodedMemoryAddress(nullptr)
    {

    }

    inline byte* getMemoryStart() const { return m_pHardCodedMemoryAddress ? m_pHardCodedMemoryAddress : m_pInstruction->getMemoryStart(); }
    inline byte* getMemoryEnd() const { return m_pHardCodedMemoryAddress ? m_pHardCodedMemoryAddress+1 : m_pInstruction->getMemoryStart()+BREAK_INSTRUCTION_SIZE; }

    Instruction* getInstruction() const { return m_pInstruction; }

    inline byte* nextAvailableBreakPointLocation()
    {
        return (getMemoryEnd() < m_pInstruction->getMemoryEnd()) 
                    ? m_pInstruction->getMemoryEnd() 
                    : getMemoryEnd();
    }

    bool contains(byte* a_pAddress) const 
    {
        return (m_pHardCodedMemoryAddress AND m_pHardCodedMemoryAddress >= getMemoryStart() AND m_pHardCodedMemoryAddress < getMemoryEnd())
            OR m_pInstruction->containsMemoryAddress(a_pAddress);
    }

    bool contains(BreakPoint* a_pBreakPoint) const 
    {
        return contains(a_pBreakPoint->getMemoryStart());
    }

    bool operator<(const BreakPoint& other) const
    {
        return getMemoryStart() <  other.getMemoryStart() ;
    }

    void setFlag(EFlag f)
    {
        m_iFlags |= f;
    }

    void unsetFlag(EFlag f)
    {
        m_iFlags &= ~f;
    }

    bool isFlagSet(EFlag f) const { return (m_iFlags & f) == f; }

    int getFlags() const { return m_iFlags; }

    bool isEnabled() const { return (m_iStates & e_State_Enabled) != 0; }
    bool isByPassed() const { return (m_iStates & e_State_Bypass) != 0; }

    void setEnabled(bool value) ;

    void setByPass(bool value) 
    { 
        if(value)
            m_iStates |= e_State_Bypass; 
        else 
            m_iStates &= ~e_State_Bypass; 
    }

    void setFlags(int flags)
    {
        m_iFlags |= flags;
    }

    void setHardCodedMemoryAddress(byte* a_pAddress)
    {
        m_pHardCodedMemoryAddress = a_pAddress;
    }

protected:
    int             m_iFlags;
    int             m_iStates;
    Instruction*    m_pInstruction;
    byte*           m_pHardCodedMemoryAddress;
    byte            m_ReplacementCode[BREAK_INSTRUCTION_SIZE];

    BreakPoint*     m_pRestoredBreakPoint;
};

class o_runtime_export JitDebuggerMutex
{
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

class o_runtime_export JitDebugger
{
    enum ERequest
    {
        e_Request_None,
        e_Request_StepOver,
        e_Request_StepInto,
    };
public:
	JitDebugger(void);
	~JitDebugger(void);

    static JitDebugger* Instance();

    o_initialize();
    o_terminate();

    void setDebuggedThread(HANDLE h) { m_DebuggedThread = h; }

    void setMutex(JitDebuggerMutex* a_pMutex)
    {
        m_pMutex = a_pMutex;
    }

    void clear();
    
    CodePosition insertBreakPoint( const CodePosition& a_Position );
    bool removeBreakPoint(const CodePosition& a_Position);

    void resume();
    void stepOver();
    void stepInto();

    void enableMethodEntryBreakPoint(Subroutine* a_pSubroutine);

    void startDebugger();
    void updateDebugger();
    void endDebugger();

    void enableBreakPoints();
    void disableBreakPoints();

    bool isDebuggerStarted() const { return m_bDebuggerStarted; }

    CodePosition getCallStackCodePosition(size_t i) const;
    Subroutine* getCallStackSubroutine(size_t i) const;
    SourceFile* getCallStackSourceFile(size_t i) const;
    Block*      getCallStackBlock(size_t i) const;
    byte*       getCallStackBasePointer(size_t i) const;
    void*       getCallStackThisPointerAddress(size_t i) const;
    size_t      getCallStackSize() const { return m_CallStackFrames.size(); }

    bool handleSoftwareBreakPoint(void* a_pGenericContext);
    bool handleHardwareBreakPoint(void* a_pGenericContext);

    void fetchCallStack(byte* eip, byte* ebp);

    void setRootBasePointer(byte* ebp);

protected:
    o_signal_data(debuggerBroke);
    o_signal_data(debuggerResumed);

private:
    Instruction* findInstructionAtCodePosition(const CodePosition& a_Posiiton) const;
    Instruction* findInstructionAtMemoryAddress( byte* a_pAddress );
    Instruction* findInstructionStartingAtMemoryAddress( byte* a_pAddress );
    BreakPoint* findBreakPointStartingAtMemoryAddress(byte* start) ;

    void updateBreakPoints();
    
    struct FrameInfo
    {
    public:
        FrameInfo() : m_pInstruction(0), m_pEBP(0), m_pThisAddress(nullptr) {}
        FrameInfo(Instruction* ainsn
            , byte* aebp
            , void* athis_address) : m_pInstruction(ainsn), m_pEBP(aebp), m_pThisAddress(athis_address) {}

        Instruction* getInstruction() const { return m_pInstruction; }
        byte* getEBP() const { return m_pEBP; }
        void* getThisAddress() const { return m_pThisAddress; }

    protected:
        Instruction* m_pInstruction;
        byte* m_pEBP;
        void* m_pThisAddress;
    };

    BreakPoint* addBreakPoint(Instruction* a_pBreakPoint, int flags);
    BreakPoint* setOutOfScriptBreakPoint(byte* start, int flags);
    void removeBreakPoint( BreakPoint* a_pBreakPoint, BreakPoint::EFlag flag );
    bool removeBreakPoint( Instruction* a_pInstruction );
    void removeBreakPoints( BreakPoint::EFlag flags );
    BreakPoint* getBreakPoint(Instruction* a_pBreakPoint);
    void addRestorerBreakPoint(BreakPoint* restored_bp);
    Instruction* findNextInstruction(Instruction* insn, byte* ebp);
    Instruction* findInstructionJumpDestination(Instruction* a_pInstruction, byte* a_pAddress);
    bool doesBreakPointMustBeEnabled(BreakPoint* a_pBreakPoint) const;
    const vector<Instruction*>& findMethodInstructionsForLine(Method* a_pMethod, int a_uiLine);
    void cleanStepOvers();


protected:
    void collectDebuggableNativeSubroutines();
    void startDebuggingSubroutines();
    void endDebuggingSubroutines();
    void subroutineCreated(void* a_pSubroutine);
    void subroutineDestroyed(void* a_pSubroutine);
    void registerSubroutine(Subroutine* a_pSubroutine);
    void unregisterSubroutine(Subroutine* a_pSubroutine);
    LanguageElement* getSubroutineRootOwner(Subroutine* a_pSubroutine) const;
    bool isSubroutineReadyForDebug(Subroutine* a_pSubroutine) const;

private:
    void applyStepOver();
    void applyStepInto();

private:
    map<Instruction*, BreakPoint*> m_BreakPoints;
    ERequest            m_Request;
    JitDebuggerMutex*   m_pMutex;
    vector<BreakPoint*> m_RememberedBreakPoints;

    vector<Subroutine*> m_DebuggableSubroutines;
    vector<Subroutine*> m_DebuggableSubroutinesNotReady;

    // Step by step
    HANDLE          m_StepByStepBreakPointHandle;
    Subroutine*     m_StepByStepSubroutine;
    byte*           m_StepByStepEBP;
    byte*           m_StepByStepEIP;
    int             m_StepByStepLine;

    BreakPoint*        m_pCurrentBreakPoint;
    Instruction*        m_pCurrentHardwareBreakpointInstruction;
    HANDLE                  m_DebuggedThread;
    vector<FrameInfo>       m_CallStackFrames;
    int                     m_iEnablingCounter;
    byte*                   m_EBP;
    byte*                   m_RootEBP;
    void*                   m_pGenericContext;
    bool                    m_bDebuggerStarted;
    bool                    m_bBroke;
    bool                    m_bStepIntoEnabled;
};

o_namespace_end(phantom, reflection, runtime)

o_classN((phantom, reflection, runtime), JitDebugger)
{
	o_reflection
    {
        o_signal(debuggerBroke, ());
        o_signal(debuggerResumed, ());
        o_slot(void, subroutineCreated, (void*));
        o_slot(void, subroutineDestroyed, (void*));
	};
};
o_exposeN((phantom, reflection, runtime), JitDebugger);

#endif
