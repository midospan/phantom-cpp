#if !defined(Q_MOC_RUN)
#include "phantom/phantom.h"
#endif


#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_QT_STATIC_LIB)
#    ifdef PHANTOM_QT_DLL
#        define o_qt_export __declspec(dllexport)
#    else
#       if defined( __MINGW32__ )
#           define o_qt_export
#       else
#            define o_qt_export __declspec(dllimport)
#       endif
#    endif
#else
#    define o_qt_export
#endif    // #if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_STATIC_LIB)


o_namespace_begin(phantom, qt)

o_qt_export void setNameMetaDataIndex(size_t index);
o_qt_export void setIconMetaDataIndex(size_t index);

o_qt_export size_t getNameMetaDataIndex();
o_qt_export size_t getIconMetaDataIndex();

o_namespace_end(phantom, qt)