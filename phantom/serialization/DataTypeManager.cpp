/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "DataTypeManager.h"
/* *********************************************** */
o_registerN((phantom, serialization), DataTypeManager);

o_namespace_begin(phantom, serialization)

void    DataTypeManager::registerPlaceholderTypeByName(const string& qualifiedName, const string& placeHolderName)
{
    o_assert(getPlaceholderTypeName(qualifiedName).empty());
    o_assert(placeHolderName != qualifiedName);
    m_PlaceholderTypeByNameMap[qualifiedName] = placeHolderName;
}
void    DataTypeManager::unregisterPlaceholderTypeByName(const string& qualifiedName)
{
    o_assert(NOT(getPlaceholderTypeName(qualifiedName).empty()));
    m_PlaceholderTypeByNameMap.erase(qualifiedName);
}

reflection::Type* DataTypeManager::solveTypeById( uint id ) const
{
    o_warning(false, "TODO : implement");
    return nullptr;
}

reflection::Type* DataTypeManager::solveTypeByName( const string& qualifiedName ) const
{
    reflection::Type* pType = phantom::typeByName(qualifiedName);
    if(pType) return pType;
    return getPlaceholderTypeByName(qualifiedName);
}

void    DataTypeManager::registerPlaceholderTypeById(uint id, uint placeHolderId)
{
    m_PlaceholderTypeByIdMap[id] = placeHolderId;
}
void    DataTypeManager::unregisterPlaceholderTypeById(uint id)
{
    m_PlaceholderTypeByIdMap.erase(id);
}

reflection::Type* DataTypeManager::getPlaceholderTypeByName( const string& qualifiedName ) const
{
    auto found = m_PlaceholderTypeByNameMap.find(qualifiedName);
    return found != m_PlaceholderTypeByNameMap.end() ? solveTypeByName(found->second) : nullptr;
}

const string& DataTypeManager::getPlaceholderTypeName( const string& qualifiedName ) const
{
    static string nullstr;
    auto found = m_PlaceholderTypeByNameMap.find(qualifiedName);
    return found != m_PlaceholderTypeByNameMap.end() ? found->second : nullstr;
}

void DataTypeManager::unregisterAllByPlaceholderTypeName( const string& placeholder )
{
    vector<string> keysToRemove;
    auto it = m_PlaceholderTypeByNameMap.begin();
    auto end = m_PlaceholderTypeByNameMap.end();
    for(;it!=end;++it)
    {
        if(it->second == placeholder)
            keysToRemove.push_back(it->first);
    }
    {
        auto it = keysToRemove.begin();
        auto end = keysToRemove.end();
        for(;it!=end;++it)
        {
            m_PlaceholderTypeByNameMap.erase(*it);
        }
    }
}

o_namespace_end(phantom, serialization)