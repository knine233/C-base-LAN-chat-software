#include<WINSOCK2.H>
#include<WINSOCK2.H>
#include<STDIO.H>
#include<iostream>
#include<cstring>
#include<thread>
#pragma warning(disable:4996)			//���ӻᱨ��
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
			cout<<"������������"<<endl;
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
		sendData = data1.c_str(); //stringתconst char*
		//char * sendData = "��ã�TCP����ˣ����ǿͻ���\n";
		send(sclient, sendData, strlen(sendData), 0);
		//send()������������ָ����socket�����Է�����
		//int send(int s, const void * msg, int len, unsigned int flags)
		//sΪ�ѽ��������ӵ�socket��msgָ���������ݣ�len��Ϊ���ݳ��ȣ�����flagsһ����0
		//�ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ���-1������ԭ�����error
		if(data1 == "Esc")
		{
			cout<<"�˳��˵�ǰ����ģʽ"<<endl;
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

string rev_string(SOCKET sclient)//�����ַ��� 
{
	char revData[255];
	int last=recv(sclient, revData, 255, 0);
	if(last <= 0)						//ʵʱ����û��Ƿ�Ͽ�����
	{
		cout<<"������������"<<endl;
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
	cout<<"���ڿ�ʼע�ᣡ"<<endl;
	while(1)
	{
		string user[2],keyword; 
		cout<<"�������û���(�����пո񡢻س����Ʊ��):"<<endl;
		cin>>user[0]; 
		cout<<"����������(�����пո񡢻س����Ʊ��):"<<endl;
		cin>>user[1];
		while(1)
		{
			cout<<"��ȷ������(�����пո񡢻س����Ʊ��):"<<endl;
			cin>> keyword;
			if(keyword == user[1])
				break;
			else
				cout<<"���벻һ�£�"<<endl; 
		} 
		send_string(user[0]+"\t"+user[1],sclient);
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0) {
			recData[ret] = 0x00;
			printf(recData);
		}
		string answer = recData;
		if(answer == "�û�ע��ɹ������μ����룡\n")
			break;
	}
	cout<<"ע�������"<<endl; 
	cout<<endl;
	cout<<endl;
}

string client_login(SOCKET sclient)
{
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------"<<endl;
	cout<<"���ڿ�ʼ��¼��"<<endl;
	cout<<"���������˵��ͬʱ�������˿͵�¼����ȴ�һ�ᣡ"<<endl;
	string user[2],keyword; 
	while(1)
	{
		cout<<"�������û���(�����пո񡢻س����Ʊ��):"<<endl;
		cin>>user[0]; 
		cout<<"����������(�����пո񡢻س����Ʊ��):"<<endl;
		cin>>user[1];
		send_string(user[0]+"\t"+user[1],sclient);
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0) {
			recData[ret] = 0x00;
			printf(recData);
			string answer = recData;
			if(answer == "�û���¼�ɹ���\n")
				break;
		}
		else
		{
			cout<<"�������Ѿ��˳����ͻ����޷��������У����˳�"<<endl;
		}
	}
	cout<<"��½������"<<endl; 
	cout<<endl;
	cout<<endl;
	return user[0];
}

string register_or_login(SOCKET sclient)
{
	cout<<"---------------------"<<endl;
	cout<<"���ӳɹ���"<<endl;
	cout<<"�˵���"<<endl;
	cout<<"0---ע��"<<endl;
	cout<<"1---��¼"<<endl; 
	cout<<"---------------------"<<endl;
	string username;
	char index;
	cin>>index;
	while(index!='0' and index!='1')
	{
		cout<<"���������룡"<<endl;
		cin>>index; 
	}
	if(index=='0')
	{
		send_string("ע��", sclient) ;
		client_register(sclient);
		username=client_login(sclient);
	}
	else
	{
		send_string("��¼", sclient); 
		username=client_login(sclient);
	}
	return username;
} 

void one_to_one_chat(SOCKET sclient)
{
	string q=rev_string(sclient);
	cout<<q;
	if(q=="����ֻ����һ����Ŷ\n") return;
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
	while(q=="�û������ڣ�\n")
	{
		cout<<"���������룺";
		cin>>name;
		send_string(name,sclient);
	}
}

