#ifndef QWIDGETSITEM_H
#define QWIDGETSITEM_H

#include "QWidgetsPrerequisites.h"
#include <QGraphicsObject>

class QBlockDiagramModel;

class QWIDGETS_EXPORT QBlockDiagramItem : public QGraphicsObject
{
  Q_OBJECT

public:
    QBlockDiagramItem();
    QBlockDiagramItem(const QString& a_strName);
    ~QBlockDiagramItem();
  
    QBlockDiagramModel* scene() const;

    const QString& getName() const { return m_strName; }

    void setName(const QString& a_strName) { m_strName = a_strName; }

    virtual bool isNodeSlot() const { return false; }
    virtual bool isLinkEnd() const { return false; }
    virtual bool isLink() const { return false; }
    virtual bool isNode() const { return false; }
    virtual bool isConnector() const { return false; }

    virtual void terminate() 
    {
        prepareGeometryChange();
    }

    void  deferDestruction();

    void setUserData(void* a_pUserData)
    {
        m_pUserData = a_pUserData;
    }

    void*   getUserData() const { return m_pUserData; }

    virtual void destroyMe() { delete this; }
    
signals:
    void moved();

protected slots:
    virtual   void prepareGeometryChangeSlot() { prepareGeometryChange(); }

private:
  QString       m_strName;
  void*         m_pUserData;
    
};

#endif // QWIDGETSITEM_H
