#include "clockwidget.h"
#include <qwidget.h>
#include <QPainter>
#include <qevent.h>
#include <QFont>
#include <QPoint>
#include <QTimer>
#include <QTime>
#include <QRectF>
#include <qmath.h>
#include <qglobal.h>

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}

void ClockWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -30)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -65)
    };
    static const QPoint secondHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -80)
    };

    QColor hourColor(200, 100, 0, 200);
    QColor minuteColor(0, 127, 127, 150);
    QColor secondColor(0, 160, 230, 150);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 平移坐标系原点至中心点
    painter.translate(width()/2, height()/2);
    // 缩放
    painter.scale(side/200.0, side/200.0);
    // 绘制时针
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.save();
    // 旋转
    painter.rotate(30.0*((time.hour() + time.minute()/60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    painter.setPen(hourColor);

    for(int i = 0; i< 12; i++) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    int radius = 100;
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    int pointSize = font.pointSize();
    // 绘制小时文本
    int nHour = 0;
    for (int i = 0; i < 12; i++) {
        nHour = i + 3;
        if (nHour > 12) nHour -= 12;
        painter.drawText(textRectF(radius*0.8, pointSize, i*30), Qt::AlignCenter, QString::number(nHour));
    }
    // 绘制分针
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);
    painter.save();
    painter.rotate(6.0*(time.minute()+time.second()/60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();
    painter.setPen(minuteColor);
    // 绘制分钟文本
    for (int j = 0; j < 60; j++) {
        if ((j%5)!=0) painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }
    // 绘制秒针
    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);
    painter.save();
    painter.rotate(6.0*time.second());
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();

}

ClockWidget::~ClockWidget()
{

}

QRectF ClockWidget::textRectF(double radius, int pointSize, double angle)
{
    QRectF rectF;
    rectF.setX(radius*qCos(angle*M_PI/180.0) - pointSize*2);
    rectF.setY(radius*qSin(angle*M_PI/180.0) - pointSize/2.0);
    rectF.setWidth(pointSize*4);
    rectF.setHeight(pointSize);
    return rectF;
}
