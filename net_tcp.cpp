#include "net_tcp.h"

tcp::tcp(int num)
{
	_pRoot = new tcp_package;
	memset(_pRoot,0,sizeof(tcp_package));
	_pRoot->pNext = NULL;
	
	struct tcp_package* pTemp;
	struct tcp_package* pPtr = _pRoot;

	for (int i = 0;i != num;++i)
	{
		pTemp = new tcp_package;
		memset(pTemp,0,sizeof(tcp_package));
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

	_pIp = new struct ip_package;
	memset(_pRoot,0,sizeof(ip_package));
	_pIp->pNext = NULL;

	struct ip_package* ptemp;
	struct ip_package* pptr = _pIp;

	for (int i = 0;i != num;++i)
	{
		ptemp = new ip_package;
		memset(ptemp,0,sizeof(ip_package));
		ptemp->pNext = NULL;
		if(_pIp->pNext == NULL)
		{
			_pIp->pNext = ptemp;
			pptr = ptemp;
		}
		else
		{
			pptr->pNext = ptemp;
			pptr = pptr->pNext;
		}
	}
}

tcp::~tcp()
{
	struct tcp_package* pTemp = _pRoot;
	struct ip_package* ptemp = _pIp;

	cout<<"Destroy!"<<endl;

	while(pTemp != NULL)
	{
		pTemp = _pRoot->pNext;
		delete _pRoot;
		_pRoot = pTemp;
	}

	while(ptemp != NULL)
	{
		ptemp = _pIp->pNext;
                delete _pIp;
                _pIp = ptemp;
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

	char buff[20];
	char opinion[2048];
	char data[65536];
	int other_byte = 20;
	struct ip_package* Temp = _pIp;

	sockaddr_in source_sock;
	int ON = sizeof(source_sock);
	
	while(Temp != NULL)
	{
		//cout<<"recv now"<<endl;

		if(recvfrom(_sockFd,buff,sizeof(buff),0,(sockaddr*)(&source_sock),(socklen_t*)(&ON)) < 0)
                {
                        cout<<"RECVFROM FAILED"<<endl;
                        return;
                }
                else
                {
                        memcpy(&(Temp->head),buff,20);
                }

		//cout<<"recv success"<<endl;

                if((other_byte = (unsigned int)(Temp->head.ihl)*4) > 20)
                {
                        if(recvfrom(_sockFd,opinion,other_byte - 20,0,NULL,NULL) < 0)
                        {
                                cout<<"RECVFROM FAILED"<<endl;
                                return;
                        }
                        else
                        {
                                memcpy(&(Temp->opinion),opinion,40);
                        }
                }

		other_byte = (unsigned int)(Temp->head.tot_len) - other_byte;
		cout<<"data : "<<other_byte<<endl;

                if(recvfrom(_sockFd,data,other_byte,0,NULL,NULL) < 0)
                {
                        cout<<"RECVFROM FAILED"<<endl;
                        return;
                }
                else
                {
                        memcpy(&(Temp->data),data,other_byte);
                }

		/*if(recvfrom(_sockFd,buff,sizeof(buff),0,(sockaddr*)(&source_sock),(socklen_t*)(&ON)) < 0)
		{
			cout<<"RECVFROM FAILED"<<endl;
			return;
		}
		else
		{
			memcpy(&(Temp->head),buff,20);
		}*/

		unsigned long TT = ntohl(source_sock.sin_addr.s_addr);
		unsigned long T1 = (TT>>24)&(0x000000FF);
		unsigned long T2 = (TT>>16)&(0x000000FF);
		unsigned long T3 = (TT>>8)&(0x000000FF);
		unsigned long T4 = TT&(0x000000FF);
		//sprintf(Temp->address,"%ld.%ld.%ld.%ld",T1,T2,T3,T3);
		memset(&source_sock,0,ON);
		CutPackage(Temp);
		//ShowPackage(Temp);

		Temp = Temp->pNext;
	}
}

void tcp::CutPackage(ip_package* pTemp)
{
        unsigned int temp = (pTemp->head.protocol);

        unsigned long TT = ntohl(pTemp->head.saddr);
        unsigned long T1 = (TT>>24)&(0x000000FF);
        unsigned long T2 = (TT>>16)&(0x000000FF);
        unsigned long T3 = (TT>>8)&(0x000000FF);
        unsigned long T4 = TT&(0x000000FF);
        cout<<"ip : "<<T1<<"."<<T2<<"."<<T3<<"."<<T4<<endl;


        temp = temp & 0x000000ff;

        switch(temp)
        {
        case 1://ICMP
                cout<<"This is a ICMP package."<<endl;
                break;
        case 2://IGMP
                cout<<"This is a IGMP package."<<endl;
                break;
        case 6://TCP
                cout<<"This is a TCP package."<<endl;
                break;
        case 17://UDP
                cout<<"This is a UDP package."<<endl;
                break;
        case 88://IGRP
                cout<<"This is a IGRP package."<<endl;
                break;
        case 89:
                cout<<"This is a OSPF package."<<endl;
                break;
        default:
                cout<<"This is a OTHER package which i don't know."<<endl;
                break;
        }
}

void tcp::ShowPackage(tcp_package* pTemp)
{
	cout<<"============================PACKAGE==============================="<<endl;
	cout<<"SOURCE IPv4:\t"<<pTemp->address<<endl;
	cout<<"source_port:\t"<<pTemp->head.source_port<<endl;
	cout<<"dest_port:\t"<<pTemp->head.dest_port<<endl;
	cout<<"seq:\t\t"<<pTemp->head.seq<<endl;
	cout<<"ack_seq:\t"<<pTemp->head.ack_seq<<endl;
	cout<<"doff:\t\t"<<pTemp->head.doff<<" unit 4type/1"<<endl;
	cout<<"res1:\t\t"<<pTemp->head.res1<<endl;
}
