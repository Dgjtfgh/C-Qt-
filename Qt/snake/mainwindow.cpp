#include "mainwindow.h"
#include "config.h"
#include "gamecontroller.h"
#include <QApplication>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    scene(new QGraphicsScene(this)),
    view(new QGraphicsView(scene, this)),
    game(new GameController(*scene, this))
{
    setCentralWidget(view);
//    resize(600, 600);
    setFixedSize(600, 600);

    createAction();
    createMenus();
    initScene();
    initSceneBackground();

    QTimer::singleShot(0, this, SLOT(adjustViewSize()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::adjustViewSize(){
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::createAction(){
    newGameAcction = new QAction(tr("&新游戏"), this);
    newGameAcction->setShortcuts(QKeySequence::New);
    newGameAcction->setStatusTip(tr("开始一局新游戏"));
    connect(newGameAcction, &QAction::triggered, this, &MainWindow::newGame);

    exitAcction = new QAction(tr("&退出"), this);
    exitAcction->setShortcut(tr("Ctrl+Q"));
    exitAcction->setStatusTip(tr("退出游戏"));
    connect(exitAcction, &QAction::triggered, this, &MainWindow::close);

    pauseAcction = new QAction(tr("&暂停"), this);
    pauseAcction->setStatusTip(tr("暂停..."));
    connect(pauseAcction, &QAction::triggered, game, &GameController::pause);

    resumeAcction = new QAction(tr("&继续"), this);
    resumeAcction->setStatusTip(tr("继续..."));
    resumeAcction->setEnabled(false);
    game->setResumeAction(resumeAcction);
    connect(resumeAcction, &QAction::triggered, game, &GameController::resume);

    gameHelpAction = new QAction(tr("&帮助"), this);
    gameHelpAction->setShortcut(tr("Ctrl+H"));
    gameHelpAction->setStatusTip(tr("游戏帮助"));
    connect(gameHelpAction, &QAction::triggered, this, &MainWindow::gameHelp);

    aboutAction = new QAction(tr("&关于"), this);
    aboutAction->setStatusTip(tr("显示应用的关于页面"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    aboutQtAction = new QAction(tr("关于&Qt"), this);
    aboutQtAction->setStatusTip(tr("显示Qt的about页"));
    connect(aboutQtAction, &QAction::triggered, qApp, QApplication::aboutQt);
}

void MainWindow::createMenus() {
    QMenu *options = menuBar()->addMenu(tr("&开始"));
    options->addAction(newGameAcction);
    options->addSeparator();
    options->addAction(pauseAcction);
    options->addAction(resumeAcction);
    options->addSeparator();
    options->addAction(exitAcction);

    QMenu *help = menuBar()->addMenu(tr("&帮助"));
    help->addAction(gameHelpAction);
    help->addAction(aboutAction);
    help->addAction(aboutQtAction);
}

void MainWindow::initScene()
{
    scene->setSceneRect(-100, -100, 200, 200);
}

void MainWindow::initSceneBackground()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::white));
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}

void MainWindow::newGame(){
    QTimer::singleShot(0, game, SLOT(gameOver()));
}

void MainWindow::about(){
    QMessageBox::about(this, tr("关于游戏"), tr("<h2>贪吃蛇游戏</h2>"
                                            "<p>此处省略五百字......</p>"));
}

void MainWindow::gameHelp(){
    QMessageBox::about(this, tr("游戏帮助"), tr("利用方向键控制蛇的行走方向，让蛇吃到食物 <p>空格键控制暂停和继续</p>"));
}
