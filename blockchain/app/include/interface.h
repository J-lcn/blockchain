

#ifndef _INTERFACE_H_
#define _INTERFACE_H_



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





void SendTransaction();
void Disconn();
void GetAccount();


#endif
