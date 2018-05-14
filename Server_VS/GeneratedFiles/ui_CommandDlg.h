/********************************************************************************
** Form generated from reading UI file 'CommandDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMANDDLG_H
#define UI_COMMANDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CommandDlg
{
public:
    QLineEdit *COMMText;
    QLabel *label;
    QPushButton *SendBtn;
    QLabel *label_2;
    QLabel *StatusLabel;

    void setupUi(QWidget *CommandDlg)
    {
        if (CommandDlg->objectName().isEmpty())
            CommandDlg->setObjectName(QStringLiteral("CommandDlg"));
        CommandDlg->resize(448, 160);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(12);
        CommandDlg->setFont(font);
        COMMText = new QLineEdit(CommandDlg);
        COMMText->setObjectName(QStringLiteral("COMMText"));
        COMMText->setGeometry(QRect(80, 39, 301, 31));
        COMMText->setFocusPolicy(Qt::StrongFocus);
        label = new QLabel(CommandDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 50, 81, 16));
        label->setFont(font);
        SendBtn = new QPushButton(CommandDlg);
        SendBtn->setObjectName(QStringLiteral("SendBtn"));
        SendBtn->setGeometry(QRect(160, 90, 75, 23));
        SendBtn->setFocusPolicy(Qt::NoFocus);
        label_2 = new QLabel(CommandDlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 130, 81, 20));
        StatusLabel = new QLabel(CommandDlg);
        StatusLabel->setObjectName(QStringLiteral("StatusLabel"));
        StatusLabel->setGeometry(QRect(100, 130, 81, 20));

        retranslateUi(CommandDlg);

        QMetaObject::connectSlotsByName(CommandDlg);
    } // setupUi

    void retranslateUi(QWidget *CommandDlg)
    {
        CommandDlg->setWindowTitle(QApplication::translate("CommandDlg", "\347\273\210\347\253\257\345\221\275\344\273\244", nullptr));
        label->setText(QApplication::translate("CommandDlg", "\347\273\210\347\253\257\345\221\275\344\273\244", nullptr));
        SendBtn->setText(QApplication::translate("CommandDlg", "\345\217\221\351\200\201", nullptr));
        label_2->setText(QApplication::translate("CommandDlg", "\345\217\221\351\200\201\347\212\266\346\200\201\357\274\232", nullptr));
        StatusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CommandDlg: public Ui_CommandDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMANDDLG_H
