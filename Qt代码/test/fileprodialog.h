#ifndef FILEPRODIALOG_H
#define FILEPRODIALOG_H

#include <QDialog>
#include "client.h"
#include "server.h"
#include <WINSOCK2.H>
namespace Ui {
class Fileprodialog;
}

class Fileprodialog : public QDialog
{
    Q_OBJECT
signals:
    void snd_request_by_server(QString info);
    void to_close_this_subwin();
    void update_the_progressbar(const qint64 & progress);
    void wakeup_tips_window(int event_type);

public:
    SOCKET soc_for_TCP_file;
    QString filepath;
    QString filename;
    QString usrname;
    qint64 size_of_file_by_Byte;
    std::thread *for_service;
public:
    explicit Fileprodialog(QWidget *parent = nullptr);
    Fileprodialog(QString info);/*for recerver*/
    ~Fileprodialog();

    void set_usr_combobox(QStringList usrs);
    bool set_up_TCP_host();
    bool set_up_TCP_client(QString host_IP);
    void host_service();
    void client_recv();


private slots:
    void on_toolButton_clicked();
    void on_pushButton_snd_clicked();
    void s_to_close_this_subwin();
    void s_update_the_progressbar(const qint64 &progress);

    void s_wakeup_tips_window(int event_type);

private:
    Ui::Fileprodialog *ui;
};

#endif // FILEPRODIALOG_H
