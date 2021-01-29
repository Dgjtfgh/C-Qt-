#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include "settingdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QTranslator t;
//    t.load(":/resources/tr_zh.qm");
//    a.installTranslator(&t);
    MainWindow w;
    w.show();

    return a.exec();
}
