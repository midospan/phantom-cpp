/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "DataComboBoxEditor.h"
#include "DataComboBoxEditor.hxx"
#include "DataComboBox.h"
/* *********************************************** */
o_registerN((phantom, qt), DataComboBoxEditor);

namespace phantom { namespace qt {

    DataComboBoxEditor::DataComboBoxEditor( 
          phantom::serialization::DataBase* a_pDataBase
        , phantom::reflection::Type* a_pType
        , const phantom::vector<phantom::data>& currentData
        , const phantom::vector<phantom::data>& editedData
        , bool a_bAllowsNone ) 
        : VariableWidgetEditor( new DataComboBox(a_pDataBase, a_pType, currentData, editedData, nullptr, a_bAllowsNone)
        , SIGNAL(dataSelected(const phantom::data&))
        , a_pType->pointerType())
    {

    }

    void DataComboBoxEditor::setValue( const void* a_pSrc ) const
    {
        ((DataComboBox*)m_pWidget)->setCurrentData(*((void**)a_pSrc));
    }

    void DataComboBoxEditor::getValue( void* a_pDest ) const
    {
        phantom::data d = ((DataComboBox*)m_pWidget)->getCurrentData();
        // TODO move this 'd.isNull()' test in 'phantom::data::cast()'
        *((void**)a_pDest) = d.isNull() ? 0 : d.cast(m_pValueType->removePointer()).address();
    }

    void DataComboBoxEditor::opened()
    {
        static_cast<DataComboBox*>(m_pWidget)->showPopup();
    }

} // qt 
} // phantom 