

#ifndef ModuleLoader_h__
#define ModuleLoader_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <QTreeWidget>
#include <phantom/util/Message.h>
/* **************** Declarations ***************** */
/* *********************************************** */
namespace phantom { 

class Message;

namespace qt {

class ModuleItem;
class o_qt_export ModuleLoader : public QTreeWidget
{
    Q_OBJECT

    friend class ModuleItem;

public:
    ModuleLoader(const QString& a_strPath, Message* a_pRootMessage = nullptr);
    ~ModuleLoader(void);

    o_initialize();

protected:
    void moduleInstanciated(void* a_pModule) {}
    void moduleDestroyed(void* a_pModule) {}

protected slots:
    void slotItemDoubleClicked(QTreeWidgetItem*, int);

protected:
    QString m_strPath;
    QIcon m_LoadedIcon;
    QIcon m_UnloadedIcon;
    phantom::Message* m_pRootMessage;

};

}}


o_classN((phantom, qt), ModuleLoader, o_no_copy)
{
    o_reflection
    {
        o_slot(void, moduleInstanciated, (void*));
        o_slot(void, moduleDestroyed, (void*));
    };
};
o_exposeN((phantom, qt), ModuleLoader);

#endif