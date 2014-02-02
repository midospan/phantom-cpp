/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "CharLineEditor.h"
#include "CharLineEditor.hxx"
#include <QtGui/QLineEdit>
/* *********************************************** */
o_registerN((phantom, qt), CharLineEditor);

namespace phantom { namespace qt {

CharLineEditor::CharLineEditor()
: VariableWidgetEditor(new QLineEdit, SIGNAL(returnPressed()), typeOf<char>())
{
    ((QLineEdit*)m_pWidget)->setMaxLength(1);
}

void CharLineEditor::setValue( const void* a_pSrc ) const
{
    char str[2] = { *((char*)a_pSrc), 0};
    static_cast<QLineEdit*>(m_pWidget)->setText(str);
}

void CharLineEditor::getValue( void* a_pDest ) const
{
    *((char*)a_pDest) = *static_cast<QLineEdit*>(m_pWidget)->text().toAscii().constData();
}


UCharLineEditor::UCharLineEditor()
    : VariableWidgetEditor(new QLineEdit, SIGNAL(returnPressed()), typeOf<char>())
{
    ((QLineEdit*)m_pWidget)->setMaxLength(1);
}

void UCharLineEditor::setValue( const void* a_pSrc ) const
{
    char str[2] = { (char)(*((unsigned char*)a_pSrc)), 0};
    static_cast<QLineEdit*>(m_pWidget)->setText(str);
}

void UCharLineEditor::getValue( void* a_pDest ) const
{
    *((unsigned char*)a_pDest) = (unsigned char)*static_cast<QLineEdit*>(m_pWidget)->text().toAscii().constData();
}

}}
