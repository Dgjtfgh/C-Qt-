#include "dirmodel.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QSplitter>
#include <QFileSystemModel>
#include <QDir>

DirModel::DirModel()
{

        model = new QFileSystemModel;
//        model = new QDirModel;
        model->setRootPath(QDir::rootPath());
//        model->setReadOnly(false);
//        model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

        treeView = new QTreeView;
        treeView->setModel(model);
        treeView->header()->setStretchLastSection(true);
        treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
        treeView->header()->setSortIndicatorShown(true);

        listview = new QTableView;
        QModelIndex listindex = model->index(QDir::rootPath());
        listview->setRootIndex(listindex);
        listview->setModel(model);


        QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
        splitter->addWidget(treeView);
        splitter->addWidget(listview);

        QModelIndex index = model->index(QDir::currentPath());
        treeView->expand(index);
        treeView->scrollTo(index);
        treeView->resizeColumnToContents(0);

        QHBoxLayout *btnLayout = new QHBoxLayout;
        QPushButton *createBtn = new QPushButton(tr("Create Directory..."));
        QPushButton *delBtn = new QPushButton(tr("Remove"));
        btnLayout->addWidget(createBtn);
        btnLayout->addWidget(delBtn);
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(splitter);
        mainLayout->addLayout(btnLayout);
        this->setLayout(mainLayout);
        this->resize(400, 200);

        connect(createBtn, SIGNAL(clicked()), this, SLOT(mkdir()));
        connect(delBtn, SIGNAL(clicked()), this, SLOT(rm()));
}


void DirModel::mkdir()
{
        QModelIndex index = treeView->currentIndex();
        if (!index.isValid()) {
                return;
        }
        QString dirName = QInputDialog::getText(this,
                                                tr("Create Directory"),
                                                tr("Directory name"));
        if (!dirName.isEmpty()) {
                if (!model->mkdir(index, dirName).isValid()) {
                        QMessageBox::information(this,
                                                 tr("Create Directory"),
                                                 tr("Failed to create the directory"));
                }
        }
}


void DirModel::rm()
{
        QModelIndex index = treeView->currentIndex();
        if (!index.isValid()) {
                return;
        }
        bool ok;
        if (model->fileInfo(index).isDir()) {
                ok = model->rmdir(index);
        } else {
                ok = model->remove(index);
        }
        if (!ok) {
                QMessageBox::information(this,
                                                                 tr("Remove"),
                                                                 tr("Failed to remove %1").arg(model->fileName(index)));
        }
}
