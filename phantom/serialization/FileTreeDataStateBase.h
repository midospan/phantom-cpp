/* TODO LICENCE HERE */

#ifndef serialization_FileTreeDataStateBase_h__
#define serialization_FileTreeDataStateBase_h__

/* ****************** Includes ******************* */
#include "phantom/serialization/DataStateBase.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), FileTreeDataStateBase)
namespace boost { namespace filesystem { class path; } }
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export FileTreeDataStateBase : public DataStateBase
{
public:
    FileTreeDataStateBase(FileTreeDataBase* a_pDataBase, const string& a_Url, uint a_uiSerializationFlag);
    o_destructor ~FileTreeDataStateBase(void)     {}

    virtual bool hasStateSaved(Node* a_pNode, uint a_uiStateId) const;

    string statePath(Node* a_pNode, uint a_uiStateId) const;

    string dataPath(const phantom::data& a_Data, uint a_uiGuid, Node* a_pNode, uint a_uiStateId) const;

    FileTreeDataBase* getFileTreeDataBase() const;

protected:
    virtual void loadState(Node* a_pNode, const vector<data>& a_DataList, uint a_uiStateId);
    virtual void saveState(Node* a_pNode, const vector<data>& a_DataList, uint a_uiStateId);
    virtual void loadDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId);
    virtual void saveDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId);
        
};

o_namespace_end(phantom, serialization)

#endif 