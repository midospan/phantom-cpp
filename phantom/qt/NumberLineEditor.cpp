/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "NumberLineEditor.h"
#include <QtGui/QLineEdit>
/* *********************************************** */
o_registerN((phantom, qt), NumberLineEditor);
o_registerNT((phantom, qt), (typename), (t_Ty), TNumberLineEditor);

namespace phantom { namespace qt {

NumberLineEditor::NumberLineEditor(reflection::Type* a_pType)
: VariableWidgetEditor(new QLineEdit, SIGNAL(returnPressed()), a_pType)
{
}

}}
