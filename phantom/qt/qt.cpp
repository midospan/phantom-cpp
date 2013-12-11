/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
/* *********************************************** */
o_namespace_begin(phantom, qt)

static size_t g_NameMetaDataIndex = eInvalidMetaDataIndex;
static size_t g_IconMetaDataIndex = eInvalidMetaDataIndex;
static bool g_MetaDataIndexAccessed = false;

void setNameMetaDataIndex( size_t index )
{
    o_assert(!g_MetaDataIndexAccessed);
    g_NameMetaDataIndex = index;
}

void setIconMetaDataIndex( size_t index )
{
    o_assert(!g_MetaDataIndexAccessed);
    g_IconMetaDataIndex = index;
}

size_t getNameMetaDataIndex()
{
    g_MetaDataIndexAccessed = true;
    return g_NameMetaDataIndex;
}

size_t getIconMetaDataIndex()
{
    g_MetaDataIndexAccessed = true;
    return g_IconMetaDataIndex;
}

o_namespace_end(phantom, qt)