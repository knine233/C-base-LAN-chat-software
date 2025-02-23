/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Log_out;
    QWidget *centralwidget;
    QTreeWidget *treeWidget_usrlst;
    QGroupBox *groupBox_;
    QLabel *label_head;
    QLabel *label_Usrname;
    QTextBrowser *textBrowser_chatzone;
    QTextEdit *textEdit_inputzone;
    QPushButton *pushButton_send;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_filesnd;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_chatsavr;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButton_p2pchat;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 720);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/app_theme.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setTabShape(QTabWidget::Rounded);
        action_Log_out = new QAction(MainWindow);
        action_Log_out->setObjectName(QString::fromUtf8("action_Log_out"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/log_out.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Log_out->setIcon(icon1);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        treeWidget_usrlst = new QTreeWidget(centralwidget);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/client_ico.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/ip_ico.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setIcon(1, icon3);
        __qtreewidgetitem->setIcon(0, icon2);
        treeWidget_usrlst->setHeaderItem(__qtreewidgetitem);
        treeWidget_usrlst->setObjectName(QString::fromUtf8("treeWidget_usrlst"));
        treeWidget_usrlst->setGeometry(QRect(0, 60, 231, 621));
        treeWidget_usrlst->header()->setVisible(true);
        groupBox_ = new QGroupBox(centralwidget);
        groupBox_->setObjectName(QString::fromUtf8("groupBox_"));
        groupBox_->setGeometry(QRect(0, 0, 231, 60));
        groupBox_->setFlat(false);
        label_head = new QLabel(groupBox_);
        label_head->setObjectName(QString::fromUtf8("label_head"));
        label_head->setGeometry(QRect(0, 10, 50, 50));
        label_head->setFrameShape(QFrame::WinPanel);
        label_head->setFrameShadow(QFrame::Sunken);
        label_head->setPixmap(QPixmap(QString::fromUtf8(":/images/images/administor.png")));
        label_head->setScaledContents(true);
        label_Usrname = new QLabel(groupBox_);
        label_Usrname->setObjectName(QString::fromUtf8("label_Usrname"));
        label_Usrname->setGeometry(QRect(50, 10, 171, 50));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setUnderline(true);
        label_Usrname->setFont(font);
        label_Usrname->setFrameShape(QFrame::Panel);
        label_Usrname->setFrameShadow(QFrame::Sunken);
        label_Usrname->setAlignment(Qt::AlignCenter);
        textBrowser_chatzone = new QTextBrowser(centralwidget);
        textBrowser_chatzone->setObjectName(QString::fromUtf8("textBrowser_chatzone"));
        textBrowser_chatzone->setGeometry(QRect(240, 10, 751, 501));
        textEdit_inputzone = new QTextEdit(centralwidget);
        textEdit_inputzone->setObjectName(QString::fromUtf8("textEdit_inputzone"));
        textEdit_inputzone->setGeometry(QRect(240, 560, 751, 121));
        textEdit_inputzone->setContextMenuPolicy(Qt::NoContextMenu);
        pushButton_send = new QPushButton(centralwidget);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));
        pushButton_send->setGeometry(QRect(890, 640, 90, 30));
        QFont font1;
        font1.setPointSize(10);
        pushButton_send->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/images/send_ico.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_send->setIcon(icon4);
        pushButton_send->setIconSize(QSize(20, 20));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(250, 510, 181, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        toolButton_filesnd = new QToolButton(horizontalLayoutWidget);
        toolButton_filesnd->setObjectName(QString::fromUtf8("toolButton_filesnd"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/images/file_ico.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_filesnd->setIcon(icon5);
        toolButton_filesnd->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(toolButton_filesnd);

        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButton_chatsavr = new QToolButton(horizontalLayoutWidget);
        toolButton_chatsavr->setObjectName(QString::fromUtf8("toolButton_chatsavr"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/images/save_ico.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_chatsavr->setIcon(icon6);
        toolButton_chatsavr->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(toolButton_chatsavr);

        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        toolButton_p2pchat = new QToolButton(horizontalLayoutWidget);
        toolButton_p2pchat->setObjectName(QString::fromUtf8("toolButton_p2pchat"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/images/message_ico.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_p2pchat->setIcon(icon7);
        toolButton_p2pchat->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(toolButton_p2pchat);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 1000, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        QFont font2;
        font2.setPointSize(9);
        menu->setFont(font2);
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addSeparator();
        menu->addAction(action_Log_out);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "WeLink", nullptr));
        action_Log_out->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225(Log out)", nullptr));
#if QT_CONFIG(tooltip)
        action_Log_out->setToolTip(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\345\275\223\345\211\215\350\264\246\345\217\267", nullptr));
#endif // QT_CONFIG(tooltip)
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_usrlst->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "ip\345\234\260\345\235\200", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        groupBox_->setTitle(QString());
        label_Usrname->setText(QCoreApplication::translate("MainWindow", "Usrname", nullptr));
        textBrowser_chatzone->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_send->setToolTip(QCoreApplication::translate("MainWindow", "\345\277\253\346\215\267\351\224\256Ctrl+Enter", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_send->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
#if QT_CONFIG(shortcut)
        pushButton_send->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Return", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        toolButton_filesnd->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        toolButton_chatsavr->setToolTip(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\350\201\212\345\244\251\350\256\260\345\275\225", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        toolButton_p2pchat->setToolTip(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257\347\247\201\350\201\212", nullptr));
#endif // QT_CONFIG(tooltip)
        menu->setTitle(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
