#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H


#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QComboBox>
#include <QLabel>

typedef enum{
    UI_ZH,
    UI_EN
}LANGUAGE;

Q_DECLARE_METATYPE(LANGUAGE)

class settingDialog:public QWidget
{
    Q_OBJECT

public:
    settingDialog();
    QLabel *text;
    QComboBox *languageComBox;
//    void changeEvent(QEvent *event);
//    void translateUI();
signals:
    void changeLanguang(LANGUAGE);

private slots:
    void onIndexChanged();
};

#endif // SETTINGDIALOG_H
