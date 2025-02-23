#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include <string>
//#include <sys/epoll.h>
#include <list>
#include <thread>
#include <mutex>
#include<fstream>
#include<vector>
#include<sstream>
#include <string.h>
#include<map>
#include<algorithm>
using namespace std;

mutex mtx,for_write,for_login,for_thread,for_show,for_group;
SOCKET no_tar;		//作用上相当于空SOCKET

void show_list(list<SOCKET> oc)
{
	for_show.lock();
	list<SOCKET>::iterator l = oc.begin();
	int num = 1;
	while (l != oc.end())
	{
		printf("No.%d client:%d\n", num, *l);
		l++;
		num++;
	}
	for_show.unlock();
	return;
}

class server
{
private:
	struct sockaddr_in Addr;	//服务器端的IP地址和端口
	int listener;				//监听器
	list<SOCKET> online_clients;	//在线用户，记录accept的结果
	list<thread> services;		//用线程服务对象
	list<list<SOCKET>> connection;		//记录谁和谁连接了
	vector<string> client_name_vector,keyword_vector;
	map<SOCKET,string> socket_to_name;
	map<string,SOCKET> name_to_socket;
	
	vector<string> group_name_vector;
	vector<vector<string>> group_member_vector_vector;
	map<vector<string>,string> groupmember_to_groupname;
	map<string,vector<string>> groupname_to_groupmember;
	map<string,vector<string>> client_to_group_that_he_is_in;
	//map<string,SOCKET>

public:
	server()	//构造服务器
	{
		read_client_information();
		read_group_information();
		Addr.sin_family = PF_INET;
		Addr.sin_port = htons(8888);
		Addr.sin_addr.S_un.S_addr = INADDR_ANY;	
		listener = 0;
	}
	
	void close_socket(SOCKET sClient,list<SOCKET>::iterator pointer)
	{
		cout<<"客户"<<socket_to_name[sClient]<<"退出"<<endl; 
		cout<<"客户"<<socket_to_name[sClient]<<"对应线程结束1"<<endl;
		mtx.lock();
		cout<<"客户"<<socket_to_name[sClient]<<"对应线程结束1.5"<<endl;
		online_clients.erase(pointer);
		cout<<"客户"<<socket_to_name[sClient]<<"对应线程结束2"<<endl;
		mtx.unlock();
		closesocket(sClient);
		//for_thread.lock();
		//services.push_back(thread(&server::listening, this));
		//services.back().detach();
		//for_thread.unlock();
		cout<<"客户"<<socket_to_name[sClient]<<"对应线程结束3"<<endl;
	 } 
	 
	inline string rev_string(SOCKET sClient,list<SOCKET>::iterator pointer)//接收字符串 
	{
		char revData[255];
		int last=recv(sClient, revData, 255, 0);
		if(last <= 0)						//实时检测用户是否断开连接
		{
			printf("客户%d退出\n", sClient);
			/*mtx.lock();
			online_clients.erase(pointer);
			mtx.unlock();*/
			return "";
		}
		revData[last]=0x00;
		string str = revData;
		return str;
	}
	
	inline void send_string(const std::string& str, SOCKET s) //发送字符串 
	{
    	const char* c = str.c_str();
    	size_t len = str.length();
    	send(s, c, len, 0);
    }
    
	inline void send_char(const char *c,SOCKET s)		//这两个函数是为了少敲几个字的，同样不用在意
	{
		send(s, c, strlen(c), 0);
		return;
	}

	inline void send_char(char c[], SOCKET s)
	{
		send(s, c, strlen(c), 0);
		return;
	}
	
	void write_client_information()//向 client_information.txt写用户信息，格式为"name"+"\t"+"keyword"+"\n"，每次有人注册时都重写一遍 
	{
		//for_write实现写互斥 
		for_write.lock();
		ofstream ofs;
		ofs.open("client_information.txt",std::ios::out);
		if(!ofs.is_open())
    		cout<<"文件不能正常打开"<<endl;
		string clinet_name,keyworld;
		for(int i=0; i<client_name_vector.size(); i++)
		{
			ofs<<client_name_vector[i]<<"\t"<<keyword_vector[i]<<endl;
		}
		ofs.close();
		cout<<"用户信息已经刷新！"<<endl;
		for_write.unlock();
	}
	
