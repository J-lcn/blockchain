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
	

	while(1) {
		aos_msleep(6000);
	

	};

}


























