/********************************************************************************
** Form generated from reading UI file 'ConfigWnd.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGWND_H
#define UI_CONFIGWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigWnd
{
public:
    QLineEdit *IPEdit;
    QLabel *label_3;
    QPushButton *SetBtn;
    QLineEdit *PortEdit;
    QLabel *label_2;
    QLabel *label;
    QPlainTextEdit *AttrTextEdit;

    void setupUi(QWidget *ConfigWnd)
    {
        if (ConfigWnd->objectName().isEmpty())
            ConfigWnd->setObjectName(QStringLiteral("ConfigWnd"));
        ConfigWnd->resize(345, 300);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        ConfigWnd->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("../Image/png/Weather.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ConfigWnd->setWindowIcon(icon);
        ConfigWnd->setStyleSheet(QStringLiteral("background:rgb(77,77,77);color:white"));
        IPEdit = new QLineEdit(ConfigWnd);
        IPEdit->setObjectName(QStringLiteral("IPEdit"));
        IPEdit->setGeometry(QRect(100, 20, 113, 20));
        label_3 = new QLabel(ConfigWnd);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 130, 54, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        label_3->setFont(font1);
        SetBtn = new QPushButton(ConfigWnd);
        SetBtn->setObjectName(QStringLiteral("SetBtn"));
        SetBtn->setGeometry(QRect(120, 260, 75, 23));
        PortEdit = new QLineEdit(ConfigWnd);
        PortEdit->setObjectName(QStringLiteral("PortEdit"));
        PortEdit->setGeometry(QRect(100, 80, 113, 20));
        label_2 = new QLabel(ConfigWnd);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 80, 61, 16));
        label_2->setFont(font1);
        label = new QLabel(ConfigWnd);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 51, 21));
        label->setFont(font1);
        label->setStyleSheet(QStringLiteral(""));
        AttrTextEdit = new QPlainTextEdit(ConfigWnd);
        AttrTextEdit->setObjectName(QStringLiteral("AttrTextEdit"));
        AttrTextEdit->setGeometry(QRect(100, 120, 191, 121));

        retranslateUi(ConfigWnd);

        QMetaObject::connectSlotsByName(ConfigWnd);
    } // setupUi

    void retranslateUi(QWidget *ConfigWnd)
    {
        ConfigWnd->setWindowTitle(QApplication::translate("ConfigWnd", "IP\347\253\257\345\217\243\345\217\267\351\205\215\347\275\256", nullptr));
        label_3->setText(QApplication::translate("ConfigWnd", "\346\217\217\350\277\260\357\274\232", nullptr));
        SetBtn->setText(QApplication::translate("ConfigWnd", "\350\256\276\347\275\256", nullptr));
        label_2->setText(QApplication::translate("ConfigWnd", "\347\253\257\345\217\243\345\217\267:", nullptr));
        label->setText(QApplication::translate("ConfigWnd", "IP\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigWnd: public Ui_ConfigWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGWND_H
