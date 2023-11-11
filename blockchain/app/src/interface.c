#include "interface.h"
#include "app_main.h"





void SendTransaction()
{

	Srcmessage srcmessage;
	srcmessage.srcdata=(uint8_t *)"hello";
	srcmessage.srcdatasize=5;
	srcmessage.srcdataname=(uint8_t *)"T";
	srcmessage.srcdatanamesize=1;
	Receivemessage receivemessage;
	receivemessage.buffer=(uint8_t *)malloc(500);
	receivemessage.buffersize=500;
	printf("Start building the Txrequest...\n");
	blockchainpb(&srcmessage,&receivemessage);
	printf("receivemessage.messagesize:%d\n",receivemessage.messagesize);

	printf("Start send the Txrequest...\n");
	request requestlu;
	char *name="blockchain";
	requestlu.server_name=(unsigned char *)name;
	requestlu.server_namelen=strlen(name);
	
	requestlu.buffer=receivemessage.buffer;
	requestlu.bufferlen=receivemessage.messagesize;
	response responselu;
	responselu.buffer=(unsigned char *)malloc(50);
	responselu.bufferlen=50;
	Rpcblockchain(&requestlu, &responselu);
	responselu.buffer[responselu.bufferlen]='\0';
	printf("responselu.buffer:%s\n",responselu.buffer);
	printf("responselu.bufferlen:%d\n",responselu.bufferlen);
	free(responselu.buffer);
	free(receivemessage.buffer);
}


void Disconn()
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



void GetAccount()
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











