#ifndef o_qt_VariableEditor_h__
#define o_qt_VariableEditor_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
#include "QtTreePropertyBrowser.h"
/* **************** Declarations ***************** */
class QPushButton;
o_declareN(class, (phantom, qt), VariableEditor);
/* *********************************************** */

namespace phantom { namespace qt {

class BufferedVariable;
class VariableWidget;
class VariableEditor;
class VariableManager;
class VariableEditorFactory;
class CollectionElementVariable;
class VariableWidgetEditor;

class o_qt_export VariableEditor : public QtTreePropertyBrowser
{
    Q_OBJECT

    friend class VariableEditorFactory;
    friend class VariableAction;
    friend class VariableManager;

public:
    typedef fastdelegate::FastDelegate< void ( phantom::reflection::Variable* a_pVariable, void const* valueSource ) > variable_value_set_delegate;

    static void     defaultVariableValueSetDelegate(phantom::reflection::Variable* a_pVariable, void const* valueSource);

public:
    VariableEditor(VariableManager* a_pManager, const QString& variableColumnName);
    ~VariableEditor(void);

	o_initialize() {};

    void    setVariableValueSetDelegate(variable_value_set_delegate d);

    void    registerVariableTypeEditorClass(reflection::Type* a_pType, reflection::Class* a_pClass);

    VariableManager* getVariableManager() const { return m_pManager; }

    QtBrowserItem* getBrowserItem(BufferedVariable* a_pVariable) const ;

    void updateBrowserItem(QtBrowserItem* bitem)
    {
        updateItem(browserItemToItem(bitem));
    }


    bool isAutoSaveEnabled() const { return m_bAutoSaveEnabled; }
    void setAutoSaveEnabled(bool a_bEnabled) { m_bAutoSaveEnabled = a_bEnabled; }

    bool isAutoSaveStateEnabled() const { return m_bAutoSaveStateEnabled; }
    void setAutoSaveStateEnabled(bool a_bEnabled) { m_bAutoSaveStateEnabled = a_bEnabled; }

    void setDataBase(serialization::DataBase* a_pDataBase);
    serialization::DataBase* getDataBase() const { return m_pDataBase; }

public slots:
    void refresh();
    void reedit();
    void edit(const phantom::vector<phantom::data>& a_Data);

protected:
    void init();
    virtual void updateCustomExtraColumns( QTreeWidgetItem * item, QtProperty * property );
    virtual void updateItemLook(QtBrowserItem* item);
    QWidget* createEditor(VariableManager*a_pManager, QtProperty *property, QWidget *parent);

protected slots:
    void createPropertyPopupMenu(const QPoint& pos);
    virtual void slotVariableChanged(BufferedVariable* a_pVariable);
    virtual void slotEditorDestroyed();
    virtual void slotEditorValueChanged();

signals:
    void variableAboutToBeAccessed(BufferedVariable* a_pVariable) ;
    void variableAccessed(BufferedVariable* a_pVariable);
    void variableAboutToBeChanged(BufferedVariable* a_pVariable);
    void variableChanged(BufferedVariable* a_pVariable);

protected:
    VariableManager*        m_pManager;
    VariableWidget*         m_pOpenedEditor;
    vector<phantom::data>   m_EditedData;
    reflection::Type*       m_pEditedType;
    QMap<reflection::Type*, reflection::Class*>             m_VariableTypeToEditorClass;
    variable_value_set_delegate                             m_variable_value_set_delegate;
    serialization::DataBase*                                m_pDataBase;
    bool m_bChangingPropertyValue;
    bool m_bAutoSaveEnabled;
    bool m_bAutoSaveStateEnabled;
};


} // qt 
} // phantom 



#endif // phantom_qt_VariableEditor_h__
