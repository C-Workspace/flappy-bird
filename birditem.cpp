#include "birditem.h"

#include <QTimer>
#include <QGraphicsScene>

birdItem::birdItem(QPixmap pixMap) :
    wingPosition(WingPosition::Up),\
    wingDirection(0)
{
    setPixmap(pixMap);

    QTimer *birdWingsTimer = new QTimer(this);
    connect(birdWingsTimer, &QTimer::timeout,[=]() {
        updatePixMap();
    });

    birdWingsTimer->start(80);

    groundPosition = scenePos().y() + 290;

    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

    rotationAnimation = new QPropertyAnimation(this, "rotation", this);
}

qreal birdItem::rotation() const
{
    return m_rotation;
}

qreal birdItem::y() const
{
    return m_y;
}

void birdItem::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal curPosY = y();

    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(285);

    connect(yAnimation, &QPropertyAnimation::finished, [=](){
        fallToGround();
    });

    yAnimation->start();

    rotateTo(-20, 200, QEasingCurve::OutCubic);
}

void birdItem::startFlying()
{
    yAnimation->start();
    rotateTo(90, 1200, QEasingCurve::InQuad);
}

void birdItem::freeze()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void birdItem::setRotation(qreal rotation)
{
    m_rotation = rotation;

    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(rotation);
    t.translate(-c.x(), -c.y());
    setTransform(t);
}

void birdItem::setY(qreal y)
{
    moveBy(0,y-m_y);
    m_y = y;
}

void birdItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();
}

void birdItem::fallToGround()
{
    if (y() < groundPosition) {

        rotationAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setEndValue(groundPosition);
        yAnimation->start();

        rotateTo(90, 1100, QEasingCurve::InCubic);



    }
}

void birdItem::updatePixMap()
{
    if (wingPosition == WingPosition::Middle) {

        if (wingDirection) {
            // Up
            setPixmap(QPixmap(":/images/bird.png"));
            wingPosition == WingPosition::Up;
            wingDirection = 0;
        }else {
            // Down
            setPixmap(QPixmap(":/images/bird.png"));
            wingPosition == WingPosition::Down;
            wingDirection = 1;
        }
    }else {
        setPixmap(QPixmap(":/images/bird.png"));
        wingPosition = WingPosition::Middle;
    }
}
