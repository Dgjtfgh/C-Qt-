#include "stringlist.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>

StringList::StringList()
{
    model = new QStringListModel(this);
    QStringList data;
    data << "Letter A" << "Letter B" << "Letter C";
    model->setStringList(data);
    listView = new QListView(this);
    listView->setModel(model);
    QHBoxLayout *btnLayout = new QHBoxLayout;
    QPushButton *insertBtn = new QPushButton(tr("insert"), this);
    QPushButton *delBtn = new QPushButton(tr("Delete"), this);
    QPushButton *showBtn = new QPushButton(tr("Show"), this);
    btnLayout->addWidget(insertBtn);
    btnLayout->addWidget(delBtn);
    btnLayout->addWidget(showBtn);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(listView);
    mainLayout->addLayout(btnLayout);
    this->setLayout(mainLayout);
    this->resize(400, 200);
    connect(insertBtn, SIGNAL(clicked()), this, SLOT(insertData()));
    connect(delBtn, SIGNAL(clicked()), this, SLOT(deleteData()));
    connect(showBtn, SIGNAL(clicked()), this, SLOT(showData()));
}


void StringList::insertData()
{
    bool isOK;
    QString text = QInputDialog::getText(NULL, "Insert", "Please input new data:",
                                                                                 QLineEdit::Normal, "You are inserting new data.", &isOK);
    if(isOK) {
        int row = listView->currentIndex().row();
        model->insertRows(row, 1);
        QModelIndex index = model->index(row);
        model->setData(index, text);
        listView->setCurrentIndex(index);
        listView->edit(index);
     }
}


void StringList::deleteData()
{
    if(model->rowCount() > 1) {
        model->removeRows(listView->currentIndex().row(), 1);
    }
}


void StringList::showData()
{
    QStringList data = model->stringList();
    QString str;
    foreach(QString s, data) {
        str += s + "\n";
    }
    QMessageBox::information(this, "Data", str);
}
