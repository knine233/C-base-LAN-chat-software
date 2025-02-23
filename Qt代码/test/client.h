#ifndef CLIENT_H
#define CLIENT_H
#include<WINSOCK2.H>
#include<STDIO.H>
#include<iostream>
#include<cstring>
#include<thread>
#include <QString>
#include <QObject>
class client:public QObject
{
    Q_OBJECT
public:
    SOCKET socket_for_server;
    sockaddr_in serAddr;
    SOCKET socket_for_file_recvr;
public:
    bool init(QString host_IP);
    bool login_register_check(QString raw,bool &is_login);
    void hear();
    void sendmsg(QString msg, bool is_group_msg = true, bool is_private_msg = false);
    void offline(bool when_pre_login);
    void snd_file();
    void setupTCP_for_file();

signals:
    void recv_private_msg(QString msg);
    void recv_file_request(QString info);
    void recv_group_msg(QString msg);
    void host_offline();
    void mem_changed(QString msg, bool is_online);

};
#endif // CLIENT_H
