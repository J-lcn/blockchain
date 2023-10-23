



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











/*
 * Copyright (C) 2019-2020 Alibaba Group Holding Limited
 */
#ifndef _BLOCKCHAINSOCKET_H_
#define _BLOCKCHAINSOCKET_H_





void blockchainsend(char *src_host,char * src_port,char *des_host,char * des_port,void *data,uint32_t datasize);












#endif










