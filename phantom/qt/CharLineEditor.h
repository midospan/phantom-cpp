#ifndef ghost_gui_CharLineEditor_h__
#define ghost_gui_CharLineEditor_h__


/* ****************** Includes ******************* */
#include <phantom/qt/VariableWidgetEditor.h>
/* **************** Declarations ***************** */
class QWidget;
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export CharLineEditor : public VariableWidgetEditor
{
public:
    CharLineEditor();

public:
    virtual void setValue(const void* a_pSrc) const;
    virtual void getValue(void* a_pDest) const;
};

class o_qt_export UCharLineEditor : public VariableWidgetEditor
{
public:
    UCharLineEditor();

public:
    virtual void setValue(const void* a_pSrc) const;
    virtual void getValue(void* a_pDest) const;
};

}}

o_classNS((phantom, qt), CharLineEditor, (VariableWidgetEditor))
{
    o_reflection
    {
    };
};
o_exposeN((phantom, qt), CharLineEditor);

o_classNS((phantom, qt), UCharLineEditor, (VariableWidgetEditor))
{
    o_reflection
    {
    };
};
o_exposeN((phantom, qt), UCharLineEditor);

#endif // ghost_gui_CharLineEditor_h__