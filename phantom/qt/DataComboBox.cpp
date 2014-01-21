/* ******************* Includes ****************** */
#include "ghost/gui/gui.h"
#include "DataComboBox.h"
#include "ghost/gui/Application.h"
#include "ghost/gui/DataValueFilter.h"
/* *********************************************** */

 
namespace ghost { 
namespace gui {


    DataComboBox::DataComboBox( phantom::serialization::DataBase* a_pDataBase 
        , const phantom::vector<phantom::data>& currentData 
        , phantom::reflection::Type* a_pFilterType 
        , const phantom::vector<phantom::data>& editedData
        , DataValueFilter* a_pDataValueFilter /*= NULL*/) 

    : m_pDataBase(a_pDataBase)
        , m_pFilterType(a_pFilterType)
        , m_EditedData(editedData)
        , m_pDataValueFilter(a_pDataValueFilter)
    {
        connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentDataIndexChanged(int)));

        addNodeDataCascade(m_pParentNode);
		addItem(QIcon("resources/icons/famfamfam/null.png"), "none", 0);
        
		int currentIndex = findData((phantom::uint)currentData.address());
        if(currentIndex != -1)
        {
            setCurrentIndex(currentIndex);
        }
        /*if(m_pDataValueFilter)
        {
            o_assert(m_EditedData.type()->isKindOf(m_pDataValueFilter->getTargetClassType()));
        }*/
        computeCommonParentNode();
    }

    void DataComboBox::addData( const phantom::data& a_Data )
    {
        phantom::string name = m_pDataBase->getDataAttributeValue(a_Data, m_pDataBase->getAttributeIndex("name"));
        addItem( QIcon(a_Data.type()->getMetaDataValue(getIconMetaDataIndex()).c_str()), name.c_str(), (phantom::uint)a_Data.address());
    }

    void DataComboBox::addNodeDataCascade( phantom::serialization::Node* a_pNode )
    {
        for(auto it = a_pNode->beginData(); it != a_pNode->endData(); ++it)
        {
            phantom::data d = *it;
            if(std::find(m_EditedData.begin(), m_EditedData.end(), d) == m_EditedData.end() 
                AND d.type()->isKindOf(m_pFilterType))
                //AND ((m_pDataValueFilter == NULL) OR (m_pDataValueFilter->accepts(m_EditedData.address(), d))) 
            {
                addData(d);
            }
        }
        if(a_pNode->getParentNode())
        {
            addNodeDataCascade(a_pNode->getParentNode());
        }
		model()->sort(0);
    }

    void DataComboBox::computeCommonParentNode()
    {
        serialization::Node* pCommonNode = m_pDataBase->getNode(m_EditedData.front());
        for(auto it = m_EditedData.begin()+1; it != m_EditedData.end(); ++it) 
        {
            serialization::Node* pNode = m_pDataBase->getNode(*it);
            if(pNode == pCommonNode) continue;
            if(pCommonNode->hasParentNodeCascade(pNode))
            {
                pCommonNode = pNode;
            }
            else 
            {
                while(pCommonNode && !pNode->hasParentNodeCascade(pCommonNode))
                {
                    pCommonNode = pCommonNode->getParentNode();
                }
            }
        }
        o_assert(pCommonNode);
        m_pParentNode = pCommonNode;
    }

}}