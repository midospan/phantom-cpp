#if !defined(Q_MOC_RUN)
#include "phantom/qt/qt.h"
#endif


#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_QT_JIT_STATIC_LIB)
#    ifdef PHANTOM_QT_JIT_DLL
#        define o_qt_jit_export __declspec(dllexport)
#    else
#       if defined( __MINGW32__ )
#           define o_qt_jit_export
#       else
#            define o_qt_jit_export __declspec(dllimport)
#       endif
#    endif
#else
#    define o_qt_jit_export
#endif    // #if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_STATIC_LIB)
