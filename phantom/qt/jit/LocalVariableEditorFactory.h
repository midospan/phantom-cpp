#ifndef phantom_qt_LocalVariableEditorFactory_h__
#define phantom_qt_LocalVariableEditorFactory_h__


/* ****************** Includes ******************* */
#include "phantom/qt/jit/qt_jit.h"
#include "phantom/qt/VariableEditorFactory.h"
/* **************** Declarations ***************** */

/* *********************************************** */

namespace phantom { 
namespace qt {
namespace jit {

class LocalVariableEditor;

class o_qt_jit_export LocalVariableEditorFactory : public VariableEditorFactory
{
    Q_OBJECT

public:
	LocalVariableEditorFactory(void);
	~LocalVariableEditorFactory(void) {}

    virtual QWidget* createEditor(VariableManager *manager, QtProperty *property, QWidget *parent);
	

};


} // qt 
} // phantom 
}

o_classNS((phantom, qt, jit), LocalVariableEditorFactory, (VariableEditorFactory), o_no_copy)
{
	o_reflection
	{
		
	};
};
o_exposeN((phantom, qt, jit), LocalVariableEditorFactory);


#endif // phantom_qt_LocalVariableEditorFactory_h__
