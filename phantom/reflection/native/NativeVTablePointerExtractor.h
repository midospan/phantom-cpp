/*
    This file is part of PHANTOM
         P reprocessed
         H igh-level
         A llocator
         N ested state-machines and
         T emplate
         O riented
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

#ifndef o_phantom_reflection_native_NativeVTablePointerExtractor_h__
#define o_phantom_reflection_native_NativeVTablePointerExtractor_h__

/* ****************** Includes ******************* */
/* ************* t_Class Declarations ************** */
/* *********************************************** */

#include <phantom/def_export.h>

o_namespace_begin(phantom, reflection, native)

template<typename t_CtorSignature>
struct NativeVTablePointerExtractor
{
    static void** apply() { return nullptr; }
};

union asm_leak_union_hack
{
    void (*ptr)();
    void* hacked;
};

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO 

#if o_ARCHITECTURE == o_ARCHITECTURE_X86

byte* extract_asm_jmp_address_at(byte* address)
{
    byte* baseAddress = address;
    byte op = *address++;
    switch((int)op)
    {
    case 0xE9: // jmp rel 32bit
        return baseAddress+5+*(size_t*)address;
    case 0xE8: // jmp rel 16bit
        return baseAddress+5+*(size_t*)address;
    case 0xEA: // jmp far
        return *(byte**)address;
    case 0xff:
        return *(byte**)address;
    default:
        assert(false);
    }
    return 0;
}

inline void** extract_vtable_pointer_from_asm(void* codeAddress)
{
    size_t thunkOffset = *(size_t*)((byte*)codeAddress+1);
    byte* realPtr = (byte*)codeAddress+thunkOffset+5;
    byte* ctorCallInstruction = realPtr+7;
    //byte* ctorFuncForwardAddress = extract_asm_jmp_address_at(ctorCallInstruction);
    byte* ctorFuncAddress = extract_asm_jmp_address_at(ctorCallInstruction);
    byte* vtableValueAddress = ctorFuncAddress+0x14;
    return *(void***)vtableValueAddress;
}

#else // o_ARCHITECTURE

/// TODO : define same code but for x64
inline void** extract_vtable_pointer_from_asm(void* codeAddress) { return nullptr; }

#endif

template<typename t_Ty>
struct NativeVTablePointerExtractor<t_Ty()>
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value && !boost::is_abstract<t_Ty>::value, "t_Ty must be polymorphic");
    static o_noinline void asmLeak()
    {
        struct Dummy : public t_Ty { o_noinline Dummy() { }  }; // will call base constructor but can still have default argument setup in asm
        struct Dummy2 : public Dummy { o_noinline Dummy2() { }  }; // => create a second derivation to be sure fakeNew has always the same code for any class
        Dummy2 a;
    }
    static void** apply()
    {
        asm_leak_union_hack u;
        u.ptr = &NativeVTablePointerExtractor<t_Ty()>::asmLeak;
        return extract_vtable_pointer_from_asm(u.hacked);
    }
};

template<typename t_Ty
    , typename t_0
>
struct NativeVTablePointerExtractor<t_Ty(t_0)>
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value && !boost::is_abstract<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static o_noinline void asmLeak()
    {
        struct Dummy : public t_Ty { o_noinline Dummy() : t_Ty(*t0()) { }  }; // will call base constructor but can still have default argument setup in asm
        struct Dummy2 : public Dummy { o_noinline Dummy2() { }  }; // => create a second derivation to be sure fakeNew has always the same code for any class
        Dummy2 a;
    }
    static void** apply()
    {
        asm_leak_union_hack u;
        u.ptr = &NativeVTablePointerExtractor<t_Ty(t_0)>::asmLeak;
        return extract_vtable_pointer_from_asm(u.hacked);
    }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
>
struct NativeVTablePointerExtractor<t_Ty(t_0, t_1)>
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value && !boost::is_abstract<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static o_noinline void asmLeak()
    {
        struct Dummy : public t_Ty { o_noinline Dummy() : t_Ty(*t0(), *t1()) { }  }; // will call base constructor but can still have default argument setup in asm
        struct Dummy2 : public Dummy { o_noinline Dummy2() { }  }; // => create a second derivation to be sure fakeNew has always the same code for any class
        Dummy2 a;
    }
    static void** apply()
    {
        asm_leak_union_hack u;
        u.ptr = &NativeVTablePointerExtractor<t_Ty(t_0, t_1)>::asmLeak;
        return extract_vtable_pointer_from_asm(u.hacked);
    }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
