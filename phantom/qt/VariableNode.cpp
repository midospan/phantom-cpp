/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableNode.h"
#include "VariableNode.hxx"
#include "phantom/std/string.h"
/* *********************************************** */
o_registerN((phantom, qt), VariableNode);
 
namespace phantom { 
namespace qt {

VariableNode::VariableNode( const string& a_strName ) 
    : m_strName(a_strName)
    , m_pVariableType(nullptr)
    , m_pParentNode(nullptr)
    , m_Modifiers(0)
{
    update();
}

VariableNode::VariableNode( const string& a_strName, const vector<reflection::Variable*>& a_Variables ) 
    : m_strName(a_strName)
    , m_pVariableType(a_Variables[0]->getValueType()->removeReference()->removeConst())
    , m_pParentNode(nullptr)
    , m_Variables(a_Variables)
    , m_Modifiers(a_Variables[0]->getModifiers())
{
#if defined(_DEBUG)
    checkCommonAncestorType();
#endif
    for(auto it = m_Variables.begin(); it != m_Variables.end(); ++it)
    {
        void* pAddress = (*it)->getAddress();
        m_Buffered.push_back(pAddress == nullptr);
        if(pAddress == nullptr)
        {
            auto pType = m_pVariableType->removeReference()->removeConst();
            pAddress = pType->allocate();
            pType->safeConstruct(pAddress);
            // skip install (rtti)
            pType->initialize(pAddress);
        }
        m_Addresses.push_back( pAddress );       

    }
    update();
}

VariableNode::VariableNode( const vector<reflection::Variable*>& a_Variables ) 
    : m_strName(m_Variables[0]->getName())
    , m_pVariableType(a_Variables[0]->getValueType()->removeReference()->removeConst())
    , m_pParentNode(nullptr)
    , m_Variables(a_Variables)
    , m_Modifiers(a_Variables[0]->getModifiers())
{
#if defined(_DEBUG)
    checkCommonAncestorType();
#endif
    for(auto it = m_Variables.begin(); it != m_Variables.end(); ++it)
    {
        void* pAddress = (*it)->getAddress();
        m_Buffered.push_back(pAddress == nullptr);
        if(pAddress == nullptr)
        {
            auto pType = m_pVariableType->removeReference()->removeConst();
            pAddress = pType->allocate();
            pType->safeConstruct(pAddress);
            // skip install (rtti)
            pType->initialize(pAddress);
        }
        m_Addresses.push_back( pAddress );       

    }
    update();
}

o_initialize_cpp(VariableNode)
{
    for(auto it = m_Variables.begin(); it != m_Variables.end(); ++it)
    {
        o_connect(*it, valueChanged(), this, valueChanged());
    }
}

o_terminate_cpp(VariableNode)
{
    if(m_pParentNode)
    {
        m_pParentNode->removeChildNode(this);
    }
    o_assert(m_pParentNode == nullptr);
    while(m_ChildNodes.size())
    {
        o_dynamic_delete m_ChildNodes.back();
    }
}

VariableNode::~VariableNode()
{
    for(auto it = m_Variables.begin(); it != m_Variables.end(); ++it)
    {
        o_dynamic_delete *it;
    }
    for(size_t i = 0; i<m_Addresses.size(); ++i)
    {
        if(m_Buffered[i])
        {
            m_pVariableType->terminate(m_Addresses[i]);
            m_pVariableType->destroy(m_Addresses[i]);
            m_pVariableType->deallocate(m_Addresses[i]);
        }
    }
}

bool VariableNode::hasMultipleValues() const
{
    if(m_Variables.empty()) return false;
    reflection::Type* pType = m_pVariableType->removeReference()->removeConst();
    void* pBufferMain = pType->newInstance();
    void* pBufferTest = pType->newInstance();
    m_Variables.front()->getValue(pBufferMain);
    for(auto it = m_Variables.begin()+1; it != m_Variables.end(); ++it)
    {
        (*it)->getValue(pBufferTest);
        if(pType->hasLess())
        {
            if(pType->less(pBufferTest, pBufferMain) || pType->less(pBufferMain, pBufferTest))
            {
                pType->deleteInstance(pBufferMain);
                pType->deleteInstance(pBufferTest);
                return true;
            }
        }
        else if(!pType->areValueEqual(pBufferTest, pBufferMain)) 
        {
            pType->deleteInstance(pBufferMain);
            pType->deleteInstance(pBufferTest);
            return true;
        }
    }
    pType->deleteInstance(pBufferMain);
    pType->deleteInstance(pBufferTest);
    return false;
}

reflection::Class* VariableNode::getVariableClass() const
{
    return m_Variables.size() ? classOf(m_Variables[0]) : nullptr;
}

reflection::Type* VariableNode::getValueType() const
{
    return m_pVariableType;
}

void VariableNode::flush() const
{
    for(size_t i = 0; i<m_Variables.size(); ++i)
    {
        if(m_Buffered[i])
        {
            m_Variables[i]->setValue(m_Addresses[i]); 
        }
    }
    if(m_pParentNode)
        m_pParentNode->flush();
}

void VariableNode::update() const
{
    for(size_t i = 0; i<m_Variables.size(); ++i)
    {
        if(m_Buffered[i])
        {
            m_Variables[i]->getValue(m_Addresses[i]);
        }
    }
}

void VariableNode::getValue( void* a_pDest ) const
{
    if(m_Variables.size()) m_Variables[0]->getValue(a_pDest);
}

void VariableNode::setValue( void const* a_pSrc ) const
{
    for(auto it = m_Variables.begin(); it != m_Variables.end(); ++it)
    {
        (*it)->setValue(a_pSrc);
    }
    update();
    if(m_pParentNode)
    {
        m_pParentNode->flush();
    }
}

VariableNode* VariableNode::getNextChild( VariableNode* a_pCurrent ) const
{
    for(auto it = m_ChildNodes.begin(); it != m_ChildNodes.end(); ++it)
    {
        if((*it == a_pCurrent))
        {
            return (++it == m_ChildNodes.end()) ? nullptr : *it;
        }
    }
    return nullptr;
}

VariableNode* VariableNode::getPrevChild( VariableNode* a_pCurrent ) const
{
    for(auto it = m_ChildNodes.rbegin(); it != m_ChildNodes.rend(); ++it)
    {
        if((*it == a_pCurrent))
        {
            return (++it == m_ChildNodes.rend()) ? nullptr : *it;
        }
    }
    return nullptr;
}

void VariableNode::addChildNode( VariableNode* a_pVariableNode )
{
    m_ChildNodes.push_back(a_pVariableNode);
    o_assert(a_pVariableNode->m_pParentNode == nullptr);
    a_pVariableNode->m_pParentNode = this;
    o_emit childNodeAdded(a_pVariableNode);
}

void VariableNode::removeChildNode( VariableNode* a_pVariableNode )
{
    o_assert(a_pVariableNode->m_pParentNode == this);
    o_emit childNodeAboutToBeRemoved(a_pVariableNode);
    a_pVariableNode->m_pParentNode = nullptr;
    m_ChildNodes.erase(std::find(m_ChildNodes.begin(), m_ChildNodes.end(), a_pVariableNode));
}

void VariableNode::getValues( void** a_pMultipleDest ) const
{
    for(size_t i = 0; i<m_Variables.size(); ++i)
    {
        m_Variables[i]->getValue(a_pMultipleDest[i]);
    }
}

void VariableNode::setValues( void const ** a_pMultipleSrc ) const
{
    for(size_t i = 0; i<m_Variables.size(); ++i)
    {
        m_Variables[i]->setValue(a_pMultipleSrc[i]);
    }
    update();
    if(m_pParentNode)
    {
        m_pParentNode->flush();
    }
}


}}
