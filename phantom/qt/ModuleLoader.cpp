/* ******************* Includes ****************** */
#include <phantom/qt/qt.h>
#include "ModuleLoader.h"
#include <QDir>
#include <QFileInfo>
#include <windows.h>
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom, qt), ModuleLoader);

namespace phantom { namespace qt {

    class ModuleItem : public QTreeWidgetItem
    {
        friend class ModuleLoader;

    public:
        ModuleItem(ModuleLoader* a_pModuleLoader, const QString& absolutePath);
    
        void updateLook();

    protected:
        QString m_strAbsolutePath;
        ModuleLoader* m_pModuleLoader;
    };

    ModuleLoader::ModuleLoader( const QString& a_strPath, Message* a_pRootMessage ) 
        : m_strPath( a_strPath )
        , m_LoadedIcon(":/../../bin/resources/icons/plugin.png")
        , m_UnloadedIcon(":/../../bin/resources/icons/plugin_disabled.png")
        , m_pRootMessage(a_pRootMessage)
    {
        setColumnCount(1);
        QStringList headerLabels;
        headerLabels.append("Message");
        setHeaderLabels(headerLabels);
        connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slotItemDoubleClicked(QTreeWidgetItem*,int)));
    }

    o_initialize_cpp(ModuleLoader)
    {
        QDir dir(m_strPath);
        QStringList pluginNames = dir.entryList(QDir::Files|QDir::NoDotAndDotDot, QDir::Name);
        QStringList::iterator it = pluginNames.begin();
        QStringList::iterator end = pluginNames.end();
        for(it; it != end; it++)
        {
            string name = it->toAscii().constData();
            size_t extensionPos = name.find_first_of('.');
            if(extensionPos == string::npos OR name.substr(extensionPos+1) != "dll")
            {
                continue;
            }
            QFileInfo fileInfo( m_strPath + "/" + name.c_str() );
            ModuleItem* pItem = new ModuleItem(this, fileInfo.absoluteFilePath());
            addTopLevelItem(pItem);
        }
    }

    ModuleLoader::~ModuleLoader( void )
    {

    }


    void ModuleLoader::slotItemDoubleClicked( QTreeWidgetItem* a_pItem, int )
    {
        if(a_pItem == nullptr) return;

        ModuleItem* pItem = ((ModuleItem*)a_pItem);
        Module* pModule = phantom::moduleByFileName(pItem->m_strAbsolutePath.toAscii().constData());
        Message* pMessageUnloadFailed = nullptr;
        if(pModule)
        {
            bool canUnload = true;
            for(auto it = pModule->beginLanguageElements(); it != pModule->endLanguageElements(); ++it)
            {
                reflection::Class* pClass = (*it)->asClass();
                if(pClass)
                {
                    if(pClass->getInstanceCount() != 0)
                    {
                        canUnload = false;
                        if(m_pRootMessage)
                        {
                            if(pMessageUnloadFailed == nullptr) 
                                pMessageUnloadFailed = m_pRootMessage->error("Cannot unload module : %s", a_pItem->text(0).toAscii().constData());
                            pMessageUnloadFailed->error("Class still used : %s", pClass->getQualifiedDecoratedName().c_str());
                        }
                        else return;
                    }
                }
            }

            if(!canUnload)
                return;

            if(FreeLibrary((HMODULE)pModule->getPlatformHandle()))
            {
                if(m_pRootMessage) m_pRootMessage->success("Module unloaded : %s", a_pItem->text(0).toAscii().constData());
            }
            else
            {
                if(m_pRootMessage)
                {
                    if(pMessageUnloadFailed == nullptr) pMessageUnloadFailed = m_pRootMessage->error("Cannot unload module : %s", a_pItem->text(0).toAscii().constData());
                    LPVOID lpMsgBuf;
                    LPVOID lpDisplayBuf;
                    DWORD dw = GetLastError(); 

                    FormatMessage(
                        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                        FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        dw,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR) &lpMsgBuf,
                        0, NULL );

                    string clampedMessage = (char*)lpMsgBuf;
                    clampedMessage = clampedMessage.substr(0, clampedMessage.find_first_of("\r\n"));

                    pMessageUnloadFailed->error("System DLL unloading failed : %s", clampedMessage.c_str());

                    LocalFree(lpMsgBuf);
                }
            }
        }
        else 
        {
            if(LoadLibrary(pItem->m_strAbsolutePath.toAscii().constData()))
            {
                if(m_pRootMessage) m_pRootMessage->success("Module loaded : %s", a_pItem->text(0).toAscii().constData());
            }
            else
            {
                if(m_pRootMessage)
                {
                    if(pMessageUnloadFailed == nullptr) pMessageUnloadFailed = m_pRootMessage->error("Cannot load module : %s", a_pItem->text(0).toAscii().constData());
                    LPVOID lpMsgBuf;
                    LPVOID lpDisplayBuf;
                    DWORD dw = GetLastError(); 

                    FormatMessage(
                        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                        FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        dw,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR) &lpMsgBuf,
                        0, NULL );

                    string clampedMessage = (char*)lpMsgBuf;
                    clampedMessage = clampedMessage.substr(0, clampedMessage.find_first_of("\r\n"));
                    pMessageUnloadFailed->error("System DLL loading failed : %s", clampedMessage.c_str());

                    LocalFree(lpMsgBuf);
                }
            }
        }
        for(size_t i = 0; i<topLevelItemCount(); ++i)
        {
            static_cast<ModuleItem*>(topLevelItem(i))->updateLook();
        }
    }


    ModuleItem::ModuleItem( ModuleLoader* a_pModuleLoader, const QString& a_strAbsolutePath ) 
        : m_strAbsolutePath(a_strAbsolutePath)
        , m_pModuleLoader(a_pModuleLoader)
    {
        updateLook();
    }

    void ModuleItem::updateLook()
    {
        Module* pModule = phantom::moduleByFileName(m_strAbsolutePath.toAscii().constData());

        setIcon(0, pModule ? m_pModuleLoader->m_LoadedIcon : m_pModuleLoader->m_UnloadedIcon);
        QFileInfo fileInfo( m_strAbsolutePath );
        setText(0, fileInfo.baseName());

    }
    
}}