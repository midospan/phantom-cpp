
#include "QBlockDiagramInputOutputNodeLayout.h"
#include "QBlockDiagramNodeSlot.h"
#include "QBlockDiagramNode.h"
#include <QGraphicsSimpleTextItem>
#include <qmath.h>

QBlockDiagramInputOutputNodeLayout::QBlockDiagramInputOutputNodeLayout(Qt::Orientation orientation, int a_SectionCount /*= 1*/)
  : QBlockDiagramNodeLayout()
  , m_fMinimumSpacing(20)
  , m_Orientation(orientation)
  , m_SectionCount(a_SectionCount)
{
    Q_ASSERT(a_SectionCount > 0);
    m_Inputs.resize(a_SectionCount);
    m_Outputs.resize(a_SectionCount);
}

QBlockDiagramInputOutputNodeLayout::~QBlockDiagramInputOutputNodeLayout()
{

}

void QBlockDiagramInputOutputNodeLayout::update( QRectF a_Bounds )
{
    int max_inout_count = qMax(getInputCount(), getOutputCount());
    if(m_Orientation == Qt::Horizontal)
    {
        qreal h = a_Bounds.height();
        {
            qreal spacing = h/(max_inout_count+m_SectionCount);
            qreal yOffset = spacing;
            int s = 0;
            for(;s<m_Inputs.count(); ++s)
            {
                auto& inputs = m_Inputs[s];
                int i = 0;
                for(;i<inputs.count();++i)
                {
                    qreal x = a_Bounds.x();
                    qreal y = a_Bounds.y()+yOffset;
                    inputs[i]->setPos(x, y);
                    inputs[i]->getTextItem()->setPos(20.f, -1-inputs[i]->getTextItem()->boundingRect().height()/2);
                    inputs[i]->setLinkDirectionAngle(180);
                    yOffset += spacing;
                }
                yOffset = (getMaxCount(s)+2)*spacing;
            }
        }
        {
            qreal spacing = h/(max_inout_count+m_SectionCount);
            qreal yOffset = spacing;
            int s = 0;
            for(;s<m_Outputs.count(); ++s)
            {
                auto& outputs = m_Outputs[s];
                int i = 0;
                for(;i<outputs.count();++i)
                {
                    qreal x = a_Bounds.x()+a_Bounds.width();
                    qreal y = a_Bounds.y()+yOffset;
                    outputs[i]->setPos(x, y);
                    outputs[i]->getTextItem()->setPos(-20.f-outputs[i]->getTextItem()->boundingRect().width(), -1-outputs[i]->getTextItem()->boundingRect().height()/2);
                    outputs[i]->setLinkDirectionAngle(0);
                    yOffset += spacing;
                }
                yOffset = (getMaxCount(s)+2)*spacing;
            }
        }
    }
    else
    {
        qreal w = a_Bounds.width();
        {
            qreal spacing = w/(max_inout_count+m_SectionCount);
            qreal xOffset = spacing;
            int s = 0;
            for(;s<m_Inputs.count(); ++s)
            {
                auto& inputs = m_Inputs[s];
                int i = 0;
                for(;i<inputs.count();++i)
                {
                    inputs[i]->setPos(a_Bounds.x()+xOffset, a_Bounds.y());
                    inputs[i]->setLinkDirectionAngle(-90);
                    xOffset += spacing;
                }
                xOffset = (getMaxCount(s)+2)*spacing;
            }
        }
        {
            qreal spacing = w/(max_inout_count+m_SectionCount);
            qreal dw = spacing;
            qreal xOffset = spacing;
            int s = 0;
            for(;s<m_Outputs.count();++s)
            {
                auto& outputs = m_Outputs[s];
                int i = 0;
                for(;i<outputs.count();++i)
                {
                    outputs[i]->setPos(a_Bounds.x()+xOffset, a_Bounds.y()+a_Bounds.height());
                    outputs[i]->setLinkDirectionAngle(90);
                    xOffset += spacing;
                }
                xOffset = (getMaxCount(s)+2)*spacing;
            }
        }
    }
}

QBlockDiagramNodeSlot* QBlockDiagramInputOutputNodeLayout::slotAt( int index ) const
{
    int c = 0;
    for(int i = 0; i<m_Inputs.count(); ++i)
    {
        auto& inputs = m_Inputs[i];
        if((index - c) < inputs.count())
        {
            return inputs[index-c];
        }
        c+= inputs.size();
    }
    for(int i = 0; i<m_Outputs.count(); ++i)
    {
        auto& outputs = m_Outputs[i];
        if((index - c) < outputs.count())
        {
            return outputs[index-c];
        }
        c += outputs.size();
    }
    Q_ASSERT(false);
    return nullptr;
}

