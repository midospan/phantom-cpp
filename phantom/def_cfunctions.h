/* TODO LICENCE HERE */

#ifndef o_phantom_cfunctions_h__
#define o_phantom_cfunctions_h__



// COMPILER SPECIFIC C FUNCTIONS

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO    // VISUAL STUDIO C functions
#   if defined(_UNICODE)
#       define o_auto_sprintf                swprintf
#       define o_auto_vsprintf                vswprintf
#       define o_auto_strcmp                    wcscmp
#       define o_auto_strlen                    wcslen
#   else
#       define o_auto_sprintf                sprintf
#       define o_auto_vsprintf                vsprintf
#       define o_auto_strcmp                    strcmp
#       define o_auto_strlen                    strlen
#   endif

#   define o_itoa(value,buf,size,radix) _itoa_s(value,buf,size,radix)
#   define o_secured_sprintf            sprintf_s

#elif (o_COMPILER == o_COMPILER_GCC) || (o_COMPILER == o_COMPILER_CLANG)   // GCC C functions
#   if defined(_UNICODE)
#       error wide string printf version not defined for GCC ... 
#       define o_auto_sprintf                    swprintf
#       define o_auto_vsprintf                    vswprintf
#       define o_auto_strcmp                        wcscmp
#       define o_auto_strlen                        wcslen
#   else
#       define o_auto_sprintf                sprintf
#       define o_auto_vsprintf                vsprintf
#       define o_auto_strcmp                    strcmp
#       define o_auto_strlen                    strlen
#   endif

#   define o_secured_sprintf            snprintf

#   define o_itoa(value,buf,size,radix) itoa(value,buf,radix)


#endif



#endif // _cfunctions_h__
