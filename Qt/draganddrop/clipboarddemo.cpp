#include "clipboarddemo.h"
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QClipboard>

ClipboardDemo::ClipboardDemo(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *northLayout = new QHBoxLayout;
    QHBoxLayout *southLayout = new QHBoxLayout;

    editor = new QTextEdit;
    QLabel *label = new QLabel;
    label->setText("Text Input: ");
    label->setBuddy(editor);
    QPushButton *copyButton = new QPushButton;
    copyButton->setText("Set Clipboard");
    QPushButton *pasteButton = new QPushButton;
    pasteButton->setText("Get Clipboard");

    northLayout->addWidget(label);
    northLayout->addWidget(editor);
    southLayout->addWidget(copyButton);
    southLayout->addWidget(pasteButton);
    mainLayout->addLayout(northLayout);
    mainLayout->addLayout(southLayout);

    connect(copyButton, SIGNAL(clicked()), this, SLOT(setClipboard()));
    connect(pasteButton, SIGNAL(clicked()), this, SLOT(getClipboard()));
}

void ClipboardDemo::setClipboard()
{
    board = QApplication::clipboard();
    QString str = editor->toPlainText();
    board->setText(str);
}

void ClipboardDemo::getClipboard()
{
    QString str = board->text();
    QMessageBox::information(NULL, "From clipboard", str);
}
