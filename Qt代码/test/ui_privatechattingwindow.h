/********************************************************************************
** Form generated from reading UI file 'privatechattingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRIVATECHATTINGWINDOW_H
#define UI_PRIVATECHATTINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrivateChattingWindow
{
public:
    QWidget *centralwidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QPlainTextEdit *plainTextEdit;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *PrivateChattingWindow)
    {
        if (PrivateChattingWindow->objectName().isEmpty())
            PrivateChattingWindow->setObjectName(QString::fromUtf8("PrivateChattingWindow"));
        PrivateChattingWindow->resize(720, 480);
        centralwidget = new QWidget(PrivateChattingWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(130, 10, 581, 441));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        plainTextEdit = new QPlainTextEdit(formLayoutWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, plainTextEdit);

        textBrowser = new QTextBrowser(formLayoutWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        formLayout->setWidget(0, QFormLayout::FieldRole, textBrowser);

        PrivateChattingWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(PrivateChattingWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 720, 21));
        PrivateChattingWindow->setMenuBar(menuBar);

        retranslateUi(PrivateChattingWindow);

        QMetaObject::connectSlotsByName(PrivateChattingWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PrivateChattingWindow)
    {
        PrivateChattingWindow->setWindowTitle(QCoreApplication::translate("PrivateChattingWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrivateChattingWindow: public Ui_PrivateChattingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRIVATECHATTINGWINDOW_H
