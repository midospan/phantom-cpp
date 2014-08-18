#ifndef o_JitSubroutine_h__
#define o_JitSubroutine_h__


/* ****************** Includes ******************* */
#include <phantom/jit.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection, jit), JitSubroutine);
/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)


class o_jit_export JitSubroutine : public Extension
{
    friend class JitClass;

    JitSubroutine(Subroutine* a_pSubroutine, EJitAbi a_eAbi);
    ~JitSubroutine(void);

    void startCompilation();
    void abortCompilation();
    void endCompilation();

    Subroutine* getSubroutine() const {return static_cast<Subroutine*>(m_pElement); }

    Signature* getSignature() const { return getSubroutine()->getSignature(); }
    
    void reset();

    /*int get_opcode (jit_insn insn)
    jit_value get_dest (jit_insn insn)
    jit_value get_value1 (jit_insn insn)
    jit_value get_value2 (jit_insn insn)
    jit_label get_label (jit_insn insn)
    jit_function_t get_function (jit_insn insn)
    void * get_native (jit_insn insn)
    const char * get_name (jit_insn insn)
    Type* get_signature (jit_insn insn)
    int dest_is_value (jit_insn insn)*/
    int label (jit_label *l);
    int new_block ();

    jit_value   load (jit_value value);
    jit_value   dup (jit_value value);
    jit_value   loadSmall (jit_value value);
    int         store (jit_value dest, jit_value value);
    jit_value   loadRelative (jit_value value, int offset, Type* type);
    int         storeRelative (jit_value dest, int offset, jit_value value);
    jit_value   addRelative (jit_value value, int offset);
    jit_value   loadElem (jit_value base_addr, jit_value index, Type* elem_type);
    jit_value   loadElemAddress (jit_value base_addr, jit_value index, Type* elem_type);
    int         storeElem (jit_value base_addr, jit_value index, jit_value value);
    int         checkNull (jit_value value);
    jit_value   add (jit_value value1, jit_value value2);
    jit_value   addOVF (jit_value value1, jit_value value2);
    jit_value   sub (jit_value value1, jit_value value2);
    jit_value   subOVF (jit_value value1, jit_value value2);
    jit_value   mul (jit_value value1, jit_value value2);
    jit_value   mulOVF (jit_value value1, jit_value value2);
    jit_value   div (jit_value value1, jit_value value2);
    jit_value   rem (jit_value value1, jit_value value2);
    jit_value   remIEEE (jit_value value1, jit_value value2);
    jit_value   neg (jit_value value1);
    jit_value   and BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1, jit_value value2);
    jit_value   or BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1, jit_value value2);
    jit_value   xor (jit_value value1, jit_value value2);
    jit_value   not (jit_value value1);
    jit_value   shl (jit_value value1, jit_value value2);
    jit_value   shr (jit_value value1, jit_value value2);
    jit_value   ushr (jit_value value1, jit_value value2);
    jit_value   sshr (jit_value value1, jit_value value2);
    jit_value   eq (jit_value value1, jit_value value2);
    jit_value   ne (jit_value value1, jit_value value2);
    jit_value   lt (jit_value value1, jit_value value2);
    jit_value   le (jit_value value1, jit_value value2);
    jit_value   gt (jit_value value1, jit_value value2);
    jit_value   ge (jit_value value1, jit_value value2);
    jit_value   cmpl (jit_value value1, jit_value value2);
    jit_value   cmpg (jit_value value1, jit_value value2);
    jit_value   toBool (jit_value value1);
    jit_value   toNotBool (jit_value value1);
    jit_value   acos BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   asin BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   atan BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   atan2 BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1, jit_value value2);
    jit_value   cos BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   cosh BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   exp BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   log BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   log10 BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   pow BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1, jit_value value2);
    jit_value   sin BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   sinh BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   sqrt BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   tan BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   tanh BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   ceil BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   floor BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   rint BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   round BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   trunc BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   isNAN (jit_value value1);
    jit_value   isFinite (jit_value value1);
    jit_value   isInf (jit_value value1);
    jit_value   abs BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    jit_value   min BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1, jit_value value2);
    jit_value   max BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1, jit_value value2);
    jit_value   sign BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value value1);
    int         branch (jit_label *label);
    int         branchIf (jit_value value, jit_label *label);
    int         branchIfNot (jit_value value, jit_label *label);
    int         jumpTable (jit_value value, jit_label *labels, uint num_labels);
    jit_value   addressOf (jit_value value1);
    jit_value   referenceOf (jit_value value1);
    jit_value   addressOfLabel (jit_label *label);
    jit_value   implicitCast(jit_value value, Type* dest );
    jit_value   cast(jit_value value, Type* dest );
    jit_value   convert(jit_value value, Type* dest);
    jit_value   callSubroutine (Subroutine* a_pSubroutine, jit_value *args, uint a_uiArgCount, int flags);
    void        callSignal (Signal* a_pSignal, jit_value *args, uint a_uiArgCount, int flags);
    jit_value   callIndirect (jit_value value, Signature* signature, jit_value *args, uint a_uiArgCount, int flags);
    jit_value   callIndirectVtable (jit_value value, Signature* signature, jit_value *args, uint a_uiArgCount, int flags);
    jit_value   callNative (const char *name, void *native_func, EJitAbi abi, Signature* signature, jit_value* args, uint a_uiArgCount, int exception_return, int flags);
    jit_value   callIntrinsic (const char *name, void *intrinsic_func, const void* descriptor, jit_value arg1, jit_value arg2);
    jit_value   callIntrinsic( const string& a_strInstrinsicName, jit_value* a_pValues, size_t a_uiValueCount );
    jit_value   callIntrinsic( const string& a_strInstrinsicName, jit_value v0 ); 
    jit_value   callIntrinsic( const string& a_strInstrinsicName, jit_value v0, jit_value v1 );
    jit_value   callIntrinsic( const string& a_strInstrinsicName, jit_value v0, jit_value v1, jit_value v2 );
    jit_value   callIntrinsic( const string& a_strInstrinsicName, jit_value v0, jit_value v1, jit_value v2, jit_value v3 );
    int         incomingReg (jit_value value, int reg);
    int         incomingFramePosn (jit_value value, int frame_offset);
    int         outgoingReg (jit_value value, int reg);
    int         outgoingFramePosn (jit_value value, int frame_offset);
    int         returnReg (jit_value value, int reg);
    int         setupForNested (int nested_level, int reg);
    int         flushStruct (jit_value value);
    jit_value   import (jit_value value);
    int         push (jit_value value);
    int         pushPtr (jit_value value, Type* type);
    int         setParam (jit_value value, int offset);
    int         setParamPtr (jit_value value, Type* type, int offset);
    int         pushReturnAreaPtr ();
    int         popStack (int num_items);
    int         deferPopStack (int num_items);
    int         flushDeferPop (int num_items);
    int         returnValue (jit_value value);
    int         returnPtr (jit_value value, Type* type);
    int         defaultReturn ();
    int         throwValue(jit_value value);
    jit_value   getCallStack ();
    jit_value   thrownException ();
    int         usesCatcher ();
    jit_value   startCatcher ();
    int         branchIfPCNotInRange (jit_label start_label, jit_label end_label, jit_label *label);
    int         rethrowUnhandled ();
    int         startFinally (jit_label *finally_label);
    int         returnFromFinally ();
    int         callFinally (jit_label *finally_label);
    jit_value   startFilter (jit_label *label, Type* type);
    int         returnFromFilter (jit_value value);
    jit_value   callFilter (jit_label *label, jit_value value, Type* type);
    int         memcpy BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value dest, jit_value src, jit_value size);
    int         memmove BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value dest, jit_value src, jit_value size);
    int         memset BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value dest, jit_value value, jit_value size);
    jit_value   alloca BOOST_PREVENT_MACRO_SUBSTITUTION (jit_value size);
    int         moveBlocksToEnd (jit_label from_label, jit_label to_label);
    int         moveBlocksToStart (jit_label from_label, jit_label to_label);
    int         markOffset (int offset);

    void        ref(jit_value value);

    jit_value   getStructPointer () const;
    jit_value   createValue (Type* type);
    jit_value   createCharConstant (char const_value);
    jit_value   createUCharConstant (uchar const_value);
    jit_value   createShortConstant (short const_value);
    jit_value   createUShortConstant (ushort const_value);
    jit_value   createIntConstant (int const_value);
    jit_value   createUIntConstant (uint const_value);
    jit_value   createSizeTConstant (size_t const_value);
    jit_value   createVoidPtrConstant (void* const_value);
    jit_value   createLongLongConstant (longlong const_value);
    jit_value   createFloatConstant (float const_value);
    jit_value   createDoubleConstant (double const_value);
    jit_value   createConstant (const jit_constant *const_value);
    jit_value   getParameter (uint param) const;
    jit_value   getThis() const ;

    EJitAbi     getAbi() const { return m_eAbi; }

    void compileDebugPrint( const char* to_print );

    /*void        iterInit (jit_insn_iter_t*iter, jit_block block);
    void        iterInitLast (jit_insn_iter_t*iter, jit_block block);
    jit_insn    iterNext (jit_insn_iter_t*iter);
    jit_insn    iterPrevious (jit_insn_iter_t *iter);*/

    void pushCodeLocation(const CodeLocation& codeLocation);
    void popCodeLocation();

    bool isCompiled() const;

    jit_context getContext() const;
    jit_function getJitFunction() const { return m_jit_function; }
    virtual jit_function getJitCallFunction() const { return m_jit_function; }

    static void instructionCompilationCallback( void* insn, byte* start, byte* end );
    static void compilationSuccessCallback(void* func);
    
    string convertIntrinsicName(const string& a_strInstrinsicName);

protected:
    virtual void setClosures();

protected:
    Subroutine* m_pSubroutine;
    phantom::vector<CodeLocation> sm_CodeLocationStack;
    jit_function  m_jit_function;
    jit_context   m_jit_context;
    EJitAbi       m_eAbi;
};

o_namespace_end(phantom, reflection, jit)

#endif
