#ifndef o_qt_Action_h__
#define o_qt_Action_h__

/* ****************** Includes ******************* */
#include <QtGui/QAction>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), Action);
/* *********************************************** */

namespace phantom { namespace qt {
    
class o_qt_export Action : public QAction
{
    Q_OBJECT
         
public:
    Action(QIcon a_Icon, const QString& a_strName, QObject* a_pParent = nullptr);
    Action(QObject* a_pParent);
    ~Action();

    o_initialize();

    virtual void doAction() = 0;

protected:
    o_signal_data(aboutToBeDone);
    o_signal_data(done);

protected slots:
    void internalDoAction()
    {
        o_emit aboutToBeDone();
        doAction();
        o_emit done();
    }

};


}}

#endif // o_qt_Action_h__
