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
	EnumComboBox(phantom::reflection::Enum* a_pEnum) 
        : m_pEnum(a_pEnum)
    {
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
	~EnumComboBox(void) 
    {

    }

    void setCurrentEnumValue(size_t a_uiEnumValue)
    {
        int index = findData(a_uiEnumValue);
        o_assert(index != -1);
        setCurrentIndex(index);
    }

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
