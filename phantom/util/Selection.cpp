/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Selection.h"
#include "Selection.hxx"
/* *********************************************** */
o_registerN((phantom), Selection);

o_namespace_begin(phantom)


//================================================
// Constructors / Destructor
//================================================

Selection::Selection()
: m_pCommonAncestorType(NULL)
{

}

Selection::~Selection()
{

}


//================================================
// Accessors
//================================================

const phantom::data& Selection::getData(size_t a_uiIndex) const
{
	return m_SelectedDatas[a_uiIndex];
}

size_t Selection::getDataCount() const
{
	return m_SelectedDatas.size();
}

phantom::reflection::Type* Selection::getCommonAncestorType() const
{
	return m_pCommonAncestorType;
}


//================================================
// Operations
//================================================

void Selection::recomputeCommonAncestorType()
{
	phantom::reflection::Type* pOldType = m_pCommonAncestorType;
	m_pCommonAncestorType = NULL;
	if (NOT(m_SelectedDatas.empty()))
	{
		m_pCommonAncestorType = m_SelectedDatas[0].type();
		for(auto itData = m_SelectedDatas.begin(); itData != m_SelectedDatas.end() AND m_pCommonAncestorType != NULL; ++itData)
		{
			m_pCommonAncestorType = m_pCommonAncestorType->getCommonAncestor(itData->type());
		}
	}
}
//================================================
// Slots
//================================================

void Selection::select(const phantom::vector<phantom::data>& a_Datas)
{
	// New datas
	for(auto itData = a_Datas.begin(); itData != a_Datas.end(); ++itData)
	{
		phantom::vector<phantom::data>::iterator it = std::find(m_SelectedDatas.begin(), m_SelectedDatas.end(), *itData);
		if (it == m_SelectedDatas.end())
		{
			phantom::data d = *itData;
			m_SelectedDatas.push_back(d);
		}
	}

	// New common type
	recomputeCommonAncestorType();

    o_emit selectionChanged();
}

void Selection::deselect(const phantom::vector<phantom::data>& a_Datas)
{
	// Remove datas
	phantom::vector<phantom::data> oldDatas;
	oldDatas.insert(oldDatas.begin(), m_SelectedDatas.begin(), m_SelectedDatas.end());
	for(auto itData = oldDatas.begin(); itData != oldDatas.end(); ++itData)
	{
		phantom::vector<phantom::data>::iterator it = std::find(m_SelectedDatas.begin(), m_SelectedDatas.end(), *itData);
		if (it != m_SelectedDatas.end())
		{
			m_SelectedDatas.erase(it);
		}
	}

	// New common type
	recomputeCommonAncestorType();

    o_emit selectionChanged();
}

void Selection::deselectAll()
{
	// Clear all
	m_SelectedDatas.clear();
	m_pCommonAncestorType = NULL;

    o_emit selectionChanged();
}

o_namespace_end(phantom)
