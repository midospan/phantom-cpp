/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "phantom/serialization/BinaryPackageNode.h"
#include <phantom/serialization/BinaryPackageDataBase.h>
#include <phantom/serialization/BinaryPackageDataBase.hxx>
/* *********************************************** */
o_registerN((phantom, serialization), BinaryPackageDataBase);

o_namespace_begin(phantom, serialization)

BinaryPackageDataBase::BinaryPackageDataBase(const string& a_strUrl, uint a_uiSerializationFlag)
: PackageDataBase(a_strUrl, a_uiSerializationFlag)
{

}

o_destructor BinaryPackageDataBase::~BinaryPackageDataBase()
{

}

string BinaryPackageDataBase::dataFileExtension(void* a_pData) const 
{
	return "bin"; 
}

Node* BinaryPackageDataBase::createNode(uint a_uiGuid, Node* a_pParentNode) const
{
  return NULL;
  /*o_new(BinaryPackageNode)(
    const_cast<BinaryPackageDataBase*>(this)
    , a_uiGuid
    , phantom::as<BinaryPackageNode*>(a_pParentNode));*/
}

void BinaryPackageDataBase::destroyNode(Node* a_pNode) const
{
    o_delete(BinaryPackageNode) a_pNode; 
}

void BinaryPackageDataBase::saveRuntimeTypes()
{

}

void BinaryPackageDataBase::loadRuntimeTypes( reflection::Module* a_pModule )
{

}

o_namespace_end(phantom, serialization)