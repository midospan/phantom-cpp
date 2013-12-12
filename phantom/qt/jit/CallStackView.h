#ifndef phantom_qt_CallStackView_h__
#define phantom_qt_CallStackView_h__


/* ****************** Includes ******************* */
#include <QTreeWidget>
/* **************** Declarations ***************** */

/* *********************************************** */

namespace phantom { namespace qt {

class CallStackView : public QTreeWidget
{
    Q_OBJECT

public:
	CallStackView(void);
	~CallStackView(void) {}

    void activate();
    void deactivate();

    void selectCall(int index);

    int getCurrentCallIndex() const { return m_iCurrentCallIndex; }

protected slots:
    void slotItemDoubleClicked(QTreeWidgetItem* a_pItem, int a_iColumn);

signals:
    void callSelected(int i);

protected:
    int m_iCurrentCallIndex;
};


} // qt 
} // phantom 


o_classN((phantom, qt), CallStackView, o_no_copy)
{
	o_reflection
	{
        o_slot(void, activate, ());
        o_slot(void, deactivate, ());
	};
};
o_exposeN((phantom, qt), CallStackView);


#endif // phantom_qt_CallStackView_h__
