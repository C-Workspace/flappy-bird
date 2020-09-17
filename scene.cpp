#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),\
    gameON(false), score(0), bestScore(0)
{
    setUpPillarTimer();
}

void Scene::addBird()
{
    bird = new birdItem(QPixmap(":/images/bird.png"));
    addItem(bird);
}

void Scene::startGame()
{
    bird->startFlying();

    if (!pillarTimer->isActive()) {
        cleanPillars();
        setGameON(true);
        setScore(0);
        hideGameOver();
        pillarTimer->start(1000);
    }

}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer, &QTimer::timeout, [=](){


        pillarItem *pillarItem = new class pillarItem();
        connect(pillarItem, &pillarItem::collideFail, [=](){
            pillarTimer->stop();
            freezeBirdAndPillars();
            setGameON(false);
            showGameOver();
        });
    addItem(pillarItem);
    });
}

void Scene::freezeBirdAndPillars()
{
    bird->freeze();

    QList<QGraphicsItem*> sceneItems = items();
    foreach (QGraphicsItem *item, sceneItems) {
        pillarItem *pillar = dynamic_cast<pillarItem*>(item);
        if (pillar) {
            pillar->freeze();
        }
    }
}

void Scene::setScore(int value)
{
    score = value;
}

bool Scene::getGameON() const
{
    return gameON;
}

void Scene::setGameON(bool value)
{
    gameON = value;
}

void Scene::incrementScore()
{
    score++;
    if (score > bestScore) {
        bestScore = score;
    }
    qDebug() << "Score : " << score << "Best Score : " << bestScore;
}

void Scene::cleanPillars()
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach (QGraphicsItem *item, sceneItems) {
        pillarItem *pillar = dynamic_cast<pillarItem*>(item);\
        if (pillar) {
            removeItem(pillar);
            delete pillar;
        }
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        if (gameON) {
            bird->shootUp();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (gameON) {
            bird->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::showGameOver()
{
//    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/images/gameOver.png"));
//    addItem(gameOverPix);
//    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
//                                                gameOverPix->boundingRect().height()/2));

//    scoreTextItem = new QGraphicsTextItem();

//    QString htmlString = "<p> Score : " + QString::number(score) + "</p>"
//            + "<p> Best Score: " + QString::number(bestScore) + "</p";

//    QFont mFont("Consolas", 30, QFont::Bold);

//    scoreTextItem->setHtml(htmlString);
//    scoreTextItem->setFont(mFont);
//    scoreTextItem->setDefaultTextColor(Qt::red);
//    addItem(scoreTextItem);

//    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2,
//                                                 -gameOverPix->boundingRect().height()/2));
}

void Scene::hideGameOver()
{
//        if (gameOverPix) {
//            removeItem(gameOverPix);
//            delete gameOverPix;
//            gameOverPix = nullptr;
//        }

//        if (scoreTextItem) {
//            removeItem(scoreTextItem);
//            delete scoreTextItem;
//            scoreTextItem = nullptr;
//        }
}
