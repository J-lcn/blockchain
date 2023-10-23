


#include <stdlib.h>

#include <string.h>

#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "Txrequest.pb.h"
#include <pb.h>
#include <time.h>

#define PB_FIELD_MAX 128


#ifndef _BLOCKCHAINPB_H_
#define _BLOCKCHAINPB_H_






int blockchainpb(void * srcdata,uint32_t srcdatasize, char *srcdataname, uint32_t srcdatanamesize, char *enckey, 
					const uint8_t *prikey, uint32_t prikey_len, uint8_t *buffer, uint32_t buffersize, 
							uint32_t *messagesize, char *tx_idparm, uint32_t tx_idsize, int64_t  timestampparm,char *idp,uint32_t idpsize);





#endif
