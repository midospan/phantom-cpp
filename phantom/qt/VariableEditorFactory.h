#ifndef ghost_gui_VariableEditorFactory_h__
#define ghost_gui_VariableEditorFactory_h__


/* ****************** Includes ******************* */
#include <QtGui/QLabel>
#include <QtGui/QToolButton>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
/* **************** Declarations ***************** */

/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export VariableEditorFactory : public QtAbstractEditorFactory<VariableManager>
{
    Q_OBJECT



};


} // qt 
} // phantom 


o_classN((phantom, qt), VariableEditorFactory, o_no_copy)
{
	o_reflection
	{
	};
};
o_exposeN((phantom, qt), VariableEditorFactory);


#endif // ghost_gui_VariableEditorFactory_h__
