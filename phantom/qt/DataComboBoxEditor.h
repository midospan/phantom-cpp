#ifndef phantom_qt_DataComboBoxEditor_h__
#define phantom_qt_DataComboBoxEditor_h__


/* ****************** Includes ******************* */
#include <QComboBox>
#include <phantom/qt/VariableWidgetEditor.h>
/* **************** Declarations ***************** */

/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export DataComboBoxEditor : public VariableWidgetEditor
{
public:
    DataComboBoxEditor(phantom::serialization::DataBase* a_pDataBase
        , const phantom::vector<phantom::data>& currentData
        , phantom::reflection::Type* a_pFilterType
        , const phantom::vector<phantom::data>& editedData);

    virtual void setValue(const void* a_pSrc) const 
    {
        ((DataComboBox*)m_pWidget)->setCurrentEnumValue(*((size_t*)a_pSrc));
    }
    virtual void getValue(void* a_pDest) const 
    {
        *((size_t*)a_pDest) = ((DataComboBox*)m_pWidget)->getCurrentEnumValue();
    }
};


} // qt 
} // phantom 

o_classNS((phantom, qt), DataComboBoxEditor, (VariableWidgetEditor))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt), DataComboBoxEditor);

#endif // phantom_qt_EnumComboBox_h__
