/* TODO LICENCE HERE */

#ifndef serialization_BinaryPackageDataBase_h__
#define serialization_BinaryPackageDataBase_h__


/* ****************** Includes ******************* */
#include <phantom/serialization/PackageDataBase.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), BinaryPackageDataBase)
/* *********************************************** */

o_namespace_begin(phantom, serialization)


class o_export BinaryPackageDataBase : public PackageDataBase
{
    friend class BinaryPackageNode;


public:

    BinaryPackageDataBase(const string& url, uint a_uiSerializationFlag);
    o_destructor ~BinaryPackageDataBase();
    
    virtual string				dataFileExtension(void* a_pData) const;

    virtual Node*				createNode(uint a_uiGuid, Node* a_pParentNode) const;
    virtual void				destroyNode(Node* a_pNode) const;
    virtual void                saveRuntimeTypes();
    virtual void                loadRuntimeTypes(reflection::Module* a_pModule);
};

o_namespace_end(phantom, serialization)

#endif //serialization_BinaryPackageDataBase_h__