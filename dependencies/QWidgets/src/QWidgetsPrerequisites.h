#ifndef QBlockDiagramPrerequisites_h__
#define QBlockDiagramPrerequisites_h__


#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(QWIDGETS_STATIC_LIB)
#    ifdef QWIDGETS_DLL
#        define QWIDGETS_EXPORT __declspec(dllexport)
#    else
#       if defined( __MINGW32__ )
#           define QWIDGETS_EXPORT
#       else
#            define QWIDGETS_EXPORT __declspec(dllimport)
#       endif
#    endif
#else
#    define QWIDGETS_EXPORT
#endif

#endif // QBlockDiagramPrerequisites_h__
