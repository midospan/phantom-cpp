/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "RemoveDataCommand.h"
#include "RemoveDataCommand.hxx"
#include <phantom/serialization/Node.h>
#include <phantom/reflection/Expression.h>
/* *********************************************** */
o_registerN((phantom, qt), RemoveDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

RemoveDataCommand::RemoveDataCommand(serialization::DataBase* a_pDataBase, const vector<uint>& a_Guids)
: DataBaseCommand(a_pDataBase)
{
    m_Guids = a_Guids;
    setName("Remove");
    vector<phantom::data> allData;
    m_pDataBase->rootNode()->fetchDataCascade(allData);
    for(size_t i = 0; i<m_Guids.size(); ++i)
    {
        phantom::data d = m_pDataBase->getData(m_Guids[i]);
        o_assert(!d.isNull());
        for(auto it = allData.begin(); it != allData.end(); ++it)
        {
            if(m_pDataBase->getComponentDataOwner(*it) == d)
                m_Guids.push_back(m_pDataBase->getGuid(*it));
        }
    }
    std::sort(m_Guids.begin(), m_Guids.end());
    m_Guids.resize(std::unique(m_Guids.begin(), m_Guids.end())-m_Guids.begin());
    for(auto it = m_Guids.begin(); it != m_Guids.end(); ++it)
    {
        pushCommand(o_new(UndoCommand)((m_pDataBase->getNode(*it) ? "Node '" : "Data '") + m_pDataBase->getAttributeValues(m_pDataBase->getData(*it).address())[0] + "' ("+lexical_cast<string>((void*)(*it))+")" ));
    }
}

RemoveDataCommand::~RemoveDataCommand()
{

}

//================================================
// Operations
//================================================


RemoveDataCommand* RemoveDataCommand::clone() const
{
    return o_new(RemoveDataCommand)(m_pDataBase, m_Guids);
}

void RemoveDataCommand::redoReplayed()
{
    for(auto it = m_Guids.begin(); it != m_Guids.end(); ++it)
    {
        auto d = m_pDataBase->getData(*it);
        if(m_pDataBase->getComponentDataOwner(d).isNull())
        {
            m_pDataBase->getNode(d)->removeData(d);
        }
        else 
        {
            m_pDataBase->getNode(d)->removeComponentData(d);
        }
    }
}

void RemoveDataCommand::undoReplayed()
{
    for(auto it = m_Guids.rbegin(); it != m_Guids.rend(); ++it)
    {
        reflection::Type* pType = typeByName(m_Types[*it]);
        o_assert(pType AND pType->isDefaultInstanciable());
        void* pData = pType->newInstance();
        auto foundRef = m_ComponentReferenceExpressions.find(*it);
        if(foundRef != m_ComponentReferenceExpressions.end())
        {
            // Component
            reflection::Expression* pExpression = phantom::expressionByName("("+foundRef->second+")=static_cast<"+pType->getQualifiedDecoratedName()+"*>(0x"+lexical_cast<string>(pData)+")");
            o_assert(pExpression);
            pExpression->eval();
            deleteElement(pExpression);
        }
        else 
        {
            serialization::Node* pNode = m_pDataBase->getNode(m_Nodes[*it]);
            o_assert(pNode);
            m_pDataBase->addData(data(pData, pType), pNode);
        }
    }
}

void RemoveDataCommand::record()
{
    for(auto it = m_Guids.begin(); it != m_Guids.end(); )
    {
        auto d = m_pDataBase->getData(*it);
        auto owner = m_pDataBase->getComponentDataOwner(d);
        if(owner.isNull())
        {
            m_Types[*it] = d.type()->getQualifiedDecoratedName();
            m_Nodes[*it] = m_pDataBase->getNode(d)->getGuid();
            m_pDataBase->getNode(d)->removeData(d);
            ++it;
            continue;
        }
        else 
        {
            while(!owner.isNull())
            {
                if(std::find(m_Guids.begin(), m_Guids.end(), m_pDataBase->getGuid(owner)) != m_Guids.end())
                {
                    it = m_Guids.erase(it);
                    // Owner found, we don't have to remove this component ourself, removing the owner will do it automatically
                    goto end;
                }
                owner = m_pDataBase->getComponentDataOwner(owner);
            }
            // No owner found in the removed guid list, we need to keep removing ourself the component
            m_Types[*it] = d.type()->getQualifiedDecoratedName();
            m_ComponentReferenceExpressions[*it] = m_pDataBase->getComponentDataReferenceExpression(d);
            m_pDataBase->getNode(d)->removeComponentData(d);
            ++it;
            continue;
        }
    end:
        it = m_Guids.erase(it);
    }
}

}}
