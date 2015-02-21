/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/serialization/XmlFileTreeDataBase.h>
#include <phantom/serialization/XmlFileTreeNode.h>
#include <phantom/serialization/XmlFileTreeNode.hxx>
/* *********************************************** */
o_registerN((phantom, serialization), XmlFileTreeNode);

o_namespace_begin(phantom, serialization)

XmlFileTreeNode::XmlFileTreeNode(XmlFileTreeDataBase* a_pDataBase, uint guid, XmlFileTreeNode* a_pParentNode)
    : FileTreeNode(a_pDataBase, guid, a_pParentNode) 
{
}

o_namespace_end(phantom, serialization)