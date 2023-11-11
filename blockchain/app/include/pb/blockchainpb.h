


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


typedef struct _srcmessage{

	uint8_t * srcdata;
	uint32_t srcdatasize;
	uint8_t *srcdataname;
	uint32_t srcdatanamesize;

} Srcmessage;


typedef struct _receivemessage{

	uint8_t *buffer;
	uint32_t buffersize;
	uint32_t messagesize;

} Receivemessage;


int blockchainpb(Srcmessage *meg, Receivemessage *recmeg );




#endif
