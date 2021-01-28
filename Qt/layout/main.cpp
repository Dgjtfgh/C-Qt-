#include "dialog.h"
#include "stackdlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
//    StackDlg w;
    w.show();
    return a.exec();
}
