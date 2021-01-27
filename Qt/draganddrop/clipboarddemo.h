#ifndef CLIPBOARDDEMO_H
#define CLIPBOARDDEMO_H

#include <QWidget>
#include <QTextEdit>

class ClipboardDemo : public QWidget
{
    Q_OBJECT

public:
    ClipboardDemo(QWidget *parent = 0);
    QClipboard *board;
    QTextEdit *editor;

private slots:
    void setClipboard();
    void getClipboard();
};

#endif // CLIPBOARDDEMO_H
