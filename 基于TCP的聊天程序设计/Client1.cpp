#include<WINSOCK2.H>
#include<WINSOCK2.H>
#include<STDIO.H>
#include<iostream>
#include<cstring>
#include<thread>
#pragma warning(disable:4996)			//不加会报错
#include<mutex>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

mutex for_output;
void hear(SOCKET sclient)
{
	while(1)
	{
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0) {
			recData[ret] = 0x00;
			//for_output.lock();
			if((string)recData == "quit")
			    break;
			printf(recData);
			//for_output.unlock();
		}
		else
		{	//for_output.lock();
			cout<<"服务器已下线"<<endl;
			//for_output.unlock();
			break; 
		}
	}
}

void speak(SOCKET sclient)
{
	string data1;
	while(true)
	{
		//for_output.lock(); 
		getline(cin,data1);
		//for_output.unlock();
		const char* sendData;
		sendData = data1.c_str(); //string转const char*
		//char * sendData = "你好，TCP服务端，我是客户端\n";
		send(sclient, sendData, strlen(sendData), 0);
		//send()用来将数据由指定的socket传给对方主机
		//int send(int s, const void * msg, int len, unsigned int flags)
		//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
		//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error
		if(data1 == "Esc")
		{
			cout<<"退出了当前聊天模式"<<endl;
			break;
		}
	}
}

void send_string(const std::string& str, SOCKET s) 
{
	const char* c = str.c_str();
    size_t len = str.length();
    send(s, c, len, 0);
}

string rev_string(SOCKET sclient)//接收字符串 
{
	char revData[255];
	int last=recv(sclient, revData, 255, 0);
	if(last <= 0)						//实时检测用户是否断开连接
	{
		cout<<"服务器已下线"<<endl;
		return "";
	}
	revData[last]=0x00;
	string str = revData;
	return str;
}
    
void client_register(SOCKET sclient)
{
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------"<<endl;
	cout<<"现在开始注册！"<<endl;
	while(1)
	{
		string user[2],keyword; 
		cout<<"请输入用户名(不能有空格、回车、制表符):"<<endl;
		cin>>user[0]; 
		cout<<"请设置密码(不能有空格、回车、制表符):"<<endl;
		cin>>user[1];
		while(1)
		{
			cout<<"请确认密码(不能有空格、回车、制表符):"<<endl;
			cin>> keyword;
			if(keyword == user[1])
				break;
			else
				cout<<"密码不一致！"<<endl; 
		} 
		send_string(user[0]+"\t"+user[1],sclient);
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0) {
			recData[ret] = 0x00;
			printf(recData);
		}
		string answer = recData;
		if(answer == "用户注册成功，请牢记密码！\n")
			break;
	}
	cout<<"注册结束！"<<endl; 
	cout<<endl;
	cout<<endl;
}

string client_login(SOCKET sclient)
{
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------"<<endl;
	cout<<"现在开始登录！"<<endl;
	cout<<"如果阻塞，说明同时有其他顾客登录，请等待一会！"<<endl;
	string user[2],keyword; 
	while(1)
	{
		cout<<"请输入用户名(不能有空格、回车、制表符):"<<endl;
		cin>>user[0]; 
		cout<<"请输入密码(不能有空格、回车、制表符):"<<endl;
		cin>>user[1];
		send_string(user[0]+"\t"+user[1],sclient);
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0) {
			recData[ret] = 0x00;
			printf(recData);
			string answer = recData;
			if(answer == "用户登录成功！\n")
				break;
		}
		else
		{
			cout<<"服务器已经退出，客户端无法正常运行，请退出"<<endl;
		}
	}
	cout<<"登陆结束！"<<endl; 
	cout<<endl;
	cout<<endl;
	return user[0];
}

string register_or_login(SOCKET sclient)
{
	cout<<"---------------------"<<endl;
	cout<<"连接成功！"<<endl;
	cout<<"菜单栏"<<endl;
	cout<<"0---注册"<<endl;
	cout<<"1---登录"<<endl; 
	cout<<"---------------------"<<endl;
	string username;
	char index;
	cin>>index;
	while(index!='0' and index!='1')
	{
		cout<<"请重新输入！"<<endl;
		cin>>index; 
	}
	if(index=='0')
	{
		send_string("注册", sclient) ;
		client_register(sclient);
		username=client_login(sclient);
	}
	else
	{
		send_string("登录", sclient); 
		username=client_login(sclient);
	}
	return username;
} 

void one_to_one_chat(SOCKET sclient)
{
	string q=rev_string(sclient);
	cout<<q;
	if(q=="现在只有你一个人哦\n") return;
	/*while(1)
	{
		if(q=="") break;
		q=rev_string(sclient);
		cout<<q;
		if(q=="1") break;
	}*/
	string name;
	cin>>name;
	send_string(name,sclient);
	q=rev_string(sclient);
	cout<<q;
	while(q=="用户不存在！\n")
	{
		cout<<"请重新输入：";
		cin>>name;
		send_string(name,sclient);
	}
}

string creat_group_chat(SOCKET sclient)
{
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------"<<endl;
	cout<<"现在开始创建群组！"<<endl;
	string group; 
	string client_name;
	//vector<string> client_vector;
	while(1)
	{
		cout<<"请输入群组名(不能有空格、回车、制表符):"<<endl;
		cin>>group; 
		/*cout<<"请输入你要拉进群的用户(每输一个按一次回车，以“end”做结束):"
		cin>>client_name;
		while(client_name!="end")
		{
			
		}*/
		send_string(group,sclient);
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0) {
			recData[ret] = 0x00;
			printf(recData);
			string answer = recData;
			if(answer == "群组创建成功！\n")
				break;
		}
	}
	cout<<"群组创建结束！"<<endl; 
	cout<<endl;
	cout<<endl;
	return group;
}