	void write_group_information()
	{
		for_group.lock();
		ofstream ofs;
		ofs.open("group_information.txt",std::ios::out);
		if(!ofs.is_open())
    		cout<<"文件不能正常打开"<<endl;
		//string group_name;
		//vector<string> group_member;
		for(int i=0; i<group_name_vector.size(); i++)
		{
			ofs<<group_name_vector[i]<<"\t";
			for(vector<string>::iterator it = groupname_to_groupmember[group_name_vector[i]].begin();it!=groupname_to_groupmember[group_name_vector[i]].end();it++)
				ofs<<*it<<"\t";
			ofs<<endl;
		}
		ofs.close();
		cout<<"群组信息已经刷新！"<<endl;
		for_group.unlock();
	}
	
	void read_client_information()//从 client_information.txt读用户信息
	{
		ifstream ifs;
    	ifs.open("client_information.txt",std::ios::in);
    	if(!ifs)
    		cout<<"文件不能正常打开"<<endl; 
    	string client_name,keyword;
    	string line,last_line="whatever";
    	int count=0;
    	while(1)
    	{	
    		getline(ifs,line);
    		if(line=="")
    		{
    			break;
			}
			cout<<line<<endl; 
    		stringstream ss(line);
    		ss>>client_name>>keyword;
    		client_name_vector.push_back(client_name);
    		keyword_vector.push_back(keyword);
    		last_line = line;
    	}
    	ifs.close();
	}
	
	void read_group_information()
	{
		ifstream ifs;
    	ifs.open("group_information.txt",std::ios::in);
    	if(!ifs)
    		cout<<"文件不能正常打开"<<endl; 
    	string group_name;
    	string tmp,last_tmp;
    	vector<string> group_member_vector;
    	string line,last_line="whatever";
    	int count=0;
    	while(1)
    	{	
    		group_member_vector.clear();
    		getline(ifs,line);
    		if(line=="" || last_line==line)
    		{
    			break;
			}
			cout<<line<<endl; 
    		stringstream ss(line);
    		ss>>group_name;
    		last_tmp = group_name;
    		while(1)
    		{
    			ss>>tmp;
    			if(tmp.length()==0 || tmp==last_tmp)
    				break;
    			group_member_vector.push_back(tmp);
    			client_to_group_that_he_is_in[tmp].push_back(group_name);
    			last_tmp = tmp;
			}
			vector<string> g=group_member_vector;
    		group_name_vector.push_back(group_name);
    		group_member_vector_vector.push_back(g);
    		groupmember_to_groupname[g]=group_name;
    		groupname_to_groupmember[group_name] = g;
    		last_line = line;
    	}
    	ifs.close();
	}
	
	void client_login(SOCKET sClient,list<SOCKET>::iterator pointer)//用户登录 
	{
		//send_string("如果阻塞，说明同时有其他顾客登录，请等待一会！\n",sClient); 
		for_login.lock();
		char revData[255];
		while(1)
		{
			int ret=recv(sClient, revData, 255, 0);
			if(ret <= 0)						//实时检测用户是否断开连接
			{
				printf("客户%d退出\n", sClient);
				/*mtx.lock();
				online_clients.erase(pointer);
				mtx.unlock();*/
				break;
			}
			else
			{
				revData[ret] = 0x00;
				int client_name_repeat = -1;
				string client_name,keyword;
				string clientData = revData;
				//revData[ret] = 0x00;
				stringstream sstream(clientData);
				sstream>>client_name>>keyword;
				for(int i=0;i<client_name_vector.size();i++)
				{
					if(client_name == client_name_vector[i])
					{
						client_name_repeat = i;
						break;
					}
				}
				if(client_name_repeat == -1)
				{
					cout<<"用户不存在！\n"<<endl;
					send_string("用户不存在！\n",sClient);
					continue;
				}
				if(keyword_vector[client_name_repeat] != keyword)
				{
					send_string("用户密码错误！请重新登录！\n",sClient);
					cout<<"用户"<<sClient<<"登录失败!"<<endl;
				}
				else
				{
					socket_to_name[sClient] = client_name; //将套接字与用户名关联 
					name_to_socket[client_name] = sClient; //将用户名与套接字关联 
					send_string("用户登录成功！\n",sClient);
					cout<<"用户"<<client_name<<"登录成功!"<<"套接字为"<<sClient<<endl;
					send_to_all(client_name + "上线了！\n",sClient);
					break;
				}
			}
		 } 
		 for_login.unlock();
	}
	
	void send_to_all(string sendData,SOCKET sClient)
	{
		for(list<SOCKET>::iterator it = online_clients.begin();it != online_clients.end();it++)
		{
			if(*it == sClient)
				continue;
			send_string(sendData,*it);
		}
	}
	
