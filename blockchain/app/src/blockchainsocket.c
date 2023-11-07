




#include"blockchainsocket.h"

#include "app_main.h"

void blockchainsocket(char *des_host,char * des_port)
{

	int _socket=socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(atoi(des_port));
	in_addr_t dst;
	inet_pton(AF_INET,des_host,&dst);
	addr.sin_addr.s_addr=dst;
	socklen_t addrlen=sizeof(addr);
	/****************************************/
	int enable_keepalive = 1;
	setsockopt(_socket,SOL_SOCKET,SO_KEEPALIVE,&enable_keepalive,sizeof(enable_keepalive));
	int keepalive_idle = 30;  // 连接空闲时的Keep-Alive间隔
        int keepalive_interval = 30;  // 两次Keep-Alive探测之间的间隔
        int keepalive_count = 5;  // 未响应的Keep-Alive探测次数

        // 设置Keep-Alive参数
        setsockopt(_socket, IPPROTO_TCP, TCP_KEEPIDLE, &keepalive_idle, sizeof(keepalive_idle));
        setsockopt(_socket, IPPROTO_TCP, TCP_KEEPINTVL, &keepalive_interval, sizeof(keepalive_interval));
        setsockopt(_socket, IPPROTO_TCP, TCP_KEEPCNT, &keepalive_count, sizeof(keepalive_count));

	/**************************************************/
	connect(_socket,(struct sockaddr *)&addr,addrlen);
	aos_kv_setint("blockchainsocket", _socket);
	aos_kv_setint("mutexsocket", 1);

}


void blockchainsend(void *datain,uint32_t datasize, uint8_t *receivedata,uint32_t *receivedatasize)
{	int mutexsockettmp=1;
	aos_kv_getint("mutexsocket", &mutexsockettmp);
	if(mutexsockettmp==-1){
		printf("socket busying..." );
	}
	while(mutexsockettmp==-1){
		aos_kv_getint("mutexsocket", &mutexsockettmp);
		aos_msleep(600);
	}
	aos_kv_setint("mutexsocket", -1);
	int _socket=0;
	aos_kv_getint("blockchainsocket", &_socket);
	const char *data=(const char *)datain;
	send(_socket,data,datasize,0);
	uint8_t mem[1500]={0};
	uint32_t receivesize =read(_socket,mem,1500);
	memcpy(receivedata,mem,receivesize);
	*receivedatasize=receivesize;
	aos_kv_setint("mutexsocket", 1);
	

}

/*

void blockchainsntp()
{
	
		sntp_init();
		sntp_setoperatingmode(SNTP_OPMODE_POLL);
		u8_t sntp_getoperatingmode1=sntp_getoperatingmode();
		printf("sntp_getoperatingmode1:%d\n",sntp_getoperatingmode1);
		
		ip_addr_t addr;
		ipaddr_aton("52.231.114.183", &addr);
		sntp_setserver((u8_t)0, &addr);
		u8_t sntp_enabled1=sntp_enabled();
		printf("sntp_enabled1:%d\n",sntp_enabled1);

}


*/





















