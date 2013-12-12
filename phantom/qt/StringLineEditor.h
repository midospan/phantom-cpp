#ifndef phantom_qt_StringLineEditor_h__
#define phantom_qt_StringLineEditor_h__


/* ****************** Includes ******************* */
#include <phantom/qt/VariableWidgetEditor.h>
/* **************** Declarations ***************** */
class QWidget;
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

o_classNS((phantom, qt), StringLineEditor, (VariableWidgetEditor))
{
    o_reflection
    {
    };
};
o_exposeN((phantom, qt), StringLineEditor);

#endif // phantom_qt_StringLineEditor_h__