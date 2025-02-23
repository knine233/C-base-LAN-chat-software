#include "client.h"

namespace winsock {
int Connect(SOCKET s, const sockaddr *name, int namelen){
    return connect(s, name, namelen);
}/*使用命名空间，防止与connect重名*/
}
bool client::init(QString host_IP)
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0) exit(-1);
    socket_for_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_for_server == INVALID_SOCKET) exit(-1);
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(8888);
    serAddr.sin_addr.S_un.S_addr = inet_addr(host_IP.toStdString().c_str());
    if (winsock::Connect(socket_for_server, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
        closesocket(socket_for_server);
        return false;
    }
    return true;

}
bool client::login_register_check(QString name_and_pwd, bool &is_login)//检查是否注册过，是则返回true，否则返回false，触发注册事件
{
    std::string snd_str = name_and_pwd.toStdString();
    char buffer[16];
    send(socket_for_server, snd_str.c_str(), snd_str.length(),0);
    recv(socket_for_server, buffer, 16, 0);
    if(buffer[0] == '2') is_login = true;
    return buffer[0]=='1';
}

#include <QMessageBox>
void client::hear()
{
    while(true)
    {
        char recData[2048];
        int ret = recv(socket_for_server, recData, 2047, 0);
        if (ret > 0) {
            int event_type = recData[ret-1] - '0';
            recData[ret-1] = 0x00;
            switch(event_type){
            case 1://群发事件
                emit recv_group_msg(QString(recData));
                break;
            case 2://接收文件事件
                emit recv_file_request(QString(recData));
                break;
            case 3://接收私聊事件
                emit recv_private_msg(QString(recData));
                break;
            case 4://成员上线
                emit mem_changed(QString(recData),true);
                break;
            case 5://成员离线
                emit mem_changed(QString(recData),false);
                break;
            }

        }
        else
        {
//            QMessageBox::information(nullptr,"断开连接","服务器已下线！");
            emit host_offline();
//            closesocket(socket_for_server);
//            socket_for_server = INVALID_SOCKET;
            break;
        }
    }

}
void client::sendmsg(QString data, bool is_group_msg, bool is_private_msg)
{
    std::string sendData;
    if(is_group_msg) data.append("1");
    if(is_private_msg) data.append("3");//这里保证两个布尔量不同时为真
//    else data.append("3");
    /*不是群发消息说明是文件请求或私聊请求，其信息已处理过，无需再加标识符*/
    sendData = data.toStdString();
    if(socket_for_server == INVALID_SOCKET) return;//说明当前用户已下线
    send(socket_for_server, sendData.c_str(), sendData.length(), 0);

}
void client::offline(bool when_pre_login)
{
    if(when_pre_login)
    {
        send(socket_for_server,"0",1,0);
        closesocket(socket_for_server);
    }
    else{

    }
}
