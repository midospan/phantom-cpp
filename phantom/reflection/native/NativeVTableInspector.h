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

#ifndef o_phantom_reflection_native_NativeVTableInspector_h__
#define o_phantom_reflection_native_NativeVTableInspector_h__

/* ****************** Includes ******************* */
/* ************* t_Class Declarations ************** */
/* *********************************************** */

#include <phantom/def_export.h>


#define NativeVTableInspector_hack_member_function(_index_) \
    size_t NativeVTableInspector_hack_member_function_##_index_() { sm_ResultIndex = _index_; return 0; }


o_namespace_begin(phantom, reflection, native)

class o_export NativeVTableInspector
{
public:
    typedef size_t (NativeVTableInspector::*member_function_pointer)();
    static size_t sm_ResultIndex;

public:
    NativeVTableInspector_hack_member_function(0)
    NativeVTableInspector_hack_member_function(1)
    NativeVTableInspector_hack_member_function(2)
    NativeVTableInspector_hack_member_function(3)
    NativeVTableInspector_hack_member_function(4)
    NativeVTableInspector_hack_member_function(5)
    NativeVTableInspector_hack_member_function(6)
    NativeVTableInspector_hack_member_function(7)
    NativeVTableInspector_hack_member_function(8)
    NativeVTableInspector_hack_member_function(9)
    NativeVTableInspector_hack_member_function(10)
    NativeVTableInspector_hack_member_function(11)
    NativeVTableInspector_hack_member_function(12)
    NativeVTableInspector_hack_member_function(13)
    NativeVTableInspector_hack_member_function(14)
    NativeVTableInspector_hack_member_function(15)
    NativeVTableInspector_hack_member_function(16)
    NativeVTableInspector_hack_member_function(17)
    NativeVTableInspector_hack_member_function(18)
    NativeVTableInspector_hack_member_function(19)
    NativeVTableInspector_hack_member_function(20)
    NativeVTableInspector_hack_member_function(21)
    NativeVTableInspector_hack_member_function(22)
    NativeVTableInspector_hack_member_function(23)
    NativeVTableInspector_hack_member_function(24)
    NativeVTableInspector_hack_member_function(25)
    NativeVTableInspector_hack_member_function(26)
    NativeVTableInspector_hack_member_function(27)
    NativeVTableInspector_hack_member_function(28)
    NativeVTableInspector_hack_member_function(29)
    NativeVTableInspector_hack_member_function(30)
    NativeVTableInspector_hack_member_function(31)
    NativeVTableInspector_hack_member_function(32)
    NativeVTableInspector_hack_member_function(33)
    NativeVTableInspector_hack_member_function(34)
    NativeVTableInspector_hack_member_function(35)
    NativeVTableInspector_hack_member_function(36)
    NativeVTableInspector_hack_member_function(37)
    NativeVTableInspector_hack_member_function(38)
    NativeVTableInspector_hack_member_function(39)
    NativeVTableInspector_hack_member_function(40)
    NativeVTableInspector_hack_member_function(41)
    NativeVTableInspector_hack_member_function(42)
    NativeVTableInspector_hack_member_function(43)
    NativeVTableInspector_hack_member_function(44)
    NativeVTableInspector_hack_member_function(45)
    NativeVTableInspector_hack_member_function(46)
    NativeVTableInspector_hack_member_function(47)
    NativeVTableInspector_hack_member_function(48)
    NativeVTableInspector_hack_member_function(49)
    NativeVTableInspector_hack_member_function(50)
    NativeVTableInspector_hack_member_function(51)
    NativeVTableInspector_hack_member_function(52)
    NativeVTableInspector_hack_member_function(53)
    NativeVTableInspector_hack_member_function(54)
    NativeVTableInspector_hack_member_function(55)
    NativeVTableInspector_hack_member_function(56)
    NativeVTableInspector_hack_member_function(57)
    NativeVTableInspector_hack_member_function(58)
    NativeVTableInspector_hack_member_function(59)
    NativeVTableInspector_hack_member_function(60)
    NativeVTableInspector_hack_member_function(61)
    NativeVTableInspector_hack_member_function(62)
    NativeVTableInspector_hack_member_function(63)
    NativeVTableInspector_hack_member_function(64)
    NativeVTableInspector_hack_member_function(65)
    NativeVTableInspector_hack_member_function(66)
    NativeVTableInspector_hack_member_function(67)
    NativeVTableInspector_hack_member_function(68)
    NativeVTableInspector_hack_member_function(69)
    NativeVTableInspector_hack_member_function(70)
    NativeVTableInspector_hack_member_function(71)
    NativeVTableInspector_hack_member_function(72)
    NativeVTableInspector_hack_member_function(73)
    NativeVTableInspector_hack_member_function(74)
    NativeVTableInspector_hack_member_function(75)
    NativeVTableInspector_hack_member_function(76)
    NativeVTableInspector_hack_member_function(77)
    NativeVTableInspector_hack_member_function(78)
    NativeVTableInspector_hack_member_function(79)
    NativeVTableInspector_hack_member_function(80)
    NativeVTableInspector_hack_member_function(81)
    NativeVTableInspector_hack_member_function(82)
    NativeVTableInspector_hack_member_function(83)
    NativeVTableInspector_hack_member_function(84)
    NativeVTableInspector_hack_member_function(85)
    NativeVTableInspector_hack_member_function(86)
    NativeVTableInspector_hack_member_function(87)
    NativeVTableInspector_hack_member_function(88)
    NativeVTableInspector_hack_member_function(89)
    NativeVTableInspector_hack_member_function(90)
    NativeVTableInspector_hack_member_function(91)
    NativeVTableInspector_hack_member_function(92)
    NativeVTableInspector_hack_member_function(93)
    NativeVTableInspector_hack_member_function(94)
    NativeVTableInspector_hack_member_function(95)
    NativeVTableInspector_hack_member_function(96)
    NativeVTableInspector_hack_member_function(97)
    NativeVTableInspector_hack_member_function(98)
    NativeVTableInspector_hack_member_function(99)