>
struct NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2)>
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value && !boost::is_abstract<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static o_noinline void asmLeak()
    {
        struct Dummy : public t_Ty { o_noinline Dummy() : t_Ty(*t0(), *t1(), *t2()) { }  }; // will call base constructor but can still have default argument setup in asm
        struct Dummy2 : public Dummy { o_noinline Dummy2() { }  }; // => create a second derivation to be sure fakeNew has always the same code for any class
        Dummy2 a;
    }
    static void** apply()
    {
        asm_leak_union_hack u;
        u.ptr = &NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2)>::asmLeak;
        return extract_vtable_pointer_from_asm(u.hacked);
    }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
>
struct NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3)>
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value && !boost::is_abstract<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static o_noinline void asmLeak()
    {
        struct Dummy : public t_Ty { o_noinline Dummy() : t_Ty(*t0(), *t1(), *t2(), *t3()) { }  }; // will call base constructor but can still have default argument setup in asm
        struct Dummy2 : public Dummy { o_noinline Dummy2() { }  }; // => create a second derivation to be sure fakeNew has always the same code for any class
        Dummy2 a;
    }
    static void** apply()
    {
        asm_leak_union_hack u;
        u.ptr = &NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3)>::asmLeak;
        return extract_vtable_pointer_from_asm(u.hacked);
    }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
>
struct NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4)>
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value && !boost::is_abstract<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    static o_noinline void asmLeak()
    {
        struct Dummy : public t_Ty { o_noinline Dummy() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4()) { }  }; // will call base constructor but can still have default argument setup in asm
        struct Dummy2 : public Dummy { o_noinline Dummy2() { }  }; // => create a second derivation to be sure fakeNew has always the same code for any class
        Dummy2 a;
    }
    static void** apply()
    {
        asm_leak_union_hack u;
        u.ptr = &NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4)>::asmLeak;
        return extract_vtable_pointer_from_asm(u.hacked);
    }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
    , typename t_5
>
struct NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5)>
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value && !boost::is_abstract<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_5>::type>::type t_5nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    static t_5nocvr* t5() { static t_5nocvr* dummy; return dummy; }
    static o_noinline void asmLeak()
    {
        struct Dummy : public t_Ty { o_noinline Dummy() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4(), *t5()) { }  }; // will call base constructor but can still have default argument setup in asm
        struct Dummy2 : public Dummy { o_noinline Dummy2() { }  }; // => create a second derivation to be sure fakeNew has always the same code for any class
        Dummy2 a;
    }
    static void** apply()
    {
        asm_leak_union_hack u;
        u.ptr = &NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5)>::asmLeak;
        return extract_vtable_pointer_from_asm(u.hacked);
    }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
    , typename t_5
    , typename t_6
>
struct NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6)>
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value && !boost::is_abstract<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_5>::type>::type t_5nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_6>::type>::type t_6nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    static t_5nocvr* t5() { static t_5nocvr* dummy; return dummy; }
    static t_6nocvr* t6() { static t_6nocvr* dummy; return dummy; }
    static o_noinline void asmLeak()
    {
        struct Dummy : public t_Ty { o_noinline Dummy() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4(), *t5(), *t6()) { }  }; // will call base constructor but can still have default argument setup in asm
        struct Dummy2 : public Dummy { o_noinline Dummy2() { }  }; // => create a second derivation to be sure fakeNew has always the same code for any class
        Dummy2 a;
    }
    static void** apply()
    {
        asm_leak_union_hack u;
        u.ptr = &NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6)>::asmLeak;
        return extract_vtable_pointer_from_asm(u.hacked);
    }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
    , typename t_5
    , typename t_6
    , typename t_7
>
struct NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7)>
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value && !boost::is_abstract<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_5>::type>::type t_5nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_6>::type>::type t_6nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_7>::type>::type t_7nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    static t_5nocvr* t5() { static t_5nocvr* dummy; return dummy; }
    static t_6nocvr* t6() { static t_6nocvr* dummy; return dummy; }
    static t_7nocvr* t7() { static t_7nocvr* dummy; return dummy; }
    static o_noinline void asmLeak()
    {
        struct Dummy : public t_Ty { o_noinline Dummy() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4(), *t5(), *t6(), *t7()) { }  }; // will call base constructor but can still have default argument setup in asm
        struct Dummy2 : public Dummy { o_noinline Dummy2() { }  }; // => create a second derivation to be sure fakeNew has always the same code for any class
        Dummy2 a;
    }
    static void** apply()
    {
        asm_leak_union_hack u;
        u.ptr = &NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7)>::asmLeak;
        return extract_vtable_pointer_from_asm(u.hacked);
    }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
    , typename t_5
    , typename t_6
    , typename t_7
    , typename t_8
