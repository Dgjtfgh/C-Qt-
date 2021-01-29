#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingdialog.h"
#include <QTranslator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTranslator *t;
    void init();
private slots:
    void changeLanguang(LANGUAGE);
private:
    Ui::MainWindow *ui;
    settingDialog *d;

};

#endif // MAINWINDOW_H
