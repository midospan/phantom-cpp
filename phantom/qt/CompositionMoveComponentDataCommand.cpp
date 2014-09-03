/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "CompositionMoveComponentDataCommand.h"
#include "CompositionMoveComponentDataCommand.hxx"
#include "UpdateComponentDataCommand.h"
#include <phantom/serialization/Node.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/CompositionClass.h>
#include "ComponentReferenceExpressionChangeCommand.h"
/* *********************************************** */
o_registerN((phantom, qt), CompositionMoveComponentDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================
    
CompositionMoveComponentDataCommand::CompositionMoveComponentDataCommand( serialization::DataBase* a_pDataBase
    , const phantom::data& a_OwnerData
    , reflection::Expression* a_pCompositionExpression
    , size_t oldIndex
    , size_t newIndex)
    : UndoCommand()
    , m_pDataBase(a_pDataBase)
    , m_uiOwnerGuid(a_pDataBase->getGuid(a_OwnerData))
    , m_strCompositionExpression(a_pCompositionExpression->getName())
    , m_uiNewIndex(newIndex)
    , m_uiOldIndex(oldIndex)
{
    o_assert(m_pDataBase);
    setName("Move component data from index '"+lexical_cast<string>(oldIndex)+"' to '"+lexical_cast<string>(newIndex)+"' in "+ m_pDataBase->getDataAttributeValue(a_OwnerData, "name")+"'("+lexical_cast<string>((void*)m_uiOwnerGuid)+")");

    createSubCommands(a_pCompositionExpression);
}

CompositionMoveComponentDataCommand::CompositionMoveComponentDataCommand( serialization::DataBase* a_pDataBase
    , uint a_uiOwnerGuid
    , const string& a_strCompositionExpression
    , size_t oldIndex
    , size_t newIndex )
    : UndoCommand()
    , m_pDataBase(a_pDataBase)
    , m_uiOwnerGuid(a_uiOwnerGuid)
    , m_strCompositionExpression(a_strCompositionExpression)
    , m_uiNewIndex(newIndex)
    , m_uiOldIndex(oldIndex)
{
    o_assert(m_pDataBase);
    auto d = m_pDataBase->getData(m_uiOwnerGuid);
    setName("Move component data from index '"+lexical_cast<string>(oldIndex)+"' to '"+lexical_cast<string>(newIndex)+"' in "+ m_pDataBase->getDataAttributeValue(m_pDataBase->getData(m_uiOwnerGuid), "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
    
    reflection::Expression* pCompositionExpression = phantom::expressionByName(m_strCompositionExpression);
    createSubCommands(pCompositionExpression);
    phantom::deleteElement(pCompositionExpression);
}

CompositionMoveComponentDataCommand::~CompositionMoveComponentDataCommand()
{

}

void CompositionMoveComponentDataCommand::createSubCommands(reflection::Expression* a_pCompositionExpression)
{
    setRedoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent);
    setUndoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent);
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(a_pCompositionExpression->getValueType()->removeReference()->removeConst());
    void* pComposition = a_pCompositionExpression->loadEffectiveAddress();
    if(m_uiOldIndex > m_uiNewIndex)
    {
        for(size_t i = m_uiNewIndex; i<m_uiOldIndex; ++i)
        {
            void* pComponent = nullptr;
            void* pNextComponent = nullptr;
            pCompositionClass->get(pComposition, i, &pComponent);
            pCompositionClass->get(pComposition, i+1, &pNextComponent);
            pushCommand(o_new(ComponentReferenceExpressionChangeCommand)(m_pDataBase, pComponent, m_pDataBase->getComponentDataReferenceExpression(pNextComponent)));
        }
    }
    else 
    {
        for(size_t i = m_uiOldIndex+1; i<=m_uiNewIndex; ++i)
        {
            void* pComponent = nullptr;
            void* pPrevComponent = nullptr;
            pCompositionClass->get(pComposition, i, &pComponent);
            pCompositionClass->get(pComposition, i-1, &pPrevComponent);
            pushCommand(o_new(ComponentReferenceExpressionChangeCommand)(m_pDataBase, pComponent, m_pDataBase->getComponentDataReferenceExpression(pPrevComponent)));
        }
    }
    void* pOldIndexComponent = nullptr;
    void* pNewIndexComponent = nullptr;
    pCompositionClass->get(pComposition, m_uiOldIndex, &pOldIndexComponent);
    pCompositionClass->get(pComposition, m_uiOldIndex, &pNewIndexComponent);
    pushCommand(o_new(ComponentReferenceExpressionChangeCommand)(m_pDataBase, pOldIndexComponent, m_pDataBase->getComponentDataReferenceExpression(pNewIndexComponent)));
}
//================================================
// Operations
//================================================


void CompositionMoveComponentDataCommand::redo()
{
    reflection::Expression* pCompositionExpression = phantom::expressionByName(m_strCompositionExpression);
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pCompositionExpression->getValueType()->removeReference()->removeConst());
    pCompositionClass->move(pCompositionExpression->loadEffectiveAddress(), m_uiOldIndex, m_uiNewIndex);
    m_pDataBase->saveData(m_pDataBase->getData(m_uiOwnerGuid));
    phantom::deleteElement(pCompositionExpression);
}

void CompositionMoveComponentDataCommand::undo()
{
    reflection::Expression* pCompositionExpression = phantom::expressionByName(m_strCompositionExpression);
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pCompositionExpression->getValueType()->removeReference()->removeConst());
    pCompositionClass->move(pCompositionExpression->loadEffectiveAddress(), m_uiNewIndex, m_uiOldIndex);
    m_pDataBase->saveData(m_pDataBase->getData(m_uiOwnerGuid));
    phantom::deleteElement(pCompositionExpression);
}

CompositionMoveComponentDataCommand* CompositionMoveComponentDataCommand::clone() const
{
    return o_new(CompositionMoveComponentDataCommand)(m_pDataBase, m_uiOwnerGuid, m_strCompositionExpression, m_uiOldIndex, m_uiNewIndex);
}

}}
