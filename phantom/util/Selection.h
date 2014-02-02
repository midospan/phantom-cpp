#pragma once
#ifndef o_Selection_h__
#define o_Selection_h__

/* ****************** Includes ******************* */
#include "phantom/phantom.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom), Selection);
/* *********************************************** */

o_namespace_begin(phantom)

/* ************************************************ *
 * \class Selection
 * \brief Represents a selection of data (grouping them and deducing their common ancestor type)
 * ************************************************ */
class o_export Selection
{
public:
	//================================================
	// Constructors / Destructor
	//================================================

	Selection();
	~Selection();

	//================================================
	// Accessors
	//================================================

    const phantom::data&		    getData(size_t a_uiIndex) const;
	size_t						    getDataCount() const;
                                 
	phantom::reflection::Type*	    getCommonAncestorType() const;
    
    void select(const phantom::vector<phantom::data>& a_Datas);
    void deselect(const phantom::vector<phantom::data>& a_Datas);
    void deselectAll();

protected:
    
	//================================================
	// Slots
	//================================================

	void recomputeCommonAncestorType();

protected: 

    //================================================
    // Signals
    //================================================
    o_signal_data(selectionChanged);

protected:
	//================================================
	// Fields
	//================================================

	phantom::vector<phantom::data>	m_SelectedDatas;
	phantom::reflection::Type*		m_pCommonAncestorType;
};

o_namespace_end(phantom)

#endif // o_Selection_h__
