#ifndef o_phantom_reflection_native_NativeVTableIndexInspector_h__
#define o_phantom_reflection_native_NativeVTableIndexInspector_h__

/* ****************** Includes ******************* */
/* ************* t_Class Declarations ************** */
/* *********************************************** */
#include <cstddef>
#include <iostream>

#define NativeVTableIndexInspector_hackmethod(_index_) \
    int NativeVTableIndexInspector_hackmethod_##_index_() { return _index_; }


class NativeVTableIndexInspector
{
public:
    typedef int (NativeVTableIndexInspector::*method_pointer)();

public:
    NativeVTableIndexInspector_hackmethod(0)
    NativeVTableIndexInspector_hackmethod(1)
    NativeVTableIndexInspector_hackmethod(2)
    NativeVTableIndexInspector_hackmethod(3)
    NativeVTableIndexInspector_hackmethod(4)
    NativeVTableIndexInspector_hackmethod(5)
    NativeVTableIndexInspector_hackmethod(6)
    NativeVTableIndexInspector_hackmethod(7)
    NativeVTableIndexInspector_hackmethod(8)
    NativeVTableIndexInspector_hackmethod(9)
    NativeVTableIndexInspector_hackmethod(10)
    NativeVTableIndexInspector_hackmethod(11)
    NativeVTableIndexInspector_hackmethod(12)
    NativeVTableIndexInspector_hackmethod(13)
    NativeVTableIndexInspector_hackmethod(14)
    NativeVTableIndexInspector_hackmethod(15)
    NativeVTableIndexInspector_hackmethod(16)
    NativeVTableIndexInspector_hackmethod(17)
    NativeVTableIndexInspector_hackmethod(18)
    NativeVTableIndexInspector_hackmethod(19)
    NativeVTableIndexInspector_hackmethod(20)
    NativeVTableIndexInspector_hackmethod(21)
    NativeVTableIndexInspector_hackmethod(22)
    NativeVTableIndexInspector_hackmethod(23)
    NativeVTableIndexInspector_hackmethod(24)
    NativeVTableIndexInspector_hackmethod(25)
    NativeVTableIndexInspector_hackmethod(26)
    NativeVTableIndexInspector_hackmethod(27)
    NativeVTableIndexInspector_hackmethod(28)
    NativeVTableIndexInspector_hackmethod(29)
    NativeVTableIndexInspector_hackmethod(30)
    NativeVTableIndexInspector_hackmethod(31)
    NativeVTableIndexInspector_hackmethod(32)
    NativeVTableIndexInspector_hackmethod(33)
    NativeVTableIndexInspector_hackmethod(34)
    NativeVTableIndexInspector_hackmethod(35)
    NativeVTableIndexInspector_hackmethod(36)
    NativeVTableIndexInspector_hackmethod(37)
    NativeVTableIndexInspector_hackmethod(38)
    NativeVTableIndexInspector_hackmethod(39)
    NativeVTableIndexInspector_hackmethod(40)
    NativeVTableIndexInspector_hackmethod(41)
    NativeVTableIndexInspector_hackmethod(42)
    NativeVTableIndexInspector_hackmethod(43)
    NativeVTableIndexInspector_hackmethod(44)
    NativeVTableIndexInspector_hackmethod(45)
    NativeVTableIndexInspector_hackmethod(46)
    NativeVTableIndexInspector_hackmethod(47)
    NativeVTableIndexInspector_hackmethod(48)
    NativeVTableIndexInspector_hackmethod(49)
    NativeVTableIndexInspector_hackmethod(50)
    NativeVTableIndexInspector_hackmethod(51)
    NativeVTableIndexInspector_hackmethod(52)
    NativeVTableIndexInspector_hackmethod(53)
    NativeVTableIndexInspector_hackmethod(54)
    NativeVTableIndexInspector_hackmethod(55)
    NativeVTableIndexInspector_hackmethod(56)
    NativeVTableIndexInspector_hackmethod(57)
    NativeVTableIndexInspector_hackmethod(58)
    NativeVTableIndexInspector_hackmethod(59)
    NativeVTableIndexInspector_hackmethod(60)
    NativeVTableIndexInspector_hackmethod(61)
    NativeVTableIndexInspector_hackmethod(62)
    NativeVTableIndexInspector_hackmethod(63)
    NativeVTableIndexInspector_hackmethod(64)
    NativeVTableIndexInspector_hackmethod(65)
    NativeVTableIndexInspector_hackmethod(66)
    NativeVTableIndexInspector_hackmethod(67)
    NativeVTableIndexInspector_hackmethod(68)
    NativeVTableIndexInspector_hackmethod(69)
    NativeVTableIndexInspector_hackmethod(70)
    NativeVTableIndexInspector_hackmethod(71)
    NativeVTableIndexInspector_hackmethod(72)
    NativeVTableIndexInspector_hackmethod(73)
    NativeVTableIndexInspector_hackmethod(74)
    NativeVTableIndexInspector_hackmethod(75)
    NativeVTableIndexInspector_hackmethod(76)
    NativeVTableIndexInspector_hackmethod(77)
    NativeVTableIndexInspector_hackmethod(78)
    NativeVTableIndexInspector_hackmethod(79)
    NativeVTableIndexInspector_hackmethod(80)
    NativeVTableIndexInspector_hackmethod(81)
    NativeVTableIndexInspector_hackmethod(82)
    NativeVTableIndexInspector_hackmethod(83)
    NativeVTableIndexInspector_hackmethod(84)
    NativeVTableIndexInspector_hackmethod(85)
    NativeVTableIndexInspector_hackmethod(86)
    NativeVTableIndexInspector_hackmethod(87)
    NativeVTableIndexInspector_hackmethod(88)
    NativeVTableIndexInspector_hackmethod(89)
    NativeVTableIndexInspector_hackmethod(90)
    NativeVTableIndexInspector_hackmethod(91)
    NativeVTableIndexInspector_hackmethod(92)
    NativeVTableIndexInspector_hackmethod(93)
    NativeVTableIndexInspector_hackmethod(94)
    NativeVTableIndexInspector_hackmethod(95)
    NativeVTableIndexInspector_hackmethod(96)
    NativeVTableIndexInspector_hackmethod(97)
    NativeVTableIndexInspector_hackmethod(98)
    NativeVTableIndexInspector_hackmethod(99)

protected:


