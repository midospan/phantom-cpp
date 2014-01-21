/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "DataComboBoxEditor.h"
/* *********************************************** */
o_registerN((phantom, qt), DataComboBoxEditor);

namespace phantom { namespace qt {

    DataComboBoxEditor::DataComboBoxEditor( reflection::Enum* a_pEnum ) 
        : VariableWidgetEditor( new DataComboBox(a_pEnum), SIGNAL(currentEnumValueChanged(size_t)), a_pEnum)
    {

    }

} // qt 
} // phantom 