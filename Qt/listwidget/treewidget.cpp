#include "treewidget.h"

TreeWidget::TreeWidget()
{
    tree = new QTreeWidget(this);
    tree->setColumnCount(1);
    QTreeWidgetItem *root = new QTreeWidgetItem(tree, QStringList(QString("Root")));
    QTreeWidgetItem *leaf = new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
    root->addChild(leaf);
    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
    leaf2->setCheckState(0, Qt::Checked);
    root->addChild(leaf2);
    QList<QTreeWidgetItem *> rootList;
    rootList << root;
    tree->insertTopLevelItems(0, rootList);
    this->resize(400, 200);
}
