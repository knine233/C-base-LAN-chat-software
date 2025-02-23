#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"
#include "client.h"
#include "fileprodialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    server *host;
signals:
    void snd_file_request_to_client(QString info);
public:
//    MainWindow(bool is_host,QString usrname = "Administrator");
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(bool client);
    ~MainWindow();
    void ad_initialize(const QString & usrname = "Administrator");
    void init_usrname(QString name);
    void display_msg_on_screen(QString raw_msg,int msg_type,bool empty_input = false);
    client *peer;
    QString chat_mate;
    /*下面是一些常量声明*/
    const char *delimiter = "\\~$^/";
    const QString Admin_colr = "rgb(225, 199, 2)";
    const QString me_colr = "rgb(33, 155, 33)";
    const QString cli_colr = "rgb(33, 33, 206)";

private slots:

    void on_toolButton_filesnd_clicked();
    void s_pre_connection_request();
    void s_recv_group_msg(QString msg);
    void s_upload_to_display_msg(QString msg);
    void on_pushButton_send_clicked();
    void s_update_host_usrlist(QString info, bool is_append);

    void on_toolButton_chatsavr_clicked();

    void on_toolButton_p2pchat_clicked();
    void s_recv_file_request(QString info);
    void s_snd_request_by_server(QString info);
    void s_recv_private_msg(QString raw_msg);
    void s_host_offline();

};


#endif // MAINWINDOW_H
