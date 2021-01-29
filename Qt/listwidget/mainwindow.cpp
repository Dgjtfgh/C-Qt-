#include "mainwindow.h"
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);
    buttons[0] = new QPushButton(tr("dirmodel"), NULL);
    buttons[1] = new QPushButton(tr("listwidget"), NULL);
    buttons[2] = new QPushButton(tr("sortview"), NULL);
    buttons[3] = new QPushButton(tr("stringlist"), NULL);
    buttons[4] = new QPushButton(tr("tablewidget"), NULL);
    buttons[5] = new QPushButton(tr("treewidget"), NULL);

//    QHBoxLayout *hlayout1 = new QHBoxLayout;
//    hlayout1->addWidget(buttons[0]);
//    hlayout1->addWidget(buttons[1]);
//    QHBoxLayout *hlayout2 = new QHBoxLayout;
//    hlayout2->addWidget(buttons[2]);
//    hlayout2->addWidget(buttons[3]);
//    QHBoxLayout *hlayout3 = new QHBoxLayout;
//    hlayout3->addWidget(buttons[4]);
//    hlayout3->addWidget(buttons[5]);
//    QVBoxLayout *vlayout = new QVBoxLayout;
//    vlayout->addLayout(hlayout1);
//    vlayout->addLayout(hlayout2);
//    vlayout->addLayout(hlayout3);
//    widget->setLayout(vlayout);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(buttons[0], 0, 0);
    for (int i = 0; i <= 4; i+=2) {
        layout->addWidget(buttons[i], (i/2), 0);
        layout->addWidget(buttons[i+1], (i/2), 1);
    }
    widget->setLayout(layout);
    connect(buttons[0], SIGNAL(clicked()), &dmw, SLOT(show()));
    connect(buttons[1], SIGNAL(clicked()), &lww, SLOT(show()));
    connect(buttons[2], SIGNAL(clicked()), &svw, SLOT(show()));
    connect(buttons[3], SIGNAL(clicked()), &slw, SLOT(show()));
    connect(buttons[4], SIGNAL(clicked()), &taw, SLOT(show()));
    connect(buttons[5], SIGNAL(clicked()), &trw, SLOT(show()));

}

MainWindow::~MainWindow()
{

}