    NativeVTableInspector_hack_member_function(100)
    NativeVTableInspector_hack_member_function(101)
    NativeVTableInspector_hack_member_function(102)
    NativeVTableInspector_hack_member_function(103)
    NativeVTableInspector_hack_member_function(104)
    NativeVTableInspector_hack_member_function(105)
    NativeVTableInspector_hack_member_function(106)
    NativeVTableInspector_hack_member_function(107)
    NativeVTableInspector_hack_member_function(108)
    NativeVTableInspector_hack_member_function(109)
    NativeVTableInspector_hack_member_function(110)
    NativeVTableInspector_hack_member_function(111)
    NativeVTableInspector_hack_member_function(112)
    NativeVTableInspector_hack_member_function(113)
    NativeVTableInspector_hack_member_function(114)
    NativeVTableInspector_hack_member_function(115)
    NativeVTableInspector_hack_member_function(116)
    NativeVTableInspector_hack_member_function(117)
    NativeVTableInspector_hack_member_function(118)
    NativeVTableInspector_hack_member_function(119)
    NativeVTableInspector_hack_member_function(120)
    NativeVTableInspector_hack_member_function(121)
    NativeVTableInspector_hack_member_function(122)
    NativeVTableInspector_hack_member_function(123)
    NativeVTableInspector_hack_member_function(124)
    NativeVTableInspector_hack_member_function(125)
    NativeVTableInspector_hack_member_function(126)
    NativeVTableInspector_hack_member_function(127)
    NativeVTableInspector_hack_member_function(128)
    NativeVTableInspector_hack_member_function(129)
    NativeVTableInspector_hack_member_function(130)
    NativeVTableInspector_hack_member_function(131)
    NativeVTableInspector_hack_member_function(132)
    NativeVTableInspector_hack_member_function(133)
    NativeVTableInspector_hack_member_function(134)
    NativeVTableInspector_hack_member_function(135)
    NativeVTableInspector_hack_member_function(136)
    NativeVTableInspector_hack_member_function(137)
    NativeVTableInspector_hack_member_function(138)
    NativeVTableInspector_hack_member_function(139)
    NativeVTableInspector_hack_member_function(140)
    NativeVTableInspector_hack_member_function(141)
    NativeVTableInspector_hack_member_function(142)
    NativeVTableInspector_hack_member_function(143)
    NativeVTableInspector_hack_member_function(144)
    NativeVTableInspector_hack_member_function(145)
    NativeVTableInspector_hack_member_function(146)
    NativeVTableInspector_hack_member_function(147)
    NativeVTableInspector_hack_member_function(148)
    NativeVTableInspector_hack_member_function(149)
    NativeVTableInspector_hack_member_function(150)
    NativeVTableInspector_hack_member_function(151)
    NativeVTableInspector_hack_member_function(152)
    NativeVTableInspector_hack_member_function(153)
    NativeVTableInspector_hack_member_function(154)
    NativeVTableInspector_hack_member_function(155)
    NativeVTableInspector_hack_member_function(156)
    NativeVTableInspector_hack_member_function(157)
    NativeVTableInspector_hack_member_function(158)
    NativeVTableInspector_hack_member_function(159)
    NativeVTableInspector_hack_member_function(160)
    NativeVTableInspector_hack_member_function(161)
    NativeVTableInspector_hack_member_function(162)
    NativeVTableInspector_hack_member_function(163)
    NativeVTableInspector_hack_member_function(164)
    NativeVTableInspector_hack_member_function(165)
    NativeVTableInspector_hack_member_function(166)
    NativeVTableInspector_hack_member_function(167)
    NativeVTableInspector_hack_member_function(168)
    NativeVTableInspector_hack_member_function(169)
    NativeVTableInspector_hack_member_function(170)
    NativeVTableInspector_hack_member_function(171)
    NativeVTableInspector_hack_member_function(172)
    NativeVTableInspector_hack_member_function(173)
    NativeVTableInspector_hack_member_function(174)
    NativeVTableInspector_hack_member_function(175)
    NativeVTableInspector_hack_member_function(176)
    NativeVTableInspector_hack_member_function(177)
    NativeVTableInspector_hack_member_function(178)
    NativeVTableInspector_hack_member_function(179)
    NativeVTableInspector_hack_member_function(180)
    NativeVTableInspector_hack_member_function(181)
    NativeVTableInspector_hack_member_function(182)
    NativeVTableInspector_hack_member_function(183)
    NativeVTableInspector_hack_member_function(184)
    NativeVTableInspector_hack_member_function(185)
    NativeVTableInspector_hack_member_function(186)
    NativeVTableInspector_hack_member_function(187)
    NativeVTableInspector_hack_member_function(188)
    NativeVTableInspector_hack_member_function(189)
    NativeVTableInspector_hack_member_function(190)
    NativeVTableInspector_hack_member_function(191)
    NativeVTableInspector_hack_member_function(192)
    NativeVTableInspector_hack_member_function(193)
    NativeVTableInspector_hack_member_function(194)
    NativeVTableInspector_hack_member_function(195)
    NativeVTableInspector_hack_member_function(196)
    NativeVTableInspector_hack_member_function(197)
    NativeVTableInspector_hack_member_function(198)
    NativeVTableInspector_hack_member_function(199)

