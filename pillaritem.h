#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class pillarItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setx);
public:
    explicit pillarItem();
    ~pillarItem();

    qreal x() const;

    void freeze();

signals:
    void collideFail();

public slots:

    void setx(qreal x);

private:
    bool collisionDetected();
    QGraphicsItem *topPillar;
    QGraphicsItem *bottomPillar;
    QPropertyAnimation *xAnimation;
    int yPos;

    qreal m_x;
    bool pastBird;
};

#endif // PILLARITEM_H
