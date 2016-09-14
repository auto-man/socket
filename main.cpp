#include "net_tcp.h"
//#include "net_ip.h"

int
main()
{
	tcp TEST(50);
	//ip test(100);
	TEST.Recv();
	//test.Recv();
	return 0;
}
