#ifndef WIDGET_H
#define WIDGET_H
#include <QStackedWidget>
#include <QStackedLayout>
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void moveView();
    void moveview(QMouseEvent *event);

private:
    Ui::Widget *ui;
    QStackedLayout *layout;
};

#endif // WIDGET_H
