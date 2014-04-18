#ifndef phantom_qt_LocalVariableEditor_h__
#define phantom_qt_LocalVariableEditor_h__


/* ****************** Includes ******************* */
#include "phantom/qt/jit/qt_jit.h"
#include "phantom/qt/VariableEditor.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt, jit), LocalVariableEditor);
/* *********************************************** */

namespace phantom { 
    
namespace qt {

namespace jit {

class LocalVariableModel;
class o_qt_jit_export LocalVariableEditor : public VariableEditor
{
    Q_OBJECT

public:
	LocalVariableEditor(void);
	~LocalVariableEditor(void) {}

    LocalVariableModel* getLocalVariableModel() const;

protected:
    virtual void updateItemLook(QtBrowserItem *item);

protected slots:
    void setCallStackIndex(int index);

};

} // jit
} // qt 
} // phantom 

#endif // phantom_qt_LocalVariableEditor_h__
