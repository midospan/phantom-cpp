

#ifndef ModuleExplorer_h__
#define ModuleExplorer_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <QTreeWidget>
#include <phantom/util/Message.h>
/* **************** Declarations ***************** */
/* *********************************************** */
namespace phantom { 

class Message;
class ModuleLoader;

namespace qt {

class ModuleItem;
class o_qt_export ModuleExplorer : public QTreeWidget
{
    Q_OBJECT

    friend class ModuleItem;

public:
    ModuleExplorer(void);
    ~ModuleExplorer(void);

    void setMessage(Message* a_pMessage);
    void setPath(const string& a_strPath);
    void setModuleLoader(ModuleLoader* a_pModuleLoader);

protected:
    void moduleLoaded(const string& a_strPath);
    void moduleUnloaded(const string& a_strPath);

protected slots:
    void slotItemDoubleClicked(QTreeWidgetItem*, int);

protected:
    o_signal_data(moduleAboutToBeLoaded);
    o_signal_data(moduleLoaded);
    o_signal_data(moduleLoadFailed);
    o_signal_data(moduleAboutToBeUnloaded);
    o_signal_data(moduleUnloaded);
    o_signal_data(moduleUnloadFailed);

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
        o_slot(void, moduleLoaded, (const string&));
        o_slot(void, moduleUnloaded, (const string&));
    };
};
o_exposeN((phantom, qt), ModuleExplorer);

#endif