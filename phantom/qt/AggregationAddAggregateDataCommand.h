#pragma once
#ifndef phantom_qt_AggregationAddAggregateDataCommand_h__
#define phantom_qt_AggregationAddAggregateDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/DataBaseCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), AggregationAddAggregateDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class AggregationAddAggregateDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export AggregationAddAggregateDataCommand : public DataBaseCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    AggregationAddAggregateDataCommand(serialization::DataBase* a_pDataBase, uint a_uiGuid, reflection::Expression* a_pAggregationExpression);
    AggregationAddAggregateDataCommand(serialization::DataBase* a_pDataBase, uint a_uiGuid, const string& a_strAggregationExpression);
	~AggregationAddAggregateDataCommand();


	//================================================
	// Operations
	//================================================

    virtual void record();

    virtual AggregationAddAggregateDataCommand* clone() const;

protected:
	//================================================
	// Fields
	//================================================
    string                          m_strAggregationExpression;
    uint                            m_uiGuid;
    bitfield                        m_Modifiers;

};

} // qt 
} // phantom

#endif // phantom_qt_AggregationAddAggregateDataCommand_h__
