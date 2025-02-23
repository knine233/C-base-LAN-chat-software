#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "client.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    bool identity_check(QString usr, QString pwd);

private slots:
    void on_loginButton_clicked();

    void on_loginclientButton_clicked();

private:
    Ui::LoginDialog *ui;
    MainWindow *chatwindow;
    bool is_host;
    client* virtual_client;
};

#endif // LOGINDIALOG_H
