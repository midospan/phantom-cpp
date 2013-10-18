
#include "phantom/phantom.h"

#define NativeVTableInspector_vtableentry(_index_) \
    &NativeVTableInspector::NativeVTableInspector_hackmethod_##_index_

o_namespace_begin(phantom, reflection, native)

int        NativeVTableInspector::sm_inspection_result = -1;
void*    NativeVTableInspector::sm_vptr_impostor = &NativeVTableInspector::sm_vtable_impostor;

NativeVTableInspector::vptr_imspostor_t 
        NativeVTableInspector::sm_vtable_impostor = {

    NativeVTableInspector_vtableentry(0)     ,
    NativeVTableInspector_vtableentry(1)    ,
    NativeVTableInspector_vtableentry(2)    ,
    NativeVTableInspector_vtableentry(3)    ,
    NativeVTableInspector_vtableentry(4)    ,
    NativeVTableInspector_vtableentry(5)    ,
    NativeVTableInspector_vtableentry(6)    ,
    NativeVTableInspector_vtableentry(7)    ,
    NativeVTableInspector_vtableentry(8)    ,
    NativeVTableInspector_vtableentry(9)    ,
    NativeVTableInspector_vtableentry(10)    ,
    NativeVTableInspector_vtableentry(11)    ,
    NativeVTableInspector_vtableentry(12)    ,
    NativeVTableInspector_vtableentry(13)    ,
    NativeVTableInspector_vtableentry(14)    ,
    NativeVTableInspector_vtableentry(15)    ,
    NativeVTableInspector_vtableentry(16)    ,
    NativeVTableInspector_vtableentry(17)    ,
    NativeVTableInspector_vtableentry(18)    ,
    NativeVTableInspector_vtableentry(19)    ,
    NativeVTableInspector_vtableentry(20)    ,
    NativeVTableInspector_vtableentry(21)    ,
    NativeVTableInspector_vtableentry(22)    ,
    NativeVTableInspector_vtableentry(23)    ,
    NativeVTableInspector_vtableentry(24)    ,
    NativeVTableInspector_vtableentry(25)    ,
    NativeVTableInspector_vtableentry(26)    ,
    NativeVTableInspector_vtableentry(27)    ,
    NativeVTableInspector_vtableentry(28)    ,
    NativeVTableInspector_vtableentry(29)    ,
    NativeVTableInspector_vtableentry(30)    ,
    NativeVTableInspector_vtableentry(31)    ,
    NativeVTableInspector_vtableentry(32)    ,
    NativeVTableInspector_vtableentry(33)    ,
    NativeVTableInspector_vtableentry(34)    ,
    NativeVTableInspector_vtableentry(35)    ,
    NativeVTableInspector_vtableentry(36)    ,
    NativeVTableInspector_vtableentry(37)    ,
    NativeVTableInspector_vtableentry(38)    ,
    NativeVTableInspector_vtableentry(39)    ,
    NativeVTableInspector_vtableentry(40)    ,
    NativeVTableInspector_vtableentry(41)    ,
    NativeVTableInspector_vtableentry(42)    ,
    NativeVTableInspector_vtableentry(43)    ,
    NativeVTableInspector_vtableentry(44)    ,
    NativeVTableInspector_vtableentry(45)    ,
    NativeVTableInspector_vtableentry(46)    ,
    NativeVTableInspector_vtableentry(47)    ,
    NativeVTableInspector_vtableentry(48)    ,
    NativeVTableInspector_vtableentry(49)    ,
    NativeVTableInspector_vtableentry(50)    ,
    NativeVTableInspector_vtableentry(51)    ,
    NativeVTableInspector_vtableentry(52)    ,
    NativeVTableInspector_vtableentry(53)    ,
    NativeVTableInspector_vtableentry(54)    ,
    NativeVTableInspector_vtableentry(55)    ,
    NativeVTableInspector_vtableentry(56)    ,
    NativeVTableInspector_vtableentry(57)    ,
    NativeVTableInspector_vtableentry(58)    ,
    NativeVTableInspector_vtableentry(59)    ,
    NativeVTableInspector_vtableentry(60)    ,
    NativeVTableInspector_vtableentry(61)    ,
    NativeVTableInspector_vtableentry(62)    ,
    NativeVTableInspector_vtableentry(63)    ,
    NativeVTableInspector_vtableentry(64)    ,
    NativeVTableInspector_vtableentry(65)    ,
    NativeVTableInspector_vtableentry(66)    ,
    NativeVTableInspector_vtableentry(67)    ,
    NativeVTableInspector_vtableentry(68)    ,
    NativeVTableInspector_vtableentry(69)    ,
    NativeVTableInspector_vtableentry(70)    ,
    NativeVTableInspector_vtableentry(71)    ,
    NativeVTableInspector_vtableentry(72)    ,
    NativeVTableInspector_vtableentry(73)    ,
    NativeVTableInspector_vtableentry(74)    ,
    NativeVTableInspector_vtableentry(75)    ,
    NativeVTableInspector_vtableentry(76)    ,
    NativeVTableInspector_vtableentry(77)    ,
    NativeVTableInspector_vtableentry(78)    ,
    NativeVTableInspector_vtableentry(79)    ,
    NativeVTableInspector_vtableentry(80)    ,
    NativeVTableInspector_vtableentry(81)    ,
    NativeVTableInspector_vtableentry(82)    ,
    NativeVTableInspector_vtableentry(83)    ,
    NativeVTableInspector_vtableentry(84)    ,
    NativeVTableInspector_vtableentry(85)    ,
    NativeVTableInspector_vtableentry(86)    ,
    NativeVTableInspector_vtableentry(87)    ,
    NativeVTableInspector_vtableentry(88)    ,
    NativeVTableInspector_vtableentry(89)    ,
    NativeVTableInspector_vtableentry(90)    ,
    NativeVTableInspector_vtableentry(91)    ,
    NativeVTableInspector_vtableentry(92)    ,
    NativeVTableInspector_vtableentry(93)    ,
    NativeVTableInspector_vtableentry(94)    ,
    NativeVTableInspector_vtableentry(95)    ,
    NativeVTableInspector_vtableentry(96)    ,
    NativeVTableInspector_vtableentry(97)    ,
    NativeVTableInspector_vtableentry(98)    ,
    NativeVTableInspector_vtableentry(99)

};

o_namespace_end(phantom, reflection, native)

#undef NativeVTableInspector_vtableentry