
#include "QBlockDiagramTest.h"
#include "QBlockDiagramView.h"
#include "QBlockDiagramModel.h"
#include "QBlockDiagramNode.h"
#include "QBlockDiagramNodeSlot.h"
#include "QBlockDiagramLink.h"
#include "QBlockDiagramLinkEnd.h"
#include "QBlockDiagramInputOutputNodeLayout.h"
#include <qmath.h>

QBlockDiagramTest::QBlockDiagramTest(QWidget *parent)
    : QMainWindow(parent)
{

  QBlockDiagramView* view = new QBlockDiagramView();
  QBlockDiagramModel* model = new QBlockDiagramModel();
  QBlockDiagramNode* node0 = new QBlockDiagramNode();
  QBlockDiagramNode* node1 = new QBlockDiagramNode();

  node0->setNodeFlag(AutoGenerateLink);
  node1->setNodeFlag(AutoGenerateLink);

//   QBlockDiagramLink* link = new QBlockDiagramLink();
//   QBlockDiagramLink* link2 = new QBlockDiagramLink();
//   link->getEnd(QBlockDiagramLink::eFirst)->setPos(100, 200);
//   link->getEnd(QBlockDiagramLink::eSecond)->setPos(300, 200);

  model->addItem(node0);
  model->addItem(node1);
  //model->addItem(link);
 // model->addItem(link2);
  view->setScene(model);

  QBlockDiagramInputOutputNodeLayout* pLayout0 = new QBlockDiagramInputOutputNodeLayout(Qt::Horizontal);
  QBlockDiagramInputOutputNodeLayout* pLayout1 = new QBlockDiagramInputOutputNodeLayout(Qt::Horizontal);
  pLayout0->setMinimumSpacing(32.f);
  pLayout1->setMinimumSpacing(32.f);
  node0->setLayout(pLayout0);
  node1->setLayout(pLayout1);

  node0->setPos(300,300);

  int i = 0;
  int count = 16;
  QBlockDiagramNodeSlot** slot_array_0 = new QBlockDiagramNodeSlot*[count];
  QBlockDiagramNodeSlot** slot_array_1 = new QBlockDiagramNodeSlot*[count];
  

    for(;i<count;++i)
    {
        slot_array_0[i] = new QBlockDiagramNodeSlot(QString("slot")+QString::number(i));
        slot_array_1[i] = new QBlockDiagramNodeSlot(QString("slot")+QString::number(i));
        pLayout0->addSlot(slot_array_0[i]);
        pLayout1->addSlot(slot_array_1[i]);
    }
    setCentralWidget(view);
}

QBlockDiagramTest::~QBlockDiagramTest()
{

}
