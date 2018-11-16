/********************************************************************************
** Form generated from reading UI file 'DMTDDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DMTDDLG_H
#define UI_DMTDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DMTDDlg
{
public:
    QPushButton *BrowsingBtn;
    QLabel *label;
    QLineEdit *PathLineEdit;
    QProgressBar *DoingBar;
    QPushButton *ImpBtn;
    QLabel *label_2;
    QLabel *NumberLabel;

    void setupUi(QDialog *DMTDDlg)
    {
        if (DMTDDlg->objectName().isEmpty())
            DMTDDlg->setObjectName(QStringLiteral("DMTDDlg"));
        DMTDDlg->resize(525, 160);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        DMTDDlg->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("../Image/upload.ico"), QSize(), QIcon::Normal, QIcon::Off);
        DMTDDlg->setWindowIcon(icon);
        DMTDDlg->setStyleSheet(QStringLiteral(""));
        BrowsingBtn = new QPushButton(DMTDDlg);
        BrowsingBtn->setObjectName(QStringLiteral("BrowsingBtn"));
        BrowsingBtn->setGeometry(QRect(430, 40, 75, 21));
        BrowsingBtn->setFont(font);
        label = new QLabel(DMTDDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 81, 20));
        label->setFont(font);
        PathLineEdit = new QLineEdit(DMTDDlg);
        PathLineEdit->setObjectName(QStringLiteral("PathLineEdit"));
        PathLineEdit->setGeometry(QRect(90, 40, 321, 20));
        DoingBar = new QProgressBar(DMTDDlg);
        DoingBar->setObjectName(QStringLiteral("DoingBar"));
        DoingBar->setGeometry(QRect(10, 120, 521, 23));
        DoingBar->setValue(0);
        ImpBtn = new QPushButton(DMTDDlg);
        ImpBtn->setObjectName(QStringLiteral("ImpBtn"));
        ImpBtn->setGeometry(QRect(430, 80, 75, 23));
        ImpBtn->setFont(font);
        label_2 = new QLabel(DMTDDlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 80, 81, 20));
        label_2->setFont(font);
        NumberLabel = new QLabel(DMTDDlg);
        NumberLabel->setObjectName(QStringLiteral("NumberLabel"));
        NumberLabel->setGeometry(QRect(90, 80, 81, 20));
        NumberLabel->setFont(font);

        retranslateUi(DMTDDlg);

        QMetaObject::connectSlotsByName(DMTDDlg);
    } // setupUi

    void retranslateUi(QDialog *DMTDDlg)
    {
        DMTDDlg->setWindowTitle(QApplication::translate("DMTDDlg", "\350\241\245\346\212\204\346\225\260\346\215\256", nullptr));
        BrowsingBtn->setText(QApplication::translate("DMTDDlg", "\346\265\217\350\247\210", nullptr));
        label->setText(QApplication::translate("DMTDDlg", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        ImpBtn->setText(QApplication::translate("DMTDDlg", "\345\257\274\345\205\245", nullptr));
        label_2->setText(QApplication::translate("DMTDDlg", "\346\225\260\346\215\256\351\207\217\357\274\232", nullptr));
        NumberLabel->setText(QApplication::translate("DMTDDlg", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DMTDDlg: public Ui_DMTDDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DMTDDLG_H
