#pragma once
#ifndef phantom_qt_AggregationMoveAggregateDataCommand_h__
#define phantom_qt_AggregationMoveAggregateDataCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/DataBaseCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), AggregationMoveAggregateDataCommand);
/* *********************************************** */

namespace phantom { namespace qt {


/* ************************************************ *
 * \class AggregationMoveAggregateDataCommand
 * \brief Command to add a node
 * ************************************************ */
class o_qt_export AggregationMoveAggregateDataCommand : public DataBaseCommand
{
public:

	//================================================
	// Constructors / Destructor
	//================================================

    AggregationMoveAggregateDataCommand(serialization::DataBase* a_pDataBase, const phantom::data& a_OwnerData, reflection::Expression* a_pAggregationExpression, size_t oldIndex, size_t newIndex);
    AggregationMoveAggregateDataCommand(serialization::DataBase* a_pDataBase, uint a_uiOwnerGuid, const string& a_strAggregationExpression, size_t oldIndex, size_t newIndex);
	~AggregationMoveAggregateDataCommand();


	//================================================
	// Operations
	//================================================

	virtual void record();
    virtual AggregationMoveAggregateDataCommand* clone() const;

protected:
    void createSubCommands(reflection::Expression* a_pAggregationExpression);

protected:
	//================================================
	// Fields
	//================================================
    string                          m_strTypeName;
    string                          m_strAggregationExpression;
    uint                            m_uiOwnerGuid;
    size_t                          m_uiNewIndex;
    size_t                          m_uiOldIndex;

};

} // qt 
} // phantom

#endif // phantom_qt_AggregationMoveAggregateDataCommand_h__
