#include "mainwindow.h"
#include <QStatusBar>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QtGui/QKeySequence>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    openAction = new QAction(tr("&open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("open a file"));
    openAction->setIcon(QIcon(":/Open.png"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    openAction1 = new QAction(tr("&color"), this);
    connect(openAction1, SIGNAL(triggered()), this, SLOT(open1()));

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction((openAction));
    file->addAction((openAction1));

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->addAction(openAction1);

    msgLabel = new QLabel;
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);

    statusBar()->addWidget(msgLabel);


}

void MainWindow::open()
{
    QString path = QFileDialog::getOpenFileName(this, tr("open Image"), ".", tr("Image Files(*.jpg *.png *.pdf)"));
    if(path.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You select ")+path);
    }

//    bool isOK;
//    QString text = QInputDialog::getText(
//                NULL, "Input Dialog",
//                "Please input your comment",
//                QLineEdit::Normal,
//                "吃",
//                &isOK);
//    if(isOK) {
//        QMessageBox::information(
//                   NULL, "Information",
//                   "Your comment is: <b>" + text + "</b>",
//                   QMessageBox::Yes | QMessageBox::No,
//                   QMessageBox::Yes);
//    }

}

void MainWindow::open1()
{
//    static 函数都是要返回一个 StandardButton
//    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Show Qt", "Do you want to show Qt dialog?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//    if(rb == QMessageBox::Yes)
//    {
//        QMessageBox::aboutQt(NULL, "About Qt");
//    }
//    构造函数的方式
//    QMessageBox message(QMessageBox::NoIcon, "Show Qt", "Do you want to show Qt dialog?", QMessageBox::Yes | QMessageBox::No, NULL);
//    if(message.exec() == QMessageBox::Yes) // 自己运行判断一下
//    {
//            QMessageBox::aboutQt(NULL, "About Qt");
//    }

    QColor color = QColorDialog::getColor(Qt::white, this);
    QString msg = QString("r: %1, g: %2, b: %3").arg(QString::number(color.red()), QString::number(color.green()), QString::number(color.blue()));
    QMessageBox::information(NULL, "Selected color", msg);
}


MainWindow::~MainWindow()
{

}
