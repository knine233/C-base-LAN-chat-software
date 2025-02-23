#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <winsock2.h>
#include <string>
#include <list>
#include <thread>
#include <mutex>
#include <QObject>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <sstream>
#include <map>
#include <QStringList>

class server: public QObject
{
    Q_OBJECT
public:
signals:
    void pre_connection_request();
    void upload_to_display_msg(QString msg);
    void update_host_usrlist(QString info, bool is_append);
    void recv_clinet_file_request(QString info);
public:
    sockaddr_in Addr;	//the server's ip address and port
    SOCKET listener;				//the socket of server
    std::list<SOCKET> online_clients;	//record the online client
    std::list<std::thread> services;	//manage the clients
    std::map<SOCKET,QString> soc_to_usrname;
    std::map<SOCKET,QString> soc_to_ip;
    std::map<QString,SOCKET> usrname_to_soc;
    QString my_ip;
    const char *delimiter = "\\~$^/";

public:
    server();
//    ~server();
    std::mutex mtx_listen;
    std::mutex mtx_broadcast;
    std::mutex mtx_thread;
    bool init_and_run();
    void broadcast(char *content, const int &len, int event_type, SOCKET resource);
    void snd_private_msg(SOCKET sender, char *raw_data, const int &end);
private:
    inline void send_string(const std::string& str, SOCKET destination);//send string conviniently
    void service();//each service serve one specific client
    SOCKET listening();
    bool check_register(SOCKET virtual_client,bool &is_login);

    bool register_rec(SOCKET virtual_client);
    void send_cur_usrlist(SOCKET new_client);
    void file_agency(SOCKET sender, QString info);
private slots:
    void s_snd_file_request_to_client(QString info);

};





#endif // SERVER_H
