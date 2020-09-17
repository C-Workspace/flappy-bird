#include "pillaritem.h"
#include "birditem.h"
#include "scene.h"
#include <QRandomGenerator>
#include <QGraphicsScene>

pillarItem::pillarItem() :
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/marioPipeInvert.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/marioPipe.png"))),
    pastBird(false)
{

    topPillar->setPos(QPointF(0,0) - QPoint(topPillar->boundingRect().width()/2,
                      topPillar->boundingRect().height() + 60));
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2,
                                                60));
    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));


    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1300);

    connect(xAnimation, &QPropertyAnimation::finished,[=](){
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();


}

pillarItem::~pillarItem()
{
    delete topPillar;
    delete bottomPillar;
}

qreal pillarItem::x() const
{
    return m_x;
}

void pillarItem::freeze()
{
    xAnimation->stop();
}

void pillarItem::setx(qreal x)
{
    m_x = x;

    if (x < 0 && !pastBird) {
        pastBird = true;
        QGraphicsScene *mScene = scene();
        Scene *myScene = dynamic_cast<Scene*>(mScene);
        if (myScene) {
            myScene->incrementScore();
        }
    }

    if (collisionDetected()) {
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPointF(x, yPos));
}

bool pillarItem::collisionDetected()
{
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());

    foreach (QGraphicsItem *item, collidingItems) {
        birdItem *birdItem = dynamic_cast<class birdItem*>(item);
        if (birdItem) {
            return true;
        }
    }
    return false;
}
