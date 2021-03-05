#include "mainwindow.h"
#include "cscrollscreenview.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(10,10,800,600);
//    this->setStyleSheet("background-color:black;");
    CScrollScreenView *w = new CScrollScreenView(this, 5);
    QWidget *firstPageWidget = new QLabel("111111");
    QWidget *secondPageWidget = new QLabel("222222");
    QWidget *thirdPageWidget = new QLabel("333333");
    QWidget *fourthPageWidget = new QLabel("444444");
    QWidget *fifthPageWidget = new QLabel("55555");
    w->setStyleSheet("background-color:green;");
    w->setGeometry(100,100,400,400);
    w->addPage(firstPageWidget);
    w->addPage(secondPageWidget);
    w->addPage(thirdPageWidget);
    w->addPage(fourthPageWidget);
    w->addPage(fifthPageWidget);
//    this->setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}
