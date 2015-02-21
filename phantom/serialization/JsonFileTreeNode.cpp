/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/serialization/JsonFileTreeDataBase.h>
#include <phantom/serialization/JsonFileTreeNode.h>
#include <phantom/serialization/JsonFileTreeNode.hxx>
/* *********************************************** */
o_registerN((phantom, serialization), JsonFileTreeNode);

o_namespace_begin(phantom, serialization)

JsonFileTreeNode::JsonFileTreeNode(JsonFileTreeDataBase* a_pDataBase, uint guid, JsonFileTreeNode* a_pParentNode)
    : FileTreeNode(a_pDataBase, guid, a_pParentNode) 
{
}

o_namespace_end(phantom, serialization)
