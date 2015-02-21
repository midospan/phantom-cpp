/* TODO LICENCE HERE */

#ifndef o_phantom_export_h__
#define o_phantom_export_h__


/* ****************** Includes ******************* */

/* *********************************************** */

//==========================================================
// Macro for export / import
//==========================================================

#ifdef _VISUAL_ASSIST_HELPER
    #define _VISUAL_ASSIST_HELPER
    #undef    _VISUAL_ASSIST_HELPER
#endif

#ifdef _VISUAL_ASSIST_HELPER
    #define PHANTOM_STATIC_LIB
    #define PHANTOMENGINEDLL_EXPORTS
#endif

#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_STATIC_LIB)
#    ifdef PHANTOM_DLL
#        define o_export __declspec(dllexport)
#    else
#       if defined( __MINGW32__ )
#           define o_export
#       else
#            define o_export __declspec(dllimport)
#       endif
#    endif
#else
#    define o_export
#endif    // #if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_STATIC_LIB)


#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS)
#    ifdef PHANTOM_STATIC_MODULE
#        define o_export_typeInfosOf 
#    else
#        define o_export_typeInfosOf __declspec(dllexport)
#    endif
#else
#    define o_export_typeInfosOf
#endif    // #if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_STATIC_LIB)

//==========================================================
// Deactivation of warning 4251
// "T1 needs a DLL interface to be used by T2 class clients"
//==========================================================

#ifdef _MSC_VER
#   pragma warning(disable : 4251)
#endif

#endif // o_phantom_export_h__