    NativeVTableInspector_hack_member_function(200)
    NativeVTableInspector_hack_member_function(201)
    NativeVTableInspector_hack_member_function(202)
    NativeVTableInspector_hack_member_function(203)
    NativeVTableInspector_hack_member_function(204)
    NativeVTableInspector_hack_member_function(205)
    NativeVTableInspector_hack_member_function(206)
    NativeVTableInspector_hack_member_function(207)
    NativeVTableInspector_hack_member_function(208)
    NativeVTableInspector_hack_member_function(209)
    NativeVTableInspector_hack_member_function(210)
    NativeVTableInspector_hack_member_function(211)
    NativeVTableInspector_hack_member_function(212)
    NativeVTableInspector_hack_member_function(213)
    NativeVTableInspector_hack_member_function(214)
    NativeVTableInspector_hack_member_function(215)
    NativeVTableInspector_hack_member_function(216)
    NativeVTableInspector_hack_member_function(217)
    NativeVTableInspector_hack_member_function(218)
    NativeVTableInspector_hack_member_function(219)
    NativeVTableInspector_hack_member_function(220)
    NativeVTableInspector_hack_member_function(221)
    NativeVTableInspector_hack_member_function(222)
    NativeVTableInspector_hack_member_function(223)
    NativeVTableInspector_hack_member_function(224)
    NativeVTableInspector_hack_member_function(225)
    NativeVTableInspector_hack_member_function(226)
    NativeVTableInspector_hack_member_function(227)
    NativeVTableInspector_hack_member_function(228)
    NativeVTableInspector_hack_member_function(229)
    NativeVTableInspector_hack_member_function(230)
    NativeVTableInspector_hack_member_function(231)
    NativeVTableInspector_hack_member_function(232)
    NativeVTableInspector_hack_member_function(233)
    NativeVTableInspector_hack_member_function(234)
    NativeVTableInspector_hack_member_function(235)
    NativeVTableInspector_hack_member_function(236)
    NativeVTableInspector_hack_member_function(237)
    NativeVTableInspector_hack_member_function(238)
    NativeVTableInspector_hack_member_function(239)
    NativeVTableInspector_hack_member_function(240)
    NativeVTableInspector_hack_member_function(241)
    NativeVTableInspector_hack_member_function(242)
    NativeVTableInspector_hack_member_function(243)
    NativeVTableInspector_hack_member_function(244)
    NativeVTableInspector_hack_member_function(245)
    NativeVTableInspector_hack_member_function(246)
    NativeVTableInspector_hack_member_function(247)
    NativeVTableInspector_hack_member_function(248)
    NativeVTableInspector_hack_member_function(249)
    NativeVTableInspector_hack_member_function(250)
    NativeVTableInspector_hack_member_function(251)
    NativeVTableInspector_hack_member_function(252)
    NativeVTableInspector_hack_member_function(253)
    NativeVTableInspector_hack_member_function(254)
    NativeVTableInspector_hack_member_function(255)
    NativeVTableInspector_hack_member_function(256)
    NativeVTableInspector_hack_member_function(257)
    NativeVTableInspector_hack_member_function(258)
    NativeVTableInspector_hack_member_function(259)
    NativeVTableInspector_hack_member_function(260)
    NativeVTableInspector_hack_member_function(261)
    NativeVTableInspector_hack_member_function(262)
    NativeVTableInspector_hack_member_function(263)
    NativeVTableInspector_hack_member_function(264)
    NativeVTableInspector_hack_member_function(265)
    NativeVTableInspector_hack_member_function(266)
    NativeVTableInspector_hack_member_function(267)
    NativeVTableInspector_hack_member_function(268)
    NativeVTableInspector_hack_member_function(269)
    NativeVTableInspector_hack_member_function(270)
    NativeVTableInspector_hack_member_function(271)
    NativeVTableInspector_hack_member_function(272)
    NativeVTableInspector_hack_member_function(273)
    NativeVTableInspector_hack_member_function(274)
    NativeVTableInspector_hack_member_function(275)
    NativeVTableInspector_hack_member_function(276)
    NativeVTableInspector_hack_member_function(277)
    NativeVTableInspector_hack_member_function(278)
    NativeVTableInspector_hack_member_function(279)
    NativeVTableInspector_hack_member_function(280)
    NativeVTableInspector_hack_member_function(281)
    NativeVTableInspector_hack_member_function(282)
    NativeVTableInspector_hack_member_function(283)
    NativeVTableInspector_hack_member_function(284)
    NativeVTableInspector_hack_member_function(285)
    NativeVTableInspector_hack_member_function(286)
    NativeVTableInspector_hack_member_function(287)
    NativeVTableInspector_hack_member_function(288)
    NativeVTableInspector_hack_member_function(289)
    NativeVTableInspector_hack_member_function(290)
    NativeVTableInspector_hack_member_function(291)
    NativeVTableInspector_hack_member_function(292)
    NativeVTableInspector_hack_member_function(293)
    NativeVTableInspector_hack_member_function(294)
    NativeVTableInspector_hack_member_function(295)
    NativeVTableInspector_hack_member_function(296)
    NativeVTableInspector_hack_member_function(297)
    NativeVTableInspector_hack_member_function(298)
    NativeVTableInspector_hack_member_function(299)