string creat_group_chat(SOCKET sclient)
{
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------"<<endl;
	cout<<"���ڿ�ʼ����Ⱥ�飡"<<endl;
	string group; 
	string client_name;
	//vector<string> client_vector;
	while(1)
	{
		cout<<"������Ⱥ����(�����пո񡢻س����Ʊ��):"<<endl;
		cin>>group; 
		/*cout<<"��������Ҫ����Ⱥ���û�(ÿ��һ����һ�λس����ԡ�end��������):"
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
			if(answer == "Ⱥ�鴴���ɹ���\n")
				break;
		}
	}
	cout<<"Ⱥ�鴴��������"<<endl; 
	cout<<endl;
	cout<<endl;
	return group;
}

int join_group_chat(SOCKET sclient)
{
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------"<<endl;
	cout<<"���ڿ�ʼ����Ⱥ�飡"<<endl;
	string q=rev_string(sclient);
	cout<<q;
	cout<<"1"<<endl; 
	if(q=="���ڻ�û��Ⱥ��Ŷ���Ƿ�Ҫ����һ����\n0---��\n1---��\n")
	{
		string ans;
		cin>>ans;
		while(ans!="0" and ans!="1")
		{
			cout<<"���䣺"<<endl;
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
	/*while(q!="ѡ����Ҫ�����Ⱥ��:")
	{
		q=rev_string(sclient);
		cout<<q;
	}*/
	string name;
	cin>>name;
	send_string(name,sclient);
	q=rev_string(sclient);
	cout<<q;
	while(q=="Ⱥ�鲻���ڣ�\n")
	{
		cout<<"���������룺";
		cin>>name;
		send_string(name,sclient);
	}
	cout<<"Ⱥ����������"<<endl; 
	cout<<endl;
	cout<<endl;
	return 2;
}

bool choose_group_chat(SOCKET sclient)
{
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------"<<endl;
	cout<<"���ڿ�ʼѡ������һ��Ⱥ�����죡"<<endl;
	string q=rev_string(sclient);
	cout<<q;
	if(q=="�㻹û�м����κ�Ⱥ�飡\n") return 1;
	/*while(q!="ѡ����Ҫ��������Ⱥ��:")
	{
		q=rev_string(sclient);
		cout<<q;
	}*/
	string name;
	cin>>name;
	send_string(name,sclient);
	q=rev_string(sclient);
	cout<<q;
	while(q=="Ⱥ�鲻���ڣ�\n")
	{
		cout<<"���������룺";
		cin>>name;
		send_string(name,sclient);
	}
	cout<<"���ڿ�����Ⱥ��"<<name<<"�����ˣ�"<<endl; 
	cout<<endl;
	cout<<endl;
	return 0;
}

bool group_chat(SOCKET sclient)
{
	cout<<"---------------------"<<endl;
	cout<<"���ڿ��Խ���Ⱥ������ˣ�"<<endl; 
	cout<<"�˵���"<<endl;
	cout<<"0---����Ⱥ��"<<endl;
	cout<<"1---����Ⱥ��"<<endl;
	cout<<"2---��Ⱥ��������"<<endl;
	cout<<"---------------------"<<endl;
	char index;
	cin>>index;
	while(index!='0' and index!='1' and index!='2')
	{
		cout<<"���������룡"<<endl;
		cin>>index; 
	}
	if(index=='0')
	{
		send_string("����Ⱥ��", sclient) ;
		creat_group_chat(sclient);
		//join_group_chat(sclient);
		return choose_group_chat(sclient);
	}
	if(index=='1')
	{
		send_string("����Ⱥ��", sclient); 
		int result=join_group_chat(sclient);
		if(result==0){
			creat_group_chat(sclient);
			//join_group_chat(sclient);
			return choose_group_chat(sclient);
		}
		else if(result==1)
		{
			cout<<"û��Ⱥ����Լ��룡�ͻ�����ֹ!"<<endl;
			exit(-1);
		}
		else
		{
			return choose_group_chat(sclient);
		}
	}
	if(index=='2')
	{
		send_string("��Ⱥ��������", sclient); 
		return choose_group_chat(sclient);
	}
}

bool choose_chat_mode(SOCKET sclient)
{
	cout<<"---------------------"<<endl;
	cout<<"���ڿ������������ˣ�"<<endl; 
	cout<<"�˵���"<<endl;
	cout<<"0---��������"<<endl;
	cout<<"1---��������"<<endl;
	cout<<"---------------------"<<endl;
	char index;
	cin>>index;
	while(index!='0' and index!='1')
	{
		cout<<"���������룡"<<endl;
		cin>>index; 
	}
	if(index=='0')
	{
		send_string("��������", sclient) ;
		one_to_one_chat(sclient);
	}
	else
	{
		send_string("��������", sclient); 
		return group_chat(sclient);
	}
	return 0;
}

int main()
{
	//��ʼ��WSA�����۷����������û��������ʼ��WSA�����򱨴�
	WORD sockVersion = MAKEWORD(2, 2);			
	WSADATA data;
	//WSAStartup�����ķ���ֵ��һ������������������óɹ���												
	//����ֵΪ0����ʾ��ʼ���ɹ��������������ʧ�ܣ�����ֵ��Ϊ0����ʾ��ʼ��ʧ�ܡ�
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
	//��ʼ��socket
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
	{ //����ʧ��
		printf("connect error !");
		closesocket(sclient);
		return 0;
	}
	
	
	string username=register_or_login(sclient);
	bool need_to_continue;
	while(1)
	{
		need_to_continue = choose_chat_mode(sclient);
		//���̷ֿ߳�����д,�������õ������˲������
		if(need_to_continue) continue;
		thread th(hear,sclient);
		th.detach();

		speak(sclient);

    	// �ȴ�һ��ʱ�䣬��ȷ���߳����㹻��ʱ������ֹ��־
    	std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	
	closesocket(sclient);
	WSACleanup();
	return 0;
}
