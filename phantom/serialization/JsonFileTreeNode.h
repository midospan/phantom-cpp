/* TODO LICENCE HERE */

#ifndef serialization_JsonFileTreeNode_h__
#define serialization_JsonFileTreeNode_h__

/* ****************** Includes ******************* */
#include "phantom/serialization/FileTreeNode.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), JsonFileTreeNode);
o_fwd(class, phantom, serialization, JsonFileTreeDataBase);
o_fwd(class, phantom, serialization, JsonFileTreeDataStateBase);
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export JsonFileTreeNode : public FileTreeNode
{
    friend class JsonFileTreeDataStateBase;

public:
    JsonFileTreeNode(JsonFileTreeDataBase* a_pDataBase, uint guid, JsonFileTreeNode* a_pParentNode);

};

o_namespace_end(phantom, serialization)

#endif // serialization_JsonFileTreeNode_h__