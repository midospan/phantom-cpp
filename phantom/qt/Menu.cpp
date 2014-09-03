#include <phantom/qt/qt.h>
#include <phantom/qt/Menu.h>
#include <phantom/qt/Action.h>
#include <phantom/qt/Menu.hxx>

o_registerN((phantom, qt), Menu);
 
namespace phantom { namespace qt {

    Menu::Menu( QIcon a_Icon, const QString& a_strName, QWidget* a_pParent )
        : QMenu(a_strName, a_pParent)
    {
        setIcon(a_Icon);
    }

    Menu::Menu( QWidget* a_pParent )
        : QMenu(a_pParent)
    {
    }

    Menu::~Menu()
    {
        for(auto it = m_Actions.begin(); it != m_Actions.end(); ++it)
        {
            o_dynamic_delete *it;
        }
    }

    void Menu::addAction( Action* a_pAction )
    {
        QMenu::addAction(a_pAction);
        m_Actions.push_back(a_pAction);
    }

}}