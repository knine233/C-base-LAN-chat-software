#include "fileprodialog.h"
#include "ui_fileprodialog.h"
#include <QFileDialog>
const char *delimiter = "\\~$^/";

Fileprodialog::Fileprodialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fileprodialog)
{
    ui->setupUi(this);
    ui->progressBar->reset();
    connect(this,SIGNAL(update_the_progressbar(qint64)),this,SLOT(s_update_the_progressbar(qint64)));
    connect(this,SIGNAL(to_close_this_subwin()),this,SLOT(s_to_close_this_subwin()));
    connect(this,SIGNAL(wakeup_tips_window(int)),this, SLOT(s_wakeup_tips_window(int)));
    setWindowTitle("文件传输");
}

Fileprodialog::~Fileprodialog()
{
    delete ui;
}

#include <QMessageBox>
Fileprodialog::Fileprodialog(QString info) :/*for receiver*/
    QDialog(nullptr),
    ui(new Ui::Fileprodialog)
{
    ui->setupUi(this);
    QStringList data = info.split(delimiter);
    connect(this,SIGNAL(to_close_this_subwin()),this,SLOT(s_to_close_this_subwin()));
    connect(this,SIGNAL(update_the_progressbar(qint64)),this,SLOT(s_update_the_progressbar(qint64)));
    connect(this,SIGNAL(wakeup_tips_window(int)),this, SLOT(s_wakeup_tips_window(int)));
    /*对窗口做出一定的改变，以适应文件接收端的需求*/
    setWindowTitle("文件传输");
    ui->label_indi_usr->setText("源用户：");
    ui->label_indi_file->setText("接收文件：");
    ui->comboBox_usr_choose->addItem(data[0]);
    ui->lineEdit_filename->setText(data[1]);
    QVariant tmp(data[2]);
    size_of_file_by_Byte = tmp.toLongLong();
    data[2].truncate(data[2].length()-3);
    ui->lineEdit_filesize->setText(data[2] + "kB");
    filename = data[1];
    ui->comboBox_usr_choose->setEditable(false);
    ui->pushButton_snd->hide();
    ui->progressBar->reset();
    ui->toolButton->setEnabled(false);

}

#include <QFileInfo>
void Fileprodialog::on_toolButton_clicked()
{/*当按下文件选择按钮时，打开文件选择窗口，并把选中的文件信息存储起来*/
    filepath = QFileDialog::getOpenFileName(this);
    filename = filepath.right(filepath.size()-filepath.lastIndexOf('/')-1);
    QFileInfo f_info(filepath);
    size_of_file_by_Byte = f_info.size();
    ui->lineEdit_filename->setText(filename);
    ui->lineEdit_filesize->setText(QString::number(size_of_file_by_Byte/1000) + "kB");
}
void Fileprodialog::set_usr_combobox(QStringList usrs)
{/*把当前在线用户push进用户选择栏里*/
    ui->comboBox_usr_choose->addItems(usrs);
}

