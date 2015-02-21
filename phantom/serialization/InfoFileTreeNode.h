/* TODO LICENCE HERE */

#ifndef serialization_InfoFileTreeNode_h__
#define serialization_InfoFileTreeNode_h__

/* ****************** Includes ******************* */
#include "phantom/serialization/FileTreeNode.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), InfoFileTreeNode);
o_fwd(class, phantom, serialization, InfoFileTreeDataBase);
o_fwd(class, phantom, serialization, InfoFileTreeDataStateBase);
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export InfoFileTreeNode : public FileTreeNode
{
    friend class InfoFileTreeDataStateBase;

public:
    InfoFileTreeNode(InfoFileTreeDataBase* a_pDataBase, uint guid, InfoFileTreeNode* a_pParentNode);
    
};

o_namespace_end(phantom, serialization)

#endif // serialization_InfoFileTreeNode_h__