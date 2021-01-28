#ifndef SLIDWINDOW_H
#define SLIDWINDOW_H

#include <QObject>
#include <QWidget>
#include <QTimer>

class slidwindow: public QWidget
{
    Q_OBJECT

public:
    explicit slidwindow(QWidget *parent);
    int press_x;  //鼠标按下时的位置
    int press_y;
    int relea_x;  //鼠标释放时的位置
    int relea_y;
public slots:
    void moveview(QMouseEvent *event);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;//重写mouseMoveEvent函数
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    QTimer *timer;
signals:
    void mousemove(QMouseEvent *event);
};

#endif // SLIDWINDOW_H
