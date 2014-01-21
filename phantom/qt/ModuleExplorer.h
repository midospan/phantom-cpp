

#ifndef ModuleExplorer_h__
#define ModuleExplorer_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <QTreeWidget>
#include <phantom/util/Message.h>
/* **************** Declarations ***************** */
o_declare(class, phantom, Module);
/* *********************************************** */
namespace phantom { 

class Message;
class ModuleLoader;

namespace qt {

class LibraryItem;
class o_qt_export ModuleExplorer : public QTreeWidget
{
    Q_OBJECT

    friend class LibraryItem;

public:
    ModuleExplorer(void);
    ~ModuleExplorer(void);

    void setMessage(Message* a_pMessage);
    void setPath(const string& a_strPath);
    void setModuleLoader(ModuleLoader* a_pModuleLoader);
    LibraryItem* getItem(const QString& absolutePath) const;

protected:
    void libraryLoaded(const string& a_strPath);
    void libraryUnloaded(const string& a_strPath);
    void moduleLoaded(Module* a_pModule, size_t, size_t a_uiLoadCount);
    void moduleUnloaded(Module* a_pModule, size_t, size_t a_uiLoadCount);

protected slots:
    void slotItemDoubleClicked(QTreeWidgetItem*, int);

protected:
    string m_strPath;
    QIcon m_LoadedIcon;
    QIcon m_UnloadedIcon;
    Message* m_pRootMessage;
    ModuleLoader* m_pModuleLoader;

};

}}


o_classN((phantom, qt), ModuleExplorer, o_no_copy)
{
    o_reflection
    {
        o_slot(void, libraryLoaded, (const string&));
        o_slot(void, libraryUnloaded, (const string&));
        o_slot(void, moduleLoaded, (Module*, size_t, size_t));
        o_slot(void, moduleUnloaded, (Module*, size_t, size_t));
    };
};
o_exposeN((phantom, qt), ModuleExplorer);

#endif