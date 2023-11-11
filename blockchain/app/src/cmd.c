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



		SendTransaction();


}




void _Conn_(char *wbuf, int wbuf_len, int argc, char **argv)
{
	
	blockchainsocket(argv[1],argv[2]);
	
	


}


void _Disconn_(char *wbuf, int wbuf_len, int argc, char **argv)
{
	
	Disconn();
	


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
	GetAccount();
	


}





















