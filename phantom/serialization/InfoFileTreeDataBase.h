/* TODO LICENCE HERE */

#ifndef serialization_InfoFileTreeDataBase_h__
#define serialization_InfoFileTreeDataBase_h__

/* ****************** Includes ******************* */
#include <phantom/serialization/FileTreeDataBase.h>
/* *********************************************** */
/* The *.hxx file must be the last #include */
#include "phantom/def_export.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), InfoFileTreeDataBase);
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export InfoFileTreeDataBase : public FileTreeDataBase
{
    friend class InfoFileTreeNode;

public:
    InfoFileTreeDataBase(const string& url, uint a_uiSerializationFlag) : FileTreeDataBase(url, a_uiSerializationFlag) {}
    o_destructor ~InfoFileTreeDataBase(void)     {}
    
    virtual string  dataFileExtension(void* a_pData) const { return "txt"; }
    
    virtual Node*   createNode(uint a_Guid, Node* a_pParentNode) const;
    virtual void    destroyNode(Node* a_pNode) const;

    virtual void write(const string& a_Path, const property_tree& a_Tree) const;

    virtual void read(const string& a_Path, property_tree& a_Tree) const;
};

o_namespace_end(phantom, serialization)

#endif 