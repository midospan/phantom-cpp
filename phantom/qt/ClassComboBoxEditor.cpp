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
        , const vector<reflection::Class*>& a_CurrentValues) 
        : VariableWidgetEditor( new ClassComboBox(a_pBaseClass, a_CurrentValues[0], ClassComboBox::e_FilterBit_Derived)
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

    void ClassComboBoxEditor::setValues( const void** a_ppSrc ) const
    {
        for(size_t i = 0; i<m_pVariableNode->getExpressionCount(); ++i)
        {
            ((ClassComboBox*)m_pWidget)->setCurrentClass((reflection::Class*)*((void**)a_ppSrc[i]));
        }
    }

    void ClassComboBoxEditor::getValues( void** a_ppDest ) const
    {
        for(size_t i = 0; i<m_pVariableNode->getExpressionCount(); ++i)
        {
            *((void**)a_ppDest[i]) = ((ClassComboBox*)m_pWidget)->getCurrentClass();
        }
    }

} // qt 
} // phantom 