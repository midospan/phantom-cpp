/* TODO LICENCE HERE */

#ifndef serialization_XmlFileTreeNode_h__
#define serialization_XmlFileTreeNode_h__

/* ****************** Includes ******************* */
#include "phantom/serialization/FileTreeNode.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), XmlFileTreeNode);
o_fwd(class, phantom, serialization, XmlFileTreeDataBase);
o_fwd(class, phantom, serialization, XmlFileTreeDataStateBase);
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export XmlFileTreeNode : public FileTreeNode
{
    friend class XmlFileTreeDataStateBase;

public:
    XmlFileTreeNode(XmlFileTreeDataBase* a_pDataBase, uint guid, XmlFileTreeNode* a_pParentNode);

};

o_namespace_end(phantom, serialization)

#endif // serialization_XmlFileTreeNode_h__