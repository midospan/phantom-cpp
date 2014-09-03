#ifndef o_qt_Menu_h__
#define o_qt_Menu_h__

/* ****************** Includes ******************* */
#include <QtGui/QMenu>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), Menu);
/* *********************************************** */

namespace phantom { namespace qt {
    
class Action;

class o_qt_export Menu : public QMenu
{
    Q_OBJECT
         
public:
    Menu(QIcon a_Icon, const QString& a_strName, QWidget* a_pParent = nullptr);
    Menu(QWidget* a_pParent = nullptr);
    ~Menu();

    void addAction(Action* a_pAction);


protected:
    vector<Action*> m_Actions;
};


}}

#endif // o_qt_Menu_h__
