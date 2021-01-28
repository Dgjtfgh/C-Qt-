#ifndef SNAKE_H
#define SNAKE_H

//#include "gamecontroller.h"
//#include "foodbock.h"
#include <QGraphicsItem>
#include <QWidget>
#include <QRectF>
#include <QPainter>
#include <QPainterPath>

class GameController;

class snake:public QGraphicsItem
{
//    Q_OBJECT
public:
    snake(GameController & controller);
    ~snake();
    enum Direction {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setMoveDirection(Direction direction);
    Direction currentDirection();
//signals:
//    void ateFood(Food * food);
//    void ateItself();

protected:
    void advance(int phase);

private:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void handleCollisions();
    QPointF head;
    int growing;
    int speed;
    QList<QPointF> tail;
    int tickCounter;
    Direction moveDirection;
    GameController &controller;
};

#endif //  SNAKE_H
