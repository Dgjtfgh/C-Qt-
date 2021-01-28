#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QAction>
#include <iostream>
#include <qDebug>
#include "gamecontroller.h"
#include "foodbock.h"
#include "snake.h"

GameController::GameController(QGraphicsScene &scene, QObject *parent):
    QObject(parent),
    scene(scene),
    s(new snake(*this)),
    isPause(false)
{
//    s= new snake();
    timer.start(1000/33);

    Food *a1 = new Food(0, -50);
    scene.addItem(a1);
    scene.addItem(s);

    scene.installEventFilter(this);
//    connect(s, SIGNAL(ateFood(Food*)), this, SLOT(snakeAteFood(Food*));
//    connect(s, &snake::ateItself, this, &GameController::snakeAteItself);
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    isPause = false;
}

GameController::~GameController()
{
}

void GameController::snakeAteFood(Food *food){
        scene.removeItem(food);
        addNewFood();
    }

void GameController::snakeAteItself(){
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::handleKeyPressed(QKeyEvent *event){
    if(!isPause){
        switch(event->key()){
        case Qt::Key_Left:
            s->setMoveDirection(snake::MoveLeft);
            break;
        case Qt::Key_Right:
            s->setMoveDirection(snake::MoveRight);
            break;
        case Qt::Key_Up:
            s->setMoveDirection(snake::MoveUp);
            break;
        case Qt::Key_Down:
            s->setMoveDirection(snake::MoveDown);
            break;
        case Qt::Key_Space:
            pause();
            break;
        }
    } else resume();
}

void GameController::addNewFood(){
    int x, y;
    do {
        x = (int)(qrand()%200)/10-10;
        y = (int)(qrand()%200)/10-10;

        x*=10;
        y*=10;
    } while(s->shape().contains(s->mapFromScene(QPointF(x+5, y+5))));

    Food *food = new Food(x, y);
    qDebug()<< "("<<x<<","<<y<<")";
    scene.addItem(food);
}

void GameController::gameOver(){
    disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    if (QMessageBox::Yes == QMessageBox::information(NULL,
                tr("游戏失败！"), tr("再来一局？"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)) {
        connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
        scene.clear();

        s = new snake(*this);
        scene.addItem(s);
        addNewFood();
    } else {
        exit(0);
    }
}

void GameController::pause(){
    disconnect(&timer, SIGNAL(timeout()),
               &scene, SLOT(advance()));
    isPause = true;
    setResum();
}

void GameController::resume(){
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    isPause = false;
    setResum();
}

void GameController::setResum() {
    if(isPause == true) {
        resumeAction->setEnabled(true);
    } else {
        resumeAction->setEnabled(false);
    }
}

bool GameController::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}
