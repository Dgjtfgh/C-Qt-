#ifndef STACKDLG_H
#define STACKDLG_H
#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QStackedWidget>
#include <QWidget>

class StackDlg : public QDialog
{
    Q_OBJECT
public:
    StackDlg(QWidget *parent = 0, Qt::WindowFlags f1 = 0);
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QListWidget *listWidget;
    QStackedWidget *stackWidget;
};

#endif // STACKDLG_H