    typedef method_pointer            vptr_imspostor_t [100]; 

    static vptr_imspostor_t            sm_vtable_impostor;
    static int                        sm_inspection_result;
    static void*                    sm_vptr_impostor;

public:
    template<typename _FuncPtr, typename _Placeholder>
    static void                        replaceVTable(_FuncPtr old, _Placeholder n)
    {
        
    }
    template<typename _FuncPtr>
    static int                        getFuncPtr(_FuncPtr ptr)
    {
#if defined(__GNUC__) || defined (__clang__)
        union
        {
            struct {
                union {
                    void (*fn)();
                    ptrdiff_t vtable_index;
                };
                ptrdiff_t delta;
            } wrap_fp;
            
            _FuncPtr fp;
        } u;
        u.fp = ptr;
        //std::cout<<u.wrap_fp.delta<<std::endl;
        return (u.wrap_fp.vtable_index-1)/sizeof(u.wrap_fp.fn);
#else
        NativeVTableIndexInspector::method_pointer mp = *reinterpret_cast<NativeVTableIndexInspector::method_pointer*>(&ptr);
        return (reinterpret_cast<NativeVTableIndexInspector*>(&sm_vptr_impostor)->*mp)();
#endif
    }
    
    template<typename _FuncPtr>
    static int                        getIndexOf(_FuncPtr ptr)
    {
#if defined(__GNUC__) || defined (__clang__)
        union
        {
            struct {
                union {
                    void (*fn)();
                    ptrdiff_t vtable_index;
                };
                ptrdiff_t delta;
            } wrap_fp;

            _FuncPtr fp;
        } u;
        u.fp = ptr;
        //std::cout<<u.wrap_fp.delta<<std::endl;
        return (u.wrap_fp.vtable_index-1)/sizeof(u.wrap_fp.fn);
#else
        NativeVTableIndexInspector::method_pointer mp = *reinterpret_cast<NativeVTableIndexInspector::method_pointer*>(&ptr);
        return (reinterpret_cast<NativeVTableIndexInspector*>(&sm_vptr_impostor)->*mp)();
#endif
    }
    template<typename t_ClassPtr>
    static int                        getVirtualMethodCount()
    {
        class Hacker : public t_ClassPtr
        {
        public:
            virtual void last_virtual() { }
        };
        return getIndexOf(&Hacker::last_virtual);
    }
};

#undef NativeVTableIndexInspector_hackmethod


#endif