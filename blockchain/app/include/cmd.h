

#ifndef _CMD_H_
#define _CMD_H_



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
















void registercmd();
void _GetAccount_(char *wbuf, int wbuf_len, int argc, char **argv);
void _GenAccount_(char *wbuf, int wbuf_len, int argc, char **argv);
void _Conn_(char *wbuf, int wbuf_len, int argc, char **argv);
void _SendTransaction_(char *wbuf, int wbuf_len, int argc, char **argv);
void _SNTP_(char *wbuf, int wbuf_len, int argc, char **argv);
void TxTimestamp();
void _Disconn_(char *wbuf, int wbuf_len, int argc, char **argv);

#endif
