#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>

class TableWidget : public QWidget
{
public:
        TableWidget();

private:
        QTableWidget *table;
};

#endif // TABLEWIDGET_H
