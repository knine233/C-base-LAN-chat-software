/********************************************************************************
** Form generated from reading UI file 'fileprodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEPRODIALOG_H
#define UI_FILEPRODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_Fileprodialog
{
public:
    QComboBox *comboBox_usr_choose;
    QLabel *label_indi_usr;
    QLabel *label_indi_file;
    QPushButton *pushButton_snd;
    QLabel *label_usrico;
    QLabel *label_indi_size;
    QLineEdit *lineEdit_filesize;
    QProgressBar *progressBar;
    QLineEdit *lineEdit_filename;
    QToolButton *toolButton;
    QLabel *label_indi_progress;

    void setupUi(QDialog *Fileprodialog)
    {
        if (Fileprodialog->objectName().isEmpty())
            Fileprodialog->setObjectName(QString::fromUtf8("Fileprodialog"));
        Fileprodialog->resize(542, 293);
        Fileprodialog->setMinimumSize(QSize(542, 293));
        Fileprodialog->setMaximumSize(QSize(542, 293));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/app_theme.png"), QSize(), QIcon::Normal, QIcon::Off);
        Fileprodialog->setWindowIcon(icon);
        comboBox_usr_choose = new QComboBox(Fileprodialog);
        comboBox_usr_choose->setObjectName(QString::fromUtf8("comboBox_usr_choose"));
        comboBox_usr_choose->setGeometry(QRect(150, 30, 200, 30));
        label_indi_usr = new QLabel(Fileprodialog);
        label_indi_usr->setObjectName(QString::fromUtf8("label_indi_usr"));
        label_indi_usr->setGeometry(QRect(60, 30, 75, 30));
        QFont font;
        font.setPointSize(11);
        label_indi_usr->setFont(font);
        label_indi_file = new QLabel(Fileprodialog);
        label_indi_file->setObjectName(QString::fromUtf8("label_indi_file"));
        label_indi_file->setGeometry(QRect(60, 80, 75, 30));
        label_indi_file->setFont(font);
        pushButton_snd = new QPushButton(Fileprodialog);
        pushButton_snd->setObjectName(QString::fromUtf8("pushButton_snd"));
        pushButton_snd->setGeometry(QRect(430, 70, 80, 30));
        QFont font1;
        font1.setPointSize(9);
        pushButton_snd->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/send_ico.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_snd->setIcon(icon1);
        pushButton_snd->setIconSize(QSize(20, 20));
        label_usrico = new QLabel(Fileprodialog);
        label_usrico->setObjectName(QString::fromUtf8("label_usrico"));
        label_usrico->setGeometry(QRect(350, 30, 32, 30));
        label_usrico->setFrameShape(QFrame::Box);
        label_usrico->setFrameShadow(QFrame::Raised);
        label_usrico->setPixmap(QPixmap(QString::fromUtf8(":/images/images/administor.png")));
        label_usrico->setScaledContents(true);
        label_indi_size = new QLabel(Fileprodialog);
        label_indi_size->setObjectName(QString::fromUtf8("label_indi_size"));
        label_indi_size->setGeometry(QRect(170, 140, 50, 30));
        label_indi_size->setFont(font);
        lineEdit_filesize = new QLineEdit(Fileprodialog);
        lineEdit_filesize->setObjectName(QString::fromUtf8("lineEdit_filesize"));
        lineEdit_filesize->setGeometry(QRect(220, 140, 120, 30));
        QFont font2;
        font2.setPointSize(10);
        lineEdit_filesize->setFont(font2);
        lineEdit_filesize->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_filesize->setReadOnly(true);
        progressBar = new QProgressBar(Fileprodialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(155, 210, 280, 30));
        progressBar->setValue(24);
        lineEdit_filename = new QLineEdit(Fileprodialog);
        lineEdit_filename->setObjectName(QString::fromUtf8("lineEdit_filename"));
        lineEdit_filename->setGeometry(QRect(150, 80, 200, 30));
        lineEdit_filename->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_filename->setReadOnly(true);
        toolButton = new QToolButton(Fileprodialog);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(350, 80, 32, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/file_ico.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon2);
        toolButton->setIconSize(QSize(28, 28));
        label_indi_progress = new QLabel(Fileprodialog);
        label_indi_progress->setObjectName(QString::fromUtf8("label_indi_progress"));
        label_indi_progress->setGeometry(QRect(90, 210, 60, 30));
        label_indi_progress->setFont(font);

        retranslateUi(Fileprodialog);

        QMetaObject::connectSlotsByName(Fileprodialog);
    } // setupUi

    void retranslateUi(QDialog *Fileprodialog)
    {
        Fileprodialog->setWindowTitle(QString());
        label_indi_usr->setText(QCoreApplication::translate("Fileprodialog", "\351\200\211\346\213\251\347\224\250\346\210\267", nullptr));
        label_indi_file->setText(QCoreApplication::translate("Fileprodialog", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_snd->setToolTip(QCoreApplication::translate("Fileprodialog", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_snd->setText(QCoreApplication::translate("Fileprodialog", "\345\217\221\351\200\201", nullptr));
        label_indi_size->setText(QCoreApplication::translate("Fileprodialog", "\345\244\247\345\260\217\357\274\232", nullptr));
        label_indi_progress->setText(QCoreApplication::translate("Fileprodialog", "\350\277\233\345\272\246\346\235\241\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Fileprodialog: public Ui_Fileprodialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEPRODIALOG_H
