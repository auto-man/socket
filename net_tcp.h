#ifndef __NET_TCP__H
#define __NET_TCP__H

#include "net_socket.h"

#define S_LITTLE_ENDIAN

struct tcphdr
{
	unsigned short int	source_port;
	unsigned short int	dest_port;
	unsigned int		seq;
	unsigned int		ack_seq;
#if defined(S_BIG_ENDIAN)
	unsigned short int	doff:4,
				res1:4,

				cwr:1,
				ece:1,

				urg:1,
				ack:1,
				psh:1,
				rst:1,
				syn:1,
				fin:1;
#elif defined(S_LITTLE_ENDIAN)
	unsigned short int	res1:4,
				doff:4,

				fin:1,
				syn:1,
				rst:1,
				psh:1,
				ack:1,
				urg:1,

				ece:1,
				cwr:1;
#else
	unsigned short int	error;
#endif
	unsigned short int	window;
	unsigned short int	check;
	unsigned short int	urg_ptr;
};

struct tcp_package
{
	struct tcphdr	head;
	unsigned char	opinion[40];
	char		data[8192];
	char		address[36];
	tcp_package*	pNext;
};

class tcp : public net_socket
{
public:
	tcp(int num = 3);
	~tcp();

	void Recv();
	void ShowPackage(tcp_package* pTemp);
	void CutPackage(ip_package* pTemp);
private:
	struct ip_package*	_pIp;
	struct tcp_package*	_pRoot;
};

#endif
