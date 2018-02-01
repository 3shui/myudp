#include "iostream"
#include "udp.h"
using namespace std;
int main(int argc,char *args[]) {
	if (argc > 1) {
		if (args[1][0] == '1')
			socket_send();
		else
			socket_receive();
	}
	return 0;
}