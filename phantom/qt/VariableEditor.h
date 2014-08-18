#ifndef o_qt_VariableEditor_h__
#define o_qt_VariableEditor_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
#include "QtTreePropertyBrowser.h"
#include "qtpropertymanager.h"
/* **************** Declarations ***************** */
class QPushButton;
o_declareN(class, (phantom, qt), VariableEditor);
/* *********************************************** */

namespace phantom { namespace qt {

class VariableNode;
class VariableWidget;
class VariableEditor;
class VariableModel;
class VariableEditorFactory;
class CollectionElementVariable;
class VariableWidgetEditor;
class VariableEditorManager;

class o_qt_export VariableEditor : public QtTreePropertyBrowser 
{
    Q_OBJECT

    friend class VariableEditorFactory;
    friend class VariableAction;
    friend class VariableModel;

public:
    typedef fastdelegate::FastDelegate< void ( VariableEditor* a_pVariableEditor, VariableNode* a_pVariable, void const* a_ppValueSources ) > variable_value_set_delegate;

    static void     defaultVariableValueSetDelegate(VariableEditor* a_pVariableEditor, VariableNode* a_pVariable, void const* a_pValue);

public:
    VariableEditor(const QString& variableColumnName);
    ~VariableEditor(void);

	o_initialize() {};

    void    setVariableValueSetDelegate(variable_value_set_delegate d);

    void    registerVariableTypeEditorClass(reflection::Type* a_pType, reflection::Class* a_pClass);

    VariableModel* getVariableModel() const { return m_pVariableModel; }
    void setVariableModel(VariableModel* a_pVariableModel);

    QtBrowserItem* getBrowserItem(VariableNode* a_pVariable) const ;

    void updateBrowserItem(QtBrowserItem* bitem)
    {
        updateItem(browserItemToItem(bitem));
    }

    bool isAutoSaveEnabled() const { return m_bAutoSaveEnabled; }
    void setAutoSaveEnabled(bool a_bEnabled) { m_bAutoSaveEnabled = a_bEnabled; }

    bool isAutoSaveStateEnabled() const { return m_bAutoSaveStateEnabled; }
    void setAutoSaveStateEnabled(bool a_bEnabled) { m_bAutoSaveStateEnabled = a_bEnabled; }


    void registerProperty(QtProperty* property, VariableNode* a_pVariable);

    QtProperty* unregisterProperty(VariableNode* a_pVariable);

    QString valueText(const QtProperty *property) const;
    QString valueText( VariableNode* a_pVariable ) const;
    QIcon   valueIcon(const QtProperty *property) const;
    QIcon   valueIcon( VariableNode* a_pVariable ) const;

    VariableNode*  getVariableNode(QtProperty* property) const;

    QtProperty* getProperty(VariableNode* a_pVariable) const;

protected:
    void variableNodeExpressionsAboutToBeAssigned(VariableNode* a_pVariableNode);
    void variableNodeExpressionsAssigned(VariableNode* a_pVariableNode);
    void variableNodeAboutToBeAccessed(VariableNode* a_pVariableNode);
    void variableNodeAccessed(VariableNode* a_pVariableNode);

public slots:
    void refresh();
    void reedit();

protected:
    void init();
    virtual void updateCustomExtraColumns( QTreeWidgetItem * item, QtProperty * property );
    virtual void updateItemLook(QtBrowserItem* item);
    QWidget* createEditor(VariableEditor*a_pThis, QtProperty *property, QWidget *parent);

protected slots:
    void createPropertyPopupMenu(const QPoint& pos);
    virtual void slotVariableChanged(VariableNode* a_pVariable);
    virtual void slotEditorDestroyed();
    virtual void slotEditorValueChanged();
    void variableChildNodeAdded( VariableNode* a_pVariableNode );
    void variableChildNodeAboutToBeRemoved( VariableNode* a_pVariableNode );
    void columnSectionResized(int logicalIndex, int oldSize, int newSize);

signals:
    void variableAboutToBeAccessed(VariableNode* a_pVariable) ;
    void variableAccessed(VariableNode* a_pVariable);
    void variableAboutToBeChanged(VariableNode* a_pVariable);
    void variableChanged(VariableNode* a_pVariable);

protected:
    VariableModel*                      m_pVariableModel;
    VariableWidget*                     m_pOpenedEditor;
    VariableEditorManager*              m_pManager;
    map<QtProperty*, VariableNode*>     m_Variables;
    map<VariableNode*, QtProperty*>     m_Properties;
    vector<phantom::data>               m_EditedData;
    reflection::Type*                   m_pEditedType;

    QMap<reflection::Type*, reflection::Class*> m_VariableTypeToEditorClass;
    variable_value_set_delegate                 m_variable_value_set_delegate;
    int                                 m_iUserValueColumnWidth;
    bool m_bChangingPropertyValue;
    bool m_bAutoSaveEnabled;
    bool m_bAutoSaveStateEnabled;
};


} // qt 
} // phantom 



#endif // phantom_qt_VariableEditor_h__
