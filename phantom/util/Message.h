#pragma once
#ifndef o_phantom_Message_h__
#define o_phantom_Message_h__


/* ****************** Includes ******************* */
#include <phantom/variant.h>
/* **************** Declarations ***************** */
o_declare(class, phantom, MessageTree);
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

	//================================================
	// Enumerations
	//================================================

    enum EType
    {
        e_Type_Information,
        e_Type_Success,
        e_Type_Warning,
        e_Type_Error,
    };


	//================================================
	// Constructors / Destructor
	//================================================

	Message(EType a_eType, const string& a_strText = "");
	~Message();


	//================================================
	// Accessors
	//================================================

    MessageTree*          getMessageTree() const;
    
    Message*		        getParent() const;
	Message*		        getChild(uint a_uiIndex) const;
	uint					getChildCount() const;

	const phantom::variant& getData() const;
	void                    setData(const phantom::variant& a_Data);

	EType                   getType() const;
	void                    setType(EType a_eType);
	EType                   getMostValuableMessageType() const;

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

    Message*                error(const char* a_str, ...);
    Message*                warning(const char* a_str, ...);
    Message*                information(const char* a_str, ...);
    Message*                success(const char* a_str, ...);
    void                    format(const char* a_format, ... );
    void                    format(const char* a_format, va_list args);

    void					open();


protected:

	//================================================
	// Private Operations
	//================================================

    void					setMessageTree(MessageTree* a_pMessageTree);
    void					emitMessageOpenedCascade(Message* a_pMessage);


protected:

	//================================================
	// Signals
	//================================================

    o_signal_data(childAdded, Message*);
    o_signal_data(childRemoved, Message*);
    o_signal_data(opened);
    o_signal_data(messageOpened, Message*);


protected:

	//================================================
	// Fields
	//================================================

	typedef phantom::vector<Message*> MessageVector;
    MessageTree*			m_pMessageTree;
	Message*				m_pParent;
    MessageVector			m_Children;
    EType			        m_eType;
    string                  m_strCategory;
    string			        m_strText;
    phantom::variant        m_Data;
    uint	                m_Flags;
};

o_namespace_end(phantom)

o_classN((phantom), Message)
{
    o_reflection
    {
        o_signal(opened, ());
        o_signal(messageOpened, (Message*));
        o_signal(childAdded, (Message*));
        o_signal(childRemoved, (Message*));
    };
};
o_exposeN((phantom), Message);

#endif //o_phantom_Message_h__