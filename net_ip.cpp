#include "net_ip.h"

ip::ip(int num)
{
	_pRoot = new struct ip_package;
	memset(_pRoot,0,sizeof(ip_package));
	_pRoot->pNext = NULL;
	
	ip_package* pTemp;
	ip_package* pPtr = _pRoot;

	for (int i = 0;i != num;++i)
	{
		pTemp = new ip_package;
                memset(pTemp,0,sizeof(ip_package));
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

ip::~ip()
{
	struct ip_package* pTemp = _pRoot;

	while(pTemp != NULL)
        {
                pTemp = _pRoot->pNext;
                delete _pRoot;
                _pRoot = pTemp;
        }
}

void ip::Recv()
{
	use_socket s_Temp;
	s_Temp.Af = AF_INET;
	s_Temp.Type = SOCK_RAW;
	s_Temp.Protocol = 0;

	UseSocket(s_Temp);
	Socket();

	char buff[20];
	char opinion[40];
	char data[2048];
	int other_byte = 20;
	struct ip_package* Temp = _pRoot;

	sockaddr_in source_sock;
	int ON = sizeof(source_sock);
	
	while(Temp != NULL)
	{
		if(recvfrom(_sockFd,buff,sizeof(buff),0,(sockaddr*)(&source_sock),(socklen_t*)(&ON)) < 0)
                {
                        cout<<"RECVFROM FAILED"<<endl;
                        return;
                }
                else
                {
                        memcpy(&(Temp->head),buff,20);
                }

		if((other_byte = (int)(Temp->head.ihl)*4) > 20)
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
		
		other_byte = (int)(Temp->head.tot_len) - other_byte;

		if(recvfrom(_sockFd,data,other_byte,0,NULL,NULL) < 0)
                {
                        cout<<"RECVFROM FAILED"<<endl;
                        return;
                }
		else
		{
			memcpy(&(Temp->data),data,other_byte);
		}

		//Temp->head.protocol

                unsigned long TT = ntohl(source_sock.sin_addr.s_addr);
                unsigned long T1 = (TT>>24)&(0x000000FF);
                unsigned long T2 = (TT>>16)&(0x000000FF);
                unsigned long T3 = (TT>>8)&(0x000000FF);
                unsigned long T4 = TT&(0x000000FF);
                sprintf(Temp->address,"%ld.%ld.%ld.%ld",T1,T2,T3,T3);
                memset(&source_sock,0,ON);
		CutPackage(Temp);

		Temp = Temp->pNext;
	}
}

void ip::CutPackage(ip_package* pTemp)
{
	switch((int)(pTemp->head.protocol))
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
