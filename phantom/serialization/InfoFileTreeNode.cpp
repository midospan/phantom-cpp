/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/serialization/InfoFileTreeDataBase.h>
#include <phantom/serialization/InfoFileTreeNode.h>
#include <phantom/serialization/InfoFileTreeNode.hxx>
/* *********************************************** */
o_registerN((phantom, serialization), InfoFileTreeNode);

o_namespace_begin(phantom, serialization)
    
InfoFileTreeNode::InfoFileTreeNode(InfoFileTreeDataBase* a_pDataBase, uint guid, InfoFileTreeNode* a_pParentNode)
    : FileTreeNode(a_pDataBase, guid, a_pParentNode) 
{
}

o_namespace_end(phantom, serialization)
