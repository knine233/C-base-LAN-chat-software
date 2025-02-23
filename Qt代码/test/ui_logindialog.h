/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLineEdit *pwdlineEdit;
    QPushButton *loginButton;
    QLabel *iconlabel;
    QLabel *label;
    QLabel *pwd_label;
    QLineEdit *UsrlineEdit;
    QLabel *Usr_label;
    QLabel *version_label;
    QPushButton *loginclientButton;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->setEnabled(true);
        LoginDialog->resize(490, 700);
        LoginDialog->setMinimumSize(QSize(490, 700));
        LoginDialog->setMaximumSize(QSize(490, 700));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/app_theme.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoginDialog->setWindowIcon(icon);
        pwdlineEdit = new QLineEdit(LoginDialog);
        pwdlineEdit->setObjectName(QString::fromUtf8("pwdlineEdit"));
        pwdlineEdit->setGeometry(QRect(165, 345, 200, 30));
        pwdlineEdit->setTabletTracking(true);
        pwdlineEdit->setFocusPolicy(Qt::StrongFocus);
        loginButton = new QPushButton(LoginDialog);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setEnabled(true);
        loginButton->setGeometry(QRect(140, 460, 100, 40));
        QFont font;
        font.setPointSize(11);
        loginButton->setFont(font);
        iconlabel = new QLabel(LoginDialog);
        iconlabel->setObjectName(QString::fromUtf8("iconlabel"));
        iconlabel->setGeometry(QRect(110, 100, 100, 100));
        iconlabel->setPixmap(QPixmap(QString::fromUtf8(":/images/images/app_theme.png")));
        iconlabel->setScaledContents(true);
        label = new QLabel(LoginDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 130, 181, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Cambria"));
        font1.setPointSize(25);
        font1.setBold(true);
        font1.setItalic(true);
        label->setFont(font1);
        label->setFrameShadow(QFrame::Sunken);
        pwd_label = new QLabel(LoginDialog);
        pwd_label->setObjectName(QString::fromUtf8("pwd_label"));
        pwd_label->setGeometry(QRect(75, 345, 85, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(12);
        font2.setBold(true);
        pwd_label->setFont(font2);
        pwd_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        UsrlineEdit = new QLineEdit(LoginDialog);
        UsrlineEdit->setObjectName(QString::fromUtf8("UsrlineEdit"));
        UsrlineEdit->setEnabled(true);
        UsrlineEdit->setGeometry(QRect(165, 300, 200, 30));
        UsrlineEdit->setTabletTracking(true);
        UsrlineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Usr_label = new QLabel(LoginDialog);
        Usr_label->setObjectName(QString::fromUtf8("Usr_label"));
        Usr_label->setGeometry(QRect(75, 300, 85, 30));
        Usr_label->setFont(font2);
        Usr_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        version_label = new QLabel(LoginDialog);
        version_label->setObjectName(QString::fromUtf8("version_label"));
        version_label->setGeometry(QRect(0, 680, 191, 21));
        version_label->setStyleSheet(QString::fromUtf8("color: rgb(80, 80, 80);"));
        loginclientButton = new QPushButton(LoginDialog);
        loginclientButton->setObjectName(QString::fromUtf8("loginclientButton"));
        loginclientButton->setGeometry(QRect(260, 460, 100, 40));
        loginclientButton->setFont(font);
        loginButton->raise();
        iconlabel->raise();
        label->raise();
        pwd_label->raise();
        Usr_label->raise();
        version_label->raise();
        pwdlineEdit->raise();
        UsrlineEdit->raise();
        loginclientButton->raise();
        QWidget::setTabOrder(UsrlineEdit, pwdlineEdit);
        QWidget::setTabOrder(pwdlineEdit, loginButton);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
#if QT_CONFIG(tooltip)
        pwdlineEdit->setToolTip(QCoreApplication::translate("LoginDialog", "<Password>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pwdlineEdit->setStatusTip(QCoreApplication::translate("LoginDialog", "<Password>", nullptr));
#endif // QT_CONFIG(statustip)
        loginButton->setText(QCoreApplication::translate("LoginDialog", "\344\273\245\344\270\273\346\234\272\347\231\273\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "We Link", nullptr));
        pwd_label->setText(QCoreApplication::translate("LoginDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
#if QT_CONFIG(tooltip)
        UsrlineEdit->setToolTip(QCoreApplication::translate("LoginDialog", "<Usrname>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        UsrlineEdit->setStatusTip(QCoreApplication::translate("LoginDialog", "<Usrname>", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        UsrlineEdit->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
#if QT_CONFIG(accessibility)
        UsrlineEdit->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        UsrlineEdit->setAccessibleDescription(QString());
#endif // QT_CONFIG(accessibility)
        Usr_label->setText(QCoreApplication::translate("LoginDialog", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        version_label->setText(QCoreApplication::translate("LoginDialog", "@WeLink Beta1.0", nullptr));
        loginclientButton->setText(QCoreApplication::translate("LoginDialog", "\344\273\245\345\256\242\346\210\267\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
