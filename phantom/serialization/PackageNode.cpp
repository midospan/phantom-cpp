/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/serialization/PackageDataBase.h>
#include <phantom/serialization/PackageNode.h>
#include <phantom/serialization/PackageNode.hxx>
/* *********************************************** */
o_registerN((phantom, serialization), PackageNode);

o_namespace_begin(phantom, serialization)


PackageNode::PackageNode(PackageDataBase* a_pDataBase, uint a_uiGuid, PackageNode* a_pParentNode)
: Node(a_pDataBase, a_uiGuid, a_pParentNode) 
{

}

o_namespace_end(phantom, serialization)

