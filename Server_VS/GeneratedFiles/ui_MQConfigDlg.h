/********************************************************************************
** Form generated from reading UI file 'MQConfigDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQCONFIGDLG_H
#define UI_MQCONFIGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MQConfigDlg
{
public:
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox;
    QScrollArea *ScrollArea_MinBtn;
    QWidget *scrollAreaWidgetContents_MinBtn;
    QPushButton *MinBtn;
    QScrollArea *ScrollArea_CloseBtn;
    QWidget *scrollAreaWidgetContents_CloseBtn;
    QPushButton *CloseBtn;
    QGroupBox *groupBox_2;
    QLabel *label_Name;
    QLabel *label_Password;
    QLabel *label_URL;
    QLabel *label_QueName;
    QLineEdit *LineEdit_Name;
    QLineEdit *LineEdit_Password;
    QLineEdit *LineEdit_URL;
    QLineEdit *LineEdit_QueName;
    QPushButton *ResetBtn;
    QPushButton *SetBtn;

    void setupUi(QWidget *MQConfigDlg)
    {
        if (MQConfigDlg->objectName().isEmpty())
            MQConfigDlg->setObjectName(QStringLiteral("MQConfigDlg"));
        MQConfigDlg->resize(426, 253);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(8);
        font.setBold(false);
        font.setWeight(50);
        MQConfigDlg->setFont(font);
        MQConfigDlg->setStyleSheet(QStringLiteral("background:rgb(100,100,100);color:white"));
        label = new QLabel(MQConfigDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 41, 31));
        label_2 = new QLabel(MQConfigDlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 10, 54, 12));
        groupBox = new QGroupBox(MQConfigDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(290, 10, 120, 80));
        ScrollArea_MinBtn = new QScrollArea(groupBox);
        ScrollArea_MinBtn->setObjectName(QStringLiteral("ScrollArea_MinBtn"));
        ScrollArea_MinBtn->setGeometry(QRect(10, 20, 41, 41));
        ScrollArea_MinBtn->setWidgetResizable(true);
        scrollAreaWidgetContents_MinBtn = new QWidget();
        scrollAreaWidgetContents_MinBtn->setObjectName(QStringLiteral("scrollAreaWidgetContents_MinBtn"));
        scrollAreaWidgetContents_MinBtn->setGeometry(QRect(0, 0, 39, 39));
        MinBtn = new QPushButton(scrollAreaWidgetContents_MinBtn);
        MinBtn->setObjectName(QStringLiteral("MinBtn"));
        MinBtn->setGeometry(QRect(10, 10, 21, 21));
        ScrollArea_MinBtn->setWidget(scrollAreaWidgetContents_MinBtn);
        ScrollArea_CloseBtn = new QScrollArea(groupBox);
        ScrollArea_CloseBtn->setObjectName(QStringLiteral("ScrollArea_CloseBtn"));
        ScrollArea_CloseBtn->setGeometry(QRect(60, 20, 51, 41));
        ScrollArea_CloseBtn->setWidgetResizable(true);
        scrollAreaWidgetContents_CloseBtn = new QWidget();
        scrollAreaWidgetContents_CloseBtn->setObjectName(QStringLiteral("scrollAreaWidgetContents_CloseBtn"));
        scrollAreaWidgetContents_CloseBtn->setGeometry(QRect(0, 0, 49, 39));
        CloseBtn = new QPushButton(scrollAreaWidgetContents_CloseBtn);
        CloseBtn->setObjectName(QStringLiteral("CloseBtn"));
        CloseBtn->setGeometry(QRect(10, 10, 21, 21));
        ScrollArea_CloseBtn->setWidget(scrollAreaWidgetContents_CloseBtn);
        groupBox_2 = new QGroupBox(MQConfigDlg);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(60, 29, 201, 211));
        label_Name = new QLabel(groupBox_2);
        label_Name->setObjectName(QStringLiteral("label_Name"));
        label_Name->setGeometry(QRect(20, 30, 54, 12));
        label_Password = new QLabel(groupBox_2);
        label_Password->setObjectName(QStringLiteral("label_Password"));
        label_Password->setGeometry(QRect(20, 60, 54, 12));
        label_URL = new QLabel(groupBox_2);
        label_URL->setObjectName(QStringLiteral("label_URL"));
        label_URL->setGeometry(QRect(20, 90, 54, 12));
        label_QueName = new QLabel(groupBox_2);
        label_QueName->setObjectName(QStringLiteral("label_QueName"));
        label_QueName->setGeometry(QRect(20, 120, 54, 12));
        LineEdit_Name = new QLineEdit(groupBox_2);
        LineEdit_Name->setObjectName(QStringLiteral("LineEdit_Name"));
        LineEdit_Name->setGeometry(QRect(80, 30, 113, 20));
        LineEdit_Password = new QLineEdit(groupBox_2);
        LineEdit_Password->setObjectName(QStringLiteral("LineEdit_Password"));
        LineEdit_Password->setGeometry(QRect(80, 60, 113, 20));
        LineEdit_URL = new QLineEdit(groupBox_2);
        LineEdit_URL->setObjectName(QStringLiteral("LineEdit_URL"));
        LineEdit_URL->setGeometry(QRect(80, 90, 113, 20));
        LineEdit_QueName = new QLineEdit(groupBox_2);
        LineEdit_QueName->setObjectName(QStringLiteral("LineEdit_QueName"));
        LineEdit_QueName->setGeometry(QRect(80, 120, 113, 20));
        ResetBtn = new QPushButton(groupBox_2);
        ResetBtn->setObjectName(QStringLiteral("ResetBtn"));
        ResetBtn->setGeometry(QRect(20, 170, 61, 23));
        SetBtn = new QPushButton(groupBox_2);
        SetBtn->setObjectName(QStringLiteral("SetBtn"));
        SetBtn->setGeometry(QRect(120, 170, 61, 23));

        retranslateUi(MQConfigDlg);

        QMetaObject::connectSlotsByName(MQConfigDlg);
    } // setupUi

    void retranslateUi(QWidget *MQConfigDlg)
    {
        MQConfigDlg->setWindowTitle(QApplication::translate("MQConfigDlg", "MQConfigDlg", nullptr));
        label->setText(QApplication::translate("MQConfigDlg", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("MQConfigDlg", "TextLabel", nullptr));
        groupBox->setTitle(QString());
        MinBtn->setText(QApplication::translate("MQConfigDlg", "PushButton", nullptr));
        CloseBtn->setText(QApplication::translate("MQConfigDlg", "PushButton", nullptr));
        groupBox_2->setTitle(QApplication::translate("MQConfigDlg", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        label_Name->setText(QApplication::translate("MQConfigDlg", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_Password->setText(QApplication::translate("MQConfigDlg", "\345\257\206\347\240\201", nullptr));
        label_URL->setText(QApplication::translate("MQConfigDlg", "URL", nullptr));
        label_QueName->setText(QApplication::translate("MQConfigDlg", "\351\230\237\345\210\227\345\220\215\347\247\260", nullptr));
        ResetBtn->setText(QApplication::translate("MQConfigDlg", "\351\207\215\347\275\256", nullptr));
        SetBtn->setText(QApplication::translate("MQConfigDlg", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MQConfigDlg: public Ui_MQConfigDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQCONFIGDLG_H
