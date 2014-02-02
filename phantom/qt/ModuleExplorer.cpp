/* ******************* Includes ****************** */
#include <phantom/qt/qt.h>
#include "ModuleExplorer.h"
#include "ModuleExplorer.hxx"
#include "phantom/ModuleLoader.h"
#include <QDir>
#include <QFileInfo>
#include <windows.h>
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom, qt), ModuleExplorer);

namespace phantom { namespace qt {

    class LibraryItem : public QTreeWidgetItem
    {
        friend class ModuleExplorer;

    public:
        LibraryItem(ModuleExplorer* a_pModuleExplorer, const QString& absolutePath);
    
        void updateLook();

        const QString& getAbsolutePath() const { return m_strAbsolutePath; }

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
        setColumnCount(2);
        QStringList headerLabels;
        headerLabels.append("Module");
        headerLabels.append("Loads");
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
                LibraryItem* pItem = new LibraryItem(this, fileInfo.absoluteFilePath());
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

        LibraryItem* pItem = ((LibraryItem*)a_pItem);
        if(m_pModuleLoader->isLibraryLoaded(pItem->m_strAbsolutePath.toAscii().constData()))
        {
            m_pModuleLoader->unloadLibrary(pItem->m_strAbsolutePath.toAscii().constData(), m_pRootMessage);
        }
        else 
        {
            m_pModuleLoader->loadLibrary(pItem->m_strAbsolutePath.toAscii().constData(), m_pRootMessage);
        }
    }

    void ModuleExplorer::setModuleLoader( ModuleLoader* a_pModuleLoader )
    {
        if(m_pModuleLoader == a_pModuleLoader) return;
        if(m_pModuleLoader)
        {
            disconnect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slotItemDoubleClicked(QTreeWidgetItem*,int)));
            o_disconnect(m_pModuleLoader, libraryLoaded(const string&), this, libraryLoaded(const string&));
            o_disconnect(m_pModuleLoader, libraryUnloaded(const string&), this, libraryUnloaded(const string&));
            o_disconnect(m_pModuleLoader, moduleLoaded(Module*, size_t, size_t), this, moduleLoaded(Module*, size_t, size_t));
            o_disconnect(m_pModuleLoader, moduleUnloaded(Module*, size_t, size_t), this, moduleUnloaded(Module*, size_t, size_t));
        }
        m_pModuleLoader = a_pModuleLoader;
        if(m_pModuleLoader)
        {
            connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slotItemDoubleClicked(QTreeWidgetItem*,int)));
            o_connect(m_pModuleLoader, libraryLoaded(const string&), this, libraryLoaded(const string&));
            o_connect(m_pModuleLoader, libraryUnloaded(const string&), this, libraryUnloaded(const string&));
            o_connect(m_pModuleLoader, moduleLoaded(Module*, size_t, size_t), this, moduleLoaded(Module*, size_t, size_t));
            o_connect(m_pModuleLoader, moduleUnloaded(Module*, size_t, size_t), this, moduleUnloaded(Module*, size_t, size_t));
        }
        for(size_t i = 0; i<topLevelItemCount(); ++i)
        {
            static_cast<LibraryItem*>(topLevelItem(i))->updateLook();
        }
    }

    void ModuleExplorer::libraryLoaded( const string& a_strPath )
    {
        for(size_t i = 0; i<topLevelItemCount(); ++i)
        {
            static_cast<LibraryItem*>(topLevelItem(i))->updateLook();
        }
    }

    void ModuleExplorer::libraryUnloaded( const string& a_strPath )
    {
        for(size_t i = 0; i<topLevelItemCount(); ++i)
        {
            static_cast<LibraryItem*>(topLevelItem(i))->updateLook();
        }
    }

    void ModuleExplorer::setMessage( Message* a_pMessage )
    {
        m_pRootMessage = a_pMessage;
    }

    LibraryItem* ModuleExplorer::getItem( const QString& absolutePath ) const
    {
        for(size_t i = 0; i<topLevelItemCount(); ++i)
        {
            if(static_cast<LibraryItem*>(topLevelItem(i))->getAbsolutePath() == absolutePath)
                return static_cast<LibraryItem*>(topLevelItem(i));
        }
        return nullptr;
    }

    void ModuleExplorer::moduleLoaded( Module* a_pModule, size_t, size_t a_uiLoadCount )
    {
        QFileInfo fileInfo( a_pModule->getFileName().c_str() );
        LibraryItem* pItem = getItem(fileInfo.absoluteFilePath());
        if(pItem)
        {
            pItem->setText(1, QString::number(a_uiLoadCount));
        }
    }

    void ModuleExplorer::moduleUnloaded( Module* a_pModule, size_t, size_t a_uiLoadCount )
    {
        QFileInfo fileInfo( a_pModule->getFileName().c_str() );
        LibraryItem* pItem = getItem(fileInfo.absoluteFilePath());
        if(pItem)
        {
            pItem->setText(1, QString::number(a_uiLoadCount));
        }
    }

    LibraryItem::LibraryItem( ModuleExplorer* a_pModuleExplorer, const QString& a_strAbsolutePath ) 
        : m_strAbsolutePath(a_strAbsolutePath)
        , m_pModuleExplorer(a_pModuleExplorer)
    {
        updateLook();
        setText(1, QString::number(0));
    }

    void LibraryItem::updateLook()
    {
        bool isLibraryLoaded = m_pModuleExplorer->m_pModuleLoader 
                                ? m_pModuleExplorer->m_pModuleLoader->isLibraryLoaded(m_strAbsolutePath.toAscii().constData()) 
                                : false;
        setIcon(0, isLibraryLoaded ? m_pModuleExplorer->m_LoadedIcon : m_pModuleExplorer->m_UnloadedIcon);
        QFileInfo fileInfo( m_strAbsolutePath );
        setText(0, fileInfo.baseName());
        Module* pModule = phantom::moduleByFileName(m_strAbsolutePath.toAscii().constData());
        if(pModule && m_pModuleExplorer->m_pModuleLoader)
        {
            setText(1, QString::number(m_pModuleExplorer->m_pModuleLoader->getModuleLoadCount(pModule)));
        }
        else 
        {
            setText(1, QString::number(0));
        }
    }
    
}}