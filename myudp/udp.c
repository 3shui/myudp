#include "winsock2.h"
#include "WS2tcpip.h"
#include "string.h"
#include "stdio.h"
#include "udp.h"
#pragma comment(lib, "ws2_32.lib")
int socket_send() {
	//初始化socket
	DWORD ver;//无符号整数
	WSADATA wsaData;
	ver = MAKEWORD(2,2);//告诉windows用什么版本socket
	WSAStartup(ver,&wsaData);//只要用socket必须要这个函数
	//初始化完成
	SOCKET st = socket(AF_INET,SOCK_DGRAM,0);//AF_INET代表使用tcp/ip协议,SOCK_DGRAM代表用udp,第三个参数tcp/ip中默认填0
	struct sockaddr_in addr;//
	memset(&addr,0,sizeof(addr));//这个结构包含协议，端口，地址
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8088);//转换成short网络字节流，避免大小端
	inet_pton(AF_INET,"127.0.0.1",(void*)&addr.sin_addr.S_un.S_addr); //ip地址在windows里是一个结构,
	char buf[] = "hello";
	int rc;
	printf("%s\n", "输入0退出");
	while(1){
		memset(buf, 0, sizeof(buf));
		gets(buf);
		if (buf[0] == '0') {
			printf("%s\n", "已退出");
			break;
		}
		rc = sendto(st, buf, strlen(buf), 0, (struct sockaddr *)&addr, sizeof(addr));

	}
	
	closesocket(st);
	WSACleanup();
	return rc;
}
int socket_receive() {
	//初始化socket
	DWORD ver;//无符号整数
	WSADATA wsaData;
	ver = MAKEWORD(2, 2);//告诉windows用什么版本socket
	WSAStartup(ver, &wsaData);//只要用socket必须要这个函数
							  //初始化完成
	SOCKET st = socket(AF_INET, SOCK_DGRAM, 0);//AF_INET代表使用tcp/ip协议,SOCK_DGRAM代表用udp,第三个参数tcp/ip中默认填0
	struct sockaddr_in addr;//
	memset(&addr, 0, sizeof(addr));//这个结构包含协议，端口，地址
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8088);//转换成short网络字节流，避免大小端
	addr.sin_addr.s_addr = htonl(INADDR_ANY);//接收方不需要ip
	int rc;
	if(bind(st, (struct sockaddr *)&addr, sizeof(addr))>-1){//将接收方和端口号绑定
		char buf[1024] = {0};//存储发送方的消息
		struct sockaddr_in send_ip;//用来存储发送方ip
		int len = sizeof(send_ip);
		while (1) {
			memset(buf, 0, sizeof(buf));
			rc = recvfrom(st, buf, sizeof(buf), 0, (struct sockaddr *)&send_ip, &len);
			printf("%s\n", buf);
		}
		
	}
	closesocket(st);
	WSACleanup();
	return rc;
}