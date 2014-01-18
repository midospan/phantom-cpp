/* ******************* Includes ****************** */
#include <phantom/qt/qt.h>
#include "ModuleExplorer.h"
#include "phantom/ModuleLoader.h"
#include <QDir>
#include <QFileInfo>
#include <windows.h>
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom, qt), ModuleExplorer);

namespace phantom { namespace qt {

    class ModuleItem : public QTreeWidgetItem
    {
        friend class ModuleExplorer;

    public:
        ModuleItem(ModuleExplorer* a_pModuleExplorer, const QString& absolutePath);
    
        void updateLook();

    protected:
        QString m_strAbsolutePath;
        ModuleExplorer* m_pModuleExplorer;
    };

    ModuleExplorer::ModuleExplorer( void ) 
        : m_LoadedIcon(":/../../bin/resources/icons/plugin.png")
        , m_UnloadedIcon(":/../../bin/resources/icons/plugin_disabled.png")
        , m_pRootMessage(nullptr)
        , m_pModuleLoader(nullptr)
    {
        setColumnCount(1);
        QStringList headerLabels;
        headerLabels.append("Module");
        setHeaderLabels(headerLabels);
    }

    void ModuleExplorer::setPath( const string& a_strPath )
    {
        if(m_strPath.size())
        {
            clear();
        }
        m_strPath = a_strPath;
        if(m_strPath.size())
        {
            QDir dir(m_strPath.c_str());
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
                QFileInfo fileInfo( (m_strPath + "/" + name).c_str() );
                ModuleItem* pItem = new ModuleItem(this, fileInfo.absoluteFilePath());
                addTopLevelItem(pItem);
            }
        }
    }
    
    ModuleExplorer::~ModuleExplorer( void )
    {

    }

    void ModuleExplorer::slotItemDoubleClicked( QTreeWidgetItem* a_pItem, int )
    {
        if(a_pItem == nullptr || m_pModuleLoader == nullptr) return;

        ModuleItem* pItem = ((ModuleItem*)a_pItem);
        Module* pModule = phantom::moduleByFileName(pItem->m_strAbsolutePath.toAscii().constData());
        if(m_pModuleLoader->hasLoadedModule(pModule))
        {
            m_pModuleLoader->unloadModule(pItem->m_strAbsolutePath.toAscii().constData(), m_pRootMessage);
        }
        else 
        {
            m_pModuleLoader->loadModule(pItem->m_strAbsolutePath.toAscii().constData(), m_pRootMessage);
        }
    }

    void ModuleExplorer::setModuleLoader( ModuleLoader* a_pModuleLoader )
    {
        if(m_pModuleLoader == a_pModuleLoader) return;
        if(m_pModuleLoader)
        {
            disconnect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slotItemDoubleClicked(QTreeWidgetItem*,int)));
            o_disconnect(m_pModuleLoader, moduleLoaded(const string&), this, moduleLoaded(const string&));
            o_disconnect(m_pModuleLoader, moduleUnloaded(const string&), this, moduleUnloaded(const string&));
        }
        m_pModuleLoader = a_pModuleLoader;
        if(m_pModuleLoader)
        {
            connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slotItemDoubleClicked(QTreeWidgetItem*,int)));
            o_connect(m_pModuleLoader, moduleLoaded(const string&), this, moduleLoaded(const string&));
            o_connect(m_pModuleLoader, moduleUnloaded(const string&), this, moduleUnloaded(const string&));
        }
        for(size_t i = 0; i<topLevelItemCount(); ++i)
        {
            static_cast<ModuleItem*>(topLevelItem(i))->updateLook();
        }
    }

    void ModuleExplorer::moduleLoaded( const string& a_strPath )
    {
        for(size_t i = 0; i<topLevelItemCount(); ++i)
        {
            static_cast<ModuleItem*>(topLevelItem(i))->updateLook();
        }
    }

    void ModuleExplorer::moduleUnloaded( const string& a_strPath )
    {
        for(size_t i = 0; i<topLevelItemCount(); ++i)
        {
            static_cast<ModuleItem*>(topLevelItem(i))->updateLook();
        }
    }

    void ModuleExplorer::setMessage( Message* a_pMessage )
    {
        m_pRootMessage = a_pMessage;
    }

    ModuleItem::ModuleItem( ModuleExplorer* a_pModuleExplorer, const QString& a_strAbsolutePath ) 
        : m_strAbsolutePath(a_strAbsolutePath)
        , m_pModuleExplorer(a_pModuleExplorer)
    {
        updateLook();
    }

    void ModuleItem::updateLook()
    {
        Module* pModule = phantom::moduleByFileName(m_strAbsolutePath.toAscii().constData());
        bool hasLoadedModule = m_pModuleExplorer->m_pModuleLoader ? m_pModuleExplorer->m_pModuleLoader->hasLoadedModule(m_strAbsolutePath.toAscii().constData()) : false;
        setIcon(0, hasLoadedModule ? m_pModuleExplorer->m_LoadedIcon : m_pModuleExplorer->m_UnloadedIcon);
        QFileInfo fileInfo( m_strAbsolutePath );
        setText(0, fileInfo.baseName());

    }
    
}}