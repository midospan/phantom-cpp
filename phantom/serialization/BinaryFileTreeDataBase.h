/* TODO LICENCE HERE */

#ifndef serialization_BinaryFileTreeDataBase_h__
#define serialization_BinaryFileTreeDataBase_h__

/* ****************** Includes ******************* */
#include <phantom/serialization/FileTreeDataBase.h>
/* *********************************************** */
o_declareN(class, (phantom, serialization), XmlFileTreeDataBase);
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export BinaryFileTreeDataBase : public FileTreeDataBase
{
    friend class BinaryFileTreeNode;

public:
    BinaryFileTreeDataBase(const string& url, uint a_uiSerializationFlag);
    o_destructor ~BinaryFileTreeDataBase(void)     {}
    
    virtual string  dataFileExtension(void* a_pData) const { return "bin"; }
    
    virtual Node*   createNode(uint a_Guid, Node* a_pParentNode) const;
    virtual void    destroyNode(Node* a_pNode) const;
    virtual void    saveRuntimeTypes();
    virtual void    loadRuntimeTypes(reflection::Module* a_pModule);

protected:
    size_t m_uiBufferSize;
};

o_namespace_end(phantom, serialization)

#endif 