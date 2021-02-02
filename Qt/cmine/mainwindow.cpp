#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    difficulty=1;
    ui->setupUi(this);
    cmine=new Cmine(this,9,9,10);
    ui->horizontalLayout->insertWidget(0,cmine);
    ui->label_2->setText(QString::number(cmine->count));
    ui->label_5->setText(QString::number(cmine->hqcount));
    connect(cmine,SIGNAL(sig_lost()),this,SLOT(slot_lost()));
    connect(cmine,SIGNAL(sig_count()),this,SLOT(slot_count()));
    connect(cmine,SIGNAL(changehqcount()),this,SLOT(changhqcount()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_lost()
{
    ui->label_3->setText("你完蛋了，哈哈！");
//    QString title = "恭喜恭喜！";
//    QString text = "你完蛋了，哈哈！";
//    QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon,title, text,QMessageBox::Ok, this, Qt::MSWindowsFixedSizeDialogHint);
//    msg->show();
    QMessageBox msg;
    msg.setText("你完蛋了，哈哈！");
    msg.setWindowTitle("恭喜恭喜！");
//    msg.setParent(this);
    msg.exec();

}

void MainWindow::changhqcount(){
    ui->label_5->setText(QString::number(cmine->hqcount));
}

void MainWindow::slot_count()
{
    ui->label_2->setText(QString::number(cmine->count));
    if(cmine->count==0&&cmine->hqcount==0)
    {
        ui->label_3->setText("可以呀，小老弟！");
        QMessageBox msg;
        msg.setText("可以呀，小老弟！胜利啦");
        msg.setWindowTitle("恭喜恭喜！");
        msg.exec();
    }
}

void MainWindow::on_pushButton_clicked()
{
    Cmine* _cmine=new Cmine(this,cmine->row,cmine->col,cmine->num_mine,cmine->d);
    delete cmine;
    cmine=_cmine;
    ui->horizontalLayout->insertWidget(0,cmine);
    ui->label_2->setText(QString::number(cmine->count));
    ui->label_5->setText(QString::number(cmine->hqcount));
    connect(cmine,SIGNAL(sig_lost()),this,SLOT(slot_lost()));
    connect(cmine,SIGNAL(sig_count()),this,SLOT(slot_count()));
    connect(cmine,SIGNAL(changehqcount()),this,SLOT(changhqcount()));
    ui->label_3->setText("");
    //update();
}

void MainWindow::on_pushButton_2_clicked()
{
    switch (difficulty)
    {
    case 1:
    {
        Cmine* _cmine=new Cmine(this,16,16,40);
        delete cmine;
        cmine=_cmine;
        ui->horizontalLayout->insertWidget(0,cmine);
        ui->label_2->setText(QString::number(cmine->count));
        ui->label_5->setText(QString::number(cmine->hqcount));
        connect(cmine,SIGNAL(sig_lost()),this,SLOT(slot_lost()));
        connect(cmine,SIGNAL(sig_count()),this,SLOT(slot_count()));
        connect(cmine,SIGNAL(changehqcount()),this,SLOT(changhqcount()));
        ui->label_3->setText("");
        difficulty++;
        break;
    }
    case 2:
    {
        Cmine* _cmine=new Cmine(this,24,20,99);
        delete cmine;
        cmine=_cmine;
        ui->horizontalLayout->insertWidget(0,cmine);
        ui->label_2->setText(QString::number(cmine->count));
        ui->label_5->setText(QString::number(cmine->hqcount));
        connect(cmine,SIGNAL(sig_lost()),this,SLOT(slot_lost()));
        connect(cmine,SIGNAL(sig_count()),this,SLOT(slot_count()));
        connect(cmine,SIGNAL(changehqcount()),this,SLOT(changhqcount()));
        ui->label_3->setText("");
        difficulty++;
        break;
    }
    case 3:
    {
        Cmine* _cmine=new Cmine(this,9,9,10);
        delete cmine;
        cmine=_cmine;
        ui->horizontalLayout->insertWidget(0,cmine);
        ui->label_2->setText(QString::number(cmine->count));
        ui->label_5->setText(QString::number(cmine->hqcount));
        connect(cmine,SIGNAL(sig_lost()),this,SLOT(slot_lost()));
        connect(cmine,SIGNAL(sig_count()),this,SLOT(slot_count()));
        connect(cmine,SIGNAL(changehqcount()),this,SLOT(changhqcount()));
        ui->label_3->setText("");
        difficulty=1;
        break;
    }
    default:
        break;
    }
}