>
struct NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8)>
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value && !boost::is_abstract<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_5>::type>::type t_5nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_6>::type>::type t_6nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_7>::type>::type t_7nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_8>::type>::type t_8nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    static t_5nocvr* t5() { static t_5nocvr* dummy; return dummy; }
    static t_6nocvr* t6() { static t_6nocvr* dummy; return dummy; }
    static t_7nocvr* t7() { static t_7nocvr* dummy; return dummy; }
    static t_8nocvr* t8() { static t_8nocvr* dummy; return dummy; }
    static o_noinline void asmLeak()
    {
        struct Dummy : public t_Ty { o_noinline Dummy() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4(), *t5(), *t6(), *t7(), *t8()) { }  }; // will call base constructor but can still have default argument setup in asm
        struct Dummy2 : public Dummy { o_noinline Dummy2() { }  }; // => create a second derivation to be sure fakeNew has always the same code for any class
        Dummy2 a;
    }
    static void** apply()
    {
        asm_leak_union_hack u;
        u.ptr = &NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8)>::asmLeak;
        return extract_vtable_pointer_from_asm(u.hacked);
    }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
    , typename t_5
    , typename t_6
    , typename t_7
    , typename t_8
    , typename t_9>
struct NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8, t_9)>
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value && !boost::is_abstract<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_5>::type>::type t_5nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_6>::type>::type t_6nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_7>::type>::type t_7nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_8>::type>::type t_8nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_9>::type>::type t_9nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    static t_5nocvr* t5() { static t_5nocvr* dummy; return dummy; }
    static t_6nocvr* t6() { static t_6nocvr* dummy; return dummy; }
    static t_7nocvr* t7() { static t_7nocvr* dummy; return dummy; }
    static t_8nocvr* t8() { static t_8nocvr* dummy; return dummy; }
    static t_9nocvr* t9() { static t_9nocvr* dummy; return dummy; }
    static o_noinline void asmLeak()
    {
        struct Dummy : public t_Ty { o_noinline Dummy() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4(), *t5(), *t6(), *t7(), *t8(), *t9()) { }  }; // will call base constructor but can still have default argument setup in asm
        struct Dummy2 : public Dummy { o_noinline Dummy2() { }  }; // => create a second derivation to be sure fakeNew has always the same code for any class
        Dummy2 a;
    }
    static void** apply()
    {
        asm_leak_union_hack u;
        u.ptr = &NativeVTablePointerExtractor<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8, t_9)>::asmLeak;
        return extract_vtable_pointer_from_asm(u.hacked);
    }
};

#endif // #if o_COMPILER == o_COMPILER_VISUAL_STUDIO

namespace detail 
{
    template<typename t_Ty, bool t_is_default_constructible_and_not_abstract>
    struct vtable_extractor_helper_default_constructible
    {
        static void** apply(const void*) { return NativeVTablePointerExtractor<t_Ty()>::apply(); }
    };

    template<typename t_Ty>
    struct vtable_extractor_helper_default_constructible<t_Ty, false>
    {
        static void** apply(const Class* a_pClass) 
        {
            auto it = a_pClass->beginConstructors();
            if(it != a_pClass->endConstructors())
                return (*it)->getNativeVTablePointer();
            o_warning(false, "No constructor declared in reflection of %s, cannot extract vtable information", a_pClass->getQualifiedDecoratedName().c_str());
            return nullptr;
        }
    };

    template<typename t_Ty, bool t_is_polymorphic>
    struct vtable_extractor_helper : public vtable_extractor_helper_default_constructible<t_Ty, std::is_default_constructible<t_Ty>::value AND !boost::is_abstract<t_Ty>::value>
    {

    };

    template<typename t_Ty>
    struct vtable_extractor_helper<t_Ty, false>
    {
        static void** apply(const void*) { return 0; }
    };
};

template<typename t_Ty>
struct vtable_extractor : detail::vtable_extractor_helper<t_Ty, boost::is_polymorphic<t_Ty>::value>
{
    
};

o_namespace_end(phantom, reflection, native)

#endif
