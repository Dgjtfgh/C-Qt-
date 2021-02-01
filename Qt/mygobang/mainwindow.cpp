#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QFileDialog>
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(kBoardMargin*2 + kBlockSize*(kBoardSizeNum-1), kBoardMargin*2 + kBlockSize*(kBoardSizeNum-1));

    QPushButton *nextBtn = new QPushButton(this);
    nextBtn->move(kBoardMargin-75+kBlockSize*(kBoardSizeNum-1)/2,kBoardMargin*1.15+kBlockSize*(kBoardSizeNum-1));
    nextBtn->setText(tr("下一步"));
    nextBtn->setFixedSize(150, kBoardMargin*0.8);
    nextBtn->hide();
    connect(nextBtn, SIGNAL(clicked()), this, SLOT(showNext()));

    setMouseTracking(true);

    QMenu *gameMenu = menuBar()->addMenu(tr("新对局"));
    QAction *actionPVP = new QAction("双人对战", this);
    connect(actionPVP, SIGNAL(triggered()), this, SLOT(initPVPGame()));
    connect(actionPVP, SIGNAL(triggered()), nextBtn, SLOT(hide()));
    gameMenu->addAction(actionPVP);

    QAction *actionQuit = new QAction("退出", this);
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(quitGame()));
    gameMenu->addAction(actionQuit);

    QMenu *gameTool = menuBar()->addMenu(tr("工具"));
    QAction *regetAction = new QAction("悔棋", this);
    connect(regetAction, SIGNAL(triggered()), this, SLOT(regret()));
    gameTool->addAction(regetAction);

    connect(this, SIGNAL(open()), nextBtn, SLOT(show()));
    connect(this, SIGNAL(finish()), nextBtn, SLOT(hide()));

    initGame();
}

MainWindow::~MainWindow()
{
    if(gamemodel){
        delete gamemodel;
        gamemodel = nullptr;
    }
}

void MainWindow::initGame(){
    gamemodel = new game;

    initPVPGame();
}

void MainWindow::initPVPGame(){
    gamemodel->status = PLAYING;
    gamemodel->startGame();
    update();
}

void MainWindow::quitGame(){
    if(!(QMessageBox::information(this, tr("退出"), tr("是否真的要退出游戏？"), tr("是"), tr("否")))) {
        QApplication *app;
        app->exit(0);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    switch(QMessageBox::information(this, tr("退出"), tr("是否真的要退出游戏？"), tr("是"), tr("否"), 0, 1)) {
        case 0:
            event->accept();
        break;
        case 1:
        default:
            event->ignore();
        break;
    }
}

void MainWindow::regret(){
    gamemodel->regret();
    update();
}

//void MainWindow::saveGame(){
//    QString fileName = QFileDialog::getSaveFileName(this, tr("保存棋谱"), tr("棋谱文件 (*.chess)"));

//}

void MainWindow::showNext(){
    if(!gamemodel->stack.empty()){
        gamemodel->board[gamemodel->stack.last().first][gamemodel->stack.last().second] = gamemodel->playflag?1:-1;
        gamemodel->stack.removeLast();
        gamemodel->playflag = !gamemodel->playflag;
        update();
        if(gamemodel->stack.empty()){
            emit finish();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    for(int i=0; i<kBoardSizeNum; i++) {
        painter.drawLine(kBoardMargin + kBlockSize * i, kBoardMargin, kBoardMargin + kBlockSize * i, kBoardMargin + kBlockSize * (kBoardSizeNum - 1));
        painter.drawLine(kBoardMargin, kBoardMargin + kBlockSize * i, kBoardMargin + kBlockSize * (kBoardSizeNum - 1), kBoardMargin + kBlockSize * i);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    // 绘制落子标记(防止鼠标出框越界)
    if (clickPosRow >= 0 && clickPosRow < kBoardSizeNum &&
            clickPosCol>=0 && clickPosCol < kBoardSizeNum &&
            gamemodel->board[clickPosRow][clickPosCol] == 0) {
        if(gamemodel->playflag) {
            brush.setColor(Qt::white);
        } else {
            brush.setColor(Qt::black);
        }
        painter.setBrush(brush);
        painter.drawRect(kBoardMargin + kBlockSize * clickPosCol - kMarkSize / 2, kBoardMargin + kBlockSize * clickPosRow - kMarkSize / 2, kMarkSize, kMarkSize);
    }

    // 绘制棋子
    for(int i = 0; i < kBoardSizeNum; i++) {
        for (int j = 0; j < kBoardSizeNum; j++) {
            if (gamemodel->board[i][j] == 1){
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
            } else if (gamemodel->board[i][j] == -1){
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
            }
        }
    }

    // 判断输赢
    if(clickPosRow >= 0 && clickPosRow < kBoardSizeNum &&
            clickPosCol >=0 && clickPosCol < kBoardSizeNum &&
            (gamemodel->board[clickPosRow][clickPosCol] == 1 ||
             gamemodel->board[clickPosRow][clickPosCol] == -1)) {
        if(gamemodel->isWin(clickPosRow, clickPosCol) && gamemodel->status == PLAYING) {
            qDebug() << "win";
            gamemodel->status = WIN;
            QString str;
            if (gamemodel->board[clickPosRow][clickPosCol] == 1)
                str = "白棋";
            else if (gamemodel->board[clickPosRow][clickPosCol] == -1)
                str = "黑棋";
            if (!QMessageBox::information(this, "游戏结束", str+"获胜！"));

            // 重置游戏
            gamemodel->startGame();
            gamemodel->status = PLAYING;
        }
    }

    // 判断死局
    if (gamemodel->isDeadGame()){
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "oops", "dead game!");
        if (btnValue == QMessageBox::Ok) {
            gamemodel->startGame();
            gamemodel->status = PLAYING;
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (gamemodel->status == OPEN) {
        clickPosRow = -1;
        clickPosCol = -1;
        return;
    }

    int x = event->x();
    int y = event->y();

    // 棋盘边缘不能落子
    if (x >= kBoardMargin-kBlockSize/2 &&
            x < size().width()-kBoardMargin &&
           y >= kBoardMargin-kBlockSize/2 &&
            y < size().height()-kBoardMargin ) {
        // 获取最近的左上角的点
        int col = x / kBlockSize;
        int row = y / kBlockSize;

        int leftTopPosX = kBoardMargin + kBlockSize * col;
        int leftTopPosY = kBoardMargin + kBlockSize * row;

        // 根据距离算出合适的点击位置，周围四个位置，半径距离选最近
        clickPosRow = -1;
        clickPosCol = -1;
        int len = 0;

        len = sqrt((x-leftTopPosX)*(x-leftTopPosX) + (y-leftTopPosY)*(y-leftTopPosY));
        if (len < kPosDelta) {
            clickPosCol = col;
            clickPosRow = row;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta) {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta) {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta) {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    chessOneByPerson();
}

void MainWindow::chessOneByPerson(){
    // 根据当前存储的坐标下子  只有有效点击才下子
    if (clickPosRow != -1 && clickPosCol != -1 && gamemodel->board[clickPosRow][clickPosCol] == 0) {
        gamemodel->actionByPerson(clickPosRow, clickPosCol);
        update();
    }
}
