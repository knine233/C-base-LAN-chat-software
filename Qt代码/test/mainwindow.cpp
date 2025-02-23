#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), peer(nullptr), chat_mate("1")
{
    ui->setupUi(this);
    ui->label_Usrname->setText("Administrator");
    host = new server;
    ad_initialize();
    ui->textEdit_inputzone->setFocus();

    /*信号与槽的连接一定要在对象创建后*/
    connect(host, SIGNAL(pre_connection_request()),this,SLOT(s_pre_connection_request()));
    connect(host, SIGNAL(upload_to_display_msg(QString)),this,SLOT(s_upload_to_display_msg(QString)));
    connect(host, SIGNAL(update_host_usrlist(QString,bool)),this,SLOT(s_update_host_usrlist(QString,bool)));
    connect(host, SIGNAL(recv_clinet_file_request(QString)),this,SLOT(s_recv_file_request(QString)));
    connect(this, SIGNAL(snd_file_request_to_client(QString)),host,SLOT(s_snd_file_request_to_client(QString)));
    host->init_and_run();
}

MainWindow::MainWindow(bool flag)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow), host(nullptr), chat_mate("1")
{
    if(!flag) return;//特殊情况，关闭窗口
    ui->setupUi(this);
    ui->textEdit_inputzone->setFocus();
    peer = new client;
    connect(peer,SIGNAL(recv_group_msg(QString)),this,SLOT(s_recv_group_msg(QString)));
    connect(peer,SIGNAL(mem_changed(QString,bool)),this,SLOT(s_update_host_usrlist(QString,bool)));
    connect(peer,SIGNAL(recv_file_request(QString)),this, SLOT(s_recv_file_request(QString)));
    connect(peer,SIGNAL(recv_private_msg(QString)),this,SLOT(s_recv_private_msg(QString)));
    connect(peer,SIGNAL(host_offline()),this, SLOT(s_host_offline()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QFileDialog>
#include <QString>
#include <QWidget>
void MainWindow::on_toolButton_filesnd_clicked()
{
    Fileprodialog *subwin = new Fileprodialog(this);
    connect(subwin, SIGNAL(snd_request_by_server(QString)), this, SLOT(s_snd_request_by_server(QString)));
    int maxrow = ui->treeWidget_usrlst->topLevelItemCount();
    QStringList usrs;
    if(host==nullptr)
        usrs.push_back("Administrator");

    for(int i = 1;i<maxrow;i++)
        usrs.push_back(ui->treeWidget_usrlst->topLevelItem(i)->text(0));

    subwin->set_usr_combobox(usrs);
    if(peer == nullptr) subwin->usrname = "Administrator";
    else subwin->usrname = ui->label_Usrname->text();
    subwin->show();

}

#include <QNetworkInterface>
#include <QTreeWidget>
void MainWindow::ad_initialize(const QString & usrname)
{
    QString ad_ip;
    foreach(const QHostAddress& hostAddress,QNetworkInterface::allAddresses())//对于所有检测到的地址
        if ( hostAddress != QHostAddress::LocalHost && hostAddress.toIPv4Address() )//如果格式为IPv4保留
            ad_ip = hostAddress.toString();
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,usrname);
    item->setText(1,ad_ip);
    ui->treeWidget_usrlst->addTopLevelItem(item);
    if(host != nullptr) host->my_ip = ad_ip;
}
void MainWindow::init_usrname(QString name)
{
    ui->label_Usrname->setText(name);
}

#include <QMessageBox>
void MainWindow::s_pre_connection_request()
{
    QMessageBox::information(this,QObject::tr("tips"),"有连接请求");
}
void MainWindow::s_recv_group_msg(QString msg)
{   //给client展示消息用的
    //信息的真正处理应该放在这里，而不应该在server处
    //收到格式为原客户 + 分隔符 + 信息
    display_msg_on_screen(msg,3);
}


void MainWindow::on_pushButton_send_clicked()
{
    if(chat_mate == "1")
    {
        if(host == nullptr){
            peer->sendmsg(ui->textEdit_inputzone->toPlainText());
            QString content = "[ME]" + QString(delimiter) + ui->textEdit_inputzone->toPlainText();
            display_msg_on_screen(content,1);
        }
        else{
            std::string snd_msg = ui->textEdit_inputzone->toPlainText().toStdString();
            snd_msg.append("1");
            QString content;
            content = "[ME]"+ QString(delimiter) + ui->textEdit_inputzone->toPlainText();
            display_msg_on_screen(content,1);
            host->broadcast(snd_msg.c_str(),snd_msg.length(),1,INVALID_SOCKET);
        }
    }
    else
    {
        if(host == nullptr){
            /*私聊对象名+分隔符+信息*/
            QString msg = "[ME]" + QString(delimiter) +ui->textEdit_inputzone->toPlainText() + delimiter +
                          "&lt;" + chat_mate + "&gt;";
            peer->sendmsg(chat_mate + delimiter + ui->textEdit_inputzone->toPlainText(),false, true);
            display_msg_on_screen(msg,2,true);

        }
        else{
            /*私聊对象+分割符+信息*/
            QString raw = chat_mate + QString(delimiter) + ui->textEdit_inputzone->toPlainText()+"3";
            std::string raw_str = raw.toStdString();
            host->snd_private_msg(INVALID_SOCKET,raw_str.c_str(),raw_str.length());
            raw = "[ME]" + QString(delimiter) +ui->textEdit_inputzone->toPlainText() + delimiter +
                          "&lt;" + chat_mate + "&gt;";
            display_msg_on_screen(raw,2,true);
        }
    }

}

void MainWindow::s_upload_to_display_msg(QString msg)
{   //给server展示收到的群发消息用的
    //信息的真正处理应该在这里
    //信息格式为源客户 + 分隔符 + 信息 + 标识符;
    msg.truncate(msg.length()-1);//截断最后一位信号标志位
    display_msg_on_screen(msg, 3);
}

#include <QStringList>
#include <QList>
void MainWindow::s_update_host_usrlist(QString info, bool is_append)
{
    if(is_append){
        QTreeWidgetItem *newitem = new QTreeWidgetItem();
        QStringList data = info.split(" ");
        newitem->setText(0, data[0]);
        newitem->setText(1, data[1]);
        ui->treeWidget_usrlst->addTopLevelItem(newitem);
    }
    else{
        QList<QTreeWidgetItem*> items = ui->treeWidget_usrlst->findItems(info,Qt::MatchExactly);
        QTreeWidgetItem *parent = items[0]->parent();
        if(parent)
            parent->takeChild(parent->indexOfChild(items[0]));
        else
            delete items[0];
    }
}

void MainWindow::on_toolButton_chatsavr_clicked()
{/*这里要把它改成追加模式*/
    QTextDocument* document = ui->textBrowser_chatzone->document();
    QString content = document->toPlainText();
    QString path("./txt_file/chat_history.txt");
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << content;
        file.close();
        QMessageBox::information(this,"保存聊天记录","保存成功");
    }
    else
    {
        QMessageBox::information(this,"保存聊天记录","保存失败");
    }
}


#include <QInputDialog>
void MainWindow::on_toolButton_p2pchat_clicked()
{
    int maxrow = ui->treeWidget_usrlst->topLevelItemCount();
    QStringList usrs;
    usrs.push_back("Administrator");
    for(int i = 1;i<maxrow;i++)
    {
        usrs.push_back(ui->treeWidget_usrlst->topLevelItem(i)->text(0));
    }
    bool ok;
    QString chosen_usr = QInputDialog::getItem(this, tr("私聊"), tr("请选择用户"), usrs, 0, false, &ok);
    if(ok&&!chosen_usr.isEmpty())//准备进入私聊
    {
        if(chosen_usr == "Administrator") chat_mate = "1";//把模式切换回群聊
        else chat_mate = chosen_usr;//把模式切换为私聊，且对象为chosen_usr
    }
}

void MainWindow::s_recv_file_request(QString info)
{
    /*这里的标识符在发送信号的时候就被截断了*/
    Fileprodialog *subwin = new Fileprodialog(info);
    QStringList data = info.split(delimiter);
    /*先建立预连接*/
    if(!subwin->set_up_TCP_client(data[3])){
        subwin->close();
        return;
    }
    int to_recv = QMessageBox::question(this, "文件接收提醒","用户" + data[0]+"给您发来文件：\n" + data[1] + "\n大小：" +
                                                QString::number(subwin->size_of_file_by_Byte/1000) + "kB\n是否接收？",
                                        QMessageBox::Yes | QMessageBox::No);

    if(to_recv == QMessageBox::No){
        /*告知发送方，拒绝请求*/
        send(subwin->soc_for_TCP_file,"0" ,1,0);
        closesocket(subwin->soc_for_TCP_file);
        delete subwin;
        return;
    }
    else{
        /*显示文件接收窗口*/
        send(subwin->soc_for_TCP_file, "1",1,0);
        subwin->show();
        std::thread th_file_recv(&Fileprodialog::client_recv, subwin);
        th_file_recv.detach();
        return;
    }
}

void MainWindow::s_snd_request_by_server(QString info)
{
    if(peer!=nullptr){
        /*客户要发文件*/
        peer->sendmsg(info, false);
    }
    else{
        /*主机要发文件*/
        emit snd_file_request_to_client(info);
    }
}

#include<QTime>
void MainWindow::s_recv_private_msg(QString raw_msg)
{   //接收到的格式是：发送方姓名 + 分隔符 + 信息，这里最后一位标识符被截断
    //打在公屏上的格式是timestamp\n<sender_name>-->[ME]:detail_message\n\n
    raw_msg = raw_msg + delimiter + "[ME]";
    display_msg_on_screen(raw_msg,2);
}

void MainWindow::display_msg_on_screen(QString raw_msg,int msg_type,bool empty_input)
{//msg格式：发送人 + 分隔符 + 信息（注意这里后面没有标识符） + 分隔符 + <接收方姓名>(可能有)
    QTime current_time = QTime::currentTime();
    QString timestamp = current_time.toString("hh:mm:ss");//获取时间戳并转为字符串
    timestamp = "<font style ='font-size: 9pt' >" + timestamp + "</font>";
    QStringList data = raw_msg.split(delimiter);
    QString info_line, msg_line;
    switch (msg_type) {
    case 1://自己发送的普通消息
        ui->textEdit_inputzone->clear();
        info_line = "<font style='font-size: 12pt;color:" + me_colr + ";font-weight: 800;'>" +
                    data[0] + ": </font>";
        break;
    case 2://私聊信息
        if(empty_input) ui->textEdit_inputzone->clear();
        info_line = "<font style='font-size: 12pt;color:purple;font-weight: 800;'>" +
                            data[0] + "--&gt;" + data[2] + ": </font>";
        break;
    case 3://其他人发送的普通信息
        if(data[0] == "$Admin"){
            info_line = "<font style='font-size: 12pt;color:" + Admin_colr + ";font-weight: 800;'>&lt;" +
                        data[0] + "&gt;: </font>";
        }
        else{
            info_line = "<font style='font-size: 12pt;color:" + cli_colr + ";font-weight: 800;'>&lt;" +
                        data[0] + "&gt;: </font>";
        }
        break;
    }
    msg_line = "<font style = 'font-size: 13pt;font-weight:bold'>" + data[1] + "</font><br><br>";
    ui->textBrowser_chatzone->append(timestamp);
    ui->textBrowser_chatzone->append(info_line);
    ui->textBrowser_chatzone->append(msg_line);

}

void MainWindow::s_host_offline()
{
    QMessageBox::information(this,"断开连接","服务器已下线！");
    closesocket(peer->socket_for_server);
    peer->socket_for_server = INVALID_SOCKET;
    this->close();
}
