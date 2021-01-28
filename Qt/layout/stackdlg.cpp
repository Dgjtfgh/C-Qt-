#include "stackdlg.h"
#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QStackedWidget>
#include <QWidget>
#include <QHBoxLayout>

StackDlg::StackDlg(QWidget *parent, Qt::WindowFlags f1)
: QDialog(parent,f1)
{
    setWindowTitle(tr("Stacked Widgets"));
    listWidget = new QListWidget(this);
    listWidget->insertItem(0,tr("The Window 1"));
    listWidget->insertItem(1,tr("The Window 2"));
    listWidget->insertItem(2,tr("The Window 3"));
    label1 = new QLabel(tr("It is Window 1 !"));
    label2 = new QLabel(tr("It is Window 2 !"));
    label3 = new QLabel(tr("It is Window 3 !"));
    stackWidget = new QStackedWidget(this);
    stackWidget->addWidget(label1);
    stackWidget->addWidget(label2);
    stackWidget->addWidget(label3);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(stackWidget,0,Qt::AlignHCenter);
    mainLayout->setStretchFactor(listWidget,1);
    mainLayout->setStretchFactor(stackWidget,3);
    connect(listWidget,SIGNAL(currentRowChanged(int)),stackWidget,SLOT(setCurrentIndex(int)));
}