	void client_register(SOCKET sClient,list<SOCKET>::iterator pointer)//用户注册 
	{
		char revData[255];
		while(1)
		{
			int ret=recv(sClient, revData, 255, 0);
			if(ret <= 0)						//实时检测用户是否断开连接
			{
				printf("客户%d退出\n", sClient);
				/*mtx.lock();
				online_clients.erase(pointer);
				mtx.unlock();*/
				break;
			}
			else
			{
				revData[ret] = 0x00;
				int client_name_repeat = -1;
				string client_name,keyword;
				string clientData = revData;
				//revData[ret] = 0x00;
				stringstream sstream(clientData);
				sstream>>client_name>>keyword;
				for(int i=0;i<client_name_vector.size();i++)
				{
					if(client_name == client_name_vector[i])
					{
						client_name_repeat = i;
						break;
					}
				}
				if(client_name_repeat>0)
				{
					send_string("用户已存在！请重新注册！\n",sClient);
					cout<<"用户"<<sClient<<"注册失败!"<<endl; 
				}
				else
				{
					client_name_vector.push_back(client_name);
					keyword_vector.push_back(keyword);
					char ch[255];
					sprintf(ch,"用户注册成功，请牢记密码！\n");
					send_char(ch, sClient);
					cout<<"用户"<<client_name<<"注册成功!"<<"套接字为"<<sClient<<endl;
					break;
				}
			}
		} 
		write_client_information();
	}
	
	void creat_group_chat(SOCKET sClient,list<SOCKET>::iterator pointer)
	{
		string name;
		while(1)
		{
			name=rev_string(sClient,pointer);
			if(name=="") return;
			auto it=find(group_name_vector.begin(),group_name_vector.end(),name);
			if (it != group_name_vector.end()) {
        		send_string("群组已存在！群组创建失败！\n",sClient);
        		cout<<"用户"<<sClient<<"创建群组"<<name<<"失败!"<<endl; 
    		} 
			else {
        		send_string("群组创建成功！\n",sClient);
        		cout<<"用户"<<sClient<<"创建群组"<<name<<"成功!"<<endl;
        		vector<string> tmp;
        		tmp.push_back(socket_to_name[sClient]);
        		group_name_vector.push_back(name);
        		group_member_vector_vector.push_back(tmp);
        		groupmember_to_groupname[tmp] = name;
        		groupname_to_groupmember[name] = tmp;
        		client_to_group_that_he_is_in[socket_to_name[sClient]].push_back(name);
        		break;
			}
    	}
    	write_group_information();
	}
	
	void show_group(SOCKET sClient)
	{
		int num = group_name_vector.size();
		/*char sendData[255];
		sprintf(sendData, "有 %d 个群组\n", num);
		send_char(sendData,sClient);*/
		vector<string>::iterator l = group_name_vector.begin();
		string str="";
		while (l != group_name_vector.end())
		{
			str = str+"groupname:";
			str = str + *l+"\tmember:";
			for(vector<string>::iterator it = groupname_to_groupmember[*l].begin();it != groupname_to_groupmember[*l].end();it++)
			{
				str = str + *it +"\t";
			}
			str = str +"\n";
			l++;
		}
		str = str + "选择你要加入的群组:\n";
		send_string(str,sClient);
	}
	
	void join_group_chat(SOCKET sClient,list<SOCKET>::iterator pointer)
	{
		if (group_name_vector.size() == 0)					
		{												
			send_char("现在还没有群组哦，是否要创建一个？\n0---是\n1---否\n", sClient);
			string ans = rev_string(sClient,pointer);
			if(ans == "") return;
			else if(ans=="0") creat_group_chat(sClient,pointer);
			else if(ans=="1") return;
		}
		else
		{
			show_group(sClient);
			string chosen_group;
			while(1)
			{
				chosen_group=rev_string(sClient,pointer);
				if(chosen_group=="") return;
				auto it = find(group_name_vector.begin(),group_name_vector.end(),chosen_group);
				if(it == group_name_vector.end())
				{
					cout<<"群组不存在！\n"<<endl;
					send_string("群组不存在！\n",sClient);
					continue;
				}
				else
				{
					groupname_to_groupmember[chosen_group].push_back(socket_to_name[sClient]);
					client_to_group_that_he_is_in[socket_to_name[sClient]].push_back(chosen_group);
					send_string("群组加入成功\n",sClient); 
					break;
				}
			}
		}
		write_group_information();
	}
	
