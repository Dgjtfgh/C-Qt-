#ifndef DIRMODEL_H
#define DIRMODEL_H

#include <QWidget>
#include <QDirModel>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>

class DirModel : public QWidget
{
        Q_OBJECT
public:
        DirModel();

private:
        QFileSystemModel *model;
        QTreeView *treeView;
        QTableView *listview;

private slots:
        void mkdir();
        void rm();
};


#endif // DIRMODEL_H
