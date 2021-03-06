
#include "NativeVTableIndexInspector.h"

#define NativeVTableIndexInspector_vtableentry(_index_) \
    &NativeVTableIndexInspector::NativeVTableIndexInspector_hackmethod_##_index_

int        NativeVTableIndexInspector::sm_inspection_result = -1;
void*    NativeVTableIndexInspector::sm_vptr_impostor = &NativeVTableIndexInspector::sm_vtable_impostor;

NativeVTableIndexInspector::vptr_imspostor_t 
        NativeVTableIndexInspector::sm_vtable_impostor = {

    NativeVTableIndexInspector_vtableentry(0)     ,
    NativeVTableIndexInspector_vtableentry(1)    ,
    NativeVTableIndexInspector_vtableentry(2)    ,
    NativeVTableIndexInspector_vtableentry(3)    ,
    NativeVTableIndexInspector_vtableentry(4)    ,
    NativeVTableIndexInspector_vtableentry(5)    ,
    NativeVTableIndexInspector_vtableentry(6)    ,
    NativeVTableIndexInspector_vtableentry(7)    ,
    NativeVTableIndexInspector_vtableentry(8)    ,
    NativeVTableIndexInspector_vtableentry(9)    ,
    NativeVTableIndexInspector_vtableentry(10)    ,
    NativeVTableIndexInspector_vtableentry(11)    ,
    NativeVTableIndexInspector_vtableentry(12)    ,
    NativeVTableIndexInspector_vtableentry(13)    ,
    NativeVTableIndexInspector_vtableentry(14)    ,
    NativeVTableIndexInspector_vtableentry(15)    ,
    NativeVTableIndexInspector_vtableentry(16)    ,
    NativeVTableIndexInspector_vtableentry(17)    ,
    NativeVTableIndexInspector_vtableentry(18)    ,
    NativeVTableIndexInspector_vtableentry(19)    ,
    NativeVTableIndexInspector_vtableentry(20)    ,
    NativeVTableIndexInspector_vtableentry(21)    ,
    NativeVTableIndexInspector_vtableentry(22)    ,
    NativeVTableIndexInspector_vtableentry(23)    ,
    NativeVTableIndexInspector_vtableentry(24)    ,
    NativeVTableIndexInspector_vtableentry(25)    ,
    NativeVTableIndexInspector_vtableentry(26)    ,
    NativeVTableIndexInspector_vtableentry(27)    ,
    NativeVTableIndexInspector_vtableentry(28)    ,
    NativeVTableIndexInspector_vtableentry(29)    ,
    NativeVTableIndexInspector_vtableentry(30)    ,
    NativeVTableIndexInspector_vtableentry(31)    ,
    NativeVTableIndexInspector_vtableentry(32)    ,
    NativeVTableIndexInspector_vtableentry(33)    ,
    NativeVTableIndexInspector_vtableentry(34)    ,
    NativeVTableIndexInspector_vtableentry(35)    ,
    NativeVTableIndexInspector_vtableentry(36)    ,
    NativeVTableIndexInspector_vtableentry(37)    ,
    NativeVTableIndexInspector_vtableentry(38)    ,
    NativeVTableIndexInspector_vtableentry(39)    ,
    NativeVTableIndexInspector_vtableentry(40)    ,
    NativeVTableIndexInspector_vtableentry(41)    ,
    NativeVTableIndexInspector_vtableentry(42)    ,
    NativeVTableIndexInspector_vtableentry(43)    ,
    NativeVTableIndexInspector_vtableentry(44)    ,
    NativeVTableIndexInspector_vtableentry(45)    ,
    NativeVTableIndexInspector_vtableentry(46)    ,
    NativeVTableIndexInspector_vtableentry(47)    ,
    NativeVTableIndexInspector_vtableentry(48)    ,
    NativeVTableIndexInspector_vtableentry(49)    ,
    NativeVTableIndexInspector_vtableentry(50)    ,
    NativeVTableIndexInspector_vtableentry(51)    ,
    NativeVTableIndexInspector_vtableentry(52)    ,
    NativeVTableIndexInspector_vtableentry(53)    ,
    NativeVTableIndexInspector_vtableentry(54)    ,
    NativeVTableIndexInspector_vtableentry(55)    ,
    NativeVTableIndexInspector_vtableentry(56)    ,
    NativeVTableIndexInspector_vtableentry(57)    ,
    NativeVTableIndexInspector_vtableentry(58)    ,
    NativeVTableIndexInspector_vtableentry(59)    ,
    NativeVTableIndexInspector_vtableentry(60)    ,
    NativeVTableIndexInspector_vtableentry(61)    ,
    NativeVTableIndexInspector_vtableentry(62)    ,
    NativeVTableIndexInspector_vtableentry(63)    ,
    NativeVTableIndexInspector_vtableentry(64)    ,
    NativeVTableIndexInspector_vtableentry(65)    ,
    NativeVTableIndexInspector_vtableentry(66)    ,
    NativeVTableIndexInspector_vtableentry(67)    ,
    NativeVTableIndexInspector_vtableentry(68)    ,
    NativeVTableIndexInspector_vtableentry(69)    ,
    NativeVTableIndexInspector_vtableentry(70)    ,
    NativeVTableIndexInspector_vtableentry(71)    ,
    NativeVTableIndexInspector_vtableentry(72)    ,
    NativeVTableIndexInspector_vtableentry(73)    ,
    NativeVTableIndexInspector_vtableentry(74)    ,
    NativeVTableIndexInspector_vtableentry(75)    ,
    NativeVTableIndexInspector_vtableentry(76)    ,
    NativeVTableIndexInspector_vtableentry(77)    ,
    NativeVTableIndexInspector_vtableentry(78)    ,
    NativeVTableIndexInspector_vtableentry(79)    ,
    NativeVTableIndexInspector_vtableentry(80)    ,
    NativeVTableIndexInspector_vtableentry(81)    ,
    NativeVTableIndexInspector_vtableentry(82)    ,
    NativeVTableIndexInspector_vtableentry(83)    ,
    NativeVTableIndexInspector_vtableentry(84)    ,
    NativeVTableIndexInspector_vtableentry(85)    ,
    NativeVTableIndexInspector_vtableentry(86)    ,
    NativeVTableIndexInspector_vtableentry(87)    ,
    NativeVTableIndexInspector_vtableentry(88)    ,
    NativeVTableIndexInspector_vtableentry(89)    ,
    NativeVTableIndexInspector_vtableentry(90)    ,
    NativeVTableIndexInspector_vtableentry(91)    ,
    NativeVTableIndexInspector_vtableentry(92)    ,
    NativeVTableIndexInspector_vtableentry(93)    ,
    NativeVTableIndexInspector_vtableentry(94)    ,
    NativeVTableIndexInspector_vtableentry(95)    ,
    NativeVTableIndexInspector_vtableentry(96)    ,
    NativeVTableIndexInspector_vtableentry(97)    ,
    NativeVTableIndexInspector_vtableentry(98)    ,
    NativeVTableIndexInspector_vtableentry(99)

};

#undef NativeVTableIndexInspector_vtableentry