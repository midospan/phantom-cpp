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

#ifndef o_phantom_def_math_h__
#define o_phantom_def_math_h__

/* Definitions of useful mathematical constants
* o_math_E        - e
* o_math_Log2_e    - log2(e)
* o_math_Log10_e   - log10(e)
* o_math_Ln2      - ln(2)
* o_math_Ln10     - ln(10)
* o_math_2_Pi       - 2*pi
* o_math_Pi       - pi
* o_math_Pi_by_2     - pi/2
* o_math_Pi_by_4     - pi/4
* o_math_1_by_Pi     - 1/pi
* o_math_2_by_Pi     - 2/pi
* o_math_2_Sqrt_Pi - 2/sqrt(pi)
* o_math_Sqrt_2    - sqrt(2)
* o_math_Sqrt_1_2  - 1/sqrt(2)
*/


#if o__bool__use_double_precision_real

#define o_math_to_degree     57.295779513082320876798
#define o_math_to_radian     0.01745329251994329577
#define o_math_E            2.71828182845904523536
#define o_math_Log2_e        1.44269504088896340736
#define o_math_Log10_e        0.434294481903251827651
#define o_math_Ln2            0.693147180559945309417
#define o_math_Ln10            2.30258509299404568402
#define o_math_Pi            3.14159265358979323846
#define o_math_2_Pi            6.28318530717958647693
#define o_math_Pi_by_2        1.57079632679489661923
#define o_math_Pi_by_4        0.785398163397448309616
#define o_math_1_by_Pi        0.318309886183790671538
#define o_math_2_by_Pi        0.636619772367581343076
#define o_math_2_Sqrt_Pi    1.12837916709551257390
#define o_math_Sqrt_2        1.41421356237309504880
#define o_math_Sqrt_1_2        0.707106781186547524401
#define o_math_inv_Sqrt_2        (1/o_math_Sqrt_2)
#define o_math_real_Epsilon         DBL_EPSILON
#define o_math_real_Max             DBL_MAX
#define o_math_real_Min             DBL_MIN

#else

#define o_math_to_degree     57.295779513082320876798f
#define o_math_to_radian     0.01745329251994329577f
#define o_math_E            2.71828182845904523536f
#define o_math_Log2_e        1.44269504088896340736f
#define o_math_Log10_e        0.434294481903251827651f
#define o_math_Ln2            0.693147180559945309417f
#define o_math_Ln10            2.30258509299404568402f
#define o_math_Pi            3.14159265358979323846f
#define o_math_2_Pi            6.28318530717958647693f
#define o_math_Pi_by_2        1.57079632679489661923f
#define o_math_Pi_by_4        0.785398163397448309616f
#define o_math_1_by_Pi        0.318309886183790671538f
#define o_math_2_by_Pi        0.636619772367581343076f
#define o_math_2_Sqrt_Pi    1.12837916709551257390f
#define o_math_Sqrt_2        1.41421356237309504880f
#define o_math_Sqrt_1_2        0.707106781186547524401f
#define o_math_inv_Sqrt_2        (1/o_math_Sqrt_2)
#define o_math_real_Epsilon         FLT_EPSILON
#define o_math_real_Max             FLT_MAX
#define o_math_real_Min             FLT_MIN

#endif

#define o_math_real_1_by_Epsilon		(1/o_math_real_Epsilon)

#endif // _maths_h__