bool Fileprodialog::set_up_TCP_host()
{

    /*必要的初始化*/
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0) return false;
    /*创建临时文件传输的主机socket*/
    sockaddr_in self_Addr;
    self_Addr.sin_family = PF_INET;
    self_Addr.sin_port = htons(9999);//约定好的主机端口号为9999，这里预留接口，后续可能改成动态端口
    self_Addr.sin_addr.S_un.S_addr = INADDR_ANY;
    soc_for_TCP_file = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    /*绑定端口号，这里假设一定会成功，反正后期会改成动态端口*/
    bind(soc_for_TCP_file, (struct sockaddr*)&self_Addr, sizeof(self_Addr));
    return true;
    /*之后启动函数，开始处理文件传输业务*/

}
#include <fstream>
/*这里为了避免命名冲突，重定义了这两个函数*/
SOCKET Accept(SOCKET& s, sockaddr* addr, int* addrlen){
    return accept(s,addr,addrlen);
}
int Connect(SOCKET s, const sockaddr *name, int namelen){
    return connect(s, name, namelen);
}
bool Fileprodialog::set_up_TCP_client(QString host_IP)
{
    /*必要的初始化*/
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0) return false;
    soc_for_TCP_file = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (soc_for_TCP_file == INVALID_SOCKET) return false;
    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(9999);
    serAddr.sin_addr.S_un.S_addr = inet_addr(host_IP.toStdString().c_str());
    if (Connect(soc_for_TCP_file, (struct sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
        closesocket(soc_for_TCP_file);
        QMessageBox::information(this,"文件传输提示","对方可能已下线");
        return false;
    }
    return true;
}

#include <QtCore/qtextcodec.h>
void Fileprodialog::client_recv()
{
    //接收缓冲区
    int buffer_size = 4096;
    char recv_buf[buffer_size];
    memset(recv_buf, '\0', buffer_size);

    QString newpath = "./recv_file/" + filename;
    QTextCodec* codec = QTextCodec::codecForName("gbk");
    std::string x = codec->fromUnicode(newpath.toStdWString().c_str()).toStdString();
    std::ofstream outputFile(x, std::ios::binary );	//没有就创建
    if (!outputFile.good())
    {
        closesocket(soc_for_TCP_file);
        emit wakeup_tips_window(6);
        emit to_close_this_subwin();
        return;
    }
    //准备完毕
    int bytesRead = 1;
    qint64 bytes_recv = 0;
    while (1)
    {
        //接受数据
        bytesRead = recv(soc_for_TCP_file, recv_buf, buffer_size, 0);
        //接收完毕，退出循环
        if (bytesRead <= 0) break;
        outputFile.write(recv_buf, bytesRead);
        bytes_recv += bytesRead;
        emit update_the_progressbar(bytes_recv);
        send(soc_for_TCP_file, "1", 1 ,0);
    }
    outputFile.close();
    emit wakeup_tips_window(1);
    emit to_close_this_subwin();

}

void Fileprodialog::s_to_close_this_subwin()
{
    this->close();
}
void Fileprodialog::s_update_the_progressbar(const qint64 &progress)
{
    if(size_of_file_by_Byte>1000000)//防止数值溢出，当文件大于2.1G时会超过int范围
    {
        ui->progressBar->setMaximum(size_of_file_by_Byte/10000);
        ui->progressBar->setValue(progress/10000);
    }
    else{
        ui->progressBar->setMaximum(size_of_file_by_Byte);
        ui->progressBar->setValue(progress);
    }

}

#include<QMessageBox>

void Fileprodialog::on_pushButton_snd_clicked()
{
    /*准备好借助server发给目标的信息原文本*/
    if(ui->comboBox_usr_choose->currentText().isEmpty()||filename.isEmpty()){
        QMessageBox::information(this, tr("禁止行为"), tr("信息不完善，请补全用户与文件信息 :-("));
        return;
    }
    QString info = ui->comboBox_usr_choose->currentText() + delimiter + filename +
                   delimiter + QString::number(size_of_file_by_Byte) +"2";

    /*发信号，让client发信息给server*/
    emit snd_request_by_server(info);
    /*开始启动函数处理文件传输业务*/
    if(!set_up_TCP_host()){//网络错误，无法建立TCP连接，请检查端口是否被占用
        QMessageBox::warning(this,"错误提示","无法绑定端口号");
        this->close();
    }
    ui->pushButton_snd->setEnabled(false);
    ui->toolButton->setEnabled(false);
    for_service = new std::thread(&Fileprodialog::host_service, this);
    for_service->detach();
}

#include <QtCore/qtextcodec.h>
void Fileprodialog::host_service()
{
    char buffer[4096] = {'\0'};
    std::ifstream tar_file;
    /*不按下面方式处理的话无法打开有中文路径的文件*/
    QTextCodec* codec = QTextCodec::codecForName("gbk");
    std::string x = codec->fromUnicode(filepath.toStdWString().c_str()).toStdString();
    tar_file.open(x, std::ios::in | std::ios::binary);	//指定以二进制方式打开
    if(!tar_file.good())//文件打开失败
    {
        emit wakeup_tips_window(4);
        closesocket(soc_for_TCP_file);
        emit to_close_this_subwin();

    }
    if (listen(soc_for_TCP_file, 10) == SOCKET_ERROR)
    {
        tar_file.close();
        emit wakeup_tips_window(5);
        closesocket(soc_for_TCP_file);
        emit to_close_this_subwin();

    }
    SOCKET client_soc = INVALID_SOCKET;
    sockaddr_in remoteAddr;
    int addrlen = sizeof(remoteAddr);
    /*成功与目标用户建立预连接*/
    client_soc = Accept(soc_for_TCP_file,(sockaddr*)&remoteAddr, &addrlen);
    /*等待对方答复*/
    int ret = recv(client_soc, buffer, 4096, 0);
    /*此处应该插入一个窗口，提示正在等待同意*///再注，改成多线程后没必要了
    if(ret<=0 || buffer[0]=='0'){//对方拒收文件，返回false

        closesocket(client_soc);
        tar_file.close();
        emit wakeup_tips_window(2);
        closesocket(soc_for_TCP_file);
        emit to_close_this_subwin();
        return;
    }
    qint64 bytes_have_sent = 0;
    /*开始发送文件*/
    /*应该实现一下停等*/
    while (!tar_file.eof())
    {
        tar_file.read(buffer, 4096);
        int bytesRead = tar_file.gcount();		//返回上次读取的长度
        int bytesSent = send(client_soc, buffer, bytesRead, 0);
        if (bytesSent == -1)//传送错误
        {
            closesocket(client_soc);
            tar_file.close();
            emit wakeup_tips_window(2);
            emit to_close_this_subwin();
        }
        bytes_have_sent += bytesRead;
        emit update_the_progressbar(bytes_have_sent);
        int recv_ack = recv(client_soc, buffer, 1, 0);
        if(recv_ack <= 0)
        {
            closesocket(client_soc);
            tar_file.close();
            emit wakeup_tips_window(2);
            emit to_close_this_subwin();
        }

    }
    closesocket(client_soc);
    tar_file.close();
    closesocket(soc_for_TCP_file);
    emit wakeup_tips_window(1);
    emit to_close_this_subwin();
}

void Fileprodialog::s_wakeup_tips_window(int event_type)
{
    switch (event_type) {
    case 1:
        QMessageBox::information(this,"传输结果","传输完毕！");
        break;
    case 2:
        QMessageBox::information(this,"提示","对方拒收文件");
        break;
    case 3:
        QMessageBox::warning(this,"错误提示","传输错误！请尝试重新传输");
        break;
    case 4:
        QMessageBox::warning(this, "错误提示","无法打开指定文件！");
        break;
    case 5:
        QMessageBox::warning(this,"错误提示","监听错误");
        break;
    case 6:
        QMessageBox::information(this,"提示","传输失败，可能是文件没有成功创建所致");
        break;
    }

}

/*下面的是废弃代码，仅供参考，可以无视*/
/*改为多线程前的代码，因阻塞，会造成文件传输主窗口经常无响应*/
//#include<QMessageBox>

//void Fileprodialog::on_pushButton_snd_clicked()
//{
//    /*准备好借助server发给目标的信息原文本*/
//    if(ui->comboBox_usr_choose->currentText().isEmpty()||filename.isEmpty()){
//        QMessageBox::information(this, tr("禁止行为"), tr("信息不完善，请补全用户与文件信息 :-("));
//        return;
//    }
//    QString info = ui->comboBox_usr_choose->currentText() + delimiter + filename +
//                   delimiter + QString::number(size_of_file_by_Byte) +"2";

//    /*发信号，让client发信息给server*/
//    emit snd_request_by_server(info);
//    /*开始启动函数处理文件传输业务*/
//    if(!set_up_TCP_host()){//网络错误，无法建立TCP连接，请检查端口是否被占用
//        QMessageBox::warning(this,"错误提示","无法绑定端口号");
//        this->close();
//    }
//    if(!host_service()){
//        /*关闭host套接字再退出*/
//        closesocket(soc_for_TCP_file);
//        this->close();
//    }
//    else{//传输完成，关闭窗口
//        closesocket(soc_for_TCP_file);
//        QMessageBox::information(this,"传输结果","传输完毕！");
//        this->close();
//    }
//}
//bool Fileprodialog::host_service()
//{
//    char buffer[1024] = {'\0'};
//    std::ifstream tar_file;
//    /*不按下面方式处理的话无法打开有中文路径的文件*/
//    QTextCodec* codec = QTextCodec::codecForName("gbk");
//    std::string x = codec->fromUnicode(filepath.toStdWString().c_str()).toStdString();
//    tar_file.open(x, std::ios::in | std::ios::binary);	//指定以二进制方式打开
//    if(!tar_file.good())//文件打开失败
//    {
//        QMessageBox::warning(this, "错误提示","无法打开指定文件！");
//        return false;

//    }
//    if (listen(soc_for_TCP_file, 10) == SOCKET_ERROR)
//    {
//        tar_file.close();
//        QMessageBox::warning(this,"错误提示","监听错误");
//        return false;

//    }
//    SOCKET client_soc = INVALID_SOCKET;
//    sockaddr_in remoteAddr;
//    int addrlen = sizeof(remoteAddr);
//    /*成功与目标用户建立预连接*/
//    client_soc = Accept(soc_for_TCP_file,(sockaddr*)&remoteAddr, &addrlen);
//    /*等待对方答复*/
//    int ret = recv(client_soc, buffer, 1024, 0);
//    /*此处应该插入一个窗口，提示正在等待同意*/
//    if(ret<=0 || buffer[0]=='0'){//对方拒收文件，返回false

//        closesocket(client_soc);
//        tar_file.close();
//        QMessageBox::information(this,"提示","对方拒收文件");
//        return false;
//    }
//    qint64 bytes_have_sent = 0;
//    /*开始发送文件*/
//    while (!tar_file.eof())
//    {
//        tar_file.read(buffer, 1024);
//        int bytesRead = tar_file.gcount();		//返回上次读取的长度
//        int bytesSent = send(client_soc, buffer, bytesRead, 0);
//        if (bytesSent == -1)//传送错误
//        {
//            closesocket(client_soc);
//            tar_file.close();
//            QMessageBox::warning(this,"错误提示","传输错误！请尝试重新传输");
//            return false;
//        }
//        bytes_have_sent += bytesRead;
//        //ui->progressBar->setValue(bytes_have_sent/size_of_file_by_Byte);
//        emit update_the_progressbar(bytes_have_sent);
//        //if(recv(client_soc, buffer, 1024, 0)<=0) return false;//断开连接

//    }
//    closesocket(client_soc);
//    tar_file.close();
//    return true;
//}
