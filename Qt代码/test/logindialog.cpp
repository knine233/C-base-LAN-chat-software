#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    /*创建窗口并把光标置于用户名输入框*/
    ui->setupUi(this);
    ui->UsrlineEdit->setFocus();
    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);//把密码框的显示内容改为圆点
    is_host = false;
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::identity_check(QString usr, QString pwd)
{
    return usr=="Administrator"&&pwd=="192511";
}
void LoginDialog::on_loginButton_clicked()
{
    /*点击登录主机按钮的触发事件*/
    bool flag = identity_check(ui->UsrlineEdit->text(), ui->pwdlineEdit->text());
    if(flag){
       chatwindow = new MainWindow;
       chatwindow->show();
       this->close();
    }
    else{
       QMessageBox::warning(this,QObject::tr("错误"),"您输入的信息与主机用户不符，是否考虑以用户身份登录？");
       ui->pwdlineEdit->clear();
       ui->UsrlineEdit->setFocus();
    }

}

#include<QInputDialog>
#include <QRegularExpression>
void LoginDialog::on_loginclientButton_clicked()
{
    /*点击登录客户按钮的触发事件*/
    bool ok = false;
    QString ip_info = QInputDialog::getText(this, "IP地址配置", "请配置要加入服务器的IP地址:", QLineEdit::Normal, "", &ok);
    if(ok&&!ip_info.isEmpty())
    {
       QRegularExpression regex("^\\d{1,3}(\\.\\d{1,3}){3}$");
       QRegularExpressionMatch match = regex.match(ip_info);
       if(!match.hasMatch()){
           QMessageBox::warning(this,QObject::tr("提示"),"输入的IP地址格式有误");
           return;
       }
       /*尝试建立预连接并注册或登录*/
       chatwindow = new MainWindow(true);
       virtual_client = chatwindow->peer;
       if(chatwindow->peer->init(ip_info)){
           //开始检查注册与登录状态;
           bool is_login = false;
           QString raw = ui->UsrlineEdit->text()+" "+ui->pwdlineEdit->text();
           if(virtual_client->login_register_check(raw,is_login)){
               chatwindow->show();
               chatwindow->ad_initialize(ui->UsrlineEdit->text());
               chatwindow->init_usrname(ui->UsrlineEdit->text());
               /*有个坑，在这里开始运行client的hear线程的话，该线程会不会被登录窗口终止？可能要用到线程分离*/
               std::thread hear_th(&client::hear, chatwindow->peer);
               hear_th.detach();
               this->close();
               QMessageBox::information(this,QObject::tr("提示"),"登录成功！");
               return;

           }
           else{
               //是否注册？
               //注册信息对话框
               QString tips;
               if(is_login) tips = "该账号在目标服务器已登录，是否选择注册新用户？";
               else tips = "该账号尚未在这台服务器注册，是否选择注册用户？";
               QMessageBox::StandardButton choice = QMessageBox::question(this,"注册用户",tips,
                                                                          QMessageBox::Yes | QMessageBox::No );
               if(choice == QMessageBox::Yes){
                   QString reg_name = QInputDialog::getText(this, "注册", "请输入用户名:", QLineEdit::Normal, "", &ok);
                   if(ok&&!reg_name.isEmpty()){
                       QString reg_pwd = QInputDialog::getText(this, "注册", "请输入并牢记密码:", QLineEdit::Password, "", &ok);
                        if(ok&&!reg_pwd.isEmpty()){
                           QString reg = reg_name + " " + reg_pwd;
                           if(chatwindow->peer->login_register_check(reg,is_login)){
                               chatwindow->show();
                               chatwindow->ad_initialize(reg_name);
                               chatwindow->init_usrname(reg_name);
                               std::thread hear_th(&client::hear, chatwindow->peer);
                               hear_th.detach();
                               /*这里可能有坑*/
                               this->close();
                               QMessageBox::information(this,QObject::tr("提示"),"登录成功！");
                               return;
                           }
                           else{
                               QMessageBox::information(this,QObject::tr("提示"),"注册失败！可能用户名已被抢注，或者主机已下线。");
                           }
                       }
                   }

               }
           }
       }

       else{
           QMessageBox::information(this,QObject::tr("提示"),"没有匹配到相应的服务器，请检查输入的IP地址是否正确");
           return;
       }
       chatwindow->peer->offline(true);
       delete chatwindow->peer;
       delete chatwindow;
       chatwindow = nullptr;
       virtual_client = nullptr;
    }
}


