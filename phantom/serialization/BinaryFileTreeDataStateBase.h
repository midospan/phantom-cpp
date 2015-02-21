/* TODO LICENCE HERE */

#ifndef serialization_BinaryFileTreeDataStateBase_h__
#define serialization_BinaryFileTreeDataStateBase_h__

/* ****************** Includes ******************* */
#include <phantom/serialization/FileTreeDataStateBase.h>
/* *********************************************** */
o_declareN(class, (phantom, serialization), BinaryFileTreeDataStateBase);

o_namespace_begin(phantom, serialization)

class o_export BinaryFileTreeDataStateBase : public FileTreeDataStateBase
{
    friend class BinaryFileTreeNode;

public:
    BinaryFileTreeDataStateBase(BinaryFileTreeDataBase* a_pDataBase, const string& a_Url, uint a_uiSerializationFlag)
        : FileTreeDataStateBase(a_pDataBase, a_Url, a_uiSerializationFlag) {}
    o_destructor ~BinaryFileTreeDataStateBase(void)     {}

protected:
    virtual void			loadState(Node* a_pNode, uint a_uiStateId);
    virtual void			saveState(Node* a_pNode, uint a_uiStateId);
    virtual void			loadDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId);
    virtual void			saveDataState(const phantom::data& a_Data, uint guid, Node* a_pNode, uint a_uiStateId);

	void					readBinary(const string& a_strPath, byte* a_pBuffer, uint& a_uiBufferSize);
	void					writeBinary(const string& a_strPath, byte* a_pBuffer, uint a_uiBufferSize);
};

o_namespace_end(phantom, serialization)

#endif 