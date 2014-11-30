/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ClassComboBox.h"
#include <QStyledItemDelegate>
/* *********************************************** */
 
namespace phantom { 
namespace qt {

    ClassComboBox::ClassComboBox( reflection::Class* a_pBaseClass
        , reflection::Class* a_pCurrentClass
        , FilterBits a_iFilter 
        , bool a_bAllowsNone /* = true*/ ) 
        : m_iFilter(a_iFilter)
    {
        setItemDelegate(new QStyledItemDelegate());
        m_pBaseClass = a_pBaseClass;
        if(a_bAllowsNone)
        {
            addItem(QIcon("resources/icons/famfamfam/null.png"), "none", 0);
        }
        if(m_pBaseClass)
        {
            addClass(m_pBaseClass);
        }
        connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentClassIndexChanged(int)));
        if(a_pCurrentClass && a_pCurrentClass->isKindOf(a_pBaseClass))
        {
            setCurrentClass(a_pCurrentClass);
        }
    }

    void ClassComboBox::addClass( reflection::Class* a_pClass )
    {
        if((m_iFilter & e_FilterBit_AllowNonDefaultConstructible) 
            OR (a_pClass->Type::isDefaultInstanciable()))
        {
            string name = nameOf(a_pClass);
            QIcon icon = QIcon(iconOf(a_pClass).c_str());
            addItem(icon
                , name.c_str()
                , QVariant((size_t)a_pClass));
        }
        if((m_iFilter & e_FilterBit_Derived) == 0) return;
        size_t i = 0;
        size_t count = a_pClass->getDerivedClassCount();
        for(;i<count;++i)
        {
            reflection::Class* pDerived = a_pClass->getDerivedClass(i);
            addClass(pDerived);
        }
    }

    void ClassComboBox::setCurrentClass( reflection::Class* a_pClass )
    {
        int index = findData(QVariant((size_t)a_pClass));
        if(index == -1) return;
        setCurrentIndex(index);
    }

}}