#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>

class TreeWidget : public QWidget
{
public:
        TreeWidget();

private:
        QTreeWidget *tree;
};


#endif // TREEWIDGET_H
