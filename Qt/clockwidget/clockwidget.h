#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>

class ClockWidget : public QWidget
{
    Q_OBJECT

public:
    ClockWidget(QWidget *parent = 0);
    ~ClockWidget();
    QRectF textRectF(double radius, int pointSize, double angle);
protected:
        void paintEvent(QPaintEvent *event);
};

#endif // CLOCKWIDGET_H
