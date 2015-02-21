/* TODO LICENCE HERE */

#ifndef serialization_PackageDataStateBase_h__
#define serialization_PackageDataStateBase_h__


/* ****************** Includes ******************* */
#include "phantom/serialization/DataStateBase.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), PackageDataStateBase);
namespace boost { namespace filesystem { class path; } }
/* *********************************************** */


o_namespace_begin(phantom, serialization)

class PackageDataBase;
class o_export PackageDataStateBase : public DataStateBase
{
public:

    PackageDataStateBase(PackageDataBase* a_pDataBase, const string& a_strUrl, uint a_uiSerializationFlag);
    o_destructor ~PackageDataStateBase();

    virtual bool	hasStateSaved(Node* a_pNode, uint a_uiStateId) const;


protected:

    virtual void	loadState(Node* a_pNode, const vector<data>& a_Data, uint a_uiStateId) = 0;
    virtual void	saveState(Node* a_pNode, const vector<data>& a_Data, uint a_uiStateId) = 0;
};

o_namespace_end(phantom, serialization)

#endif //serialization_PackageDataStateBase_h__