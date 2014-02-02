/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "MessageTree.h"
#include "Message.h"
#include "Message.hxx"
#include <stdarg.h>
/* *********************************************** */
o_registerN((phantom), Message);

o_namespace_begin(phantom) 


//================================================
// Constructors / Destructor
//================================================

Message::Message(EType a_eType, const string& a_strText) 
: m_strText(a_strText) 
, m_eType(a_eType)
, m_pParent(nullptr)
, m_pMessageTree(nullptr)
{

}

Message::~Message()
{
	removeAndDestroyAllChildCascade();
}


//================================================
// Accessors
//================================================

MessageTree* Message::getMessageTree() const 
{ 
	return m_pMessageTree; 
}

void Message::setMessageTree(MessageTree* a_pMessageTree)
{
	m_pMessageTree = a_pMessageTree; 
	auto it = m_Children.begin();
	for(; it != m_Children.end(); ++it)
	{
		(*it)->setMessageTree(a_pMessageTree);
	}
}

Message* Message::getParent() const 
{ 
	return m_pParent; 
}

Message* Message::getChild(uint a_uiIndex) const 
{
	return m_Children[a_uiIndex]; 
}

uint Message::getChildCount() const 
{
	return m_Children.size(); 
}

void Message::setData(const phantom::variant& a_Data)
{
	m_Data = a_Data;
}

const phantom::variant& Message::getData() const
{ 
	return m_Data; 
}

Message::EType Message::getType() const 
{ 
	return m_eType; 
}

void Message::setType(Message::EType a_eType)
{
	m_eType = a_eType;
}

Message::EType Message::getMostValuableMessageType() const
{
	Message::EType type = m_eType;
	MessageVector::const_iterator it = m_Children.begin();
	for(; it != m_Children.end(); ++it)
	{
		EType childType = (*it)->getMostValuableMessageType();
		if(childType > type)
			type = childType;
	}
	return type;
}

const string& Message::getText() const 
{ 
	return m_strText; 
}

void Message::setText(const string& a_strText) 
{ 
	m_strText = a_strText; 
}

const string& Message::getCategory() const 
{ 
	return m_strCategory; 
}

void Message::setCategory(const string& a_strCategory)
{
	m_strCategory = a_strCategory;
}


//================================================
// Operations
//================================================

void Message::format(const char* a_format, ...)
{
    va_list args;
    va_start(args, a_format);
    char buffer[512];
    buffer[511] = '\0';
    int r = vsprintf_s(buffer, 511, a_format, args);
    va_end(args);
    m_strText = buffer;
}

void Message::format(const char* a_format, va_list args)
{

    char buffer[512];
    buffer[511] = '\0';
    int r = vsprintf_s(buffer, 511, a_format, args);

    m_strText = buffer;
}

void Message::addChild(Message* a_pChild)
{
    o_assert(a_pChild->m_pParent == nullptr);
	a_pChild->m_pParent = this;
    a_pChild->setMessageTree(m_pMessageTree);
	m_Children.push_back(a_pChild);
    o_emit childAdded(a_pChild);
}

void Message::removeChild(Message* a_pChild)
{
    MessageVector::iterator it = m_Children.begin();
	for(; it != m_Children.end(); ++it)
	{
		if(*it == a_pChild) break;
	}
	o_assert( it != m_Children.end());
    o_emit childRemoved(a_pChild);
    a_pChild->setMessageTree(nullptr);
    m_Children.erase(it);
}

void Message::removeAndDestroyAllChildCascade()
{
    MessageVector::iterator it = m_Children.begin();
    for(; it != m_Children.end(); ++it)
    {
        (*it)->removeAndDestroyAllChildCascade();
        o_emit childRemoved(*it);
        o_delete(Message)(*it);
    }
    m_Children.clear();
}

Message* Message::error(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[512];
    buffer[511] = '\0';
    int r = vsprintf_s(buffer, 511, format, args);
    va_end(args);
    Message* pMessage = o_new(Message)(Message::e_Type_Error, buffer);
    addChild(pMessage);
    return pMessage;
}

Message* Message::warning(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[512];
    buffer[511] = '\0';
    int r = vsprintf_s(buffer, 511, format, args);
    va_end(args);
    Message* pMessage = o_new(Message)(Message::e_Type_Warning, buffer);
    addChild(pMessage);
    return pMessage;
}

Message* Message::information(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[512];
    buffer[511] = '\0';
    int r = vsprintf_s(buffer, 511, format, args);
    va_end(args);
    Message* pMessage = o_new(Message)(Message::e_Type_Information, buffer);
    addChild(pMessage);
    return pMessage;
}

Message* Message::success(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[512];
    buffer[511] = '\0';
    int r = vsprintf_s(buffer, 511, format, args);
    va_end(args);
    Message* pMessage = o_new(Message)(Message::e_Type_Success, buffer);
    addChild(pMessage);
    return pMessage;
}

Message* Message::clone() const
{
    Message* cloned = o_new(Message)(m_eType, m_strText);
    cloned->m_Data = m_Data;
    cloned->m_strCategory = m_strCategory;
    for(auto it = m_Children.begin(); it != m_Children.end(); ++it)
    {
        cloned->addChild((*it)->clone());
    }
    return cloned;
}

void Message::emitMessageOpenedCascade(Message* a_pMessage)
{
    o_emit messageOpened(a_pMessage);
    if(m_pParent) m_pParent->emitMessageOpenedCascade(a_pMessage);
}

void Message::open()
{
    o_emit opened();
    emitMessageOpenedCascade(this);
}

o_namespace_end(phantom)