#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QLabel>

class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void open();
    void open1();

private:
    QAction *openAction;
    QAction *openAction1;
    QLabel *msgLabel;
};

#endif // MAINWINDOW_H
