#ifndef phantom_qt_StringLineEditor_h__
#define phantom_qt_StringLineEditor_h__


/* ****************** Includes ******************* */
#include <phantom/qt/VariableWidgetEditor.h>
/* **************** Declarations ***************** */
class QWidget;
o_declareN(class, (phantom, qt), StringLineEditor);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export StringLineEditor : public VariableWidgetEditor
{
public:
    StringLineEditor();

public:
    virtual void setValue(const void* a_pSrc) const;
    virtual void getValue(void* a_pDest) const;
};

}}

#endif // phantom_qt_StringLineEditor_h__