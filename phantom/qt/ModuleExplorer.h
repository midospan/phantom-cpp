

#ifndef ModuleExplorer_h__
#define ModuleExplorer_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <QTreeWidget>
#include <phantom/util/Message.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ModuleExplorer);
/* *********************************************** */
namespace phantom { 

class Message;
class ModuleLoader;

namespace qt {

class LibraryItem;
class UndoStack;

class o_qt_export ModuleExplorer : public QTreeWidget
{
    Q_OBJECT

    friend class LibraryItem;

public:
    typedef fastdelegate::FastDelegate<void(const string& a_strPath)> delegate_t;

public:
    ModuleExplorer(void);
    ~ModuleExplorer(void);

    UndoStack* getUndoStack() const {return m_pUndoStack;}
    void setUndoStack(UndoStack* a_pUndoStack);
    void setDataBase(serialization::DataBase* a_pDataBase);
    void setMessage(Message* a_pMessage);
    void setPath(const string& a_strPath);
    void setModuleLoader(ModuleLoader* a_pModuleLoader);
    LibraryItem* getItem(const QString& absolutePath) const;
    ModuleLoader*   getModuleLoader() const { return m_pModuleLoader; }

    Message* getMessage() const { return m_pRootMessage; }

    void setPreUnloadLibraryDelegate(delegate_t a_Delegate);
    void setUnloadLibraryDelegate(delegate_t a_Delegate);
    void setLoadLibraryDelegate(delegate_t a_Delegate);

protected:
    void defaultUnloadLibrary(const string& a_strPath) const;
    void defaultLoadLibrary(const string& a_strPath) const;
    void undoableLoadLibrary(const phantom::string& a_strPath) const;
    void undoableUnloadLibrary(const phantom::string& a_strPath) const;
    void libraryLoaded(const string& a_strPath);
    void libraryUnloaded(const string& a_strPath);
    void moduleLoaded(Module* a_pModule, size_t, size_t a_uiLoadCount);
    void moduleUnloaded(Module* a_pModule, size_t, size_t a_uiLoadCount);
    virtual void loadLibrary(const string& a_strPath);
    virtual void unloadLibrary(const string& a_strPath);

protected slots:
    void slotItemDoubleClicked(QTreeWidgetItem*, int);

protected:
    string m_strPath;
    QIcon m_LoadedIcon;
    QIcon m_UnloadedIcon;
    Message* m_pRootMessage;
    UndoStack* m_pUndoStack;
    ModuleLoader* m_pModuleLoader;
    delegate_t m_LoadDelegate;
    delegate_t m_UnloadDelegate;
    delegate_t m_PreUnloadLibraryDelegate;
    serialization::DataBase* m_pDataBase;
};

}}

#endif