void QBlockDiagramInputOutputNodeLayout::addSlot( QBlockDiagramNodeSlot* a_pSlot )
{
  if(count()%2 == 1)
  {
    addOutput(0, a_pSlot);
  }
  else
  {
    addInput(0, a_pSlot);
  }
}

QSizeF QBlockDiagramInputOutputNodeLayout::sizeHint() const
{

    int max_inout_count = qMax(getInputCount(), getOutputCount());
    qreal min_height = (max_inout_count+m_SectionCount)*m_fMinimumSpacing;
  
    qreal max_input_text_width = 0.f;
    auto it = m_Inputs.begin();
    auto end = m_Inputs.end();
    for(;it!=end;++it)
    {
        auto& inputs = *it;
        auto it = inputs.begin();
        auto end = inputs.end();
        for(;it!=end;++it)
        {
            QGraphicsSimpleTextItem* pTextItem = (*it)->getTextItem();
            qreal width = pTextItem->boundingRect().width();
            if(width > max_input_text_width)
            {
                max_input_text_width = width;
            }
        }
    }
    qreal max_output_text_width = 0.f;
    it = m_Outputs.begin();
    end = m_Outputs.end();
    for(;it!=end;++it)
    {
        auto& outputs = *it;
        auto it = outputs.begin();
        auto end = outputs.end();
        for(;it!=end;++it)
        {
            QGraphicsSimpleTextItem* pTextItem = (*it)->getTextItem();
            qreal width = pTextItem->boundingRect().width();
            if(width > max_output_text_width)
            {
                max_output_text_width = width;
            }
        }
    }

    qreal min_width = max_input_text_width + 100.f + max_output_text_width;

    return (m_Orientation == Qt::Horizontal) 
        ? QSizeF(min_width, min_height)
        : QSizeF(min_height, min_width);
}

void QBlockDiagramInputOutputNodeLayout::addInput( int sectionIndex, QBlockDiagramNodeSlot* a_pSlot )
{
    m_Inputs[sectionIndex].append(a_pSlot);
    connect(a_pSlot, SIGNAL(textChanged(const QString&)), this, SLOT(slotTextChanged(const QString&)));
    if(m_pParentNode) 
    {
        m_pParentNode->addSlot(a_pSlot);
        m_pParentNode->updateGeometry();
    }
}

void QBlockDiagramInputOutputNodeLayout::addOutput( int sectionIndex, QBlockDiagramNodeSlot* a_pSlot )
{
    m_Outputs[sectionIndex].append(a_pSlot);
    connect(a_pSlot, SIGNAL(textChanged(const QString&)), this, SLOT(slotTextChanged(const QString&)));
    if(m_pParentNode) 
    {
        m_pParentNode->addSlot(a_pSlot);
        m_pParentNode->updateGeometry();
    }
}

void QBlockDiagramInputOutputNodeLayout::removeInput( int sectionIndex, QBlockDiagramNodeSlot* a_pSlot )
{
    m_Inputs[sectionIndex].erase(std::find(m_Inputs[sectionIndex].begin(), m_Inputs[sectionIndex].end(), a_pSlot));
    if(m_pParentNode) 
    {
        m_pParentNode->removeSlot(a_pSlot);
    }
}

void QBlockDiagramInputOutputNodeLayout::removeOutput( int sectionIndex, QBlockDiagramNodeSlot* a_pSlot )
{
    m_Outputs[sectionIndex].erase(std::find(m_Outputs[sectionIndex].begin(), m_Outputs[sectionIndex].end(), a_pSlot));
    if(m_pParentNode) 
    {
        m_pParentNode->removeSlot(a_pSlot);
    }
}

void QBlockDiagramInputOutputNodeLayout::slotTextChanged( const QString& text )
{
    if(m_pParentNode)
    {
        m_pParentNode->updateGeometry();
    }
}

size_t QBlockDiagramInputOutputNodeLayout::getInputCount() const
{
    size_t inputCount = 0;
    for(auto it = m_Inputs.begin(); it != m_Inputs.end(); ++it)
    {
        inputCount += it->size();
    }
    return inputCount;
}

size_t QBlockDiagramInputOutputNodeLayout::getOutputCount() const
{
    size_t outputCount = 0;
    for(auto it = m_Outputs.begin(); it != m_Outputs.end(); ++it)
    {
        outputCount += it->size();
    }
    return outputCount;
}

size_t QBlockDiagramInputOutputNodeLayout::getMaxCount( int sectionIndex ) const
{
    return std::max(m_Inputs[sectionIndex].count(), m_Outputs[sectionIndex].count());
}
