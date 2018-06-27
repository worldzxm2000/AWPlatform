/********************************************************************************
** Form generated from reading UI file 'SYSLogDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSLOGDLG_H
#define UI_SYSLOGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SYSLogDlg
{
public:
    QTableView *tableView;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *SYSLogDlg)
    {
        if (SYSLogDlg->objectName().isEmpty())
            SYSLogDlg->setObjectName(QStringLiteral("SYSLogDlg"));
        SYSLogDlg->resize(707, 471);
        tableView = new QTableView(SYSLogDlg);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(0, 10, 711, 401));
        horizontalLayoutWidget = new QWidget(SYSLogDlg);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(190, 420, 271, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        retranslateUi(SYSLogDlg);

        QMetaObject::connectSlotsByName(SYSLogDlg);
    } // setupUi

    void retranslateUi(QDialog *SYSLogDlg)
    {
        SYSLogDlg->setWindowTitle(QApplication::translate("SYSLogDlg", "\347\263\273\347\273\237\346\227\245\345\277\227", nullptr));
        label->setText(QApplication::translate("SYSLogDlg", "\347\254\254100\351\241\265", nullptr));
        label_2->setText(QApplication::translate("SYSLogDlg", "\345\205\26110000\351\241\265", nullptr));
        pushButton->setText(QApplication::translate("SYSLogDlg", "\345\211\215\344\270\200\351\241\265", nullptr));
        pushButton_2->setText(QApplication::translate("SYSLogDlg", "\345\220\216\344\270\200\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SYSLogDlg: public Ui_SYSLogDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSLOGDLG_H
