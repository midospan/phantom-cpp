#ifndef o_qt_ComponentDataComboBox_h__
#define o_qt_ComponentDataComboBox_h__


/* ****************** Includes ******************* */
#include "ClassComboBox.h"
/* **************** Declarations ***************** */

/* *********************************************** */

namespace phantom { namespace qt {
    
class ComponentDataComboBox : public ClassComboBox
{
    Q_OBJECT

public:
    ComponentDataComboBox( reflection::Class* a_pBaseClass
        , const vector<void*>& a_CurrentData
        , FilterBits a_iFilter );
    ~ComponentDataComboBox(void) 
    {
    }

    void setCurrentData(size_t i, void* a_pData);
    void* getCurrentData(size_t i) const { return m_CurrentData[i]; }
    
protected:
    reflection::Class* findCommonClass(const vector<void*>& a_Data) const;

protected slots:
    void currentClassChanged(reflection::Class* a_pClass);

signals:
    void dataChanged();

protected:
    vector<void*> m_CurrentData;
};


} // qt 
} // phantom 



#endif // ghost_gui_ComponentDataComboBox_h__
