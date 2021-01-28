#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamecontroller.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void adjustViewSize();
    void newGame();
    void gameHelp();
    void about();

private:
    void createAction();
    void createMenus();
    void initScene();
    void initSceneBackground();

    QGraphicsScene *scene;
    QGraphicsView *view;
    GameController *game;
    QAction *newGameAcction;
    QAction *pauseAcction;
    QAction *resumeAcction;
    QAction *exitAcction;
    QAction *gameHelpAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

};

#endif //  MAINWINDOW_H
