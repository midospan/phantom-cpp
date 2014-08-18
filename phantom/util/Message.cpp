/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Message.h"
#include "Message.hxx"
#include <stdarg.h>
/* *********************************************** */
o_registerN((phantom), Message);

o_namespace_begin(phantom) 


//================================================
// Constructors / Destructor
//================================================

Message::Message(EMessageType a_eType, const string& a_strText) 
: m_strText(a_strText) 
, m_eType(a_eType)
, m_pParent(nullptr)
{

}

Message::~Message()
{
	removeAndDestroyAllChildCascade();
}


//================================================
// Accessors
//================================================

Message* Message::getRootMessage() const 
{ 
	return m_pParent == nullptr ? const_cast<Message*>(this) : m_pParent->getRootMessage(); 
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

EMessageType Message::getType() const 
{ 
	return m_eType; 
}

void Message::setType(EMessageType a_eType)
{
	m_eType = a_eType;
}

EMessageType Message::getMostValuableMessageType() const
{
	EMessageType type = m_eType;
	MessageVector::const_iterator it = m_Children.begin();
	for(; it != m_Children.end(); ++it)
	{
		EMessageType childType = (*it)->getMostValuableMessageType();
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
    m_Children.push_back(a_pChild);
    o_emit childAdded(a_pChild);
    emitDescendantRemovedCascade(a_pChild);
}

void Message::removeChild(Message* a_pChild)
{
    MessageVector::iterator it = m_Children.begin();
	for(; it != m_Children.end(); ++it)
	{
		if(*it == a_pChild) break;
	}
    o_assert( it != m_Children.end());
    emitDescendantRemovedCascade(a_pChild);
    o_emit childRemoved(a_pChild);
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

Message* Message::error(const variant& a_Data, const char* a_Format,  ...)
{
    va_list args;
    va_start(args, a_Format);
    Message* pMessage = message(e_MessageType_Error, a_Data, a_Format, args);
    va_end(args);
    return pMessage;
}

Message* Message::warning(const variant& a_Data, const char* a_Format, ...)
{
    va_list args;
    va_start(args, a_Format);
    Message* pMessage = message(e_MessageType_Warning, a_Data, a_Format, args);
    va_end(args);
    return pMessage;
}

Message* Message::information(const variant& a_Data, const char* a_Format, ...)
{
    va_list args;
    va_start(args, a_Format);
    Message* pMessage = message(e_MessageType_Information, a_Data, a_Format, args);
    va_end(args);
    return pMessage;
}

Message* Message::success(const variant& a_Data, const char* a_Format, ...)
{
    va_list args;
    va_start(args, a_Format);
    Message* pMessage = message(e_MessageType_Success, a_Data, a_Format, args);
    va_end(args);
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

Message* Message::message( EMessageType a_eType, const phantom::variant& a_Data, const char* a_Format, ... )
{
    va_list args;
    va_start(args, a_Format);
    Message* pMessage = message(a_eType, a_Data, a_Format, args);
    va_end(args);
    return pMessage;
}

Message* Message::message( EMessageType a_eType, const phantom::variant& a_Data, const char* a_Format, va_list args )
{
    Message* pMessage = o_new(Message)(a_eType);
    pMessage->setData(a_Data);
    size_t size = strlen(a_Format)+512;
    char* buffer = (char*)o_malloc(size);
    buffer[size-1] = '\0';
    int r = vsprintf_s(buffer, size, a_Format, args);
    pMessage->setText(buffer);
    o_free(buffer);
    addChild(pMessage);
    return pMessage;
}

void Message::emitDescendantAddedCascade( Message* a_pMessage )
{
    if(m_pParent)
        m_pParent->emitDescendantAddedCascade(a_pMessage);
    o_emit descendantAdded(a_pMessage); 
}

void Message::emitDescendantRemovedCascade( Message* a_pMessage )
{
    o_emit descendantRemoved(a_pMessage);
    if(m_pParent)
        m_pParent->emitDescendantRemovedCascade(a_pMessage); 
}

Message::messages_def Message::messages_def::operator()( EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, ... )
{
    va_list args;
    va_start(args, a_Format);
    m_pMessage->message(a_eType, a_Data, a_Format, args);
    va_end(args);
    return messages_def(m_pMessage);
}

o_namespace_end(phantom)
