#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

signals:
    void finish();
    void open();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    game *gamemodel;
    int clickPosRow, clickPosCol;
    void initGame();
    void checkGame(int y, int x);
    void saveGame();

private slots:
    void chessOneByPerson();

    void initPVPGame();

//    void openGame();
    void quitGame();
    void regret();
    void showNext();
};

#endif // MAINWINDOW_H
