/* TODO LICENCE HERE */

#ifndef serialization_PackageNode_h__
#define serialization_PackageNode_h__


/* ****************** Includes ******************* */
#include "phantom/serialization/Node.h"
/* *********************************************** */
/* The *.hxx file must be the last #include */
#include "phantom/def_export.h"
/* **************** Declarations ***************** */
o_fwd(class, phantom, serialization, PackageDataBase);
o_declareN(class, (phantom, serialization), PackageNode);
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export PackageNode : public Node
{
    friend class PackageDataBase;


public:

    PackageNode(PackageDataBase* a_pDataBase, uint a_uiGuid, PackageNode* a_pParentNode);
};

o_namespace_end(phantom, serialization)

#endif // serialization_PackageNode_h__