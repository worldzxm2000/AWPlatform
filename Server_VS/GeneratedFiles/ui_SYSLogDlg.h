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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SYSLogDlg
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *CurrentPageLabel;
    QLabel *TotalPageabel;
    QPushButton *PageToBeginBtn;
    QPushButton *PageDownBtn;
    QPushButton *PageUpBtn;
    QPushButton *PageToEndBtn;
    QTableWidget *DataListTable;

    void setupUi(QDialog *SYSLogDlg)
    {
        if (SYSLogDlg->objectName().isEmpty())
            SYSLogDlg->setObjectName(QStringLiteral("SYSLogDlg"));
        SYSLogDlg->resize(623, 471);
        horizontalLayoutWidget = new QWidget(SYSLogDlg);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(120, 420, 431, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        CurrentPageLabel = new QLabel(horizontalLayoutWidget);
        CurrentPageLabel->setObjectName(QStringLiteral("CurrentPageLabel"));

        horizontalLayout->addWidget(CurrentPageLabel);

        TotalPageabel = new QLabel(horizontalLayoutWidget);
        TotalPageabel->setObjectName(QStringLiteral("TotalPageabel"));

        horizontalLayout->addWidget(TotalPageabel);

        PageToBeginBtn = new QPushButton(horizontalLayoutWidget);
        PageToBeginBtn->setObjectName(QStringLiteral("PageToBeginBtn"));

        horizontalLayout->addWidget(PageToBeginBtn);

        PageDownBtn = new QPushButton(horizontalLayoutWidget);
        PageDownBtn->setObjectName(QStringLiteral("PageDownBtn"));

        horizontalLayout->addWidget(PageDownBtn);

        PageUpBtn = new QPushButton(horizontalLayoutWidget);
        PageUpBtn->setObjectName(QStringLiteral("PageUpBtn"));

        horizontalLayout->addWidget(PageUpBtn);

        PageToEndBtn = new QPushButton(horizontalLayoutWidget);
        PageToEndBtn->setObjectName(QStringLiteral("PageToEndBtn"));

        horizontalLayout->addWidget(PageToEndBtn);

        DataListTable = new QTableWidget(SYSLogDlg);
        DataListTable->setObjectName(QStringLiteral("DataListTable"));
        DataListTable->setGeometry(QRect(10, 10, 601, 401));

        retranslateUi(SYSLogDlg);

        QMetaObject::connectSlotsByName(SYSLogDlg);
    } // setupUi

    void retranslateUi(QDialog *SYSLogDlg)
    {
        SYSLogDlg->setWindowTitle(QApplication::translate("SYSLogDlg", "\347\263\273\347\273\237\346\227\245\345\277\227", nullptr));
        CurrentPageLabel->setText(QApplication::translate("SYSLogDlg", "\347\254\254100\351\241\265", nullptr));
        TotalPageabel->setText(QApplication::translate("SYSLogDlg", "\345\205\26110000\351\241\265", nullptr));
        PageToBeginBtn->setText(QApplication::translate("SYSLogDlg", "\351\246\226\351\241\265", nullptr));
        PageDownBtn->setText(QApplication::translate("SYSLogDlg", "\345\211\215\344\270\200\351\241\265", nullptr));
        PageUpBtn->setText(QApplication::translate("SYSLogDlg", "\345\220\216\344\270\200\351\241\265", nullptr));
        PageToEndBtn->setText(QApplication::translate("SYSLogDlg", "\346\234\253\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SYSLogDlg: public Ui_SYSLogDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSLOGDLG_H
