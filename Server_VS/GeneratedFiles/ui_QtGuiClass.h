/********************************************************************************
** Form generated from reading UI file 'QtGuiClass.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUICLASS_H
#define UI_QTGUICLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiClass
{
public:
    QGroupBox *groupBox;
    QGroupBox *groupBox_time;
    QDateTimeEdit *RdateTimeEdit;
    QPushButton *RTimeBtn;
    QPushButton *WTimeBtn;
    QGroupBox *groupBox_IP;
    QPushButton *RIPBtn;
    QPushButton *WIPBtn;
    QLineEdit *lineEdit_IP;
    QGroupBox *groupBox_QZ;
    QPushButton *RQZBtn;
    QPushButton *WQZBtn;
    QLineEdit *lineEdit_QZ;
    QGroupBox *groupBox_FTPSEVER;
    QPushButton *RFTPSERVERBtn;
    QPushButton *WFTPSERVERBtn;
    QLineEdit *lineEdit_FTPSERVER;
    QGroupBox *groupBox_FF;
    QPushButton *RFFBtn;
    QPushButton *WFFBtn;
    QLineEdit *lineEdit_FF;
    QGroupBox *groupBox_SF;
    QPushButton *RSFBtn;
    QPushButton *WSFBtn;
    QLineEdit *lineEdit_SF;
    QGroupBox *groupBox_CAPINTERVAL;
    QPushButton *RCAPINTERVALBtn;
    QPushButton *WCAPINTERVALBtn;
    QLineEdit *lineEdit_CAPINTERVAL;
    QGroupBox *groupBox_CAPTIME;
    QPushButton *RCAPTIMEBtn;
    QPushButton *WCAPTIMEBtn;
    QLineEdit *lineEdit_BTIME;
    QLineEdit *lineEdit_ETIME;
    QLabel *label;
    QGroupBox *groupBox_SHAPSHOT;
    QPushButton *SHAPSHOTBtn;
    QGroupBox *groupBox_RESET;
    QPushButton *RESETBtn;
    QGroupBox *groupBox_FTPADMIN;
    QPushButton *RFTPADMINBtn;
    QPushButton *WFTPADMINBtn;
    QLineEdit *lineEdit_FTPADMIN;

    void setupUi(QWidget *QtGuiClass)
    {
        if (QtGuiClass->objectName().isEmpty())
            QtGuiClass->setObjectName(QStringLiteral("QtGuiClass"));
        QtGuiClass->setWindowModality(Qt::WindowModal);
        QtGuiClass->resize(571, 431);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        QtGuiClass->setFont(font);
        groupBox = new QGroupBox(QtGuiClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 551, 411));
        groupBox_time = new QGroupBox(groupBox);
        groupBox_time->setObjectName(QStringLiteral("groupBox_time"));
        groupBox_time->setGeometry(QRect(190, 10, 171, 91));
        RdateTimeEdit = new QDateTimeEdit(groupBox_time);
        RdateTimeEdit->setObjectName(QStringLiteral("RdateTimeEdit"));
        RdateTimeEdit->setGeometry(QRect(10, 20, 151, 22));
        RdateTimeEdit->setDateTime(QDateTime(QDate(2018, 9, 1), QTime(0, 0, 0)));
        RTimeBtn = new QPushButton(groupBox_time);
        RTimeBtn->setObjectName(QStringLiteral("RTimeBtn"));
        RTimeBtn->setGeometry(QRect(10, 50, 75, 23));
        WTimeBtn = new QPushButton(groupBox_time);
        WTimeBtn->setObjectName(QStringLiteral("WTimeBtn"));
        WTimeBtn->setGeometry(QRect(90, 50, 75, 23));
        groupBox_IP = new QGroupBox(groupBox);
        groupBox_IP->setObjectName(QStringLiteral("groupBox_IP"));
        groupBox_IP->setGeometry(QRect(10, 10, 171, 91));
        RIPBtn = new QPushButton(groupBox_IP);
        RIPBtn->setObjectName(QStringLiteral("RIPBtn"));
        RIPBtn->setGeometry(QRect(10, 50, 75, 23));
        WIPBtn = new QPushButton(groupBox_IP);
        WIPBtn->setObjectName(QStringLiteral("WIPBtn"));
        WIPBtn->setGeometry(QRect(90, 50, 75, 23));
        lineEdit_IP = new QLineEdit(groupBox_IP);
        lineEdit_IP->setObjectName(QStringLiteral("lineEdit_IP"));
        lineEdit_IP->setGeometry(QRect(10, 20, 151, 20));
        groupBox_QZ = new QGroupBox(groupBox);
        groupBox_QZ->setObjectName(QStringLiteral("groupBox_QZ"));
        groupBox_QZ->setGeometry(QRect(10, 110, 171, 91));
        RQZBtn = new QPushButton(groupBox_QZ);
        RQZBtn->setObjectName(QStringLiteral("RQZBtn"));
        RQZBtn->setGeometry(QRect(10, 50, 75, 23));
        WQZBtn = new QPushButton(groupBox_QZ);
        WQZBtn->setObjectName(QStringLiteral("WQZBtn"));
        WQZBtn->setGeometry(QRect(90, 50, 75, 23));
        lineEdit_QZ = new QLineEdit(groupBox_QZ);
        lineEdit_QZ->setObjectName(QStringLiteral("lineEdit_QZ"));
        lineEdit_QZ->setGeometry(QRect(10, 20, 151, 20));
        groupBox_FTPSEVER = new QGroupBox(groupBox);
        groupBox_FTPSEVER->setObjectName(QStringLiteral("groupBox_FTPSEVER"));
        groupBox_FTPSEVER->setGeometry(QRect(10, 210, 171, 91));
        RFTPSERVERBtn = new QPushButton(groupBox_FTPSEVER);
        RFTPSERVERBtn->setObjectName(QStringLiteral("RFTPSERVERBtn"));
        RFTPSERVERBtn->setGeometry(QRect(10, 50, 75, 23));
        WFTPSERVERBtn = new QPushButton(groupBox_FTPSEVER);
        WFTPSERVERBtn->setObjectName(QStringLiteral("WFTPSERVERBtn"));
        WFTPSERVERBtn->setGeometry(QRect(90, 50, 75, 23));
        lineEdit_FTPSERVER = new QLineEdit(groupBox_FTPSEVER);
        lineEdit_FTPSERVER->setObjectName(QStringLiteral("lineEdit_FTPSERVER"));
        lineEdit_FTPSERVER->setGeometry(QRect(10, 20, 151, 20));
        groupBox_FF = new QGroupBox(groupBox);
        groupBox_FF->setObjectName(QStringLiteral("groupBox_FF"));
        groupBox_FF->setGeometry(QRect(190, 210, 171, 91));
        RFFBtn = new QPushButton(groupBox_FF);
        RFFBtn->setObjectName(QStringLiteral("RFFBtn"));
        RFFBtn->setGeometry(QRect(10, 50, 75, 23));
        WFFBtn = new QPushButton(groupBox_FF);
        WFFBtn->setObjectName(QStringLiteral("WFFBtn"));
        WFFBtn->setGeometry(QRect(90, 50, 75, 23));
        lineEdit_FF = new QLineEdit(groupBox_FF);
        lineEdit_FF->setObjectName(QStringLiteral("lineEdit_FF"));
        lineEdit_FF->setGeometry(QRect(10, 20, 151, 20));
        groupBox_SF = new QGroupBox(groupBox);
        groupBox_SF->setObjectName(QStringLiteral("groupBox_SF"));
        groupBox_SF->setGeometry(QRect(10, 310, 171, 91));
        RSFBtn = new QPushButton(groupBox_SF);
        RSFBtn->setObjectName(QStringLiteral("RSFBtn"));
        RSFBtn->setGeometry(QRect(10, 50, 75, 23));
        WSFBtn = new QPushButton(groupBox_SF);
        WSFBtn->setObjectName(QStringLiteral("WSFBtn"));
        WSFBtn->setGeometry(QRect(90, 50, 75, 23));
        lineEdit_SF = new QLineEdit(groupBox_SF);
        lineEdit_SF->setObjectName(QStringLiteral("lineEdit_SF"));
        lineEdit_SF->setGeometry(QRect(10, 20, 151, 20));
        groupBox_CAPINTERVAL = new QGroupBox(groupBox);
        groupBox_CAPINTERVAL->setObjectName(QStringLiteral("groupBox_CAPINTERVAL"));
        groupBox_CAPINTERVAL->setGeometry(QRect(190, 310, 171, 91));
        RCAPINTERVALBtn = new QPushButton(groupBox_CAPINTERVAL);
        RCAPINTERVALBtn->setObjectName(QStringLiteral("RCAPINTERVALBtn"));
        RCAPINTERVALBtn->setGeometry(QRect(10, 50, 75, 23));
        WCAPINTERVALBtn = new QPushButton(groupBox_CAPINTERVAL);
        WCAPINTERVALBtn->setObjectName(QStringLiteral("WCAPINTERVALBtn"));
        WCAPINTERVALBtn->setGeometry(QRect(90, 50, 75, 23));
        lineEdit_CAPINTERVAL = new QLineEdit(groupBox_CAPINTERVAL);
        lineEdit_CAPINTERVAL->setObjectName(QStringLiteral("lineEdit_CAPINTERVAL"));
        lineEdit_CAPINTERVAL->setGeometry(QRect(10, 20, 151, 20));
        groupBox_CAPTIME = new QGroupBox(groupBox);
        groupBox_CAPTIME->setObjectName(QStringLiteral("groupBox_CAPTIME"));
        groupBox_CAPTIME->setGeometry(QRect(190, 110, 171, 91));
        RCAPTIMEBtn = new QPushButton(groupBox_CAPTIME);
        RCAPTIMEBtn->setObjectName(QStringLiteral("RCAPTIMEBtn"));
        RCAPTIMEBtn->setGeometry(QRect(10, 50, 75, 23));
        WCAPTIMEBtn = new QPushButton(groupBox_CAPTIME);
        WCAPTIMEBtn->setObjectName(QStringLiteral("WCAPTIMEBtn"));
        WCAPTIMEBtn->setGeometry(QRect(90, 50, 75, 23));
        lineEdit_BTIME = new QLineEdit(groupBox_CAPTIME);
        lineEdit_BTIME->setObjectName(QStringLiteral("lineEdit_BTIME"));
        lineEdit_BTIME->setGeometry(QRect(10, 20, 61, 20));
        lineEdit_ETIME = new QLineEdit(groupBox_CAPTIME);
        lineEdit_ETIME->setObjectName(QStringLiteral("lineEdit_ETIME"));
        lineEdit_ETIME->setGeometry(QRect(100, 20, 61, 20));
        label = new QLabel(groupBox_CAPTIME);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 20, 16, 16));
        groupBox_SHAPSHOT = new QGroupBox(groupBox);
        groupBox_SHAPSHOT->setObjectName(QStringLiteral("groupBox_SHAPSHOT"));
        groupBox_SHAPSHOT->setGeometry(QRect(370, 110, 171, 91));
        SHAPSHOTBtn = new QPushButton(groupBox_SHAPSHOT);
        SHAPSHOTBtn->setObjectName(QStringLiteral("SHAPSHOTBtn"));
        SHAPSHOTBtn->setGeometry(QRect(50, 40, 75, 23));
        groupBox_RESET = new QGroupBox(groupBox);
        groupBox_RESET->setObjectName(QStringLiteral("groupBox_RESET"));
        groupBox_RESET->setGeometry(QRect(370, 210, 171, 91));
        RESETBtn = new QPushButton(groupBox_RESET);
        RESETBtn->setObjectName(QStringLiteral("RESETBtn"));
        RESETBtn->setGeometry(QRect(50, 40, 75, 23));
        groupBox_FTPADMIN = new QGroupBox(groupBox);
        groupBox_FTPADMIN->setObjectName(QStringLiteral("groupBox_FTPADMIN"));
        groupBox_FTPADMIN->setGeometry(QRect(370, 10, 171, 91));
        RFTPADMINBtn = new QPushButton(groupBox_FTPADMIN);
        RFTPADMINBtn->setObjectName(QStringLiteral("RFTPADMINBtn"));
        RFTPADMINBtn->setGeometry(QRect(10, 50, 75, 23));
        WFTPADMINBtn = new QPushButton(groupBox_FTPADMIN);
        WFTPADMINBtn->setObjectName(QStringLiteral("WFTPADMINBtn"));
        WFTPADMINBtn->setGeometry(QRect(90, 50, 75, 23));
        lineEdit_FTPADMIN = new QLineEdit(groupBox_FTPADMIN);
        lineEdit_FTPADMIN->setObjectName(QStringLiteral("lineEdit_FTPADMIN"));
        lineEdit_FTPADMIN->setGeometry(QRect(10, 20, 151, 20));
        QWidget::setTabOrder(lineEdit_IP, RIPBtn);
        QWidget::setTabOrder(RIPBtn, WIPBtn);
        QWidget::setTabOrder(WIPBtn, RdateTimeEdit);
        QWidget::setTabOrder(RdateTimeEdit, RTimeBtn);
        QWidget::setTabOrder(RTimeBtn, WTimeBtn);
        QWidget::setTabOrder(WTimeBtn, lineEdit_FTPADMIN);
        QWidget::setTabOrder(lineEdit_FTPADMIN, RFTPADMINBtn);
        QWidget::setTabOrder(RFTPADMINBtn, WFTPADMINBtn);
        QWidget::setTabOrder(WFTPADMINBtn, lineEdit_QZ);
        QWidget::setTabOrder(lineEdit_QZ, RQZBtn);
        QWidget::setTabOrder(RQZBtn, WQZBtn);
        QWidget::setTabOrder(WQZBtn, lineEdit_BTIME);
        QWidget::setTabOrder(lineEdit_BTIME, RCAPTIMEBtn);
        QWidget::setTabOrder(RCAPTIMEBtn, lineEdit_ETIME);
        QWidget::setTabOrder(lineEdit_ETIME, WCAPTIMEBtn);
        QWidget::setTabOrder(WCAPTIMEBtn, SHAPSHOTBtn);
        QWidget::setTabOrder(SHAPSHOTBtn, lineEdit_FTPSERVER);
        QWidget::setTabOrder(lineEdit_FTPSERVER, RFTPSERVERBtn);
        QWidget::setTabOrder(RFTPSERVERBtn, WFTPSERVERBtn);
        QWidget::setTabOrder(WFTPSERVERBtn, lineEdit_FF);
        QWidget::setTabOrder(lineEdit_FF, RFFBtn);
        QWidget::setTabOrder(RFFBtn, WFFBtn);
        QWidget::setTabOrder(WFFBtn, RESETBtn);
        QWidget::setTabOrder(RESETBtn, lineEdit_SF);
        QWidget::setTabOrder(lineEdit_SF, RSFBtn);
        QWidget::setTabOrder(RSFBtn, WSFBtn);
        QWidget::setTabOrder(WSFBtn, lineEdit_CAPINTERVAL);
        QWidget::setTabOrder(lineEdit_CAPINTERVAL, RCAPINTERVALBtn);
        QWidget::setTabOrder(RCAPINTERVALBtn, WCAPINTERVALBtn);

        retranslateUi(QtGuiClass);

        QMetaObject::connectSlotsByName(QtGuiClass);
    } // setupUi

    void retranslateUi(QWidget *QtGuiClass)
    {
        QtGuiClass->setWindowTitle(QApplication::translate("QtGuiClass", "\347\273\210\347\253\257\346\216\247\345\210\266", nullptr));
        groupBox->setTitle(QString());
        groupBox_time->setTitle(QApplication::translate("QtGuiClass", "\350\256\276\345\244\207\346\227\266\351\227\264", nullptr));
        RTimeBtn->setText(QApplication::translate("QtGuiClass", "\350\257\273\345\217\226\346\227\266\351\222\237", nullptr));
        WTimeBtn->setText(QApplication::translate("QtGuiClass", "\350\256\276\347\275\256\346\227\266\351\222\237", nullptr));
        groupBox_IP->setTitle(QApplication::translate("QtGuiClass", "IP", nullptr));
        RIPBtn->setText(QApplication::translate("QtGuiClass", "\350\257\273\345\217\226IP", nullptr));
        WIPBtn->setText(QApplication::translate("QtGuiClass", "\350\256\276\347\275\256IP", nullptr));
        groupBox_QZ->setTitle(QApplication::translate("QtGuiClass", "\345\214\272\347\253\231\345\217\267", nullptr));
        RQZBtn->setText(QApplication::translate("QtGuiClass", "\350\257\273\345\217\226\345\214\272\347\253\231\345\217\267", nullptr));
        WQZBtn->setText(QApplication::translate("QtGuiClass", "\350\256\276\347\275\256\345\214\272\347\253\231\345\217\267", nullptr));
        groupBox_FTPSEVER->setTitle(QApplication::translate("QtGuiClass", "FTP\346\234\215\345\212\241\345\231\250", nullptr));
        RFTPSERVERBtn->setText(QApplication::translate("QtGuiClass", "\350\257\273\345\217\226FTP", nullptr));
        WFTPSERVERBtn->setText(QApplication::translate("QtGuiClass", "\350\256\276\347\275\256FTP", nullptr));
        groupBox_FF->setTitle(QApplication::translate("QtGuiClass", "FTP\344\275\277\350\203\275\346\240\207\350\256\260", nullptr));
        RFFBtn->setText(QApplication::translate("QtGuiClass", "\350\257\273\345\217\226\346\240\207\350\256\260", nullptr));
        WFFBtn->setText(QApplication::translate("QtGuiClass", "\350\256\276\347\275\256\346\240\207\350\256\260", nullptr));
        groupBox_SF->setTitle(QApplication::translate("QtGuiClass", "\344\274\240\346\204\237\345\231\250\344\275\277\350\203\275\346\240\207\350\256\260", nullptr));
        RSFBtn->setText(QApplication::translate("QtGuiClass", "\350\257\273\345\217\226\346\240\207\350\256\260", nullptr));
        WSFBtn->setText(QApplication::translate("QtGuiClass", "\350\256\276\347\275\256\346\240\207\350\256\260", nullptr));
        groupBox_CAPINTERVAL->setTitle(QApplication::translate("QtGuiClass", "\346\213\215\347\205\247\346\227\266\351\227\264", nullptr));
        RCAPINTERVALBtn->setText(QApplication::translate("QtGuiClass", "\350\257\273\345\217\226\351\227\264\351\232\224", nullptr));
        WCAPINTERVALBtn->setText(QApplication::translate("QtGuiClass", "\350\256\276\347\275\256\351\227\264\351\232\224", nullptr));
        groupBox_CAPTIME->setTitle(QApplication::translate("QtGuiClass", "\346\213\215\346\221\204\346\227\266\351\227\264", nullptr));
        RCAPTIMEBtn->setText(QApplication::translate("QtGuiClass", "\350\257\273\345\217\226\350\214\203\345\233\264", nullptr));
        WCAPTIMEBtn->setText(QApplication::translate("QtGuiClass", "\350\256\276\347\275\256\350\214\203\345\233\264", nullptr));
        label->setText(QApplication::translate("QtGuiClass", "~", nullptr));
        groupBox_SHAPSHOT->setTitle(QApplication::translate("QtGuiClass", "\346\212\223\346\213\215\345\233\276\347\211\207", nullptr));
        SHAPSHOTBtn->setText(QApplication::translate("QtGuiClass", "\350\257\273\345\217\226\347\272\254\345\272\246", nullptr));
        groupBox_RESET->setTitle(QApplication::translate("QtGuiClass", "\351\207\207\351\233\206\345\231\250", nullptr));
        RESETBtn->setText(QApplication::translate("QtGuiClass", "\351\207\215\345\220\257\351\207\207\351\233\206\345\231\250", nullptr));
        groupBox_FTPADMIN->setTitle(QApplication::translate("QtGuiClass", "FTP\346\234\215\345\212\241\345\231\250", nullptr));
        RFTPADMINBtn->setText(QApplication::translate("QtGuiClass", "\350\257\273\345\217\226\350\264\246\346\210\267", nullptr));
        WFTPADMINBtn->setText(QApplication::translate("QtGuiClass", "\350\256\276\347\275\256\350\264\246\346\210\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiClass: public Ui_QtGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUICLASS_H