    NativeVTableInspector_hack_member_function(300)
    NativeVTableInspector_hack_member_function(301)
    NativeVTableInspector_hack_member_function(302)
    NativeVTableInspector_hack_member_function(303)
    NativeVTableInspector_hack_member_function(304)
    NativeVTableInspector_hack_member_function(305)
    NativeVTableInspector_hack_member_function(306)
    NativeVTableInspector_hack_member_function(307)
    NativeVTableInspector_hack_member_function(308)
    NativeVTableInspector_hack_member_function(309)
    NativeVTableInspector_hack_member_function(310)
    NativeVTableInspector_hack_member_function(311)
    NativeVTableInspector_hack_member_function(312)
    NativeVTableInspector_hack_member_function(313)
    NativeVTableInspector_hack_member_function(314)
    NativeVTableInspector_hack_member_function(315)
    NativeVTableInspector_hack_member_function(316)
    NativeVTableInspector_hack_member_function(317)
    NativeVTableInspector_hack_member_function(318)
    NativeVTableInspector_hack_member_function(319)
    NativeVTableInspector_hack_member_function(320)
    NativeVTableInspector_hack_member_function(321)
    NativeVTableInspector_hack_member_function(322)
    NativeVTableInspector_hack_member_function(323)
    NativeVTableInspector_hack_member_function(324)
    NativeVTableInspector_hack_member_function(325)
    NativeVTableInspector_hack_member_function(326)
    NativeVTableInspector_hack_member_function(327)
    NativeVTableInspector_hack_member_function(328)
    NativeVTableInspector_hack_member_function(329)
    NativeVTableInspector_hack_member_function(330)
    NativeVTableInspector_hack_member_function(331)
    NativeVTableInspector_hack_member_function(332)
    NativeVTableInspector_hack_member_function(333)
    NativeVTableInspector_hack_member_function(334)
    NativeVTableInspector_hack_member_function(335)
    NativeVTableInspector_hack_member_function(336)
    NativeVTableInspector_hack_member_function(337)
    NativeVTableInspector_hack_member_function(338)
    NativeVTableInspector_hack_member_function(339)
    NativeVTableInspector_hack_member_function(340)
    NativeVTableInspector_hack_member_function(341)
    NativeVTableInspector_hack_member_function(342)
    NativeVTableInspector_hack_member_function(343)
    NativeVTableInspector_hack_member_function(344)
    NativeVTableInspector_hack_member_function(345)
    NativeVTableInspector_hack_member_function(346)
    NativeVTableInspector_hack_member_function(347)
    NativeVTableInspector_hack_member_function(348)
    NativeVTableInspector_hack_member_function(349)
    NativeVTableInspector_hack_member_function(350)
    NativeVTableInspector_hack_member_function(351)
    NativeVTableInspector_hack_member_function(352)
    NativeVTableInspector_hack_member_function(353)
    NativeVTableInspector_hack_member_function(354)
    NativeVTableInspector_hack_member_function(355)
    NativeVTableInspector_hack_member_function(356)
    NativeVTableInspector_hack_member_function(357)
    NativeVTableInspector_hack_member_function(358)
    NativeVTableInspector_hack_member_function(359)
    NativeVTableInspector_hack_member_function(360)
    NativeVTableInspector_hack_member_function(361)
    NativeVTableInspector_hack_member_function(362)
    NativeVTableInspector_hack_member_function(363)
    NativeVTableInspector_hack_member_function(364)
    NativeVTableInspector_hack_member_function(365)
    NativeVTableInspector_hack_member_function(366)
    NativeVTableInspector_hack_member_function(367)
    NativeVTableInspector_hack_member_function(368)
    NativeVTableInspector_hack_member_function(369)
    NativeVTableInspector_hack_member_function(370)
    NativeVTableInspector_hack_member_function(371)
    NativeVTableInspector_hack_member_function(372)
    NativeVTableInspector_hack_member_function(373)
    NativeVTableInspector_hack_member_function(374)
    NativeVTableInspector_hack_member_function(375)
    NativeVTableInspector_hack_member_function(376)
    NativeVTableInspector_hack_member_function(377)
    NativeVTableInspector_hack_member_function(378)
    NativeVTableInspector_hack_member_function(379)
    NativeVTableInspector_hack_member_function(380)
    NativeVTableInspector_hack_member_function(381)
    NativeVTableInspector_hack_member_function(382)
    NativeVTableInspector_hack_member_function(383)
    NativeVTableInspector_hack_member_function(384)
    NativeVTableInspector_hack_member_function(385)
    NativeVTableInspector_hack_member_function(386)
    NativeVTableInspector_hack_member_function(387)
    NativeVTableInspector_hack_member_function(388)
    NativeVTableInspector_hack_member_function(389)
    NativeVTableInspector_hack_member_function(390)
    NativeVTableInspector_hack_member_function(391)
    NativeVTableInspector_hack_member_function(392)
    NativeVTableInspector_hack_member_function(393)
    NativeVTableInspector_hack_member_function(394)
    NativeVTableInspector_hack_member_function(395)
    NativeVTableInspector_hack_member_function(396)
    NativeVTableInspector_hack_member_function(397)
    NativeVTableInspector_hack_member_function(398)
    NativeVTableInspector_hack_member_function(399)