	bool show_group_that_you_are_in(SOCKET sClient,list<SOCKET>::iterator pointer)
	{
		string sendData;
		vector<string> v = client_to_group_that_he_is_in[socket_to_name[sClient]];
		if(v.size()==0)
		{
			send_string("你还没有加入任何群组！\n",sClient);
			return 1; 
		}
		else
		{
			int num = v.size();
			sendData = "";
			for(vector<string>::iterator it = v.begin();it != v.end();it++)
			{
				sendData = sendData + *it +"\n";
			}
			sendData = sendData + "选择你想进行聊天的群组：\n"; 
			send_string(sendData,sClient);
		}
		return 0;
	}
	
	string choose_group_chat(SOCKET sClient,list<SOCKET>::iterator pointer)
	{
		vector<string> v = client_to_group_that_he_is_in[socket_to_name[sClient]];
		bool need_to_return = show_group_that_you_are_in(sClient,pointer);
		if(need_to_return) return "Error";
		string chosen_group;
		while(1)
		{
			chosen_group=rev_string(sClient,pointer);
			if(chosen_group=="") return "";
			auto it = find(v.begin(),v.end(),chosen_group);
			if(it == v.end())
			{
				cout<<"群组不存在！\n"<<endl;
				send_string("群组不存在！\n",sClient);
				continue;
			}
			else
			{
				send_string("进入群组成功！开始聊天吧！",sClient); 
				send_to_all(socket_to_name[sClient] + "进入入群组" + chosen_group + "\n",sClient);
				return chosen_group;
			}
		}
	}
	
	void debug()	//这是我debug用的，不用在意
	{

		printf("\n\n------------------我是分割线--------------------\n\n");
		printf("现有%d个连接\n", online_clients.size());
		show_list(online_clients);
		const char* sendData = "我在debug\n\n--------------------------------\n";
		//send(*online_clients.begin(), sendData, strlen(sendData), 0);
		printf("\n\n------------------我是分割线--------------------\n\n");
	}
	
	SOCKET get_target(SOCKET sClient,list<SOCKET>::iterator pointer)//这个函数的作用是当目前连接到服务器的用户大于一个人的时候，
	{	//for_login.lock();											//能让后来的用户选择与哪一个用户连接；
		if (online_clients.size() == 1)					//目前尚不完善，若一个用户主动或被动地建立了多个连接，那么只能识别最早的连接
		{												//而且若一方断开连接，连接也不会自动解除，（这个不能，只是没来得及写）
			send_char("现在只有你一个人哦\n", sClient);
			return no_tar;
		}
		int num = online_clients.size();
		string sendData;
		sendData="可选用户：\n";
		for_show.lock();
		list<SOCKET>::iterator l = online_clients.begin();
		num = 1;
		while (l != online_clients.end())
		{
			if (*l == sClient)
			{
				l++;
				continue;
			}
			string client_name = socket_to_name[*l];
			sendData = sendData + "用户：" + client_name + "\n";
			l++;
			num ++;
		}
		sendData = sendData + "请选择你想连接的用户：\n"; 
		send_string(sendData,sClient);
		for_show.unlock();
		string connect_client_name;
		while(1)
		{
			connect_client_name=rev_string(sClient,pointer);
			if(connect_client_name == "") return no_tar;
			auto it = name_to_socket.find(connect_client_name);
			if(it == name_to_socket.end())
			{
				cout<<"用户不存在！\n"<<endl;
				send_string("用户不存在！\n",sClient);
				continue;
			}
			else
			{
				return name_to_socket[connect_client_name];
			}
		}
		//for_login.unlock();
		/*char revData[255];
		int last=recv(sClient, revData, 255, 0);
		int n = revData[0] - '0';
		l = online_clients.begin();
		for (int i = 1; i < n; i++)							//我也觉得这样取list中的元素很笨，但是它不这样就报错。
			l++;											//我也没办法了，期待群里老哥的高见
		return *l;*/
	}

	void check_connection(char c[], SOCKET s)				//检查当前用户与谁建立了连接（若有多个取最早），将两者信息同步
	{
		for (list<list<SOCKET>>::iterator i = connection.begin(); i!=connection.end();i++)
		{
			list<SOCKET> temp = *i;
			for (list<SOCKET>::iterator j = temp.begin(); j != temp.end(); j++)
				if (*j == s)
				{
					list<SOCKET>::iterator k = temp.begin();
					if (j == k) k++;
					/*char c1[255];
					sprintf(c1, "用户%d向您发来信息:\n", socket_to_name[s]);
					send_char(c1, *k);*/
					send_char("\n---------------------\n", *k);
					send_string("用户"+socket_to_name[s]+":",*k);
					send_char(c, *k);
					send_char("\n---------------------\n", *k);
					if((string)c == socket_to_name[s]+"退出了当前聊天模式\n")
					{
						connection.erase(i);
					}
					return;
				}
		}
	}

