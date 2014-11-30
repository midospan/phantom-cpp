#ifndef phantom_qt_EnumComboBoxEditor_h__
#define phantom_qt_EnumComboBoxEditor_h__


/* ****************** Includes ******************* */
#include <QComboBox>
#include <phantom/qt/VariableWidgetEditor.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), EnumComboBoxEditor);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export EnumComboBox : public QComboBox
{
    Q_OBJECT

public:
	EnumComboBox(phantom::reflection::Enum* a_pEnum);
	~EnumComboBox(void) 
    {

    }

    void setCurrentEnumValue(size_t a_uiEnumValue);

    size_t getCurrentEnumValue() const 
    { 
        return itemData(currentIndex()).toUInt();
    }

signals:
    void currentEnumValueChanged(size_t a_uiEnumValue);

protected slots:
    void currentEnumIndexChanged(int index)
    {
        emit currentEnumValueChanged(itemData(index).toUInt());
    }

protected:
    phantom::reflection::Enum* m_pEnum;
};


class o_qt_export EnumComboBoxEditor : public VariableWidgetEditor
{
public:
    EnumComboBoxEditor(reflection::Enum* a_pEnum);
    virtual void setValue(const void* a_pSrc) const 
    {
        ((EnumComboBox*)m_pWidget)->setCurrentEnumValue(*((size_t*)a_pSrc));
    }
    virtual void getValue(void* a_pDest) const 
    {
        *((size_t*)a_pDest) = ((EnumComboBox*)m_pWidget)->getCurrentEnumValue();
    }
};


} // qt 
} // phantom 

#endif // phantom_qt_EnumComboBox_h__
