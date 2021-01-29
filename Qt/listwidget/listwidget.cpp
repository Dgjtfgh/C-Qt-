#include "listwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

listwidget::listwidget(QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel;
    label->setFixedWidth(70);
    list = new QListWidget;
    list->setFlow(QListView::TopToBottom);
    list->addItem(new QListWidgetItem(QIcon(":/images/line.PNG"), tr("Line")));
    list->addItem(new QListWidgetItem(QIcon(":/images/rect.PNG"), tr("Rectangle")));
    list->addItem(new QListWidgetItem(QIcon(":/images/oval.PNG"), tr("Oval")));
    list->addItem(new QListWidgetItem(QIcon(":/images/tri.PNG"), tr("Triangle")));
    list->setViewMode(QListView::IconMode);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(list);
    setLayout(layout);
    this->resize(400, 200);
    connect(list, SIGNAL(currentTextChanged(QString)), label, SLOT(setText(QString)));
}

listwidget::~listwidget()
{

}
