#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTranslator>
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    t = new QTranslator(qApp);
    if(t->load(":/resources/tr_zh.qm"))
    {
         qApp->installTranslator(t);
    }
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){
    ui->label->setText(tr("study hard and make progress every day."));
    ui->pushButton->setText(tr("setting"));
    d = new settingDialog;
    connect(ui->pushButton, &QPushButton::clicked, d, &settingDialog::show);
    connect(d, &settingDialog::changeLanguang, this, &MainWindow::changeLanguang);
}

void MainWindow::changeLanguang(LANGUAGE language){
    if(t)
    {
        qApp->removeTranslator(t);
        delete t;
        t = NULL;
        qDebug()<<"clear";
    }
    t = new QTranslator(qApp);
    switch (language) {
    case UI_ZH:
        t->load(":/resources/tr_zh.qm");
        qDebug()<<UI_ZH<<"UI_ZH";
        break;
    case UI_EN:
        t->load(":/resources/tr_en.qm");
        qDebug()<<UI_EN<<"UI_EN";
        break;
    }
    if(t->load(":/resources/tr_zh.qm"))
    {
        qDebug()<<"install";
        qApp->installTranslator(t);
    }
    repaint();
}
