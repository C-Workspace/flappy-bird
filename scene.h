#ifndef SCENE_H
#define SCENE_H
#include "pillaritem.h"
#include "birditem.h"
#include <QGraphicsScene>
#include <QTimer>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();

    void startGame();
    bool getGameON() const;
    void setGameON(bool value);

    void incrementScore();

    void setScore(int value);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
// QGraphicsScene interface
private:
    void showGameOver();
    void hideGameOver();
    void cleanPillars();
    void setUpPillarTimer();
    void freezeBirdAndPillars();

    QTimer *pillarTimer;
    birdItem *bird;

    bool gameON;

    int score;
    int bestScore;

    QGraphicsPixmapItem *gameOverPix;
    QGraphicsTextItem *scoreTextItem;
};

#endif // SCENE_H
