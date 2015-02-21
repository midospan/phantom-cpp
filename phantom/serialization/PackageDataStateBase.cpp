/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/serialization/PackageDataStateBase.h>
#include <phantom/serialization/PackageDataStateBase.hxx>
#include <phantom/serialization/PackageDataBase.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <phantom/serialization/PackageNode.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
/* *********************************************** */
o_registerN((phantom, serialization), PackageDataStateBase);

o_namespace_begin(phantom, serialization)

PackageDataStateBase::PackageDataStateBase(PackageDataBase* a_pDataBase, const string& a_strUrl, uint a_uiSerializationFlag) 
: DataStateBase(a_pDataBase, a_strUrl, a_uiSerializationFlag)
{

}

o_destructor PackageDataStateBase::~PackageDataStateBase()
{

}

bool PackageDataStateBase::hasStateSaved(Node* a_pNode, uint a_uiStateId) const
{
    return false;
}

o_namespace_end(phantom, serialization)
