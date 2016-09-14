#ifndef __NET_SOCKET__H
#define __NET_SOCKET__H

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<linux/if_packet.h>
#include<netinet/if_ether.h>
#include<net/if.h>

#define TRUE	true
#define FALSE	false

using namespace std;

struct iphdr
{
        unsigned char           ihl:4,
                                version:4;

        unsigned char           tos;
        unsigned short int      tot_len;
        unsigned short int      id;
        unsigned short int      frag_off;
        unsigned char           ttl;
        unsigned char           protocol;
        unsigned short int      check;
        unsigned int            saddr;
        unsigned int            daddr;
};

struct ip_package
{
        struct iphdr    head;
        unsigned char   opinion[40];
        unsigned char   data[65535];
        char            address[36];
        ip_package*     pNext;
};

struct use_socket
{
        int Af;                                 //AF_INET , AF_INET6...    <netinet/in.h>
        int Type;                               //SOCK_STREAM , SOCK_DGRAM , SOCK_RAW...
        int Protocol;                   //protocol type
};


class net_socket
{
public:
	virtual bool Socket();
	virtual bool Bind();
	virtual bool Listen();
	virtual int Accept();
	virtual bool Connect();
	
	virtual void UseSocket(use_socket& s_socket,bool Judge = TRUE);
	virtual void UseBind(sockaddr_in& s_sockaddr_in,bool Judge = TRUE);
	virtual void UseListen(int ListenNum = 0,bool Judge = TRUE);
	virtual void UseAccept(bool Judge = TRUE);
	virtual void UseConnect(sockaddr_in& s_sockaddr_in,bool Judge = TRUE);
	
	virtual bool IsClient(){return _bIsClient;}
protected:
	int _sockFd;
	int _listenNum;
	sockaddr_in		_s_sockaddr_in;
	sockaddr_in		_s_connect_sockaddr_in;
	sockaddr_in		_s_accept_sockaddr_in;
	use_socket		_s_use_socket;
	
	socklen_t		_socklen_t;
	
	bool _bSocket;
	bool _bBind;
	bool _bListen;
	bool _bAccept;
	bool _bConnect;
	bool _bIsClient;
};

#endif
