/*
 * 文件名: app_main.c
 * 作者: lujie
 * 日期: 2023-10-23
 * 描述: 
 */






#include <aos/yloop.h>
#include "app_main.h"




int main(void)
{
	/**    Initializing the development board   ****/
	board_yoc_init();
	printf("The development board has been initialized!!!\n");
	const struct  cli_command socket_client_v= {
		"blockchain",
		"blockchain",
		blockchain
	};
	int regstart=aos_cli_register_command(&socket_client_v);
	if (regstart==0) {
		printf("Registration of blockchain application completed!!!\n");
	} else {
		printf("Failed to register blockchain application!!!\n");
	}
	printf("Introduction to blockchain application parameters...\n");
	printf("parameter1:blockchain\n");
	printf("parameter2:srcip\n");
	printf("parameter3:srcport\n");
	printf("parameter4:desip\n");
	printf("parameter5:desport\n");
	printf("parameter6:tx_id\n");
	printf("parameter7:timestampparm\n");
	printf("parameter8:id\n");
	printf("parameter9:data\n");
	

	while(1) {
		aos_msleep(60);

	};

}






void blockchain(char *wbuf, int wbuf_len, int argc, char **argv)
{

	/*  parameter: blockchain 0 srcip 1 srcport 2 desip 3 desport 4   tx_idparm 5  timestampparm 6  idp  7  data  8  **/
	
	char *src=argv[8];
	uint32_t srcsize=strlen(src);
	const uint8_t prikey[]= {
			0x7f, 0x0f, 0x57, 0xbf, 0xa5, 0x57, 0xfb, 0x30, 0x00, 0x27, 0x5f, 0xc7, 0xf6, 0x94, \
			0x90, 0xe9, 0xc8, 0xeb, 0xde, 0xf0, 0xa3, 0xbd, 0x90, 0xfc, 0xf2, 0xac, 0xa4, 0x71, \
			0x46, 0xa2, 0x72, 0x95};
	uint32_t prikey_len=32;
	char key[]= {0x1b, 0xe1, 0xb2, 0x94, 0xaa, 0xfa, 0xab, 0xc6, 0x53, 0xea, 0x24, 0xf9, 0x1a, 0xbf, 0xc9, 0x48};
	uint8_t buffer[400]= {0};
	uint32_t buffersize=400;
	uint32_t messagesize=0;

	int64_t  timestampparm=atoi(argv[6]);
	uint32_t tx_idsize=strlen(argv[5]);
	uint32_t idpsize=strlen(argv[7]);
	printf("Start building the Txrequest...\n");
	blockchainpb((void *)src,srcsize, "Tempment", 8, key, prikey, prikey_len, buffer, buffersize,\
			 &messagesize, argv[5],tx_idsize, timestampparm,argv[7],idpsize);

	printf("Txrequestsize:%d\n",messagesize);
	printf("Txrequest:\n");
	for(int i=0; i<messagesize; i++) {
		printf("0x%02x, ",buffer[i]);
	}
	printf("\n");

	printf("Start send the Txrequest...\n");
	blockchainsend(argv[1],argv[2],argv[3],argv[4],(void *)buffer, messagesize);



}




























