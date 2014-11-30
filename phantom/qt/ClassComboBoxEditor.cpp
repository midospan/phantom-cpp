/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ClassComboBoxEditor.h"
#include "ClassComboBoxEditor.hxx"
#include "ClassComboBox.h"
#include "VariableNode.h"
/* *********************************************** */
o_registerN((phantom, qt), ClassComboBoxEditor);

namespace phantom { namespace qt {

    ClassComboBoxEditor::ClassComboBoxEditor( reflection::Class* a_pBaseClass
        , reflection::Class* a_pCurrentClass, bool a_bAllowsNone) 
        : VariableWidgetEditor( new ClassComboBox(a_pBaseClass, a_pCurrentClass, ClassComboBox::e_FilterBit_Derived, a_bAllowsNone)
            , SIGNAL(classSelected(reflection::Class*))
            , typeOf<reflection::Class*>())
    {

    }

    void ClassComboBoxEditor::setValue( const void* a_pSrc ) const
    {
        void* pClass = *((void**)a_pSrc);
        ((ClassComboBox*)m_pWidget)->setCurrentClass((reflection::Class*)pClass);
    }

    void ClassComboBoxEditor::getValue( void* a_pDest ) const
    {
        void* pCurrentData = ((ClassComboBox*)m_pWidget)->getCurrentClass();
        // TODO move this 'd.isNull()' test in 'phantom::data::cast()'
        *((void**)a_pDest) = pCurrentData;
    }

} // qt 
} // phantom 