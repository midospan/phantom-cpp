/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include <windows.h>
#include <boost/property_tree_custom/xml_parser.hpp>
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

o_qt_export string nameOf( reflection::LanguageElement* a_pLanguageElement )
{
    const string& name = a_pLanguageElement->getMetaDataValue(getNameMetaDataIndex());
    return name.empty() ? a_pLanguageElement->getName() : name;
}

o_qt_export string iconOf( reflection::LanguageElement* a_pLanguageElement )
{
    const string& name = a_pLanguageElement->getMetaDataValue(getIconMetaDataIndex());
    return name;
}

o_qt_export void loadMetaData( const string& metaDataFile )
{
    property_tree   propertyTree;
    boost::property_tree_custom::read_xml(metaDataFile.c_str(), propertyTree);
    boost::optional<property_tree&> root_opt = propertyTree.get_child_optional("metadata");
    if(root_opt.is_initialized())
    {
        property_tree& root = *root_opt;
        boost::optional<property_tree&> definition_opt = root.get_child_optional("definition");
        if(definition_opt.is_initialized())
        {
            property_tree& definition = *definition_opt;
            property_tree::const_iterator it = definition.begin();
            property_tree::const_iterator end = definition.end();
            for(;it!=end;++it)
            {
                const string& elementName = it->first;
                phantom::reflection::LanguageElement* pElement = phantom::elementByName(elementName);
                if(pElement == NULL) continue;
                property_tree::const_iterator it2 = it->second.begin();
                property_tree::const_iterator end2 = it->second.end();
                for(;it2!=end2;++it2)
                {
                    size_t metaDataIndex = phantom::metaDataIndex(it2->first);
                    if(metaDataIndex == 0xffffffff) continue;
                    const string& value = it2->second.get_value<string>();
                    pElement->setMetaDataValue(metaDataIndex, value)  ;
                }
            }
        }
    }
}

o_namespace_end(phantom, qt)

o_module("qt");