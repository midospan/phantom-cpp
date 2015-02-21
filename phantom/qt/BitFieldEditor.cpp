/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "phantom/phantom.hxx"
#include "BitFieldEditor.h"
#include "BitFieldEditor.hxx"
/* *********************************************** */
o_registerN((phantom, qt), BitFieldEditor);
 
namespace phantom { 
namespace qt {

    BitFieldChecker::BitFieldChecker( uint initialValue )
    {
        setValue(initialValue);
        QHBoxLayout* l = new QHBoxLayout; 
        setLayout(l);
        for(int i = 0; i<32; ++i)
        {
            if(i%8 == 0 && i != 0) 
                l->addSpacerItem(new QSpacerItem(10,16));
            l->addWidget(&m_BitCheckBoxes[i], 16, Qt::AlignLeft);
            connect(&m_BitCheckBoxes[i], SIGNAL(stateChanged(int)), this, SLOT(bitCheckBoxChanged(int)));
        }
        l->setSpacing(0);
        QMargins margins = l->contentsMargins();
        margins.setLeft(4);
        margins.setRight(2000);
        margins.setTop(4);
        margins.setBottom(4);
        l->setContentsMargins(margins);
        l->setSizeConstraint(QLayout::SetFixedSize);
    }

    void BitFieldChecker::setValue( uint mask )
    {
        for(int i = 0; i<32; ++i)
        {
            m_BitCheckBoxes[31-i].setChecked(((1<<i)&mask) != 0);
        }
    }

    uint BitFieldChecker::getValue() const
    {
        uint mask = 0;
        for(int i = 0; i<32; ++i)
        {
            mask |= ((1<<i) * m_BitCheckBoxes[31-i].isChecked());
        }
        return mask;
    }


    BitFieldEditor::BitFieldEditor()
        : VariableWidgetEditor(new BitFieldChecker(0), SIGNAL(valueChanged(uint)), typeOf<modifiers_t>())
    {

    }

    void BitFieldEditor::setValue( const void* a_pSrc ) const
    {
        modifiers_t bf = *((modifiers_t*)a_pSrc);
        ((BitFieldChecker*)m_pWidget)->setValue(bf);
    }

    void BitFieldEditor::getValue( void* a_pDest ) const
    {
        uint value = ((BitFieldChecker*)m_pWidget)->getValue();
        *((modifiers_t*)a_pDest) = value;
    }

}}