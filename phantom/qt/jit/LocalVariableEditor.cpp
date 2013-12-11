/* ******************* Includes ****************** */
#include "phantom/qt/jit/qt_jit.h"
#include "LocalVariableEditor.h"
#include "LocalVariableManager.h"
/* *********************************************** */
o_registerN((phantom, qt, jit), LocalVariableEditor);

 
namespace phantom { 
    namespace qt {
        namespace jit {

    LocalVariableEditor::LocalVariableEditor( void ) 
        : VariableEditor(o_new(LocalVariableManager), "Expression")
    {
        setEnabled(false);
    }

    void LocalVariableEditor::setCallStackIndex( int index )
    {
        static_cast<LocalVariableManager*>(m_pManager)->setCallStackIndex(index);
    }

    void LocalVariableEditor::updateItemLook( QtBrowserItem *item )
    {
        VariableEditor::updateItemLook(item);
        QTreeWidgetItem* pTreeItem = browserItemToItem(item);
        QFont font = pTreeItem->font(0);
        auto pVariable = m_pManager->getVariable(item->property());
        if(item->property()->propertyName() == "this" && pVariable)
        {
            font.setBold(true);
        }
        else 
        {
            font.setBold(false);
        }
        pTreeItem->setFont(0, font);
        if(pVariable == nullptr 
            AND NOT(item->property()->propertyName().isEmpty()) 
            AND getLocalVariableManager()->isWatchProperty(item->property()))
        {
            setBackgroundColor(item, QColor(255,0,0,64));
        }
        else 
        {
            setBackgroundColor(item, calculatedBackgroundColor(item));
        }
    }

    LocalVariableManager* LocalVariableEditor::getLocalVariableManager() const
    {
        return static_cast<LocalVariableManager*>(m_pManager);
    }

}}}