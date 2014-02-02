#ifndef phantom_qt_CallStackView_h__
#define phantom_qt_CallStackView_h__


/* ****************** Includes ******************* */
#include <QTreeWidget>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CallStackView);
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

#endif // phantom_qt_CallStackView_h__