    NativeVTableInspector_hack_member_function(400)
    NativeVTableInspector_hack_member_function(401)
    NativeVTableInspector_hack_member_function(402)
    NativeVTableInspector_hack_member_function(403)
    NativeVTableInspector_hack_member_function(404)
    NativeVTableInspector_hack_member_function(405)
    NativeVTableInspector_hack_member_function(406)
    NativeVTableInspector_hack_member_function(407)
    NativeVTableInspector_hack_member_function(408)
    NativeVTableInspector_hack_member_function(409)
    NativeVTableInspector_hack_member_function(410)
    NativeVTableInspector_hack_member_function(411)
    NativeVTableInspector_hack_member_function(412)
    NativeVTableInspector_hack_member_function(413)
    NativeVTableInspector_hack_member_function(414)
    NativeVTableInspector_hack_member_function(415)
    NativeVTableInspector_hack_member_function(416)
    NativeVTableInspector_hack_member_function(417)
    NativeVTableInspector_hack_member_function(418)
    NativeVTableInspector_hack_member_function(419)
    NativeVTableInspector_hack_member_function(420)
    NativeVTableInspector_hack_member_function(421)
    NativeVTableInspector_hack_member_function(422)
    NativeVTableInspector_hack_member_function(423)
    NativeVTableInspector_hack_member_function(424)
    NativeVTableInspector_hack_member_function(425)
    NativeVTableInspector_hack_member_function(426)
    NativeVTableInspector_hack_member_function(427)
    NativeVTableInspector_hack_member_function(428)
    NativeVTableInspector_hack_member_function(429)
    NativeVTableInspector_hack_member_function(430)
    NativeVTableInspector_hack_member_function(431)
    NativeVTableInspector_hack_member_function(432)
    NativeVTableInspector_hack_member_function(433)
    NativeVTableInspector_hack_member_function(434)
    NativeVTableInspector_hack_member_function(435)
    NativeVTableInspector_hack_member_function(436)
    NativeVTableInspector_hack_member_function(437)
    NativeVTableInspector_hack_member_function(438)
    NativeVTableInspector_hack_member_function(439)
    NativeVTableInspector_hack_member_function(440)
    NativeVTableInspector_hack_member_function(441)
    NativeVTableInspector_hack_member_function(442)
    NativeVTableInspector_hack_member_function(443)
    NativeVTableInspector_hack_member_function(444)
    NativeVTableInspector_hack_member_function(445)
    NativeVTableInspector_hack_member_function(446)
    NativeVTableInspector_hack_member_function(447)
    NativeVTableInspector_hack_member_function(448)
    NativeVTableInspector_hack_member_function(449)
    NativeVTableInspector_hack_member_function(450)
    NativeVTableInspector_hack_member_function(451)
    NativeVTableInspector_hack_member_function(452)
    NativeVTableInspector_hack_member_function(453)
    NativeVTableInspector_hack_member_function(454)
    NativeVTableInspector_hack_member_function(455)
    NativeVTableInspector_hack_member_function(456)
    NativeVTableInspector_hack_member_function(457)
    NativeVTableInspector_hack_member_function(458)
    NativeVTableInspector_hack_member_function(459)
    NativeVTableInspector_hack_member_function(460)
    NativeVTableInspector_hack_member_function(461)
    NativeVTableInspector_hack_member_function(462)
    NativeVTableInspector_hack_member_function(463)
    NativeVTableInspector_hack_member_function(464)
    NativeVTableInspector_hack_member_function(465)
    NativeVTableInspector_hack_member_function(466)
    NativeVTableInspector_hack_member_function(467)
    NativeVTableInspector_hack_member_function(468)
    NativeVTableInspector_hack_member_function(469)
    NativeVTableInspector_hack_member_function(470)
    NativeVTableInspector_hack_member_function(471)
    NativeVTableInspector_hack_member_function(472)
    NativeVTableInspector_hack_member_function(473)
    NativeVTableInspector_hack_member_function(474)
    NativeVTableInspector_hack_member_function(475)
    NativeVTableInspector_hack_member_function(476)
    NativeVTableInspector_hack_member_function(477)
    NativeVTableInspector_hack_member_function(478)
    NativeVTableInspector_hack_member_function(479)
    NativeVTableInspector_hack_member_function(480)
    NativeVTableInspector_hack_member_function(481)
    NativeVTableInspector_hack_member_function(482)
    NativeVTableInspector_hack_member_function(483)
    NativeVTableInspector_hack_member_function(484)
    NativeVTableInspector_hack_member_function(485)
    NativeVTableInspector_hack_member_function(486)
    NativeVTableInspector_hack_member_function(487)
    NativeVTableInspector_hack_member_function(488)
    NativeVTableInspector_hack_member_function(489)
    NativeVTableInspector_hack_member_function(490)
    NativeVTableInspector_hack_member_function(491)
    NativeVTableInspector_hack_member_function(492)
    NativeVTableInspector_hack_member_function(493)
    NativeVTableInspector_hack_member_function(494)
    NativeVTableInspector_hack_member_function(495)
    NativeVTableInspector_hack_member_function(496)
    NativeVTableInspector_hack_member_function(497)
    NativeVTableInspector_hack_member_function(498)
    NativeVTableInspector_hack_member_function(499)

