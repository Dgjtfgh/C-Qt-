#ifndef CSCROLLSCREENVIEW_H
#define CSCROLLSCREENVIEW_H

#include <QWidget>
#include <QEvent>
#include <QStackedWidget>

class CScrollScreenView : public QWidget
{
    Q_OBJECT
public:
    explicit CScrollScreenView(QWidget *parent, int indexNum);
    void addPage(QWidget *page);
protected:
//    void mouseMoveEvent(QMouseEvent *event) override;//重写mouseMoveEvent函数
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watch, QEvent *evn);
private:
    QTimer *timer;
    QStackedWidget *slidwindow;
    int indexNum;
//signals:
//    void mousemove(QMouseEvent *event);
};

#endif // CSCROLLSCREENVIEW_H
