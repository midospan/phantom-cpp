#ifndef phantom_qt_DataComboBoxEditor_h__
#define phantom_qt_DataComboBoxEditor_h__


/* ****************** Includes ******************* */
#include <QComboBox>
#include <phantom/qt/VariableWidgetEditor.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), DataComboBoxEditor);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export DataComboBoxEditor : public VariableWidgetEditor
{
public:
    DataComboBoxEditor(phantom::serialization::DataBase* a_pDataBase
        , phantom::reflection::Type* a_pType
        , const phantom::vector<phantom::data>& currentData
        , const phantom::vector<phantom::data>& editedData);

    virtual void setValue(const void* a_pSrc) const;
    virtual void getValue(void* a_pDest) const;
};


} // qt 
} // phantom 

#endif // phantom_qt_EnumComboBox_h__
