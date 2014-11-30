/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "phantom/serialization/Node.h"
#include "DataComboBox.h"
#include <QStyledItemDelegate>
/* *********************************************** */

 
namespace phantom { 
namespace qt {


    DataComboBox::DataComboBox( phantom::serialization::DataBase* a_pDataBase 
        , phantom::reflection::Type* a_pType
        , const phantom::vector<phantom::data>& currentData  
        , const phantom::vector<phantom::data>& editedData
        , DataValueFilter* a_pDataValueFilter /*= NULL*/
        , bool a_bAllowsNone /*= true*/) 

    : m_pDataBase(a_pDataBase)
        , m_pType(a_pType)
        , m_EditedData(editedData)
        , m_pDataValueFilter(a_pDataValueFilter)
    {
        setItemDelegate(new QStyledItemDelegate());
        connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentDataIndexChanged(int)));

        if(a_bAllowsNone)
        {
            addItem(QIcon("resources/icons/famfamfam/null.png"), "none", 0);
        }
        computeCommonParentNode();
        addNodeDataCascade(m_pParentNode);
        
        phantom::data commonData = currentData[0];
        for(size_t i = 1; i<currentData.size(); ++i)
        {
            if(commonData != currentData[i])
            {
                commonData = phantom::data();
                break;
            }
        }

		int currentIndex = findData((phantom::ulonglong)commonData.address());
        if(currentIndex != -1)
        {
            setCurrentIndex(currentIndex);
        }
        /*if(m_pDataValueFilter)
        {
            o_assert(m_EditedData.type()->isKindOf(m_pDataValueFilter->getTargetClassType()));
        }*/
    }

    void DataComboBox::addData( const phantom::data& a_Data )
    {
        phantom::string name = m_pDataBase->getDataAttributeValue(a_Data, m_pDataBase->getAttributeIndex("name"))
                               + " (" + lexical_cast<string>((void*)m_pDataBase->getGuid(a_Data)) + ')';
        addItem( QIcon(iconOf(a_Data.type()).c_str()), name.c_str(), (size_t)a_Data.address() );
    }

    void DataComboBox::addNodeDataCascade( phantom::serialization::Node* a_pNode )
    {
        for(auto it = a_pNode->beginData(); it != a_pNode->endData(); ++it)
        {
            phantom::data d = *it;
            if(/*std::find(m_EditedData.begin(), m_EditedData.end(), d) == m_EditedData.end() 
                AND */d.type()->isKindOf(m_pType))
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