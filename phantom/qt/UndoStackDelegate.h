#ifndef o_phantom_qt_UndoStackDelegate_h__
#define o_phantom_qt_UndoStackDelegate_h__


/* ****************** Includes ******************* */
#include <phantom/qt/qt.h>
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, qt)

class ModuleExplorer;
class DataTreeView;
class VariableEditor;
class VariableNode;
class UndoCommand;
class UndoStack;

class o_qt_export UndoStackDelegate
{
public:
    UndoStackDelegate(phantom::qt::UndoStack* a_pUndoStack, phantom::Message* a_pMessage)
        : m_pUndoStack(a_pUndoStack)
        , m_pMessage(a_pMessage)
    {

    }

    void loadLibrary(phantom::qt::ModuleExplorer* a_pModuleExplorer, const phantom::string& a_strPath);

    void unloadLibrary(phantom::qt::ModuleExplorer* a_pModuleExplorer, const phantom::string& a_strPath);

protected:
    phantom::qt::UndoStack* m_pUndoStack;
    phantom::Message*       m_pMessage;
};

o_namespace_end(phantom, qt)

#endif // o_phantom_qt_UndoStackDelegate_h__
