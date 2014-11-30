#ifndef phantom_qt_ClassComboBoxEditor_h__
#define phantom_qt_ClassComboBoxEditor_h__


/* ****************** Includes ******************* */
#include <QComboBox>
#include <phantom/qt/VariableWidgetEditor.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ClassComboBoxEditor);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export ClassComboBoxEditor : public VariableWidgetEditor
{
public:
    ClassComboBoxEditor(reflection::Class* a_pBaseClass
                                , reflection::Class* a_pCurrentClass, bool a_bAllowsNone);

    virtual void setValue(const void* a_pSrc) const;
    virtual void getValue(void* a_pDest) const;
};


} // qt 
} // phantom 

#endif // phantom_qt_EnumComboBox_h__
