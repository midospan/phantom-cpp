#include <phantom/qt/qt.h>
#include <phantom/qt/Action.h>
#include <phantom/qt/Action.hxx>

o_registerN((phantom, qt), Action);
 
namespace phantom { namespace qt {

    Action::Action( QIcon a_Icon, const QString& a_strName, QObject* a_pParent )
        : QAction(a_Icon, a_strName, a_pParent)
    {
        connect(this, SIGNAL(triggered()), this, SLOT(internalDoAction()));
    }

    Action::Action( QObject* a_pParent )
        : QAction(a_pParent)
    {
        connect(this, SIGNAL(triggered()), this, SLOT(internalDoAction()));
    }

    Action::~Action()
    {

    }

    o_initialize_cpp(Action)
    {
        reflection::Class* pClass = classOf(this);
        if(text().isEmpty())
        {
            setText(nameOf(pClass).c_str());
        }
        if(icon().isNull())
        {
            setIcon(QIcon(iconOf(pClass).c_str()));
        }
    }
}}