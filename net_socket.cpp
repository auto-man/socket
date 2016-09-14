#include "net_socket.h"

void net_socket::UseSocket(use_socket& s_socket,bool Judge)
{
	_s_use_socket.Af		= s_socket.Af;
	_s_use_socket.Type		= s_socket.Type;
	_s_use_socket.Protocol	= s_socket.Protocol;
	_bSocket				= Judge;
}

void net_socket::UseBind(sockaddr_in& s_sockaddr_in,bool Judge)
{
	memset(&_s_sockaddr_in,0,sizeof(_s_sockaddr_in));
	_s_sockaddr_in.sin_family		= s_sockaddr_in.sin_family;
	_s_sockaddr_in.sin_port			= s_sockaddr_in.sin_port;
	_s_sockaddr_in.sin_addr.s_addr	= s_sockaddr_in.sin_addr.s_addr;
	_bBind							= Judge;
}

void net_socket::UseListen(int ListenNum,bool Judge)
{
	_listenNum	= ListenNum;
	_bListen	= Judge;
	_bConnect	= !Judge;
	_bIsClient	= !Judge;
}

void net_socket::UseConnect(sockaddr_in& s_sockaddr_in,bool Judge)
{
	_s_connect_sockaddr_in.sin_family		= s_sockaddr_in.sin_family;
	_s_connect_sockaddr_in.sin_port			= s_sockaddr_in.sin_port;
	_s_connect_sockaddr_in.sin_addr.s_addr	= s_sockaddr_in.sin_addr.s_addr;
	_bConnect								= Judge;
	_bIsClient								= Judge;
	_bListen								= !Judge;
}

void net_socket::UseAccept(bool Judge)
{
	_socklen_t	= sizeof(sockaddr_in);
	_bAccept	= Judge;
}

bool net_socket::Socket()
{
	if(!_bSocket)
	{
		cout<<"socket not open yet."<<endl;
		return false;
	}
	
	_sockFd = socket(_s_use_socket.Af,_s_use_socket.Type,_s_use_socket.Protocol);

	if(_s_use_socket.Protocol == 0)
	{
		bool	flag = true;
		setsockopt(_sockFd,IPPROTO_IP,IP_HDRINCL,(char*)&flag,sizeof(flag));
	}

	if(_sockFd < 0)
	{
		cout<<"socket init failed."<<endl;
		cout<<"Failed index : "<<errno<<endl;
		cout<<"Failed socket : "<<_sockFd<<endl;
		return false;
	}
	
	return true;
}

bool net_socket::Bind()
{
	if(!(_bBind && _bSocket))
	{
		if(!_bBind)
			cout<<"bind not open yet."<<endl;
		else
			cout<<"socket not open yet."<<endl;
		
		return false;
	}
	
	if( bind(_sockFd,(sockaddr*)&_s_sockaddr_in,_socklen_t) < 0)
	{
		cout<<"bind init failed."<<endl;
		return false;
	}
	
	return true;
}

bool net_socket::Listen()
{
	if(!_bListen)
	{
		cout<<"listen not open yet."<<endl;
		return false;
	}
	
	if(listen(_sockFd,_listenNum) < 0)
	{
		cout<<"listen init failed."<<endl;
		return false;
	}
	
	return true;
}

int net_socket::Accept()
{
	if(!_bAccept)
	{
		cout<<"accept not open yet."<<endl;
		return -2;
	}
	
	int clientFd;
	if( (clientFd = accept(_sockFd,(sockaddr*)(&_s_accept_sockaddr_in),&_socklen_t)) < 0)
	{
		cout<<"accept init failed."<<endl;
		return -1;
	}
	
	return clientFd;
}

bool net_socket::Connect()
{
	if(!_bConnect)
	{
		cout<<"connect not open yet."<<endl;
		return false;
	}
	
	if(connect(_sockFd,(sockaddr*)(&_s_connect_sockaddr_in),_socklen_t) < 0)
	{
		cout<<"connect init failed."<<endl;
		return false;
	}
	
	return true;
}

















