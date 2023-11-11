

#ifndef _RPCBLOCKCHAIN_H_
#define _RPCBLOCKCHAIN_H_

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sec_crypto_aes.h>
#include <stdio.h>
#include <sec_crypto_rsa.h>
#include <sec_crypto_sha.h>
#include <sec_crypto_ecdsa.h>
#include <sec_crypto_ecdh.h>
#include <mbedtls/bignum.h>
#include <mbedtls/asn1write.h>
#include <cJSON.h>




typedef struct _request{

unsigned char *server_name;
uint32_t server_namelen;
unsigned char *buffer;
uint32_t bufferlen;
} request;



typedef struct _response{
unsigned char *buffer;
uint32_t bufferlen;

} response;


int Rpcblockchain(request *req, response *res);




#endif