    NativeVTableInspector_hack_member_function(500)
    NativeVTableInspector_hack_member_function(501)
    NativeVTableInspector_hack_member_function(502)
    NativeVTableInspector_hack_member_function(503)
    NativeVTableInspector_hack_member_function(504)
    NativeVTableInspector_hack_member_function(505)
    NativeVTableInspector_hack_member_function(506)
    NativeVTableInspector_hack_member_function(507)
    NativeVTableInspector_hack_member_function(508)
    NativeVTableInspector_hack_member_function(509)
    NativeVTableInspector_hack_member_function(510)
    NativeVTableInspector_hack_member_function(511)
    NativeVTableInspector_hack_member_function(512)
    NativeVTableInspector_hack_member_function(513)
    NativeVTableInspector_hack_member_function(514)
    NativeVTableInspector_hack_member_function(515)
    NativeVTableInspector_hack_member_function(516)
    NativeVTableInspector_hack_member_function(517)
    NativeVTableInspector_hack_member_function(518)
    NativeVTableInspector_hack_member_function(519)
    NativeVTableInspector_hack_member_function(520)
    NativeVTableInspector_hack_member_function(521)
    NativeVTableInspector_hack_member_function(522)
    NativeVTableInspector_hack_member_function(523)
    NativeVTableInspector_hack_member_function(524)
    NativeVTableInspector_hack_member_function(525)
    NativeVTableInspector_hack_member_function(526)
    NativeVTableInspector_hack_member_function(527)
    NativeVTableInspector_hack_member_function(528)
    NativeVTableInspector_hack_member_function(529)
    NativeVTableInspector_hack_member_function(530)
    NativeVTableInspector_hack_member_function(531)
    NativeVTableInspector_hack_member_function(532)
    NativeVTableInspector_hack_member_function(533)
    NativeVTableInspector_hack_member_function(534)
    NativeVTableInspector_hack_member_function(535)
    NativeVTableInspector_hack_member_function(536)
    NativeVTableInspector_hack_member_function(537)
    NativeVTableInspector_hack_member_function(538)
    NativeVTableInspector_hack_member_function(539)
    NativeVTableInspector_hack_member_function(540)
    NativeVTableInspector_hack_member_function(541)
    NativeVTableInspector_hack_member_function(542)
    NativeVTableInspector_hack_member_function(543)
    NativeVTableInspector_hack_member_function(544)
    NativeVTableInspector_hack_member_function(545)
    NativeVTableInspector_hack_member_function(546)
    NativeVTableInspector_hack_member_function(547)
    NativeVTableInspector_hack_member_function(548)
    NativeVTableInspector_hack_member_function(549)
    NativeVTableInspector_hack_member_function(550)
    NativeVTableInspector_hack_member_function(551)
    NativeVTableInspector_hack_member_function(552)
    NativeVTableInspector_hack_member_function(553)
    NativeVTableInspector_hack_member_function(554)
    NativeVTableInspector_hack_member_function(555)
    NativeVTableInspector_hack_member_function(556)
    NativeVTableInspector_hack_member_function(557)
    NativeVTableInspector_hack_member_function(558)
    NativeVTableInspector_hack_member_function(559)
    NativeVTableInspector_hack_member_function(560)
    NativeVTableInspector_hack_member_function(561)
    NativeVTableInspector_hack_member_function(562)
    NativeVTableInspector_hack_member_function(563)
    NativeVTableInspector_hack_member_function(564)
    NativeVTableInspector_hack_member_function(565)
    NativeVTableInspector_hack_member_function(566)
    NativeVTableInspector_hack_member_function(567)
    NativeVTableInspector_hack_member_function(568)
    NativeVTableInspector_hack_member_function(569)
    NativeVTableInspector_hack_member_function(570)
    NativeVTableInspector_hack_member_function(571)
    NativeVTableInspector_hack_member_function(572)
    NativeVTableInspector_hack_member_function(573)
    NativeVTableInspector_hack_member_function(574)
    NativeVTableInspector_hack_member_function(575)
    NativeVTableInspector_hack_member_function(576)
    NativeVTableInspector_hack_member_function(577)
    NativeVTableInspector_hack_member_function(578)
    NativeVTableInspector_hack_member_function(579)
    NativeVTableInspector_hack_member_function(580)
    NativeVTableInspector_hack_member_function(581)
    NativeVTableInspector_hack_member_function(582)
    NativeVTableInspector_hack_member_function(583)
    NativeVTableInspector_hack_member_function(584)
    NativeVTableInspector_hack_member_function(585)
    NativeVTableInspector_hack_member_function(586)
    NativeVTableInspector_hack_member_function(587)
    NativeVTableInspector_hack_member_function(588)
    NativeVTableInspector_hack_member_function(589)
    NativeVTableInspector_hack_member_function(590)
    NativeVTableInspector_hack_member_function(591)
    NativeVTableInspector_hack_member_function(592)
    NativeVTableInspector_hack_member_function(593)
    NativeVTableInspector_hack_member_function(594)
    NativeVTableInspector_hack_member_function(595)
    NativeVTableInspector_hack_member_function(596)
    NativeVTableInspector_hack_member_function(597)
    NativeVTableInspector_hack_member_function(598)
    NativeVTableInspector_hack_member_function(599)

protected:


    typedef member_function_pointer     vptr_imspostor_t [600];

    static vptr_imspostor_t             sm_vtable_impostor;
    static size_t                       sm_inspection_result;
    static void*                        sm_vptr_impostor;

public:
    template<typename _FuncPtr>
    static size_t                        getIndexOf(_FuncPtr ptr)
    {
#if o_COMPILER == o_COMPILER_GCC
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
        std::cout<<u.wrap_fp.delta<<std::endl;
        return (u.wrap_fp.vtable_index-1)/sizeof(u.wrap_fp.fn);
#else
        NativeVTableInspector::member_function_pointer mp = *reinterpret_cast<NativeVTableInspector::member_function_pointer*>(&ptr);
        o_assert(sm_ResultIndex == ~size_t(0));
        (reinterpret_cast<NativeVTableInspector*>(&sm_vptr_impostor)->*mp)();
        o_assert(sm_ResultIndex != ~size_t(0));
        size_t result = sm_ResultIndex;
        sm_ResultIndex = ~size_t(0);
        return result;
#endif
    }
    
