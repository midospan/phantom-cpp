/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "StringLineEditor.h"
#include <QtGui/QLineEdit>
/* *********************************************** */
o_registerN((phantom, qt), StringLineEditor);

namespace phantom { namespace qt {

StringLineEditor::StringLineEditor()
: VariableWidgetEditor(new QLineEdit, SIGNAL(returnPressed()), typeOf<string>())
{
}

void StringLineEditor::setValue( const void* a_pSrc ) const
{
    string str = *((string*)a_pSrc);
    static_cast<QLineEdit*>(m_pWidget)->setText(str.c_str());
}

void StringLineEditor::getValue( void* a_pDest ) const
{
    *((string*)a_pDest) = static_cast<QLineEdit*>(m_pWidget)->text().toAscii().constData();
}

}}
