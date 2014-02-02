#ifndef o_phantom_jit_h__
#define o_phantom_jit_h__

#include <phantom/phantom.h>

#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(JIT_STATIC_LIB)
#    ifdef _PHANTOM_JIT
#        define o_jit_export __declspec(dllexport)
#    else
#       if defined( __MINGW32__ )
#           define o_jit_export
#       else
#            define o_jit_export __declspec(dllimport)
#       endif
#    endif
#else
#    define o_jit_export
#endif    // #if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_STATIC_LIB)


#include "phantom/def_jit.h"

#endif