    template<typename t_Ty>
    static size_t  getDestructorIndex()
    {
        o_assert(sm_ResultIndex == ~size_t(0));
        reinterpret_cast<t_Ty*>(&sm_vptr_impostor)->~t_Ty();
        o_assert(sm_ResultIndex != ~size_t(0));
        size_t result = sm_ResultIndex;
        sm_ResultIndex = ~size_t(0);
        return result;
    }
};


o_namespace_end(phantom, reflection, native)

#undef NativeVTableInspector_hack_member_function

// Create easy access traits
namespace phantom
{
    template<typename t_Ty>
    struct vtable_count_of;
    template<typename t_Ty, int index>
    struct vtable_offset_of;
    template<typename t_Ty, int index>
    struct vtable_base_class_of;
    template<typename t_Ty, int index>
    struct vtable_top_class_of;

    namespace detail
    {

        template<typename t_Ty, int t_base_class_count>
        struct vtable_count_of_helper_cascade
        {
            enum { value =
                + vtable_count_of<o_NESTED_TYPE base_class_of<t_Ty, t_base_class_count-1>::type>::value
                + vtable_count_of_helper_cascade<t_Ty, t_base_class_count-1>::value};
        };

        template<typename t_Ty>
        struct vtable_count_of_helper_cascade<t_Ty, 0>
        {
            enum { value = 1 };
        };

        template<typename t_Ty>
        struct vtable_count_of_helper_cascade<t_Ty, 1>
        {
            enum { value = vtable_count_of<o_NESTED_TYPE base_class_of<t_Ty, 0>::type>::value };
        };

        template<typename t_Ty, bool t_is_polymorphic>
        struct vtable_count_of_helper : public vtable_count_of_helper_cascade<t_Ty, base_class_count_of<t_Ty>::value>
        {
        };

        template<typename t_Ty>
        struct vtable_count_of_helper<t_Ty, false>
        {
            enum { value = 0 };
        };

    }

    namespace detail
    {

        template<typename t_Ty, int id, int t_base_class_count, size_t offset>
        struct vtable_offset_of_cascade
        {
            const static size_t base_index = base_class_count_of<t_Ty>::value - t_base_class_count ;
            const static size_t temp_value = vtable_offset_of<o_NESTED_TYPE base_class_of<t_Ty, base_index>::type, id>::value ;
            const static size_t value =
                (temp_value == 0xffffff) // Not matching
                ? vtable_offset_of_cascade<t_Ty, id - vtable_count_of<o_NESTED_TYPE base_class_of<t_Ty, base_index>::type>::value, t_base_class_count-1, offset + sizeof(o_NESTED_TYPE base_class_of<t_Ty, base_index>::type)>::value
                : (offset + temp_value);
        };

        template<typename t_Ty, int id, size_t offset>
        struct vtable_offset_of_cascade<t_Ty, id, 0, offset>
        {
            const static size_t value = (id == 0) ? offset : 0xffffff;
        };


        template<typename t_Ty, int id, size_t offset>
        struct vtable_offset_of_cascade<t_Ty, id, 1, offset>
        {
            const static size_t base_index = base_class_count_of<t_Ty>::value - 1;
            const static size_t temp_value = vtable_offset_of<o_NESTED_TYPE base_class_of<t_Ty, base_index>::type, id>::value;
            const static size_t value = (temp_value == 0xffffff) // Not matching
                ? (size_t)0xffffff
                : (offset + temp_value);
        };

        template<typename t_Ty, int id, bool t_is_polymorphic>
        struct vtable_offset_of_helper : public vtable_offset_of_cascade<t_Ty, id, base_class_count_of<t_Ty>::value, 0>
        {

        };

        template<typename t_Ty, int id>
        struct vtable_offset_of_helper<t_Ty, id, false>
        {
            const static size_t value = 0xffffffff;
        };


        template<bool t_cond, typename t_True, typename t_False>
        struct vtable_class_type_selector
        {
            typedef t_True type;
        };

        template<typename t_True, typename t_False>
        struct vtable_class_type_selector<false, t_True, t_False>
        {
            typedef t_False type;
        };

        template<typename t_Ty, int id, int t_base_class_count>
        struct vtable_base_class_of_cascade
        {
            const static size_t base_index = base_class_count_of<t_Ty>::value - t_base_class_count ;
            typedef typename vtable_base_class_of<typename base_class_of<t_Ty, base_index>::type, id>::type temp_type;
            typedef typename vtable_class_type_selector<boost::is_void<temp_type>::value  // Not matching
                , typename vtable_base_class_of_cascade<t_Ty, id - vtable_count_of<typename base_class_of<t_Ty, base_index>::type>::value, t_base_class_count-1>::type
                , temp_type>::type type;
        };

        template<typename t_Ty, int id>
        struct vtable_base_class_of_cascade<t_Ty, id, 0>
        {
            typedef typename vtable_class_type_selector<(id == 0), t_Ty, void>::type type;
        };


        template<typename t_Ty, int id>
        struct vtable_base_class_of_cascade<t_Ty, id, 1>
        {
            const static size_t base_index = base_class_count_of<t_Ty>::value - 1;
            typedef typename vtable_base_class_of<typename base_class_of<t_Ty, base_index>::type, id>::type temp_type;
            typedef typename vtable_class_type_selector<boost::is_void<temp_type>::value // Not matching
                , void
                , temp_type>::type type;
        };

        template<typename t_Ty, int id, bool t_is_polymorphic>
        struct vtable_base_class_of_helper
            : public vtable_base_class_of_cascade<t_Ty, id, base_class_count_of<t_Ty>::value>
        {

        };

        template<typename t_Ty, int id>
        struct vtable_base_class_of_helper<t_Ty, id, false>
        {
            typedef void type;
        };

