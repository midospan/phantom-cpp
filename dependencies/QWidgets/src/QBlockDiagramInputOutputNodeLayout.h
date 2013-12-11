#ifndef QWIDGETSINPUTOUTPUTNODESLOTLAYOUT_H
#define QWIDGETSINPUTOUTPUTNODESLOTLAYOUT_H

#include "QBlockDiagramNodeLayout.h"
#include <QVector>

class QBlockDiagramNodeSlot;

class QWIDGETS_EXPORT QBlockDiagramInputOutputNodeLayout : public QBlockDiagramNodeLayout
{
  Q_OBJECT


public:
    QBlockDiagramInputOutputNodeLayout(Qt::Orientation a_Orientation = Qt::Horizontal, int a_SectionCount = 1);
    ~QBlockDiagramInputOutputNodeLayout();

    virtual void setMinimumSpacing(qreal a_fSpacing)
    {
        m_fMinimumSpacing = a_fSpacing;
    }
    virtual void update(QRectF a_Bounds);

    virtual QSizeF  sizeHint() const;

    virtual void  addInput(int sectionIndex, QBlockDiagramNodeSlot* a_pSlot);
    virtual void  addOutput(int sectionIndex, QBlockDiagramNodeSlot* a_pSlot);
    virtual void  removeInput(int sectionIndex, QBlockDiagramNodeSlot* a_pSlot);
    virtual void  removeOutput(int sectionIndex, QBlockDiagramNodeSlot* a_pSlot);
    
    virtual QBlockDiagramNodeSlot*  slotAt(int i) const;
    virtual int                     count() const
    {
        int c = 0;
        for(auto it = m_Inputs.begin(); it != m_Inputs.end(); ++it)
        {
            c += (int)it->size();
        }
        for(auto it = m_Outputs.begin(); it != m_Outputs.end(); ++it)
        {
            c += (int)it->size();
        }
        return c;
    }
    virtual void  addSlot(QBlockDiagramNodeSlot* a_pSlot);

    size_t getInputCount() const;
    size_t getOutputCount() const;

    size_t getMaxCount(int sectionIndex) const;

protected slots:
    void slotTextChanged(const QString& );

protected:
  QVector<QVector<QBlockDiagramNodeSlot*>>   m_Inputs;
  QVector<QVector<QBlockDiagramNodeSlot*>>   m_Outputs;
  Qt::Orientation                   m_Orientation;
  int                               m_SectionCount;
  qreal                             m_fMinimumSpacing;

    
};

#endif // QWIDGETSINPUTOUTPUTNODESLOTLAYOUT_H
