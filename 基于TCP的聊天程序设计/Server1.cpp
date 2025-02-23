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
SOCKET no_tar;		//�������൱�ڿ�SOCKET

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
	struct sockaddr_in Addr;	//�������˵�IP��ַ�Ͷ˿�
	int listener;				//������
	list<SOCKET> online_clients;	//�����û�����¼accept�Ľ��
	list<thread> services;		//���̷߳������
	list<list<SOCKET>> connection;		//��¼˭��˭������
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
	server()	//���������
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
		cout<<"�ͻ�"<<socket_to_name[sClient]<<"�˳�"<<endl; 
		cout<<"�ͻ�"<<socket_to_name[sClient]<<"��Ӧ�߳̽���1"<<endl;
		mtx.lock();
		cout<<"�ͻ�"<<socket_to_name[sClient]<<"��Ӧ�߳̽���1.5"<<endl;
		online_clients.erase(pointer);
		cout<<"�ͻ�"<<socket_to_name[sClient]<<"��Ӧ�߳̽���2"<<endl;
		mtx.unlock();
		closesocket(sClient);
		//for_thread.lock();
		//services.push_back(thread(&server::listening, this));
		//services.back().detach();
		//for_thread.unlock();
		cout<<"�ͻ�"<<socket_to_name[sClient]<<"��Ӧ�߳̽���3"<<endl;
	 } 
	 
	inline string rev_string(SOCKET sClient,list<SOCKET>::iterator pointer)//�����ַ��� 
	{
		char revData[255];
		int last=recv(sClient, revData, 255, 0);
		if(last <= 0)						//ʵʱ����û��Ƿ�Ͽ�����
		{
			printf("�ͻ�%d�˳�\n", sClient);
			/*mtx.lock();
			online_clients.erase(pointer);
			mtx.unlock();*/
			return "";
		}
		revData[last]=0x00;
		string str = revData;
		return str;
	}
	
	inline void send_string(const std::string& str, SOCKET s) //�����ַ��� 
	{
    	const char* c = str.c_str();
    	size_t len = str.length();
    	send(s, c, len, 0);
    }
    
	inline void send_char(const char *c,SOCKET s)		//������������Ϊ�����ü����ֵģ�ͬ����������
	{
		send(s, c, strlen(c), 0);
		return;
	}

	inline void send_char(char c[], SOCKET s)
	{
		send(s, c, strlen(c), 0);
		return;
	}
	
	void write_client_information()//�� client_information.txtд�û���Ϣ����ʽΪ"name"+"\t"+"keyword"+"\n"��ÿ������ע��ʱ����дһ�� 
	{
		//for_writeʵ��д���� 
		for_write.lock();
		ofstream ofs;
		ofs.open("client_information.txt",std::ios::out);
		if(!ofs.is_open())
    		cout<<"�ļ�����������"<<endl;
		string clinet_name,keyworld;
		for(int i=0; i<client_name_vector.size(); i++)
		{
			ofs<<client_name_vector[i]<<"\t"<<keyword_vector[i]<<endl;
		}
		ofs.close();
		cout<<"�û���Ϣ�Ѿ�ˢ�£�"<<endl;
		for_write.unlock();
	}
	
	void write_group_information()
	{
		for_group.lock();
		ofstream ofs;
		ofs.open("group_information.txt",std::ios::out);
		if(!ofs.is_open())
    		cout<<"�ļ�����������"<<endl;
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
		cout<<"Ⱥ����Ϣ�Ѿ�ˢ�£�"<<endl;
		for_group.unlock();
	}
	
	void read_client_information()//�� client_information.txt���û���Ϣ
	{
		ifstream ifs;
    	ifs.open("client_information.txt",std::ios::in);
    	if(!ifs)
    		cout<<"�ļ�����������"<<endl; 
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
    		cout<<"�ļ�����������"<<endl; 
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
	
	void client_login(SOCKET sClient,list<SOCKET>::iterator pointer)//�û���¼ 
	{
		//send_string("���������˵��ͬʱ�������˿͵�¼����ȴ�һ�ᣡ\n",sClient); 
		for_login.lock();
		char revData[255];
		while(1)
		{
			int ret=recv(sClient, revData, 255, 0);
			if(ret <= 0)						//ʵʱ����û��Ƿ�Ͽ�����
			{
				printf("�ͻ�%d�˳�\n", sClient);
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
					cout<<"�û������ڣ�\n"<<endl;
					send_string("�û������ڣ�\n",sClient);
					continue;
				}
				if(keyword_vector[client_name_repeat] != keyword)
				{
					send_string("�û�������������µ�¼��\n",sClient);
					cout<<"�û�"<<sClient<<"��¼ʧ��!"<<endl;
				}
				else
				{
					socket_to_name[sClient] = client_name; //���׽������û������� 
					name_to_socket[client_name] = sClient; //���û������׽��ֹ��� 
					send_string("�û���¼�ɹ���\n",sClient);
					cout<<"�û�"<<client_name<<"��¼�ɹ�!"<<"�׽���Ϊ"<<sClient<<endl;
					send_to_all(client_name + "�����ˣ�\n",sClient);
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
	
	void client_register(SOCKET sClient,list<SOCKET>::iterator pointer)//�û�ע�� 
	{
		char revData[255];
		while(1)
		{
			int ret=recv(sClient, revData, 255, 0);
			if(ret <= 0)						//ʵʱ����û��Ƿ�Ͽ�����
			{
				printf("�ͻ�%d�˳�\n", sClient);
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
					send_string("�û��Ѵ��ڣ�������ע�ᣡ\n",sClient);
					cout<<"�û�"<<sClient<<"ע��ʧ��!"<<endl; 
				}
				else
				{
					client_name_vector.push_back(client_name);
					keyword_vector.push_back(keyword);
					char ch[255];
					sprintf(ch,"�û�ע��ɹ������μ����룡\n");
					send_char(ch, sClient);
					cout<<"�û�"<<client_name<<"ע��ɹ�!"<<"�׽���Ϊ"<<sClient<<endl;
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
        		send_string("Ⱥ���Ѵ��ڣ�Ⱥ�鴴��ʧ�ܣ�\n",sClient);
        		cout<<"�û�"<<sClient<<"����Ⱥ��"<<name<<"ʧ��!"<<endl; 
    		} 
			else {
        		send_string("Ⱥ�鴴���ɹ���\n",sClient);
        		cout<<"�û�"<<sClient<<"����Ⱥ��"<<name<<"�ɹ�!"<<endl;
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
		sprintf(sendData, "�� %d ��Ⱥ��\n", num);
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
		str = str + "ѡ����Ҫ�����Ⱥ��:\n";
		send_string(str,sClient);
	}
	
	void join_group_chat(SOCKET sClient,list<SOCKET>::iterator pointer)
	{
		if (group_name_vector.size() == 0)					
		{												
			send_char("���ڻ�û��Ⱥ��Ŷ���Ƿ�Ҫ����һ����\n0---��\n1---��\n", sClient);
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
					cout<<"Ⱥ�鲻���ڣ�\n"<<endl;
					send_string("Ⱥ�鲻���ڣ�\n",sClient);
					continue;
				}
				else
				{
					groupname_to_groupmember[chosen_group].push_back(socket_to_name[sClient]);
					client_to_group_that_he_is_in[socket_to_name[sClient]].push_back(chosen_group);
					send_string("Ⱥ�����ɹ�\n",sClient); 
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
			send_string("�㻹û�м����κ�Ⱥ�飡\n",sClient);
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
			sendData = sendData + "ѡ��������������Ⱥ�飺\n"; 
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
				cout<<"Ⱥ�鲻���ڣ�\n"<<endl;
				send_string("Ⱥ�鲻���ڣ�\n",sClient);
				continue;
			}
			else
			{
				send_string("����Ⱥ��ɹ�����ʼ����ɣ�",sClient); 
				send_to_all(socket_to_name[sClient] + "������Ⱥ��" + chosen_group + "\n",sClient);
				return chosen_group;
			}
		}
	}
	
	void debug()	//������debug�õģ���������
	{

		printf("\n\n------------------���Ƿָ���--------------------\n\n");
		printf("����%d������\n", online_clients.size());
		show_list(online_clients);
		const char* sendData = "����debug\n\n--------------------------------\n";
		//send(*online_clients.begin(), sendData, strlen(sendData), 0);
		printf("\n\n------------------���Ƿָ���--------------------\n\n");
	}
	
	SOCKET get_target(SOCKET sClient,list<SOCKET>::iterator pointer)//��������������ǵ�Ŀǰ���ӵ����������û�����һ���˵�ʱ��
	{	//for_login.lock();											//���ú������û�ѡ������һ���û����ӣ�
		if (online_clients.size() == 1)					//Ŀǰ�в����ƣ���һ���û������򱻶��ؽ����˶�����ӣ���ôֻ��ʶ�����������
		{												//������һ���Ͽ����ӣ�����Ҳ�����Զ��������������ܣ�ֻ��û���ü�д��
			send_char("����ֻ����һ����Ŷ\n", sClient);
			return no_tar;
		}
		int num = online_clients.size();
		string sendData;
		sendData="��ѡ�û���\n";
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
			sendData = sendData + "�û���" + client_name + "\n";
			l++;
			num ++;
		}
		sendData = sendData + "��ѡ���������ӵ��û���\n"; 
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
				cout<<"�û������ڣ�\n"<<endl;
				send_string("�û������ڣ�\n",sClient);
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
		for (int i = 1; i < n; i++)							//��Ҳ��������ȡlist�е�Ԫ�غܱ����������������ͱ���
			l++;											//��Ҳû�취�ˣ��ڴ�Ⱥ���ϸ�ĸ߼�
		return *l;*/
	}

	void check_connection(char c[], SOCKET s)				//��鵱ǰ�û���˭���������ӣ����ж��ȡ���磩����������Ϣͬ��
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
					sprintf(c1, "�û�%d����������Ϣ:\n", socket_to_name[s]);
					send_char(c1, *k);*/
					send_char("\n---------------------\n", *k);
					send_string("�û�"+socket_to_name[s]+":",*k);
					send_char(c, *k);
					send_char("\n---------------------\n", *k);
					if((string)c == socket_to_name[s]+"�˳��˵�ǰ����ģʽ\n")
					{
						connection.erase(i);
					}
					return;
				}
		}
	}

	SOCKET listen_and_accept_and_derive_another_listen(list<SOCKET>::iterator& pointer)//����accept�������׽��� 
	{
		if (listen(listener, 10) == SOCKET_ERROR)
		{
			printf("listen error !");
			exit(-1);
		}
		bool first_time = true;		//��֤һ������ֻ������һ������
		cout << "���ڿ�ʼ����" << endl;
		SOCKET sClient = no_tar;
		sockaddr_in remoteAddr;
		int nAddrlen = sizeof(remoteAddr);
		char revData[255];
		
		while (sClient == no_tar)	//����ʧ�ܵĻ���������
		{
			printf("�ȴ�����...\n");
			sClient = accept(listener, (SOCKADDR*)&remoteAddr, &nAddrlen);
			
			if (sClient == INVALID_SOCKET)
			{
				printf("accept error !");
				continue;
			}
			
			//�����е��޹ؽ�Ҫ��С���࣬����ж��������Բ��ӣ���Ϊǰ���while��if��֤֤�������ifһ����������ֻ��ִ��һ�� 
			if (first_time && sClient != no_tar)
			{
				//����������������һ��listening�̣߳�������������ֻ��һ�������׽���listener,�Ƿ���Ҫ����������׽��֣�
				//��Ӧ���ǲ���Ҫ�ģ���Ϊ�����е����listenner��Ȼ�Ѿ������ˣ���������߳�֮������listenerʹ��Ȩ 
				//�����Ƿ����ͨ��listen�������ڽ����û����û����̣߳����Ǽ����̣߳� 
				//��û�б�Ҫ 
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
		printf("���ܵ�һ������,IP:%s , number:%d \r\n", inet_ntoa(remoteAddr.sin_addr),sClient);
		printf("����%d������\n", online_clients.size());
		return sClient;
	}
	
	void register_or_login(SOCKET sClient,list<SOCKET>::iterator pointer)
	{
		char revData[255];
		int last = recv(sClient, revData, 255, 0);
		if (last <= 0)						//ʵʱ����û��Ƿ�Ͽ�����
		{
			//printf("�ͻ�%d�˳�\n", socket_to_client(sClient));
			cout<<"�ͻ�"<<socket_to_name[sClient] <<"�˳�";
			/*mtx.lock();
			online_clients.erase(pointer);
			mtx.unlock();*/
			
		}
		else
		{
			revData[last] = 0x00;
			string request = revData;
			if(request == "ע��")
			{
				client_register(sClient,pointer); 
				client_login(sClient,pointer);
			}
			else if(request == "��¼")
			{
				client_login(sClient,pointer);
			}
		}
	 } 
	
	void one_to_one_chat(SOCKET sClient,list<SOCKET>::iterator pointer)
	{
		SOCKET target = get_target(sClient,pointer);	//get_target�ڵ�ǰ����������һ���û�ʱ�᷵��no_tar
		if (target != no_tar)
		{
			char ch[255];
			/*sprintf(ch,"�û�%d��������������\n", socket_to_client(sClient));
			send_char(ch, target);*/
			send_string("�û�"+socket_to_name[sClient]+"��������������\n",target);
			/*sprintf(ch, "�ɹ����û�%d����������\n", socket_to_client(target));
			send_char(ch, sClient);*/
			send_string("�ɹ���"+socket_to_name[target]+"����������\n",sClient);
			list<SOCKET>temp;
			//������ʵ�����Ȱ�sclient push��ȥ��Ȼ����push target����ʹ����check_connection������ 
			temp.push_back(target);
			temp.push_back(sClient);
			connection.push_back(temp);
		}
	}
	
	void group_chat(SOCKET sClient,list<SOCKET>::iterator pointer,string& chosen_group)
	{
		string decision=rev_string(sClient,pointer);
		if(decision=="") return;
		if(decision == "����Ⱥ��")
		{
			creat_group_chat(sClient,pointer);
			//join_group_chat(sClient,pointer);
			chosen_group = choose_group_chat(sClient,pointer);
		}
		else if(decision == "����Ⱥ��")
		{
			join_group_chat(sClient,pointer);
			chosen_group = choose_group_chat(sClient,pointer);
		}
		else if(decision == "��Ⱥ��������")
		{
			chosen_group = choose_group_chat(sClient,pointer);
		}
	}
	
	string choose_chat_mode(SOCKET sClient,list<SOCKET>::iterator pointer) 
	{
		string decision=rev_string(sClient,pointer);
		if(decision=="") return "";
		if(decision == "��������")
		{
			one_to_one_chat(sClient,pointer);
			return "0";
		}
		else if(decision == "��������")
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
		//��������
		while (true)
		{
			int ret = recv(sClient, revData, 255, 0);
			if (ret <= 0 || chosen_group=="")						//ʵʱ����û��Ƿ�Ͽ�����
			{
				//printf("�ͻ�%d�˳�\n", socket_to_client(sClient));
				close_socket(sClient,pointer);
				return "logout";
			}
			else
			{
				revData[ret] = 0x00;
				if((string)revData == "Esc")
				{
					cout << socket_to_name[sClient] << "�˳��˵�ǰ����ģʽ" << endl;
					if(chosen_group=="0")
					{
						
						check_connection(const_cast<char*>((socket_to_name[sClient] + "�˳��˵�ǰ����ģʽ\n").c_str()), sClient);
					}
					else
					{
						send_to_group(socket_to_name[sClient] + "�˳��˵�ǰ����ģʽ\n",sClient,chosen_group);
					}
					send_string("quit",sClient);//��һ����Ϊ����clinet��listen�߳���ֹ�����ÿͻ�������������� 
					return "quit";
				}
				cout << socket_to_name[sClient] << "��" << revData << endl;
			}
			//��������
			//char sendData[255] = "TCP�ͻ��˳ɹ�����\n\n--------------------------------\n";
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
	
	void listening()			//���������߳�ʵ�ַ�������һ�߼������û���һ���ܷ�����û�
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

	void init()					//��ʼ��������
	{
		cout << "���ڳ�ʼ��������" << endl;
		listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		//��ʼ��������
		if (listener == INVALID_SOCKET)								//��ʼ���������ֹ����
		{
			printf("socket error !");
			exit(-1);
		}

		//���������и�����,Addr�����ķ���ģ� �����ˣ�����server�Ĺ��캯����ʵ�ֵ� 
		//�󶨵�ַ
		if (bind(listener, (struct sockaddr*)&Addr, sizeof(Addr)) < 0)
		{
			perror("bind error");
			exit(-1);
		}

		//��ʼ����
		for_thread.lock();
		services.push_back(thread(&server::listening, this));
		services.back().detach();
		for_thread.unlock();
	}
	~server()	//���������
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
	while(1)				//˳��һ�ᣬ�ڷ���������������룬�ͻᴥ��debug��������ʾ��ǰ���ӵ��û�
	{ 
		system("pause");
		s.debug();
	}
	return 0;
}
