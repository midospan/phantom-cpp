
#include "QBlockDiagramNodeLayout.h"

QBlockDiagramNodeLayout::QBlockDiagramNodeLayout()
  : QObject()
  , m_pParentNode(NULL)
{

}

QBlockDiagramNodeLayout::~QBlockDiagramNodeLayout()
{

}

void QBlockDiagramNodeLayout::setParentNode( QBlockDiagramNode* a_pParentNode )
{
  m_pParentNode = a_pParentNode;
}