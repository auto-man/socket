#include "net_tcp.h"
//#include "net_ip.h"

int
main()
{
	tcp TEST(5);
	//ip test(100);
	TEST.Recv();
	//test.Recv();
	return 0;
}
