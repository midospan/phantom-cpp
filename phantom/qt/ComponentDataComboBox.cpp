/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ComponentDataComboBox.h"
/* *********************************************** */
namespace phantom { 
namespace qt {

    ComponentDataComboBox::ComponentDataComboBox( reflection::Class* a_pBaseClass
        , const vector<void*>& a_CurrentData
        , FilterBits a_iFilter) 
            : ClassComboBox(a_pBaseClass
                            , findCommonClass(a_CurrentData)
                            , a_iFilter)
            , m_CurrentData(a_CurrentData)
    {
        connect(this, SIGNAL(classSelected(reflection::Class*)), this, SLOT(currentClassChanged(reflection::Class*)));
    }

    void ComponentDataComboBox::setCurrentData( size_t i, void* a_pCurrentData )
    {
        o_assert(i<m_CurrentData.size());
        if(m_CurrentData[i] == a_pCurrentData) return;
        if(m_CurrentData[i])
        {
            reflection::Class* pOldClass = m_CurrentData[i] ? phantom::classOf(m_CurrentData[i]) : 0;
            reflection::Class* pNewClass = a_pCurrentData ? phantom::classOf(a_pCurrentData) : 0;
            setCurrentClass(pNewClass);
            o_assert(pOldClass);
            if(pNewClass)
            {
                pNewClass->smartCopy(phantom::baseOf(a_pCurrentData), phantom::baseOf(m_CurrentData[i]), pOldClass);
            }
            pOldClass->deleteInstance(m_CurrentData[i]);
        }
        m_CurrentData[i] = a_pCurrentData;
    }

    void ComponentDataComboBox::currentClassChanged( reflection::Class* a_pClass )
    {
        for(size_t i = 0; i<m_CurrentData.size(); ++i)
        {
            reflection::Class* pOldClass = m_CurrentData[i] ? phantom::classOf(m_CurrentData[i]) : 0;
            if(pOldClass == a_pClass) 
                continue;
            void* pNewData = a_pClass ? a_pClass->cast(m_pBaseClass, a_pClass->newInstance()) : nullptr;
            setCurrentData(i, pNewData);
        }
        emit dataChanged();
    }

    reflection::Class* ComponentDataComboBox::findCommonClass( const vector<void*>& a_Data ) const
    {
        if(a_Data.size() == 0) return nullptr;
        reflection::Class* pClass = phantom::classOf(a_Data[0]);
        for(size_t i = 1;i<a_Data.size(); ++i)
        {
            reflection::Class* pDataClass = phantom::classOf(a_Data[i]);
            reflection::Type* pCommonAncestor = (pDataClass && pClass) ? pClass->getCommonAncestor(pDataClass) : nullptr;
            pClass = pCommonAncestor ? pCommonAncestor->asClass() : nullptr;
        }
        return pClass;
    }

}}