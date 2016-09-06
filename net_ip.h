#ifndef __NET_IP__H
#define __NET_IP__H

#include "net_socket.h"

struct iphdr
{
	unsigned char		ihl:4,
				version:4;

	unsigned char		tos;
	unsigned short int	tot_len;
	unsigned short int	id;
	unsigned short int	frag_off;
	unsigned char		ttl;
	unsigned char		protocol;
	unsigned short int	check;
	unsigned int		saddr;
	unsigned int		daddr;
};

struct ip_package
{
	struct iphdr	head;
	unsigned char	opinion[40];
	unsigned char	data[2048];
	char		address[36];
	ip_package*	pNext;
};

class ip : public net_socket
{
public:
	ip(int num = 3);
	~ip();

	void Recv();
	void CutPackage(ip_package* pTemp);
private:
	struct ip_package*	_pRoot;
};

#endif
