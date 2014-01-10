#include <phantom/qt/qt.h>
#include <phantom/qt/Action.h>

o_registerN((phantom, qt), Action);
 
namespace phantom { namespace qt {

    Action::Action( QIcon a_Icon, const QString& a_strName, QObject* a_pParent )
        : QAction(a_Icon, a_strName, a_pParent)
    {
        connect(this, SIGNAL(triggered()), this, SLOT(doAction()));
    }

    Action::Action( QObject* a_pParent )
        : QAction(a_pParent)
    {
        connect(this, SIGNAL(triggered()), this, SLOT(doAction()));
    }

    Action::~Action()
    {

    }

    o_initialize_cpp(Action)
    {
        reflection::Class* pClass = classOf(this);
        if(text().isEmpty())
        {
            string name = pClass->getMetaDataValue(getNameMetaDataIndex());
            setText(name.empty() ? pClass->getName().c_str() : name.c_str());
        }
        if(icon().isNull())
        {
            string icon = pClass->getMetaDataValue(getIconMetaDataIndex());
            setIcon(icon.empty() ? QIcon() : QIcon(icon.c_str()));
        }
    }
}}