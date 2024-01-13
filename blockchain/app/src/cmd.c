#include "cmd.h"
#include "app_main.h"




void registercmd()
{

	

	const struct  cli_command _SendTransaction= {
		"SendTransaction",
		"SendTransaction",
		_SendTransaction_
	};
	aos_cli_register_command(&_SendTransaction);
	


	const struct  cli_command _Conn= {
		"Conn",
		"Conn",
		_Conn_
	};
	aos_cli_register_command(&_Conn);
	
	const struct  cli_command _Disconn= {
		"Disconn",
		"Disconn",
		_Disconn_
	};
	aos_cli_register_command(&_Disconn);

	
	const struct  cli_command _GenAccount= {
		"GenAccount",
		"GenAccount",
		_GenAccount_
	};
	aos_cli_register_command(&_GenAccount);
	
	
	const struct  cli_command _GetAccount= {
		"GetAccount",
		"GetAccount",
		_GetAccount_
	};
	aos_cli_register_command(&_GetAccount);
	const struct  cli_command _SNTP= {
		"SNTP",
		"SNTP",
		_SNTP_
	};
	aos_cli_register_command(&_SNTP);


}





void _SendTransaction_(char *wbuf, int wbuf_len, int argc, char **argv)
{

	
	//TxTimestamp();
	Srcmessage srcmessage;
	srcmessage.srcdata=(uint8_t *)"hello";
	srcmessage.srcdatasize=5;

	srcmessage.srcdataname=(uint8_t *)"T";
	srcmessage.srcdatanamesize=1;
	Receivemessage receivemessage;
	receivemessage.buffer=(uint8_t *)malloc(400);
	receivemessage.buffersize=400;
	printf("Start building the Txrequest...\n");
	blockchainpb(&srcmessage,&receivemessage);

	

	printf("Start send the Txrequest...\n");
	
	uint8_t sendbuffer[400]= {0};
	sendbuffer[0]=0;
	uint32_t sendsize=receivemessage.messagesize+1;
	memcpy(sendbuffer+1,receivemessage.buffer,receivemessage.messagesize);
	
	uint8_t receivedata[10]={0};
	uint32_t receivedatasize=0;
	blockchainsend((void *)sendbuffer, sendsize, receivedata,&receivedatasize);
	printf("receivedatasize:%d\n",receivedatasize);
	receivedata[receivedatasize]='\0';
	printf("receivedata:%s\n",(char *)receivedata);
	free(receivemessage.buffer);


}




void _Conn_(char *wbuf, int wbuf_len, int argc, char **argv)
{
	
	blockchainsocket(argv[1],argv[2]);
	//TxTimestamp();
	


}


void _Disconn_(char *wbuf, int wbuf_len, int argc, char **argv)
{
	
	int _socket=0;
	int mutexsockettmp=1;
	aos_kv_getint("mutexsocket", &mutexsockettmp);
	if(mutexsockettmp==-1){
		printf("socket busying..." );
	}
	while(mutexsockettmp==-1){
		aos_kv_getint("mutexsocket", &mutexsockettmp);
		aos_msleep(600);
	}
	aos_kv_getint("blockchainsocket", &_socket);
	closesocket(_socket);
	


}



void TxTimestamp()
{
	
	uint8_t sendbuffer[32]={0};
	uint32_t sendsize=32;
	uint8_t receivedata[20]={0};
	uint32_t receivedatasize=20;
	size_t base64len=30;
	char base64value[30]={0};
	
	sendsize=32;
	receivedatasize=20;
	base64len=30;
	sc_rng_get_multi_word((uint32_t *)sendbuffer, 8);
	sendbuffer[0]=35;
	blockchainsend((void *)sendbuffer, sendsize, receivedata,&receivedatasize);
	sc_base64_enc((const void *)receivedata, receivedatasize, base64value, &base64len);
	aos_kv_setstring("TxTimestamp", (const char *)base64value);
	aos_msleep(5000);
	
	


}



void _SNTP_(char *wbuf, int wbuf_len, int argc, char **argv)
{
	
	//TxTimestamp();
	ntp_sync_time("52.231.114.183");
	//blockchainsntp();
	
	


}



void _GenAccount_(char *wbuf, int wbuf_len, int argc, char **argv)
{

	NewAccount();


}

void _GetAccount_(char *wbuf, int wbuf_len, int argc, char **argv)
{
	Account account;
	InitAccount(&account);
	getAccount(&account);
	printf("account.prikeysize:%d\n",account.prikeysize);
	printf("account.prikey:\n");
	for(int i=0; i<account.prikeysize; i++) {
		printf("%02x",account.prikey[i]);
	}
	printf("\n");

	printf("account.pubkeysize:%d\n",account.pubkeysize);
	printf("account.pubkey:\n");
	for(int i=0; i<account.pubkeysize; i++) {
		printf("%02x",account.pubkey[i]);
	}
	printf("\n");
	printf("account.certhashsize:%d\n",account.certhashsize);
	printf("account.certhash:\n");
	for(int i=0; i<account.certhashsize; i++) {
		printf("%02x",account.certhash[i]);
	}
	printf("\n");
	printf("account.aesprikeysize:%d\n",account.aesprikeysize);
	printf("account.aesprikey:\n");
	for(int i=0; i<account.aesprikeysize; i++) {
		printf("%02x",account.aesprikey[i]);
	}
	printf("\n");
	


}





















