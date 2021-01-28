#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
//#include <QGraphicsScene>
//#include <QKeyEvent>
#include <QAction>
#include <QTimer>
//#include "snake.h"
//#include "foodbock.h"
//#include "wall.h"
class QGraphicsScene;
class QKeyEvent;

class snake;
class Food;
class Wall;

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QObject *parent = 0);
    ~GameController();
    void snakeAteFood(Food *food);
    void snakeAteItself();
    QAction *getResmueAction() {return resumeAction;}
    void setResumeAction(QAction* r){ resumeAction = r;}

public slots:
    void pause();
    void resume();
    void gameOver();


protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    snake *s;
    void handleKeyPressed(QKeyEvent *event);
    void addNewFood();
    void setResum();
    QAction *resumeAction;
    QTimer timer;
    QGraphicsScene &scene;
    bool isPause;
};

#endif //  GAMECONTROLLER_H
