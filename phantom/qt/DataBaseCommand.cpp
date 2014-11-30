/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "DataBaseCommand.h"
#include "DataBaseCommand.hxx"
#include <phantom/serialization/Record.h>
#include <phantom/reflection/Expression.h>
#include <phantom/Message.h>
/* *********************************************** */
o_registerN((phantom, qt), DataBaseCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

uint DataBaseCommand::sm_uiBackupId = 0xffffffff;
static size_t instanceCount = 0;

DataBaseCommand::DataBaseCommand(serialization::DataBase* a_pDataBase)
    : UndoCommand()
    , m_pDataBase(a_pDataBase)
    , m_bRecorded(false)
{
    o_assert(m_pDataBase);
    if(instanceCount == 0)
    {
        sm_uiBackupId = m_pDataBase->createBackup();
    }
    instanceCount++;
    m_pRecord = o_new(serialization::Record)(m_pDataBase, sm_uiBackupId);
}

DataBaseCommand::DataBaseCommand( const string& a_strName
    , serialization::DataBase* a_pDataBase )
    : UndoCommand(a_strName)
    , m_pDataBase(a_pDataBase)
    , m_bRecorded(false)
{
    o_assert(m_pDataBase);
    if(instanceCount == 0)
    {
        sm_uiBackupId = m_pDataBase->createBackup();
    }
    instanceCount++;
}

DataBaseCommand::~DataBaseCommand()
{
    instanceCount--;
    if(instanceCount == 0)
    {
        m_pDataBase->destroyBackup(sm_uiBackupId); 
    }
    o_delete(serialization::Record) m_pRecord;
}


//================================================
// Operations
//================================================


void DataBaseCommand::redo()
{
    // DO
    if(!m_bRecorded)
    {
        m_pRecord->startRecording();
        record();     
        m_pRecord->stopRecording();
        m_bRecorded = true;
    }
    else 
    {
        m_pRecord->startRedo();
        redoReplayed();     
        if(!m_pRecord->stopRedo())
        {
            Message* pMessage = topMessage("")->warning(data(), "Asymetric 'redo' produces different results from initial 'do'");
            UndoCommand* pCommand = this;
            Message* pChildMessage = nullptr;
            Message* pCommandMessage = nullptr;
            while(pCommand)
            {
                pCommandMessage = o_new(Message)(e_MessageType_Warning, pCommand->getName().c_str());
                if(pChildMessage)
                {
                    pCommandMessage->addChild(pChildMessage);
                }
                pChildMessage = pCommandMessage;
                pCommand = pCommand->getParent();
            }
            pMessage->warning(data(), "Fix the related code because this could lead to unintended undo/redo behavior");
        }
    }
}

void DataBaseCommand::undo()
{
    m_pRecord->startUndo();
    undoReplayed();      
    if(!m_pRecord->stopUndo())
    {
        Message* pMessage = topMessage("")->warning(data(), "Asymetric 'undo' doesn't restore initial 'do'");
        UndoCommand* pCommand = this;
        Message* pChildMessage = nullptr;
        Message* pCommandMessage = nullptr;
        while(pCommand)
        {
            pCommandMessage = o_new(Message)(e_MessageType_Warning, pCommand->getName().c_str());
            if(pChildMessage)
            {
                pCommandMessage->addChild(pChildMessage);
            }
            pChildMessage = pCommandMessage;
            pCommand = pCommand->getParent();
        }
        pMessage->addChild(pCommandMessage);
        pMessage->warning(data(), "Fix the related code because this could lead to unintended undo/redo behavior");
    }
}

}}
