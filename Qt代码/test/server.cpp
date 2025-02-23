#include "server.h"

server::server()
{
    Addr.sin_family = PF_INET;
    Addr.sin_port = htons(8888);
    Addr.sin_addr.S_un.S_addr = INADDR_ANY;
    listener = INVALID_SOCKET;
}

inline void server::send_string(const std::string& str, SOCKET destination)
{
    const char* c = str.c_str();
    size_t len = str.length();
    send(destination, c, len, 0);
}

SOCKET server::listening()
{
    mtx_listen.lock();
    if (listen(listener, 10) == SOCKET_ERROR)
    {
        printf("listen error !");
        exit(-1);
    }
    //receive TCP connection request successfully
    SOCKET client_soc = INVALID_SOCKET;
    sockaddr_in remoteAddr;
    int addrlen = sizeof(remoteAddr);
    client_soc = accept(listener,(sockaddr*)&remoteAddr, &addrlen);
    char *ip_add = inet_ntoa(remoteAddr.sin_addr);
    QString ip(ip_add);
    soc_to_ip[client_soc] = ip;
    mtx_listen.unlock();
    return client_soc;
}
void server::broadcast(char *content,const int &end,int event_type,SOCKET resource)
{
    mtx_broadcast.lock();
    content[end] = 0x00;
    content[end-1] = '0'+event_type;//这里有带标志位
    QString content_changed = QString(content);
    std::string forchar;
    QString raw_content;
    switch (event_type) {
    case 1:
//        content_changed = "<" + soc_to_usrname[resource] + ">:" + content_changed;
        content_changed = soc_to_usrname[resource] + delimiter + content_changed;
        if(resource!=INVALID_SOCKET) emit upload_to_display_msg(content_changed);
        forchar = content_changed.toStdString();
        for(auto &mem : online_clients)
            if(mem!=resource) send(mem, forchar.c_str(), forchar.length(), 0);
        break;
    case 4:
        raw_content = soc_to_usrname[resource] + " " + soc_to_ip[resource];
        emit update_host_usrlist(raw_content, true);
        raw_content.append("4");
        forchar = raw_content.toStdString();
        for(auto &mem : online_clients)
            if(mem!=resource) send(mem, forchar.c_str(), forchar.length(), 0);
        break;
    case 5:
        raw_content = soc_to_usrname[resource];
        emit update_host_usrlist(raw_content, false);
        raw_content.append("5");
        forchar = raw_content.toStdString();
        for(auto &mem : online_clients)
            if(mem!=resource) send(mem, forchar.c_str(), forchar.length(), 0);
        break;
    }

    mtx_broadcast.unlock();
}

