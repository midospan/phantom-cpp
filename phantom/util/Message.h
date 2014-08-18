#pragma once
#ifndef o_phantom_Message_h__
#define o_phantom_Message_h__


/* ****************** Includes ******************* */
#include <phantom/variant.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom), Message);
o_fwd(class, phantom, MessageTree);
/* *********************************************** */

o_namespace_begin(phantom)

/* ************************************************ *
 * \class Message
 * \brief Message.
 * ************************************************ */
class o_export Message
{
    friend class MessageTree;


public:
    struct messages_def
    {
        messages_def(Message* a_pMessage) : m_pMessage(a_pMessage) {}
        messages_def operator()(EMessageType a_eType, const phantom::variant& a_Data, char* a_Format, ... );
    protected:
        Message* m_pMessage;
    };

	//================================================
	// Enumerations
	//================================================


	//================================================
	// Constructors / Destructor
	//================================================

	Message(EMessageType a_eType = e_MessageType_Undefined, const string& a_strText = "");
	~Message();


	//================================================
	// Accessors
	//================================================

    Message*                getRootMessage() const;
    
    Message*		        getParent() const;
	Message*		        getChild(uint a_uiIndex) const;
	uint					getChildCount() const;

	const phantom::variant& getData() const;
	void                    setData(const phantom::variant& a_Data);

	EMessageType            getType() const;
	void                    setType(EMessageType a_eType);
	EMessageType            getMostValuableMessageType() const;

	const string&           getText() const;
	void                    setText( const string& a_strText);

	const string&           getCategory() const;
	void                    setCategory(const string& a_strCategory);


	//================================================
	// Operations
	//================================================

	virtual void			addChild(Message* a_pChild);
	virtual void			removeChild(Message* a_pChild);

    void                    removeAndDestroyAllChildCascade();

    Message*                clone() const;

    Message*                error(const variant& a_Data, const char* a_str, ...);
    Message*                warning(const variant& a_Data, const char* a_str, ...);
    Message*                information(const variant& a_Data, const char* a_str, ...);
    Message*                success(const variant& a_Data, const char* a_str, ...);

    void                    format(const char* a_format, ... );
    void                    format(const char* a_format, va_list args);

    void					open();

    Message*                message(EMessageType a_eType, const phantom::variant& a_Data, const char* a_Format, ... );
    Message*                message(EMessageType a_eType, const phantom::variant& a_Data, const char* a_Format, va_list args);

    messages_def            messages() { return messages_def(this); }
    

protected:

	//================================================
	// Private Operations
	//================================================

    void					emitMessageOpenedCascade(Message* a_pMessage);


protected:

	//================================================
	// Signals
	//================================================

    o_signal_data(childAdded, Message*);
    o_signal_data(childRemoved, Message*);
    o_signal_data(descendantAdded, Message*);
    o_signal_data(descendantRemoved, Message*);
    o_signal_data(opened);
    o_signal_data(messageOpened, Message*);

    void emitDescendantAddedCascade(Message* a_pMessage);
    void emitDescendantRemovedCascade(Message* a_pMessage);

protected:

	//================================================
	// Fields
	//================================================

	typedef phantom::vector<Message*> MessageVector;
	Message*				m_pParent;
    MessageVector			m_Children;
    EMessageType            m_eType;
    string                  m_strCategory;
    string			        m_strText;
    phantom::variant        m_Data;
    uint	                m_Flags;
};

o_namespace_end(phantom)

#endif //o_phantom_Message_h__