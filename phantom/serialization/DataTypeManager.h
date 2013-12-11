#ifndef o_phantom_moon_DataTypeManager_h__
#define o_phantom_moon_DataTypeManager_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export DataTypeManager
{
public:
    typedef map<string, string> placeholder_type_by_name_map;
    typedef map<uint, uint>     placeholder_type_by_id_map;

public:
    virtual reflection::Type*   solveTypeByName(const string& qualifiedName) const;
    virtual reflection::Type*   solveTypeById(uint id) const;

    void    registerPlaceholderTypeByName(const string& qualifiedName, const string& placeHolder);
    void    unregisterPlaceholderTypeByName(const string& qualifiedName);
    void    unregisterAllByPlaceholderTypeName(const string& placeholder);

    reflection::Type* getPlaceholderTypeByName(const string& qualifiedName) const;

    void    registerPlaceholderTypeById(uint id, uint placeHolderId);
    void    unregisterPlaceholderTypeById(uint id);


    const string& getPlaceholderTypeName(const string& qualifiedName) const;

    placeholder_type_by_name_map::const_iterator beginPlaceholderTypesByName() const { return m_PlaceholderTypeByNameMap.begin(); }
    placeholder_type_by_name_map::const_iterator endPlaceholderTypesByName() const { return m_PlaceholderTypeByNameMap.end(); }

    placeholder_type_by_id_map::const_iterator beginPlaceholderTypesById() const { return m_PlaceholderTypeByIdMap.begin(); }
    placeholder_type_by_id_map::const_iterator endPlaceholderTypesById() const { return m_PlaceholderTypeByIdMap.end(); }

protected:
    placeholder_type_by_name_map    m_PlaceholderTypeByNameMap;
    placeholder_type_by_id_map    m_PlaceholderTypeByIdMap;
};

o_namespace_end(phantom, serialization)

o_classN((phantom, serialization), DataTypeManager)
{
	o_reflection
	{
		
	};
};
o_exposeN((phantom, serialization), DataTypeManager);

#endif
