/* TODO LICENCE HERE */

#ifndef serialization_JsonFileTreeDataBase_h__
#define serialization_JsonFileTreeDataBase_h__

/* ****************** Includes ******************* */
#include <phantom/serialization/FileTreeDataBase.h>
/* *********************************************** */
/* The *.hxx file must be the last #include */
#include "phantom/def_export.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), JsonFileTreeDataBase);
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export JsonFileTreeDataBase : public FileTreeDataBase
{
    friend class JsonFileTreeNode;

public:
    JsonFileTreeDataBase(const string& url, uint a_uiSerializationFlag) : FileTreeDataBase(url, a_uiSerializationFlag) {}
    o_destructor ~JsonFileTreeDataBase(void)     {}
    
    virtual string  dataFileExtension(void* a_pData) const { return "json"; }
    
    virtual Node*   createNode(uint a_Guid, Node* a_pParentNode) const;
    virtual void    destroyNode(Node* a_pNode) const;

    virtual void write(const string& a_Path, const property_tree& a_Tree) const;

    virtual void read(const string& a_Path, property_tree& a_Tree) const;

};

o_namespace_end(phantom, serialization)

#endif 