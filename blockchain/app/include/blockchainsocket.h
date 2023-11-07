



#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <lwip/sockets.h>
#include <uservice/uservice.h>
#include <yoc/netmgr_service.h>
#include <uservice/eventid.h>
#include <yoc/partition.h>
#include <aos/kv.h>
#include "board.h"
#include <ulog/ulog.h>
#include <aos/kernel.h>
#include <aos/cli.h>


#include <pthread.h>








/*
 * Copyright (C) 2019-2020 Alibaba Group Holding Limited
 */
#ifndef _BLOCKCHAINSOCKET_H_
#define _BLOCKCHAINSOCKET_H_


//void blockchainsntp();
void blockchainsend(void *datain,uint32_t datasize, uint8_t *receivedata,uint32_t *receivedatasize);
void blockchainsocket(char *des_host,char * des_port);








#endif