	SOCKET listen_and_accept_and_derive_another_listen(list<SOCKET>::iterator& pointer)//返回accept产生的套接字 
	{
		if (listen(listener, 10) == SOCKET_ERROR)
		{
			printf("listen error !");
			exit(-1);
		}
		bool first_time = true;		//保证一个监听只会衍生一个监听
		cout << "正在开始监听" << endl;
		SOCKET sClient = no_tar;
		sockaddr_in remoteAddr;
		int nAddrlen = sizeof(remoteAddr);
		char revData[255];
		
		while (sClient == no_tar)	//连接失败的话重新连接
		{
			printf("等待连接...\n");
			sClient = accept(listener, (SOCKADDR*)&remoteAddr, &nAddrlen);
			
			if (sClient == INVALID_SOCKET)
			{
				printf("accept error !");
				continue;
			}
			
			//汪洋：有点无关紧要的小冗余，这个判断条件可以不加，因为前面的while和if保证证了这里的if一定成立，且只会执行一次 
			if (first_time && sClient != no_tar)
			{
				//汪洋：这里派生了另一个listening线程，但问题是这里只有一个监听套接字listener,是否需要创建别的新套接字？
				//答：应该是不需要的，因为能运行到这里，listenner必然已经用完了，不会出现线程之间争夺listener使用权 
				//汪洋：是否可以通过listen派生用于建立用户到用户的线程，而非监听线程？ 
				//答：没有必要 
				for_thread.lock();
				services.push_back(thread(&server::listening, this));
				services.back().detach();
				for_thread.unlock();
				mtx.lock();
				online_clients.push_back(sClient);
				pointer = prev(online_clients.end());
				mtx.unlock();
				first_time = false;
			}
		}
		printf("接受到一个连接,IP:%s , number:%d \r\n", inet_ntoa(remoteAddr.sin_addr),sClient);
		printf("现有%d个连接\n", online_clients.size());
		return sClient;
	}
	
	void register_or_login(SOCKET sClient,list<SOCKET>::iterator pointer)
	{
		char revData[255];
		int last = recv(sClient, revData, 255, 0);
		if (last <= 0)						//实时检测用户是否断开连接
		{
			//printf("客户%d退出\n", socket_to_client(sClient));
			cout<<"客户"<<socket_to_name[sClient] <<"退出";
			/*mtx.lock();
			online_clients.erase(pointer);
			mtx.unlock();*/
			
		}
		else
		{
			revData[last] = 0x00;
			string request = revData;
			if(request == "注册")
			{
				client_register(sClient,pointer); 
				client_login(sClient,pointer);
			}
			else if(request == "登录")
			{
				client_login(sClient,pointer);
			}
		}
	 } 
	
	void one_to_one_chat(SOCKET sClient,list<SOCKET>::iterator pointer)
	{
		SOCKET target = get_target(sClient,pointer);	//get_target在当前服务器仅有一个用户时会返回no_tar
		if (target != no_tar)
		{
			char ch[255];
			/*sprintf(ch,"用户%d与您建立了连接\n", socket_to_client(sClient));
			send_char(ch, target);*/
			send_string("用户"+socket_to_name[sClient]+"与您建立了连接\n",target);
			/*sprintf(ch, "成功与用户%d建立了连接\n", socket_to_client(target));
			send_char(ch, sClient);*/
			send_string("成功与"+socket_to_name[target]+"建立了连接\n",sClient);
			list<SOCKET>temp;
			//这里其实可以先把sclient push进去，然后再push target可以使后续check_connection更方便 
			temp.push_back(target);
			temp.push_back(sClient);
			connection.push_back(temp);
		}
	}
	
	void group_chat(SOCKET sClient,list<SOCKET>::iterator pointer,string& chosen_group)
	{
		string decision=rev_string(sClient,pointer);
		if(decision=="") return;
		if(decision == "创建群组")
		{
			creat_group_chat(sClient,pointer);
			//join_group_chat(sClient,pointer);
			chosen_group = choose_group_chat(sClient,pointer);
		}
		else if(decision == "加入群组")
		{
			join_group_chat(sClient,pointer);
			chosen_group = choose_group_chat(sClient,pointer);
		}
		else if(decision == "在群组中聊天")
		{
			chosen_group = choose_group_chat(sClient,pointer);
		}
	}
	
