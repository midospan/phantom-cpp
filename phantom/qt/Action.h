#ifndef o_qt_Action_h__
#define o_qt_Action_h__

/* ****************** Includes ******************* */
#include <QtGui/QAction>
/* **************** Declarations ***************** */

namespace phantom { namespace qt {
    
class o_qt_export Action : public QAction
{
    Q_OBJECT
         
public:
    Action(QIcon a_Icon, const QString& a_strName, QObject* a_pParent);
    Action(QObject* a_pParent);
    ~Action();

    o_initialize();

protected slots:
    virtual void doAction() = 0;

};


}}

#endif // o_qt_Action_h__
