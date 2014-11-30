#ifndef o_phantom_qt_UndoStackView_h__
#define o_phantom_qt_UndoStackView_h__


/* ****************** Includes ******************* */
#include <phantom/qt/qt.h>
#include <QTreeWidget>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), UndoStackView);
/* *********************************************** */

namespace phantom { namespace qt {

class UndoStack;
class UndoCommand;

class o_qt_export UndoStackView : public QTreeWidget
{
    Q_OBJECT

public:
	UndoStackView(void);
	~UndoStackView(void) {}
	
    void setUndoStack(UndoStack* a_pUndoStack);

protected:
    void commandAdded(UndoCommand* a_pUndoCommand);
    void commandAboutToBeRemoved(UndoCommand* a_pUndoCommand);

    QTreeWidgetItem* findCommandItem(UndoCommand* a_pUndoCommand, QTreeWidgetItem* a_pParentItem = nullptr) const;

protected slots:
    void slotCurrentItemChanged(QTreeWidgetItem* a_pCurrent, QTreeWidgetItem* a_pPrevious);
    
protected:
    UndoStack*  m_pUndoStack;
    QIcon       m_CurrentCommandIcon;
};

}}

#endif // o_phantom_qt_UndoStackView_h__
