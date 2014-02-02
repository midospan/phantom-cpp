/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "NumberLineEditor.h"
#include "NumberLineEditor.hxx"
#include <QtGui/QLineEdit>
/* *********************************************** */
o_registerN((phantom, qt), NumberLineEditor);
o_registerNT((phantom, qt), (typename), (t_Ty), TNumberLineEditor);

o_registerNTI((phantom, qt), TNumberLineEditor, (phantom::uchar));
o_registerNTI((phantom, qt), TNumberLineEditor, (short));
o_registerNTI((phantom, qt), TNumberLineEditor, (phantom::ushort));
o_registerNTI((phantom, qt), TNumberLineEditor, (int));
o_registerNTI((phantom, qt), TNumberLineEditor, (phantom::uint));
o_registerNTI((phantom, qt), TNumberLineEditor, (long));
o_registerNTI((phantom, qt), TNumberLineEditor, (phantom::ulong));
o_registerNTI((phantom, qt), TNumberLineEditor, (phantom::longlong));
o_registerNTI((phantom, qt), TNumberLineEditor, (phantom::ulonglong));
o_registerNTI((phantom, qt), TNumberLineEditor, (float));
o_registerNTI((phantom, qt), TNumberLineEditor, (double));

namespace phantom { namespace qt {

NumberLineEditor::NumberLineEditor(reflection::Type* a_pType)
: VariableWidgetEditor(new QLineEdit, SIGNAL(returnPressed()), a_pType)
{
}

}}
