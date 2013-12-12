/* ******************* Includes ****************** */
#include "phantom/qt/jit/qt_jit.h"
#include "CallStackView.h"
#include "phantom/reflection/jit/JitDebugger.h"
#include <QHeaderView>
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom, qt), CallStackView);

 
namespace phantom { 
namespace qt {

    CallStackView::CallStackView( void ) : m_iCurrentCallIndex(-1)
    {
        setEnabled(false);
        QStringList headerLabels;
        headerLabels.append("index");
        headerLabels.append("icon");
        headerLabels.append("call");
        headerLabels.append("location");
        setHeaderLabels(headerLabels);
        header()->setResizeMode(QHeaderView::ResizeToContents);
        setHeaderHidden(true);
        connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slotItemDoubleClicked(QTreeWidgetItem*, int)));
    }
    
    void CallStackView::activate()
    {
        o_assert(m_iCurrentCallIndex == -1);
        size_t callStackSize = phantom::reflection::jit::JitDebugger::Instance()->getCallStackSize();
        size_t i = 0;
        for(;i<callStackSize;++i)
        {
            QTreeWidgetItem* pItem = new QTreeWidgetItem;
            phantom::reflection::Subroutine* pSubroutine = phantom::reflection::jit::JitDebugger::Instance()->getCallStackSubroutine(i);
            QString callText = pSubroutine ? pSubroutine->getDecoratedName().c_str() : "native C++ call";
            phantom::reflection::SourceFile* pSourceFile = phantom::reflection::jit::JitDebugger::Instance()->getCallStackSourceFile(i);
            QString locationText = pSourceFile ? pSourceFile->getAbsoluteName().c_str() : "C/C++ Source";
            phantom::reflection::CodePosition callPosition = phantom::reflection::jit::JitDebugger::Instance()->getCallStackCodePosition(i);
            if(callPosition != phantom::reflection::CodePosition())
            {
                locationText += "(";
                locationText += QString::number(callPosition.line);
                locationText += ')';
            }
            pItem->setData(0, 0, i);
            pItem->setText(0, QString::number(i));
            pItem->setText(1, "");
            pItem->setText(2, callText);
            pItem->setText(3, locationText);
            insertTopLevelItem(i, pItem);
        }
        setEnabled(true);
        selectCall(0);
    }

    void CallStackView::deactivate()
    {
        selectCall(-1);
        clear();
        setEnabled(false);
    }

    void CallStackView::selectCall( int index )
    {
        printf("selectCall(%d)\n", index);
        if(index < -1 || index >= int(phantom::reflection::jit::JitDebugger::Instance()->getCallStackSize())) 
        {
            return;
        }
        if(index == m_iCurrentCallIndex) 
        {
            emit callSelected(index);
            return;
        }
        if(m_iCurrentCallIndex != -1)
        {
            topLevelItem(m_iCurrentCallIndex)->setIcon(1, QIcon());
        }
        m_iCurrentCallIndex = index;
        if(m_iCurrentCallIndex != -1)
        {
            topLevelItem(m_iCurrentCallIndex)->setIcon(1, QIcon("resources/icons/famfamfam/bug_go.png"));
        }
        emit callSelected(index);
    }

    void CallStackView::slotItemDoubleClicked( QTreeWidgetItem* a_pItem, int a_iColumn )
    {
        selectCall(a_pItem->data(0, 0).toUInt());
    }

}}
