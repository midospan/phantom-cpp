/* TODO LICENCE HERE */

#ifndef serialization_BinaryPackageNode_h__
#define serialization_BinaryPackageNode_h__


/* ****************** Includes ******************* */
#include "phantom/serialization/PackageNode.h"
/* **************** Declarations ***************** */
o_fwd(class, phantom, serialization, BinaryPackageDataBase)
o_fwd(class, phantom, serialization, BinaryPackageDataStateBase)
o_declareN(class, (phantom, serialization), BinaryPackageNode)
/* *********************************************** */

o_namespace_begin(phantom, serialization)


class o_export BinaryPackageNode : public PackageNode
{
    friend class BinaryPackageDataStateBase;


public:

    BinaryPackageNode(BinaryPackageDataBase* a_pDataBase, uint a_uiGuid, BinaryPackageNode* a_pParentNode);

    virtual void    saveIndex() ;
    virtual void    saveAttributes() ;
    virtual void    saveDataAttributes();
    virtual void    saveDataAttributes(const phantom::data& a_Data, uint a_uiGuid);

    virtual void    loadAttributes();
    virtual void    loadDataAttributes();
    virtual void    loadDataAttributes(const phantom::data& a_Data, uint a_uiGuid);
    virtual boolean canLoad(map<string, vector<string> >* missing_types_per_module);
    virtual void    cache();
    virtual void    build();
    virtual void    deserialize(uint a_uiSerializationFlag);
    virtual void    uncache();
    virtual void    restore(uint a_uiSerializationFlag);
    virtual void    unbuild();
    virtual void    configure();
    virtual void    unconfigure();


protected:

    void            saveDataAttributesHelper(const phantom::data& a_Data);
    void            loadDataAttributesHelper(const phantom::data& a_Data);
    virtual void    saveDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint a_uiGuid);
    virtual void    loadDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint a_uiGuid);
    

protected:

    list<data>      m_DataRestoreQueue;
    list<data>      m_DataAbortQueue;
};

o_namespace_end(phantom, serialization)

#endif // serialization_BinaryPackageNode_h__