	string choose_chat_mode(SOCKET sClient,list<SOCKET>::iterator pointer) 
	{
		string decision=rev_string(sClient,pointer);
		if(decision=="") return "";
		if(decision == "单人聊天")
		{
			one_to_one_chat(sClient,pointer);
			return "0";
		}
		else if(decision == "多人聊天")
		{
			string chosen_group;
			group_chat(sClient,pointer,chosen_group);
			return chosen_group;
		}
	}
	
	void send_to_group(string revData,SOCKET sClient,string chosen_group)
	{
		vector<string> v=groupname_to_groupmember[chosen_group];
		revData = socket_to_name[sClient] + ":" + revData + "\n";
		for(auto it=v.begin();it!=v.end();it++)
		{
			if(*it==socket_to_name[sClient])
				continue;
			if(name_to_socket[*it]==no_tar)
			{
				cout<<*it<<"notar"<<endl; 
				continue;
			}
			cout<<"sending to"<<name_to_socket[*it]<<endl; 
			send_string(revData,name_to_socket[*it]);
		}
	}
	
	string chat_in_particular_mode(SOCKET sClient,list<SOCKET>::iterator pointer,string chosen_group)
	{
		char revData[255];
		//接收数据
		while (true)
		{
			int ret = recv(sClient, revData, 255, 0);
			if (ret <= 0 || chosen_group=="")						//实时检测用户是否断开连接
			{
				//printf("客户%d退出\n", socket_to_client(sClient));
				close_socket(sClient,pointer);
				return "logout";
			}
			else
			{
				revData[ret] = 0x00;
				if((string)revData == "Esc")
				{
					cout << socket_to_name[sClient] << "退出了当前聊天模式" << endl;
					if(chosen_group=="0")
					{
						
						check_connection(const_cast<char*>((socket_to_name[sClient] + "退出了当前聊天模式\n").c_str()), sClient);
					}
					else
					{
						send_to_group(socket_to_name[sClient] + "退出了当前聊天模式\n",sClient,chosen_group);
					}
					send_string("quit",sClient);//这一步是为了让clinet的listen线程终止，好让客户端与服务器互动 
					return "quit";
				}
				cout << socket_to_name[sClient] << "：" << revData << endl;
			}
			//发送数据
			//char sendData[255] = "TCP客户端成功接收\n\n--------------------------------\n";
			//send(sClient, sendData, strlen(sendData), 0);
			if(chosen_group=="0")
			{
				check_connection(revData, sClient);
			}
			else
			{
				send_to_group((string)revData,sClient,chosen_group);
			}
		}
	}
	
	void listening()			//监听，用线程实现服务器能一边监听新用户，一边能服务旧用户
	{	
		list<SOCKET>::iterator pointer;							
		SOCKET sClient = listen_and_accept_and_derive_another_listen(pointer);
		register_or_login(sClient,pointer);
		string change_mode_or_log_out = "";
		while(change_mode_or_log_out != "logout")
		{
			//one_to_one_chat(sClient,pointer);
			string chosen_group=choose_chat_mode(sClient,pointer);
		    if(chosen_group == "Error") continue;
			change_mode_or_log_out = chat_in_particular_mode(sClient,pointer,chosen_group);
		}
		
	}

	void init()					//初始化服务器
	{
		cout << "正在初始化服务器" << endl;
		listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		//初始化监听器
		if (listener == INVALID_SOCKET)								//初始化错误就终止程序
		{
			printf("socket error !");
			exit(-1);
		}

		//汪洋：这里有个疑问,Addr是在哪分配的？ 明白了，是在server的构造函数里实现的 
		//绑定地址
		if (bind(listener, (struct sockaddr*)&Addr, sizeof(Addr)) < 0)
		{
			perror("bind error");
			exit(-1);
		}

		//开始监听
		for_thread.lock();
		services.push_back(thread(&server::listening, this));
		services.back().detach();
		for_thread.unlock();
	}
	~server()	//构造服务器
	{
	}
};

int main()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	server s;
	s.init();
	while(1)				//顺带一提，在服务器界面随便输入，就会触发debug函数，显示当前连接的用户
	{ 
		system("pause");
		s.debug();
	}
	return 0;
}
