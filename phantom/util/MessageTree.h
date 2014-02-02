#pragma once
#ifndef o_phantom_MessageTree_h__
#define o_phantom_MessageTree_h__


/* ****************** Includes ******************* */
#include "phantom/phantom.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom), MessageTree);
o_fwd(class, phantom, Message);
/* *********************************************** */

o_namespace_begin(phantom)


/* ************************************************ *
 * \class MessageTree
 * \brief Message stream.
 * ************************************************ */
class o_export MessageTree 
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

	MessageTree();
	~MessageTree();


	//================================================
	// Accessors
	//================================================

	Message*			getRootMessage() const;


	//================================================
	// Operations
	//================================================

    void				clear();


protected:

	//================================================
	// Fields
	//================================================

	mutable Message*    m_pRootMessage;
};

o_namespace_end(phantom)

#endif //o_phantom_MessageTree_h__