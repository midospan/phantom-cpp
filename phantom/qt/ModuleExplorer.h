

#ifndef ModuleExplorer_h__
#define ModuleExplorer_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <QTreeWidget>
#include <phantom/Message.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ModuleExplorer);
/* *********************************************** */
class QFileSystemWatcher;

namespace phantom { 

class Message;

namespace qt {

class LibraryItem;
class UndoStack;

class o_qt_export ModuleExplorer : public QTreeWidget
{
    Q_OBJECT

    friend class LibraryItem;

public:
    typedef fastdelegate::FastDelegate<void(const string& a_strPath)> delegate_t;
    typedef fastdelegate::FastDelegate<bool(const string& a_strPath)> pre_delegate_t;

public:
    ModuleExplorer(void);
    ~ModuleExplorer(void);

    UndoStack* getUndoStack() const {return m_pUndoStack;}
    void setUndoStack(UndoStack* a_pUndoStack);
    void setDataBase(serialization::DataBase* a_pDataBase);
    void setMessage(Message* a_pMessage);
    void setPath(const string& a_strPath);
    const string& getPath() const { return m_strPath; }
    void setMetaDataPath(const string& a_strPath);
    void setApplication(reflection::Application* a_pApplication);
    LibraryItem* getItem(const QString& absolutePath) const;
    reflection::Application*   getApplication() const { return m_pApplication; }

    Message* getMessage() const { return m_pRootMessage; }

    void setPreUnloadLibraryDelegate(pre_delegate_t a_Delegate);
    void setUnloadLibraryDelegate(delegate_t a_Delegate);
    void setLoadLibraryDelegate(delegate_t a_Delegate);

protected:
    void defaultUnloadLibrary(const string& a_strPath) const;
    void defaultLoadLibrary(const string& a_strPath) const;
    void undoableLoadLibrary(const phantom::string& a_strPath) const;
    void undoableUnloadLibrary(const phantom::string& a_strPath) const;
    void libraryLoaded(const string& a_strPath);
    void libraryUnloaded(const string& a_strPath);
    void moduleLoaded(reflection::Module* a_pModule, size_t, size_t a_uiLoadCount);
    void moduleUnloaded(reflection::Module* a_pModule, size_t, size_t a_uiLoadCount);
    virtual void loadLibrary(const string& a_strPath);
    virtual void unloadLibrary(const string& a_strPath);
    void loadMetaData( reflection::Module* a_pModule );
    void loadMetaData( const string& metaDataFile);
    void loadMetaDataDefinition( const string& a_Key, const property_tree& a_PropertyTree, reflection::NamedElement* a_pScope );

protected slots:
    void slotItemDoubleClicked(QTreeWidgetItem*, int);
    string moduleMetaDataPath(reflection::Module* a_pModule);
    void loadMetaData();
    void reloadMetaData( const QString& metaDataFile)
    {
        loadMetaData(metaDataFile.toAscii().constData());
    }



protected:
    string m_strPath;
    string m_strMetaDataPath;
    QIcon m_LoadedIcon;
    QIcon m_UnloadedIcon;
    Message* m_pRootMessage;
    UndoStack* m_pUndoStack;
    reflection::Application* m_pApplication;
    delegate_t m_LoadDelegate;
    delegate_t m_UnloadDelegate;
    pre_delegate_t m_PreUnloadLibraryDelegate;
    serialization::DataBase* m_pDataBase;
    QFileSystemWatcher* m_pFileSystemWatcher;
};

}}

#endif