#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>

class listwidget : public QWidget
{
    Q_OBJECT

public:
    listwidget(QWidget *parent = 0);
    ~listwidget();
private:
    QLabel *label;
    QListWidget *list;
};

#endif // LISTWIDGET_H
