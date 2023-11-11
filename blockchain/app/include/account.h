


#ifndef _ACOUNT_H_
#define _ACOUNT_H_



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
#include <key_mgr.h>



typedef struct _Account{

	uint8_t prikey[32];
	uint32_t prikeysize;
	uint8_t pubkey[64];
	uint32_t pubkeysize;
	uint8_t certhash[32];
	uint32_t certhashsize;
	uint8_t aesprikey[16];
	uint32_t aesprikeysize;

}Account;


void InitAccount(Account *account);
uint32_t genkey(uint8_t *prikey,uint32_t *prikeylen, uint8_t *pubkey,uint32_t *pubkeylen);
uint32_t NewAccount();
void getAccount(Account *account);
void setAccount(Account *account);



#endif
