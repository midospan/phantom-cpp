/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/MemberFunctionPointerAdjustmentExpression.h>
#include <phantom/reflection/MemberFunctionPointerAdjustmentExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), MemberFunctionPointerAdjustmentExpression);

o_namespace_begin(phantom, reflection) 

MemberFunctionPointerAdjustmentExpression::MemberFunctionPointerAdjustmentExpression( MemberFunctionPointerType* a_pOutputPointerType, Expression* a_pPointerExpression, ptrdiff_t a_iOffset ) 
    : Expression(a_pOutputPointerType)
    , m_pPointerExpression(a_pPointerExpression)
    , m_iOffset(a_iOffset)
{
    o_assert(m_iOffset != 0, "adjustment is not identity and offset must have non zero value");
    if(m_pPointerExpression == nullptr)
    {
        setInvalid();
    }
}

MemberFunctionPointerAdjustmentExpression::~MemberFunctionPointerAdjustmentExpression()
{
    
}

void MemberFunctionPointerAdjustmentExpression::internalEval( void* a_pDest ) const
{
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO /// /vmg + /vmv must be defined
    struct __MicrosoftUnknownMFP{
        void* m_func_address; // 64 bits for Itanium.
        ptrdiff_t m_delta;
        int m_vtordisp;
        int m_vtable_index; // or 0 if no virtual inheritance
    };
    __MicrosoftUnknownMFP input;
    m_pPointerExpression->load(&input);
    __MicrosoftUnknownMFP& output = *(__MicrosoftUnknownMFP*)a_pDest; 
    output.m_func_address = input.m_func_address;
    output.m_delta = input.m_delta + m_iOffset;
    output.m_delta = input.m_vtordisp;
    output.m_delta = input.m_vtable_index;
    o_assert(input.m_vtable_index == 0, "phantom does not support virtual inheritance");


    //         if (vindex=0) adjustedthis = this + delta
    //         else adjustedthis = this + delta + vtordisp + *(*(this + vtordisp) + vindex)
    //         CALL funcadr
#elif o_COMPILER == o_COMPILER_GCC || o_COMPILER == o_COMPILER_CLANG
    // GNU g++ uses a tricky space optimisation, also adopted by IBM's VisualAge and XLC.
    struct __GnuClangMFP {
        union {
            void* m_func_address_even; // always even
            ptrdiff_t m_vtable_index_odd; //  = vindex*2+1, always odd
        };
        ptrdiff_t m_delta;
    };
    //         adjustedthis = this + delta
    //             if (funcadr & 1) CALL (* ( *delta + (vindex+1)/2) + 4)
    //             else CALL funcadr
    __GnuClangMFP input;
    m_pPointerExpression->load(&input);
    __GnuClangMFP& output = *(__GnuClangMFP*)a_pDest; 
    output.m_vtable_index_odd = input.m_vtable_index_odd;
    output.m_delta = input.m_delta + m_iOffset;
#else
#   error define Member Function Pointer struct for the current compiler
#endif
}

MemberFunctionPointerAdjustmentExpression* MemberFunctionPointerAdjustmentExpression::clone() const
{
    return o_new(MemberFunctionPointerAdjustmentExpression)(static_cast<MemberFunctionPointerType*>(m_pValueType), m_pPointerExpression, m_iOffset);
}

o_namespace_end(phantom, reflection)
