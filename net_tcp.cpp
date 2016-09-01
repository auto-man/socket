#include "net_tcp.h"

tcp::tcp(int num)
{
	_pRoot = new tcp_package;
	_pRoot->pNext = NULL;
	
	struct tcp_package* pTemp;
	struct tcp_package* pPtr = _pRoot;
	for (int i = 1;i != num;++i)
	{
		pTemp = new tcp_package;
		pTemp->pNext = NULL;
		if(_pRoot->pNext == NULL)
		{
			_pRoot->pNext = pTemp;
			pPtr = pTemp;
		}
		else
		{
			pPtr->pNext = pTemp;
			pPtr = pPtr->pNext;
		}
	}
}

tcp::~tcp()
{
	struct tcp_package* pTemp = _pRoot;

	while(pTemp != NULL)
	{
		pTemp = _pRoot->pNext;
		delete _pRoot;
		_pRoot = pTemp;
	}
}

void tcp::Recv()
{
	use_socket s_Temp;
	s_Temp.Af = AF_INET;
	s_Temp.Type = SOCK_RAW;
	s_Temp.Protocol = 6;

	UseSocket(s_Temp);
	Socket();

	char buff[30];
	struct tcp_package* Temp = _pRoot;

	sockaddr_in source_sock;
	int ON = sizeof(source_sock);
	
	//while(Temp != NULL)
	//{
		if(recvfrom(_sockFd,buff,sizeof(buff),0,(sockaddr*)(&source_sock),(socklen_t*)(&ON)) < 0)
		{
			cout<<"RECVFROM FAILED"<<endl;
			return;
		}
		else
		{
			memcpy(&(Temp->head),buff,20);
		}
	//	Temp = Temp->pNext;
	//}
	cout<<"RECV SUCCESS"<<endl;
	unsigned long TT = ntohl(source_sock.sin_addr.s_addr);
	unsigned long T1 = (TT>>24)&(0x000000FF);
	unsigned long T2 = (TT>>16)&(0x000000FF);
	unsigned long T3 = (TT>>8)&(0x000000FF);
	unsigned long T4 = TT&(0x000000FF);
	cout<<"source ip:\t"<<T1<<"."<<T2<<"."<<T3<<"."<<T4<<endl;
	cout<<endl;
}

void tcp::ShowPackage()
{
	cout<<"source_port:\t"<<_pRoot->head.source_port<<endl;
	cout<<"dest_port:\t"<<_pRoot->head.dest_port<<endl;
	cout<<"seq:\t\t"<<_pRoot->head.seq<<endl;
	cout<<"ack_seq:\t"<<_pRoot->head.ack_seq<<endl;
	cout<<"doff:\t\t"<<_pRoot->head.doff<<" unit 4type/1"<<endl;
	cout<<"res1:\t\t"<<_pRoot->head.res1<<endl;
}
