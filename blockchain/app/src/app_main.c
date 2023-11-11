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
	//registercmd();
	
	const struct  cli_command _SendTransaction= {
		"SendTransaction",
		"SendTransaction",
		_SendTransaction_
	};
	aos_cli_register_command(&_SendTransaction);
	

	const struct  cli_command _Disconn= {
		"Disconn",
		"Disconn",
		_Disconn_
	};
	aos_cli_register_command(&_Disconn);
	
	
	const struct  cli_command _Conn= {
		"Conn",
		"Conn",
		_Conn_
	};
	aos_cli_register_command(&_Conn);

	
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
	



	/*************************************/
	
	
	/*
	int aos_vfs_init1=aos_vfs_init();
	printf("aos_vfs_init1:%d\n",aos_vfs_init1);
	
	int  fd =aos_open("/", O_WRONLY | O_CREAT | O_TRUNC);
	printf("fd:%d\n",fd);
	int aos_close1=aos_close(fd);

	printf("aos_close1:%d\n",aos_close1);

	 fd =aos_open("/demo.txt", O_RDWR);
	printf("fd:%d\n",fd);
	int  a2=aos_write(fd,"helloworld", 10);
	printf("a2:%d\n",a2);
	int aos_close2=aos_close(fd);
	printf("aos_close2:%d",aos_close2);
	


	fd =aos_open("/f.txt", O_RDONLY);
	char buf[32]={0};
	aos_read(fd, (void *)buf, 8);
	buf[10]='\0';
	aos_close(fd);
	printf("src:%s\n",buf);
	for(int i=0;i<10;i++){
	printf("%c",buf[i]);
		}

	vfs_lfs_register("lfs");
*/
	/********************************/


	while(1) {
		aos_msleep(6000);
	

	};

}


























