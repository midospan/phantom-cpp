/* ******************* Includes ****************** */
#include "phantom/qt/jit/qt_jit.h"
#include "LocalVariableEditorFactory.h"
#include "LocalVariableEditor.h"
/* *********************************************** */
o_registerN((phantom, qt, jit), LocalVariableEditorFactory);

 
namespace phantom { 
namespace qt {
namespace jit {

    LocalVariableEditorFactory::LocalVariableEditorFactory() 
    {

    }

    QWidget* LocalVariableEditorFactory::createEditor( VariableManager *manager, QtProperty *property, QWidget *parent )
    {
        return VariableEditorFactory::createEditor(manager, property, parent);
    }

}}}