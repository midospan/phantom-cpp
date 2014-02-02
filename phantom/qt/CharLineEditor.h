#ifndef phantom_qt_CharLineEditor_h__
#define phantom_qt_CharLineEditor_h__


/* ****************** Includes ******************* */
#include <phantom/qt/VariableWidgetEditor.h>
/* **************** Declarations ***************** */
class QWidget;
o_declareN(class, (phantom, qt), CharLineEditor);
o_declareN(class, (phantom, qt), UCharLineEditor);
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

#endif // phantom_qt_CharLineEditor_h__