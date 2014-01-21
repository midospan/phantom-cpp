#ifndef ghost_gui_DataComboBox_h__
#define ghost_gui_DataComboBox_h__


/* ****************** Includes ******************* */
#include <QComboBox>
/* **************** Declarations ***************** */

/* *********************************************** */

namespace ghost { namespace gui {

class DataValueFilter;

class DataComboBox : public QComboBox
{
    Q_OBJECT

    friend struct DataComboBoxFiller;

public:
    DataComboBox( phantom::serialization::DataBase* a_pDataBase
        , const phantom::vector<phantom::data>& currentData
        , phantom::reflection::Type* a_pFilterType
        , const phantom::vector<phantom::data>& editedData 
        , DataValueFilter* a_pDataValueFilter = NULL);
	~DataComboBox(void) 
    {
    }

protected:
    void    addNodeDataCascade(phantom::serialization::Node* a_pNode);

    void    addData(const phantom::data& a_Data);

    void    removeData(const phantom::data& a_Data)
    {
        int index = findData( (phantom::uint)a_Data.address() );
        o_assert(index != -1);
        removeItem(index);
    }

public:
    const phantom::data&   getCurrentData() const 
    {
        void* address = (void*)itemData(currentIndex()).toUInt();
        return m_pDataBase->getData(m_pDataBase->getGuid(address));
    }

    void*   getCurrentDataCastedAddress() const
    {
        const phantom::data& currentData = getCurrentData();
        return currentData.type()->cast(m_pFilterType, currentData.address());
    }

    void computeCommonParentNode();

protected slots:
    void currentDataIndexChanged(int index)
    {
        void* address = (void*)itemData(index).toUInt();
        if(address)
        {
            const phantom::data& d = m_pDataBase->getData(m_pDataBase->getGuid(address));
            phantom::data castedData(d.type()->cast(m_pFilterType, d.address()), m_pFilterType);
            emit dataSelected(d);
            emit dataSelectedCasted(castedData);
        }
        else
        {
            emit dataSelected(phantom::data());
            emit dataSelectedCasted(phantom::data());
        }
    }

signals:
    void    dataSelected(const phantom::data& a_Data);
    void    dataSelectedCasted(const phantom::data& a_Data);

protected:
    phantom::reflection::Type*          m_pFilterType;
    phantom::serialization::DataBase*   m_pDataBase;
    phantom::serialization::Node*       m_pParentNode;
    phantom::vector<phantom::data>      m_EditedData;
    DataValueFilter*                    m_pDataValueFilter;
};


} // gui 
} // ghost 



#endif // ghost_gui_DataComboBox_h__
