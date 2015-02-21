/* TODO LICENCE HERE */

#ifndef serialization_PackageDataBase_h__
#define serialization_PackageDataBase_h__


/* ****************** Includes ******************* */
#include "DataBase.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, serialization), PackageDataBase);
namespace boost { namespace filesystem { class path; } }
/* *********************************************** */

o_namespace_begin(phantom, serialization)


class o_export PackageDataBase : public DataBase
{
public:

	struct PackageDataBaseBuffer
	{
		uint	m_uiBufferSize;
		byte*	m_pBuffer;
		byte*	m_pCurrent;
	};

    PackageDataBase(const string& a_strUrl, uint a_uiSerializationFlag);
    o_destructor ~PackageDataBase();
	
	PackageDataBaseBuffer*			getBuffer();

	virtual void					loadNodeEntries();
    virtual void					unloadNodeEntries();

	virtual boolean					hasNodeEntry(Node* a_pNode) const;
	virtual boolean					hasDataEntry(const data& a_Data, uint a_uiGuid, Node* a_pOwnerNode) const;

	virtual uint					generateGuid();
	virtual void					releaseGuid(uint a_uiGuid);

	virtual void					createDataEntry(const phantom::data& a_Data, uint a_uiGuid, Node* a_pOwnerNode);
	virtual void					destroyDataEntry(const phantom::data& a_Data, uint a_uiGuid, Node* a_pOwnerNode);
	virtual void					moveDataEntry(const phantom::data& a_Data, uint a_uiGuid, Node* a_pOldParent, Node* a_pNewParent);

	virtual void					createNodeEntry(Node* a_pNode);
	virtual void					destroyNodeEntry(Node* a_pNode);
	virtual void					moveNodeEntry(Node* a_pNode, Node* a_pNewParent); 


protected:

	void							loadNodeEntriesHelper(Node* a_pNode, const boost::filesystem::path& a_Path);


protected:

	PackageDataBaseBuffer			m_Buffer;
};

o_namespace_end(phantom, serialization)

#endif //serialization_PackageDataBase_h__