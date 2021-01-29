#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "listwidget.h"
#include "treewidget.h"
#include "tablewidget.h"
#include "stringlist.h"
#include "dirmodel.h"
#include "sortview.h"
#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QGroupBox *horizontalGroupBox;
    QPushButton *buttons[6];
    DirModel dmw;
    SortView svw;
    StringList slw;
    TableWidget taw;
    TreeWidget trw;
    listwidget lww;
};

#endif // MAINWINDOW_H
