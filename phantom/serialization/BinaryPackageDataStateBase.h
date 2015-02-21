/* TODO LICENCE HERE */

#ifndef serialization_BinaryPackageDataStateBase_h__
#define serialization_BinaryPackageDataStateBase_h__


/* ****************** Includes ******************* */
#include <phantom/serialization/PackageDataStateBase.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), BinaryPackageDataStateBase)
/* *********************************************** */

o_namespace_begin(phantom, serialization)


class o_export BinaryPackageDataStateBase : public PackageDataStateBase
{
    friend class BinaryPackageNode;


public:
    BinaryPackageDataStateBase(BinaryPackageDataBase* a_pDataBase, const string& a_Url, uint a_uiSerializationFlag);
    o_destructor ~BinaryPackageDataStateBase();


protected:

    virtual void loadState(Node* a_pNode, uint a_uiStateId);
    virtual void saveState(Node* a_pNode, uint a_uiStateId);
    virtual void loadDataState(const phantom::data& a_Data, uint a_uiGuid, Node* a_pNode, uint a_uiStateId);
    virtual void saveDataState(const phantom::data& a_Data, uint a_uiGuid, Node* a_pNode, uint a_uiStateId);
};

o_namespace_end(phantom, serialization)

#endif //serialization_BinaryPackageDataStateBase_h__