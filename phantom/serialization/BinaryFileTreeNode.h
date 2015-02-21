/* TODO LICENCE HERE */

#ifndef serialization_BinaryFileTreeNode_h__
#define serialization_BinaryFileTreeNode_h__

/* ****************** Includes ******************* */
#include "phantom/serialization/FileTreeNode.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
/* **************** Declarations ***************** */
o_fwd(class, phantom, serialization, BinaryFileTreeDataBase)
o_fwd(class, phantom, serialization, BinaryFileTreeDataStateBase)
o_declareN(class, (phantom, serialization), BinaryFileTreeNode)
/* *********************************************** */

o_namespace_begin(phantom, serialization)

class o_export BinaryFileTreeNode : public FileTreeNode
{
    friend class BinaryFileTreeDataStateBase;
    friend class BinaryFileTreeDataBase;

public:
    BinaryFileTreeNode(BinaryFileTreeDataBase* a_pDataBase, uint guid, BinaryFileTreeNode* a_pParentNode);

    virtual void    saveIndex() ;
    virtual void    saveAttributes() ;
    virtual void    saveDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid) ;
    virtual void    saveDataAttributes();
    virtual void    saveDataAttributes(const phantom::data& a_Data, uint guid);

    virtual void    loadAttributes();
    virtual void    loadDataAttributes();
    virtual void    loadDataAttributes(const phantom::data& a_Data, uint guid);
    virtual bool    canLoad(map<string, vector<string> >* missing_types_per_module) const;
    virtual void    cache();
    virtual void    build(vector<data>& a_Data);
    virtual void    deserialize(uint a_uiSerializationFlag, vector<data>& a_Data);
    virtual void    uncache();
    virtual void    restore(uint a_uiSerializationFlag, vector<data>& a_Data);
    virtual void    unbuild();
    virtual void    configure();
    virtual void    unconfigure();

	virtual void    preCache();
	virtual bool    cacheOne(uint a_uiIndex);
	virtual void    postCache();
	virtual void    uncacheOne(const phantom::data& a_Data);
	virtual void    buildOne(const phantom::data& a_Data);
	virtual void    unbuildOne(const phantom::data& a_Data);
	virtual void    deserializeOne(const phantom::data& a_Data, uint a_uiSerializationFlag);
	virtual bool    restoreOne(const phantom::data& a_Data, uint a_uiSerializationFlag, restore_pass a_uiPass);

protected:
    void            saveDataAttributesHelper(vector<string>& a_Values, const phantom::data& a_Data);
    void            loadDataAttributesHelper(const vector<string>& a_Values, const phantom::data& a_Data);
    void            loadDataProperties(uint a_uiSerializationFlag, const phantom::data& a_Data, uint guid);

	void			readBinary(const string& a_strPath, byte* a_pBuffer, uint& a_uiBufferSize) const;
	void			writeBinary(const string& a_strPath, const byte* a_pBuffer, uint a_uiBufferSize) const;
    
protected:
    list<data>      m_DataRestoreQueue;
    list<data>      m_DataAbortQueue;
	byte*			m_pBuffer;
	uint			m_uiBufferSize;
	uint			m_uiBufferPos;
	vector<uint>    m_ParentGuids;
};

o_namespace_end(phantom, serialization)

#endif // serialization_BinaryFileTreeNode_h__