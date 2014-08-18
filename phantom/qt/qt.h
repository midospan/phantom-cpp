#ifndef o_qt_h__
#define o_qt_h__

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

o_qt_export string  nameOf(reflection::LanguageElement* a_pLanguageElement);
o_qt_export string  iconOf(reflection::LanguageElement* a_pLanguageElement);

o_qt_export reflection::Expression* expressionByName(const string& a_strName, phantom::reflection::LanguageElement* a_pScope = reinterpret_cast<phantom::reflection::LanguageElement*>(rootNamespace()));

o_qt_export void loadMetaData( const string& metaDataFile );

enum EEvalPolicy
{
    e_EvalPolicy_Local = 0x1,
    e_EvalPolicy_Children = 0x2,
    e_EvalPolicy_Descendants = 0x4 | e_EvalPolicy_Children,
    e_EvalPolicy_Parent = 0x8,
    e_EvalPolicy_Ancestors = 0x10 | e_EvalPolicy_Parent,
    e_EvalPolicy_All = e_EvalPolicy_Local | e_EvalPolicy_Descendants | e_EvalPolicy_Ancestors | 0x20,
    e_EvalPolicy_Rebuild = 0x40 | e_EvalPolicy_Local | e_EvalPolicy_Descendants,
};

o_declare_flags(EEvalPolicies, EEvalPolicy);

o_namespace_end(phantom, qt)
#endif // qt_h__