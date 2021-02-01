#include "widget.h"
#include "ui_widget.h"
#include <QStackedWidget>
#include <QStackedLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <qmath.h>
#include <QEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#define ncount 3

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QLabel *w1 = new QLabel(tr("It is Window 1 !"));
    QLabel *w2 = new QLabel(tr("It is Window 2 !"));
    QLabel *w3 = new QLabel(tr("It is Window 3 !"));

//    layout = new QStackedWidget;
    layout = new QStackedLayout;
    layout->addWidget(w1);
    layout->addWidget(w2);
    layout->addWidget(w3);

    QPushButton *button = new QPushButton(tr("switch"));

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(button);
    setLayout(mainLayout);
    connect(w1, SIGNAL(clicked()), this, SLOT(moveView()));
    connect(button, SIGNAL(clicked()), this, SLOT(moveView()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::moveView(){

    int nCount = layout->count();
    int nIndex = layout->currentIndex();
    qDebug()<<(nCount);
    qDebug()<<(nIndex);
    if (nIndex >= nCount-1) nIndex = 0;
    else nIndex++;
    qDebug()<<(nCount);
    qDebug()<<(nIndex);
    layout->setCurrentIndex(nIndex);
}

void Widget::moveview(QMouseEvent *event)
{
    static int press_x;  //鼠标按下时的位置
    static int press_y;
    static int relea_x;  //鼠标释放时的位置
    static int relea_y;
    qDebug()<<("hello world!");
    if(event->type()==QEvent::MouseButtonPress)  //如果鼠标按下
    {
        press_x = event->globalX();
        press_y = event->globalY();
    }
    if(event->type()==QEvent::MouseButtonRelease)  //如果鼠标释放
    {
         relea_x = event->globalX();
         relea_y = event->globalY();
    }
    int nCount = layout->count();
    int nIndex = layout->currentIndex();
    //判断滑动方向（右滑）
    if((relea_x - press_x)>20 && event->type()==QEvent::MouseButtonRelease && qAbs(relea_y-press_y)<50)
    {
        // 当需要显示的页面索引大于等于总页面时，切换至首页
        if (nIndex >= nCount-1)
            nIndex = 0;
        else nIndex++;
        layout->setCurrentIndex(nIndex);
    }
    if((press_x - relea_x)>20 && event->type()==QEvent::MouseButtonRelease && qAbs(relea_y-press_y)<50)
    {
        if(nIndex <= 0) nIndex = nCount-1;
        else nIndex--;
        layout->setCurrentIndex(nIndex);
    }
}
