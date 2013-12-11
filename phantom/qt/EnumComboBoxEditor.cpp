/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "EnumComboBoxEditor.h"
/* *********************************************** */
o_registerN((phantom, qt), EnumComboBoxEditor);

namespace phantom { namespace qt {

    EnumComboBoxEditor::EnumComboBoxEditor( reflection::Enum* a_pEnum ) 
        : VariableWidgetEditor( new EnumComboBox(a_pEnum), SIGNAL(currentEnumValueChanged(size_t)), a_pEnum)
    {

    }

} // qt 
} // phantom 