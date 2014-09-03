#ifndef o_qt_ClassComboBox_h__
#define o_qt_ClassComboBox_h__


/* ****************** Includes ******************* */
#include <QComboBox>
#include <phantom/qt/qt.h>
/* **************** Declarations ***************** */

/* *********************************************** */

namespace phantom { namespace qt {

    class ClassValueFilter;

    class ClassComboBox : public QComboBox
    {
        Q_OBJECT

    public:
        enum EFilterBit
        {
            e_FilterBit_Poolable = 0x1,
            e_FilterBit_AllowNonDefaultConstructible = 0x2,
            e_FilterBit_Derived = 0x4,
        };

        o_declare_flags(FilterBits, EFilterBit);
    
    public:
        ClassComboBox( reflection::Class* a_pBaseClass
            , reflection::Class*a_pCurrentClass
            , FilterBits a_iFilter
            , bool a_bAllowsNone = false);
        ~ClassComboBox(void) 
        {
        }

        void setCurrentClass(reflection::Class* a_pClass);

    protected:
        void    addClass(reflection::Class* a_pClass);

    public:
        reflection::Class*   getCurrentClass() const 
        {
            reflection::Class* pClass = (reflection::Class*)this->itemData(currentIndex()).toULongLong();
            return pClass;
        }
        reflection::Class*   getBaseClass() const 
        {
            return m_pBaseClass;
        }

    protected slots:
        void currentClassIndexChanged(int index)
        {
            reflection::Class* pClass = (reflection::Class*)this->itemData(index).toULongLong();
            emit classSelected(pClass);
        }

signals:
        void    classSelected(reflection::Class* a_Class);

    protected:
        reflection::Class*  m_pBaseClass;
        FilterBits          m_iFilter;
    };


} // qt 
} // phantom 



#endif // ghost_gui_ClassComboBox_h__
