#include "cscrollscreenview.h"
#include <QMouseEvent>
#include <QDebug>
#include <QVBoxLayout>

CScrollScreenView::CScrollScreenView(QWidget *parent, int indexNum):QWidget(parent),indexNum(indexNum)
{
//    this->setWindowFlag();
//    this->setFixedSize(400, 400);
    slidwindow = new QStackedWidget(this);
    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(slidwindow);
    pLayout->setSpacing(10);
    pLayout->setContentsMargins(10, 10, 10, 10);
    setLayout(pLayout);
    slidwindow->installEventFilter(this);
}

void CScrollScreenView::addPage(QWidget *page) {
    slidwindow->addWidget(page);
}

bool CScrollScreenView::eventFilter(QObject *watch, QEvent *evn)
{
    static int press_x;  //鼠标按下时的位置
    static int press_y;
    static int relea_x;  //鼠标释放时的位置
    static int relea_y;

    QMouseEvent *event = static_cast<QMouseEvent *>(evn); //将之转换为鼠标事件

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

    //判断滑动方向（右滑）
    if((relea_x - press_x)>20 && event->type()==QEvent::MouseButtonRelease && qAbs(relea_y-press_y)<50)
    {
//        qDebug()<<"右滑";
        int current_page = slidwindow->currentIndex();
        if(current_page<=indexNum-1)
        {
            slidwindow->setCurrentIndex(current_page-1);  //切换界面
        }
    }

    //判断滑动方向（左滑）
    if((press_x - relea_x)>20 && event->type()==QEvent::MouseButtonRelease && qAbs(relea_y-press_y)<50)
    {
//        qDebug()<<"左滑";
        int current_page = slidwindow->currentIndex();
        if(current_page>=0)
        {
            slidwindow->setCurrentIndex(current_page+1);
        }
    }

    return QWidget::eventFilter(watch,evn);
}
