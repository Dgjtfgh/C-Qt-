#include "mainwindow.h"
#include "projectlistwidget.h"
#include "clipboarddemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    ProjectListWidget pw;
//    pw.show();
    ClipboardDemo w;
    w.show();

    return a.exec();
}
