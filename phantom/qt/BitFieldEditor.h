#ifndef o_qt_BitFieldEditor_h__
#define o_qt_BitFieldEditor_h__


/* ****************** Includes ******************* */
#include <phantom/qt/VariableWidgetEditor.h>
#include <QCheckBox>
#include <QHBoxLayout>
/* **************** Declarations ***************** */

/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export BitFieldChecker : public QWidget
{
    Q_OBJECT

public:
	BitFieldChecker(uint initialValue);
	~BitFieldChecker(void) {}

    void setValue(uint mask);
    uint getValue() const;

protected slots:
    void bitCheckBoxChanged(int state)
    {
        valueChanged(getValue());
    }

signals:
    void valueChanged(uint);

protected:
    QCheckBox  m_BitCheckBoxes[32];
};


class BitFieldEditor : public VariableWidgetEditor
{
public:
    BitFieldEditor();

    virtual void setValue(const void* a_pSrc) const;
    virtual void getValue(void* a_pDest) const;
};


} // qt 
} // phantom 


o_classNS((phantom, qt), BitFieldEditor, (VariableWidgetEditor), o_no_copy)
{
	o_reflection
	{
		
	};
};
o_exposeN((phantom, qt), BitFieldChecker);


#endif // o_qt_BitFieldEditor_h__
