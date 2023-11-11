


#ifndef _BLOCKCHAINCRYPTO_H_
#define _BLOCKCHAINCRYPTO_H_



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
#include <sec_crypto_base64.h>
#include <sec_crypto_rng.h>

typedef struct {
	mbedtls_mpi R;
	mbedtls_mpi S;
} Sig;






uint32_t DerencodeSig(uint8_t *signature, uint32_t signaturesize, unsigned char *buffer, uint32_t buffersize,unsigned char **derdata, uint32_t *derdatasize);
uint32_t readSig(Sig *sig, const unsigned char *r,size_t rsize,const unsigned char *s,size_t ssize);
uint32_t writeSig(Sig *sig, unsigned char *r,size_t rsize,unsigned char *s,size_t ssize);
uint32_t freeSig(Sig *sig);
uint32_t initSig(Sig *sig);
void blockchainencrypt(void *key, void *in, void *outdata, uint32_t srcsize, uint32_t *encsize_out);
void blockchaindeencrypt(void *key, void *in, void *outdata, uint32_t srcsize, uint32_t encsize_out);
void blockchainsignature(void *n, void *e, void *d, void *src, uint32_t src_size, void *signature, uint32_t *sig_size);

void blockchainverify(void *n, void *e, void *d, void *src, uint32_t src_size, void *signature, uint32_t sig_size);
int pkcs7_padding(unsigned char *input, int inputsize, int block_size, uint32_t *padded_length);


uint32_t blockchainECChash(const void *srcdata,uint32_t srcsize,void *output,uint32_t *out_size);
uint32_t blockchainECCsign(const uint8_t *prikey,uint32_t prikey_len,const void *src, int srcsize, uint8_t *sig, uint32_t *sig_len);





#endif
