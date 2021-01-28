#include "slidwindow.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
slidwindow::slidwindow(QWidget *parent):QWidget(parent)
{
    this->setMouseTracking(true);
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(this, SIGNAL(mousemove(QMouseEvent*)), this, SLOT(moveview(QMouseEvent*)));
}

void slidwindow::mousePressEvent(QMouseEvent *event){
    press_x = event->globalX();
    press_y = event->globalY();
    qDebug()<<press_x;
}

void slidwindow::mouseReleaseEvent(QMouseEvent *event){
    relea_x = event->globalX();
    relea_y = event->globalY();
    qDebug()<<relea_x;
    emit mousemove(event);
}

void slidwindow::mouseMoveEvent(QMouseEvent *event){
    // 防抖
//    if(!timer->isActive()){
//        qDebug()<<timer->remainingTime();
//        timer->start(2000);
//    } else {
//        timer->stop();
//        timer->setSingleShot(true);
//        timer->start(2000);
//    }
    // 节流
    if(!timer->isActive()){
        qDebug()<<timer->remainingTime();
        timer->start(1000);
    }
//    emit mousemove(event);
}

void slidwindow::moveview(QMouseEvent *event)
{
    qDebug()<<event->type();
//    if(event->type()==QMouseEvent::MouseButtonPress)  //如果鼠标按下
//    {
//        qDebug()<<("hello222222");
//        press_x = event->globalX();
//        press_y = event->globalY();
//    }
//    if(event->type()==QMouseEvent::MouseButtonRelease)  //如果鼠标释放
//    {
//        qDebug()<<("hello111");
//         relea_x = event->globalX();
//         relea_y = event->globalY();
//    }
    // int width = ui->Widget_2->frameGeometry().width();
    QPoint point = this->mapToParent(QPoint(0, 0));
    qDebug()<<point;
    //判断滑动方向（右滑）
    if((relea_x - press_x)>20 && event->type()==QEvent::MouseButtonRelease && qAbs(relea_y-press_y)<50)
    {
        if(point.rx()< 0) move(point.rx()+251, point.ry());
        qDebug()<<("hello!");
    }

    //判断滑动方向（左滑）
    if((press_x - relea_x)>20 && event->type()==QEvent::MouseButtonRelease && qAbs(relea_y-press_y)<50)
    {
        if(point.rx() >= 0) move(point.rx()-251, point.ry());
    }
}
