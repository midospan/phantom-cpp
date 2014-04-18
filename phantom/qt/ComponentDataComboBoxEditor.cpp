/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ComponentDataComboBoxEditor.h"
#include "ComponentDataComboBoxEditor.hxx"
#include "ComponentDataComboBox.h"
#include "VariableNode.h"
/* *********************************************** */
o_registerN((phantom, qt), ComponentDataComboBoxEditor);

namespace phantom { namespace qt {

    ComponentDataComboBoxEditor::ComponentDataComboBoxEditor( reflection::Class* a_pBaseClass
        , const vector<void*>& a_CurrentData) 
        : VariableWidgetEditor( new ComponentDataComboBox(a_pBaseClass, a_CurrentData, ClassComboBox::e_FilterBit_Derived)
            , SIGNAL(dataChanged())
            , a_pBaseClass->pointerType())
    {

    }

    void ComponentDataComboBoxEditor::setValue( const void* a_pSrc ) const
    {
        void* pNewData = *((void**)a_pSrc);
        ((ComponentDataComboBox*)m_pWidget)->setCurrentData(0, pNewData);
    }

    void ComponentDataComboBoxEditor::getValue( void* a_pDest ) const
    {
        void* pCurrentData = ((ComponentDataComboBox*)m_pWidget)->getCurrentData(0);
        // TODO move this 'd.isNull()' test in 'phantom::data::cast()'
        *((void**)a_pDest) = pCurrentData;
    }

    void ComponentDataComboBoxEditor::setValues( const void** a_ppSrc ) const
    {
        for(size_t i = 0; i<m_pVariableNode->getVariableCount(); ++i)
        {
            ((ComponentDataComboBox*)m_pWidget)->setCurrentData(i, *((void**)a_ppSrc[i]));
        }
    }

    void ComponentDataComboBoxEditor::getValues( void** a_ppDest ) const
    {
        for(size_t i = 0; i<m_pVariableNode->getVariableCount(); ++i)
        {
            *((void**)a_ppDest[i]) = ((ComponentDataComboBox*)m_pWidget)->getCurrentData(i);
        }
    }

} // qt 
} // phantom 