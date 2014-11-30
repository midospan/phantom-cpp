#pragma once
#ifndef phantom_qt_AggregationRemoveAggregateDataCommand_h__
#define phantom_qt_AggregationRemoveAggregateDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/DataBaseCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), AggregationRemoveAggregateDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class AggregationRemoveAggregateDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export AggregationRemoveAggregateDataCommand : public DataBaseCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    AggregationRemoveAggregateDataCommand(serialization::DataBase* a_pDataBase, size_t a_uiIndex, reflection::Expression* a_pAggregationExpression);
    AggregationRemoveAggregateDataCommand(serialization::DataBase* a_pDataBase, size_t a_uiIndex, const string& a_strAggregationExpression);
	~AggregationRemoveAggregateDataCommand();


	//================================================
	// Operations
	//================================================

    virtual void record();

    virtual AggregationRemoveAggregateDataCommand* clone() const;

    // string generateAggregateName(serialization::DataBase* a_pDataBase, phantom::data a_Aggregate);

protected:
	//================================================
	// Fields
	//================================================
    string                          m_strAggregationExpression;
    uint                            m_uiGuid;
    size_t                          m_uiIndex;
    bitfield                        m_Modifiers;

};

} // qt 
} // phantom

#endif // phantom_qt_AggregationRemoveAggregateDataCommand_h__
