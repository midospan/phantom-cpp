/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include <windows.h>
/* *********************************************** */
o_namespace_begin(phantom, qt)

static size_t g_NameMetaDataIndex = eInvalidMetaDataIndex;
static size_t g_IconMetaDataIndex = eInvalidMetaDataIndex;
static bool g_MetaDataIndexAccessed = false;

o_qt_export void setNameMetaDataIndex( size_t index )
{
    o_assert(!g_MetaDataIndexAccessed);
    g_NameMetaDataIndex = index;
}

o_qt_export void setIconMetaDataIndex( size_t index )
{
    o_assert(!g_MetaDataIndexAccessed);
    g_IconMetaDataIndex = index;
}

o_qt_export size_t getNameMetaDataIndex()
{
    g_MetaDataIndexAccessed = true;
    return g_NameMetaDataIndex;
}

o_qt_export size_t getIconMetaDataIndex()
{
    g_MetaDataIndexAccessed = true;
    return g_IconMetaDataIndex;
}

o_namespace_end(phantom, qt)

o_module("qt");