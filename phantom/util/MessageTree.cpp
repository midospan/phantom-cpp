/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "MessageTree.h"
#include "Message.h"
#include <stdarg.h>
#include <stdio.h>
/* *********************************************** */
o_registerN((phantom), MessageTree);

o_namespace_begin(phantom) 


//================================================
// Constructors / Destructor
//================================================

MessageTree::MessageTree() 
: m_pRootMessage(o_new(Message)(Message::e_Type_Information))
{
    m_pRootMessage->setMessageTree(this);
}

MessageTree::~MessageTree()
{
    o_delete(Message) m_pRootMessage;
}


//================================================
// Accessors
//================================================

Message* MessageTree::getRootMessage() const
{
	return m_pRootMessage;
}


//================================================
// Operations
//================================================

void MessageTree::clear()
{
    m_pRootMessage->removeAndDestroyAllChildCascade();
}

o_namespace_end(phantom)