        template<typename t_Ty, int id, int t_base_class_count>
        struct vtable_top_class_of_cascade
        {
            const static size_t base_index = base_class_count_of<t_Ty>::value - t_base_class_count ;
            typedef typename vtable_top_class_of<typename base_class_of<t_Ty, base_index>::type, id>::type temp_type;
            typedef typename vtable_class_type_selector<boost::is_void<temp_type>::value  // Not matching
                , typename vtable_top_class_of_cascade<t_Ty, id - vtable_count_of<typename base_class_of<t_Ty, base_index>::type>::value, t_base_class_count-1>::type
                , temp_type>::type type;
        };

        template<typename t_Ty, int id>
        struct vtable_top_class_of_cascade<t_Ty, id, 0>
        {
            typedef typename vtable_class_type_selector<(id == 0), t_Ty, void>::type type;
        };


        template<typename t_Ty, int id>
        struct vtable_top_class_of_cascade<t_Ty, id, 1>
        {
            const static size_t base_index = base_class_count_of<t_Ty>::value - 1;
            typedef typename vtable_top_class_of<typename base_class_of<t_Ty, base_index>::type, id>::type temp_type;
            typedef typename vtable_class_type_selector<boost::is_void<temp_type>::value // Not matching
                , void
                , temp_type>::type type;
        };

        template<typename t_Ty, int id, bool t_is_polymorphic>
        struct vtable_top_class_of_helper
            : public vtable_top_class_of_cascade<t_Ty, id, base_class_count_of<t_Ty>::value>
        {

        };

        template<typename t_Ty, int id>
        struct vtable_top_class_of_helper<t_Ty, id, false>
        {
            typedef void type;
        };


        template<typename t_Ty>
        struct vtable_top_class_of_helper<t_Ty, 0, true>
        {
            typedef t_Ty type;
        };

        template<typename t_Ty, int t_vtable_count>
        struct vtable_info_extractor_cascade
        {
            const static size_t vtable_offset = vtable_offset_of<t_Ty, t_vtable_count-1>::value;
            typedef typename vtable_top_class_of<t_Ty, t_vtable_count-1>::type top_class;
            static void apply(const void* a_pInstance, vector<vtable_info>& vtables)
            {
                size_t instanceVirtualMemberFunctionCount = virtualMemberFunctionCountOf<top_class>();
                vtable_info vtable;
                vtable.count = instanceVirtualMemberFunctionCount;
                vtable.offset = vtable_offset;
                vtable.member_functions = *((void***)((byte*)a_pInstance + vtable_offset));
                vtable_info_extractor_cascade<t_Ty, t_vtable_count-1>::apply(a_pInstance, vtables);
                vtables.push_back(vtable);
            }
        };

        template<typename t_Ty>
        struct vtable_info_extractor_cascade<t_Ty, 0>
        {
            static void apply(const void* a_pInstance, vector<vtable_info>& vtables)
            {
            }
        };

        template<typename t_Ty, bool t_is_polymorphic>
        struct vtable_info_extractor_helper : public vtable_info_extractor_cascade<t_Ty, vtable_count_of<t_Ty>::value>
        {
        };

        template<typename t_Ty>
        struct vtable_info_extractor_helper<t_Ty, false>
        {
            static void apply(const void* a_pInstance, vector<vtable_info>& vtables) { o_assert("Non-polymorphic type doesn't have vtables so they cannot be copied"); }
        };

    }

    template<typename t_Ty>
    struct vtable_count_of : public detail::vtable_count_of_helper<t_Ty, boost::is_polymorphic<t_Ty>::value>
    {

    };

    template<typename t_Ty, int id>
    struct vtable_offset_of : public detail::vtable_offset_of_helper<t_Ty, id, boost::is_polymorphic<t_Ty>::value>
    {

    };

    template<typename t_Ty, int id>
    struct vtable_base_class_of : public detail::vtable_base_class_of_helper<t_Ty, id, boost::is_polymorphic<t_Ty>::value>
    {

    };
    template<typename t_Ty, int id>
    struct vtable_top_class_of : public detail::vtable_top_class_of_helper<t_Ty, id, boost::is_polymorphic<t_Ty>::value>
    {

    };

    template<typename t_Ty>
    struct vtable_info_extractor : public detail::vtable_info_extractor_helper<t_Ty, boost::is_polymorphic<t_Ty>::value>
    {

    };

    /// returns the vtable index of the given member_function or -1 if it's not a virtual member_function
    /// throw static assert if the tested argument is not a member function pointer
    template<typename t_Ty>
    size_t         virtualMemberFunctionIndexOf(t_Ty member_function)
    {
        o_static_assert_msg(boost::is_member_function_pointer<t_Ty>::value, "Given argument is not a member function pointer");
        return phantom::reflection::native::NativeVTableInspector::getIndexOf(member_function);
    }

    template<typename t_Ty, bool t_has_virtual_destructor_cascade>
    struct virtual_destructor_index_provider_helper
    {
        static size_t apply()
        {
            return phantom::reflection::native::NativeVTableInspector::getDestructorIndex<t_Ty>();
        }
    };

    template<typename t_Ty>
    struct virtual_destructor_index_provider_helper<t_Ty, false>
    {
        static size_t apply()
        {
            return ~size_t(0);
        }
    };

    template<typename t_Ty>
    struct virtual_destructor_index_provider : public virtual_destructor_index_provider_helper<t_Ty, has_virtual_destructor_cascade<t_Ty>::value>
    {
    };

    template<typename t_Ty>
    size_t          virtualDestructorIndex()
    {
        return virtual_destructor_index_provider<t_Ty>::apply();
    }
}


#endif
