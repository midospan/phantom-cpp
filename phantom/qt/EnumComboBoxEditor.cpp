/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "EnumComboBoxEditor.h"
#include "EnumComboBoxEditor.hxx"
#include <QStyledItemDelegate>
/* *********************************************** */
o_registerN((phantom, qt), EnumComboBoxEditor);

namespace phantom { namespace qt {

    EnumComboBox::EnumComboBox( phantom::reflection::Enum* a_pEnum ) : m_pEnum(a_pEnum)
    {
        setItemDelegate(new QStyledItemDelegate());
        connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentEnumIndexChanged(int)));

        size_t i = 0;
        size_t count = a_pEnum->getConstantCount();
        for(;i<count;++i)
        {
            size_t constantValue = 0;
            phantom::reflection::Constant* pConstant = a_pEnum->getConstant(i);
            pConstant->getValue(&constantValue);
            addItem(QIcon(iconOf(pConstant).c_str())
                , nameOf(pConstant).c_str()
                , constantValue); 
        }
    }

    void EnumComboBox::setCurrentEnumValue( size_t a_uiEnumValue )
    {
        int index = findData(a_uiEnumValue);
        if(index == -1) index = 0;
        setCurrentIndex(index);
    }


    EnumComboBoxEditor::EnumComboBoxEditor( reflection::Enum* a_pEnum ) 
        : VariableWidgetEditor( new EnumComboBox(a_pEnum), SIGNAL(currentEnumValueChanged(size_t)), a_pEnum)
    {

    }

} // qt 
} // phantom 