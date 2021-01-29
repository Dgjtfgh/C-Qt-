#include "settingdialog.h"
#include <QObject>
#include <QEvent>
#include <QDialog>
#include <QDebug>

settingDialog::settingDialog()
{
    this->setFixedSize(300, 300);
    this->setWindowTitle(tr("setting"));
    text = new QLabel(this);
    text->setGeometry(0, 50, 300, 100);
    text->setAlignment(Qt::AlignCenter);
    text->setText(tr("Go all the way to meet all the good things."));
    languageComBox = new QComboBox(this);
    languageComBox->setGeometry(100, 200, 100, 20);

    languageComBox->addItem(tr("chinese"), QVariant::fromValue(UI_ZH));
    languageComBox->addItem(tr("english"), QVariant::fromValue(UI_EN));

    qRegisterMetaType<LANGUAGE>("LANGUAGE");

    connect(languageComBox, &QComboBox::currentTextChanged, this, &settingDialog::onIndexChanged);

}


void settingDialog::onIndexChanged()
{
    LANGUAGE language = languageComBox->currentData().value<LANGUAGE>();
//    qDebug()<<language;
    emit changeLanguang(language);
}


