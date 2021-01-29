#ifndef STRINGLIST_H
#define STRINGLIST_H

#include <QWidget>
#include <QStringListModel>
#include <QListView>

class StringList : public QWidget
{
        Q_OBJECT
public:
        StringList();

private:
        QStringListModel *model;
        QListView *listView;

private slots:
        void insertData();
        void deleteData();
        void showData();
};

#endif // STRINGLIST_H