int join_group_chat(SOCKET sclient)
{
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------"<<endl;
	cout<<"现在开始加入群组！"<<endl;
	string q=rev_string(sclient);
	cout<<q;
	cout<<"1"<<endl; 
	if(q=="现在还没有群组哦，是否要创建一个？\n0---是\n1---否\n")
	{
		string ans;
		cin>>ans;
		while(ans!="0" and ans!="1")
		{
			cout<<"重输："<<endl;
			cin>>ans; 
		}
		if(ans=="0")
		{
			send_string(ans,sclient);
			return 0;
		}
		else if(ans=="1")
		{
			send_string(ans,sclient);
			return 1; 
		}
	}
	/*while(q!="选择你要加入的群组:")
	{
		q=rev_string(sclient);
		cout<<q;
	}*/
	string name;
	cin>>name;
	send_string(name,sclient);
	q=rev_string(sclient);
	cout<<q;
	while(q=="群组不存在！\n")
	{
		cout<<"请重新输入：";
		cin>>name;
		send_string(name,sclient);
	}
	cout<<"群组加入结束！"<<endl; 
	cout<<endl;
	cout<<endl;
	return 2;
}

bool choose_group_chat(SOCKET sclient)
{
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------"<<endl;
	cout<<"现在开始选择在哪一个群组聊天！"<<endl;
	string q=rev_string(sclient);
	cout<<q;
	if(q=="你还没有加入任何群组！\n") return 1;
	/*while(q!="选择你要进行聊天群组:")
	{
		q=rev_string(sclient);
		cout<<q;
	}*/
	string name;
	cin>>name;
	send_string(name,sclient);
	q=rev_string(sclient);
	cout<<q;
	while(q=="群组不存在！\n")
	{
		cout<<"请重新输入：";
		cin>>name;
		send_string(name,sclient);
	}
	cout<<"现在可以在群组"<<name<<"聊天了！"<<endl; 
	cout<<endl;
	cout<<endl;
	return 0;
}

bool group_chat(SOCKET sclient)
{
	cout<<"---------------------"<<endl;
	cout<<"现在可以进行群组操作了！"<<endl; 
	cout<<"菜单栏"<<endl;
	cout<<"0---创建群组"<<endl;
	cout<<"1---加入群组"<<endl;
	cout<<"2---在群组中聊天"<<endl;
	cout<<"---------------------"<<endl;
	char index;
	cin>>index;
	while(index!='0' and index!='1' and index!='2')
	{
		cout<<"请重新输入！"<<endl;
		cin>>index; 
	}
	if(index=='0')
	{
		send_string("创建群组", sclient) ;
		creat_group_chat(sclient);
		//join_group_chat(sclient);
		return choose_group_chat(sclient);
	}
	if(index=='1')
	{
		send_string("加入群组", sclient); 
		int result=join_group_chat(sclient);
		if(result==0){
			creat_group_chat(sclient);
			//join_group_chat(sclient);
			return choose_group_chat(sclient);
		}
		else if(result==1)
		{
			cout<<"没有群组可以加入！客户端终止!"<<endl;
			exit(-1);
		}
		else
		{
			return choose_group_chat(sclient);
		}
	}
	if(index=='2')
	{
		send_string("在群组中聊天", sclient); 
		return choose_group_chat(sclient);
	}
}

bool choose_chat_mode(SOCKET sclient)
{
	cout<<"---------------------"<<endl;
	cout<<"现在可以正常聊天了！"<<endl; 
	cout<<"菜单栏"<<endl;
	cout<<"0---单人聊天"<<endl;
	cout<<"1---多人聊天"<<endl;
	cout<<"---------------------"<<endl;
	char index;
	cin>>index;
	while(index!='0' and index!='1')
	{
		cout<<"请重新输入！"<<endl;
		cin>>index; 
	}
	if(index=='0')
	{
		send_string("单人聊天", sclient) ;
		one_to_one_chat(sclient);
	}
	else
	{
		send_string("多人聊天", sclient); 
		return group_chat(sclient);
	}
	return 0;
}

int main()
{
	//初始化WSA，无论服务器还是用户都必须初始化WSA，否则报错
	WORD sockVersion = MAKEWORD(2, 2);			
	WSADATA data;
	//WSAStartup函数的返回值是一个整数，如果函数调用成功，												
	//返回值为0，表示初始化成功；如果函数调用失败，返回值不为0，表示初始化失败。
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
	//初始化socket
	SOCKET sclient;
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket!");
		return 0;
	}
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{ //连接失败
		printf("connect error !");
		closesocket(sclient);
		return 0;
	}
	
	
	string username=register_or_login(sclient);
	bool need_to_continue;
	while(1)
	{
		need_to_continue = choose_chat_mode(sclient);
		//用线程分开读和写,这样不用等输入了才有输出
		if(need_to_continue) continue;
		thread th(hear,sclient);
		th.detach();

		speak(sclient);

    	// 等待一段时间，以确保线程有足够的时间检查终止标志
    	std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	
	closesocket(sclient);
	WSACleanup();
	return 0;
}