void server::service()
{
    SOCKET client_soc = INVALID_SOCKET;
    while(client_soc==INVALID_SOCKET)//keep listening unless receive client socket
        client_soc = listening();
    emit pre_connection_request();
    //if the client give up registing, restart the service
    mtx_listen.lock();
    bool is_login = false;
    if(check_register(client_soc, is_login)){
        send(client_soc,"1",2,0);
        send_cur_usrlist(client_soc);
        mtx_listen.unlock();

    }
    else{//didn't register or have logined
        if(is_login) send(client_soc,"2",2,0);
        else send(client_soc,"0",2,0);
        if(register_rec(client_soc)){
            send(client_soc,"1",2,0);
            send_cur_usrlist(client_soc);
            mtx_listen.unlock();
        }
        else{
            send(client_soc,"0",2,0);//register fault,close the socket
            mtx_listen.unlock();
            mtx_thread.lock();
            services.push_back(std::thread(&server::service,this));
            services.back().detach();
            mtx_thread.unlock();
            soc_to_ip.erase(client_soc);
            closesocket(client_soc);
            return;
        }

    }
    char tmp[2];
    broadcast(tmp, 1, 4, client_soc);
    //broadcast the new member to all members
    /*derive new service*/
    mtx_thread.lock();
    services.push_back(std::thread(&server::service,this));
    services.back().detach();
    online_clients.push_back(client_soc);
    auto pointer = prev(online_clients.end());
    mtx_thread.unlock();
    char revData[1024];
    /*start the service*/
    while(true)
    {
        int ret = recv(client_soc, revData, 1023, 0);
        if(ret<=0) break;//which means client is offline
        char event_type = revData[ret-1]-'0';//indicate the type of event
        switch (event_type)
        {
        case 1://normal broadcast event
            broadcast(revData, ret, 1, client_soc);
            break;
        case 2://file sending request event
            /*derive a agency thread to handle the file transition service*/
            mtx_thread.lock();
            revData[ret] = 0x00;
            services.push_back(std::thread(&server::file_agency,this,client_soc,QString(revData)));
            services.back().detach();
            mtx_thread.unlock();
            break;
        case 3://private chatting event
            snd_private_msg(client_soc, revData, ret);
            break;

        }


    }
    //broadcast offline
    online_clients.erase(pointer);
    broadcast(tmp, 1, 5, client_soc);
    usrname_to_soc.erase(soc_to_usrname[client_soc]);
    soc_to_usrname.erase(client_soc);
    soc_to_ip.erase(client_soc);
    closesocket(client_soc);


}
bool server::init_and_run()
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0) return false;
    listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listener==INVALID_SOCKET) return false;
    if(bind(listener, (struct sockaddr*)&Addr, sizeof(Addr)) < 0) return false;
    soc_to_usrname[INVALID_SOCKET] = QString("$Admin");
    soc_to_ip[INVALID_SOCKET] = my_ip;
    services.push_back(std::thread(&server::service, this));
    services.back().detach();
    return true;
    //need a sign to keep this function or the main process running
    //这里后来发现主窗口会继续运行，不会使此处分离出来的线程结束，故无需循环等待
}
bool server::check_register(SOCKET virtual_client,bool &is_login)
{
    char buffer[256];
    int end = recv(virtual_client, buffer, 255, 0);
    buffer[end] = 0x00;
    QString raw(buffer), line;
//    QString path(":/registered/txt_file/register_table.txt");
    QString path("./txt_file/register_table.txt");
    QFile table(path);
    if(!table.open(QIODevice::ReadOnly|QIODevice::Text)) return false;
    QTextStream tstream(&table);
    tstream.setAutoDetectUnicode(true);
    while(!tstream.atEnd()){
        line = tstream.readLine();
        if(line == raw){
            table.close();
            QString tmp_name;
            for(auto&x:raw){
                if(x!=' ') tmp_name.append(x);
                else break;
            }
            if(usrname_to_soc.find(tmp_name) != usrname_to_soc.end())
            {//说明用户已登录
                is_login = true;
                return false;
            }
            soc_to_usrname[virtual_client] = tmp_name;
            usrname_to_soc[tmp_name] = virtual_client;
            return true;
        }
    }
    table.close();
    return false;

}
bool server::register_rec(SOCKET virtual_client)
{
    char buffer[256];
    int end = recv(virtual_client, buffer, 255, 0);
    if(end<=0) return false;//unpredicted transactions
    if(end == 1&&buffer[0] == '0') return false;//give up register
    buffer[end] = 0x00;
    QString raw(buffer);
    QStringList tmp,data = raw.split(" ");
    QString path("./txt_file/register_table.txt"),line;
    QFile forread(path);
    if(!forread.open(QIODevice::ReadOnly|QIODevice::Text)) return false;
    QTextStream ifs(&forread);
    ifs.setAutoDetectUnicode(true);
    while(!ifs.atEnd()){
        line = ifs.readLine();
        tmp = line.split(" ");
        if(tmp[0]==data[0]){
            forread.close();
            return false;
        }
    }
    forread.close();
    QFile table(path);
    if(!table.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)) return false;
    table.seek(table.size());
    QTextStream wts(&table);

    wts.setAutoDetectUnicode(true);
    wts<<raw<<Qt::endl;
    table.close();

    soc_to_usrname[virtual_client] = data[0];
    usrname_to_soc[data[0]] = virtual_client;
    return true;
}

void server::send_cur_usrlist(SOCKET new_client)
{
    QString raw;
    std::string for_char;
    for(auto &x:online_clients){
        raw = soc_to_usrname[x] + " " + soc_to_ip[x] + "4";
        for_char = raw.toStdString();
        send(new_client,for_char.c_str(),for_char.length(),0);
    }
}

void server::file_agency(SOCKET sender, QString info)
{
    info.truncate(info.length()-1);/*pop the signal bit*/
    QStringList infolst = info.split(delimiter);
    /*如果是某个客户想发文件给服务器：*/
    if(infolst[0] == "Administrator")
    {
        info = soc_to_usrname[sender] + delimiter + infolst[1] + delimiter + infolst[2]
               + delimiter + soc_to_ip[sender];
        emit recv_clinet_file_request(info);
        return;
    }
    SOCKET receiver = usrname_to_soc[infolst[0]];
    /*ask the receiver if he/she would receive the file*/
    //这里有个漏洞，如果请求被服务目标客户的service抢先接收了，这里就收不到了
    //为了解决这个漏洞，决定让两个客户建立TCP直连并传输文件
    //agency接收到的info格式是：目标用户名+文件名+大小+标识符
    //发送到接收方的格式是：发送用户名+文件名+大小+发送方ip+标识符
    info = soc_to_usrname[sender] + delimiter + infolst[1] + delimiter + infolst[2] + delimiter + soc_to_ip[sender] + "2";
    std::string for_char = info.toStdString();
    send(receiver, for_char.c_str(),for_char.length(),0);

}
void server::s_snd_file_request_to_client(QString info)
{
    file_agency(INVALID_SOCKET, info);
}

void server::snd_private_msg(SOCKET sender, char *raw_data, const int &end)
{
    //接收到的格式是，私聊接收对象名 + 分隔符 + 信息 + 类型标识符
    //发送给目标的格式是，私聊发起对象名 + 分割符 + 信息 + 类型标识符
    //如果是server想发私聊给目标用户，则只需把sender参数改为INVALID_SOCKET即可
    raw_data[end] = 0x00;
    QStringList infolst = QString(raw_data).split(delimiter);
    QString msg = "&lt;" + soc_to_usrname[sender]  + "&gt;" + delimiter + infolst[1];
    std::string for_char = msg.toStdString();
    send(usrname_to_soc[infolst[0]], for_char.c_str(), for_char.length(), 0);
}
