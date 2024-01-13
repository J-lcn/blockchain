
#include "blockchaincrypto.h"
#include "app_main.h"
int pkcs7_padding(unsigned char *input, int inputsize, int block_size, uint32_t *padded_length)
{
	int datasize=inputsize;
	if(datasize % block_size==0) {
		*padded_length=datasize;
	} else {
		int padding_size = block_size - (datasize % block_size);
		for (int i = 0; i < padding_size; i++) {
			input[datasize + i] = (unsigned char) padding_size;
		}
		*padded_length=datasize+padding_size;
	}
	return 0;
}


void blockchainencrypt(void *key, void *in, void *outdata, uint32_t srcsize, uint32_t *encsize_out)
{

	uint32_t encsize_in=0;
	void *indata=NULL;
	indata=in;
	encsize_in=srcsize;
	pkcs7_padding((unsigned char *)indata, srcsize, 16, &encsize_in) ;
	*encsize_out=encsize_in;
	sc_aes_t aes;
	uint32_t idx=0;
	sc_aes_init(&aes, idx);
	sc_aes_key_bits_t key_len=SC_AES_KEY_LEN_BITS_128;
	sc_aes_set_encrypt_key(&aes, key, key_len);
	sc_aes_ecb_encrypt(&aes, indata, outdata, encsize_in);
	sc_aes_uninit(&aes);

}

void blockchaindeencrypt(void *key, void *in, void *outdata, uint32_t srcsize, uint32_t encsize_out)
{

	sc_aes_t aes;
	uint32_t idx=0;
	sc_aes_init(&aes, idx);
	char outdatabuf[100]= {0};
	sc_aes_key_bits_t key_len=SC_AES_KEY_LEN_BITS_128;
	sc_aes_set_decrypt_key(&aes, key, key_len);
	sc_aes_ecb_decrypt(&aes, in, (void *)outdatabuf, encsize_out);
	memcpy(outdata,outdatabuf,srcsize);
	sc_aes_uninit(&aes);

}


void blockchainsignature(void *n, void *e, void *d, void *src, uint32_t src_size, void *signature, uint32_t *sig_size)
{


	sc_rsa_t rsa;
	uint32_t idx=0;
	sc_rsa_key_bits_t data_bits=SC_RSA_KEY_BITS_1024;
	sc_rsa_init(&rsa, idx, data_bits);
	sc_rsa_context_t context;
	context.n=n;
	context.e=e;
	context.d=d;
	context.key_bits=1024;
	context.padding_type=SC_RSA_PADDING_MODE_PKCS1;
	context.hash_type=SC_RSA_HASH_TYPE_SHA256;
	sc_rsa_hash_type_t hash_type=SC_RSA_HASH_TYPE_SHA256;
	sc_rsa_sign(&rsa, &context, src, src_size,signature, hash_type);
	*sig_size=context.key_bits;
	sc_rsa_uninit(&rsa);
}

void blockchainverify(void *n, void *e, void *d, void *src, uint32_t src_size, void *signature, uint32_t sig_size)
{

	sc_rsa_t rsa;
	uint32_t idx=0;
	sc_rsa_key_bits_t data_bits=SC_RSA_KEY_BITS_1024;
	sc_rsa_init(&rsa, idx, data_bits);
	sc_rsa_context_t context;
	context.n=n;
	context.e=e;
	context.d=d;
	context.key_bits=1024;
	context.padding_type=SC_RSA_PADDING_MODE_PKCS1;
	context.hash_type=SC_RSA_HASH_TYPE_SHA256;
	sc_rsa_hash_type_t hash_type=SC_RSA_HASH_TYPE_SHA256;
	bool sc_rsa_verifylu=sc_rsa_verify(&rsa, &context, src, src_size,signature,src_size, hash_type);
	if(sc_rsa_verifylu==0) {
		printf("verify failure!");
	} else {
		printf("verify succes!");
	}
	sc_rsa_uninit(&rsa);

}




uint32_t blockchainECCsign(const uint8_t *prikey,uint32_t prikey_len,const void *src, int srcsize, uint8_t *sig, uint32_t *sig_len)
{
	uint32_t ret=0;
	sc_ecdsa_t sc_ecdsa_tlu;
	sc_ecdsa_init(&sc_ecdsa_tlu, 0);
	sc_ecdsa_load_curve(&sc_ecdsa_tlu, SC_CURVES_SECP521R1);
	uint8_t output[300];
	memset(output,0,300);
	uint32_t out_size=0;
	blockchainECChash((const void *)src,srcsize,(void *)output,&out_size);
	ret=sc_ecdsa_sign(&sc_ecdsa_tlu,  prikey,  prikey_len, (const uint8_t *)output, out_size, sig, sig_len);
	sc_ecdsa_uninit(&sc_ecdsa_tlu);
	return ret;

}


uint32_t blockchainECChash(const void *srcdata,uint32_t srcsize,void *output,uint32_t *out_size)
{
	uint32_t ret=0;
	sc_sha_t sc_sha_tlu;
	sc_sha_init(&sc_sha_tlu, 0);

	sc_sha_context_t sc_sha_context_tlu;
	sc_sha_context_tlu.mode=SC_SHA_MODE_256;
	sc_mbedtls_sha1_context sha1_ctxlu;
	sc_mbedtls_sha1_init( &sha1_ctxlu);
	sc_mbedtls_sha256_context sha2_ctxlu;
	sc_mbedtls_sha256_init(&sha2_ctxlu);
	sc_sha_context_tlu.sha1_ctx=sha1_ctxlu;
	sc_sha_context_tlu.sha2_ctx=sha2_ctxlu;
	sc_sha_start(&sc_sha_tlu, &sc_sha_context_tlu, SC_SHA_MODE_256);
	sc_sha_update(&sc_sha_tlu, &sc_sha_context_tlu, srcdata, srcsize);
	ret=sc_sha_finish(&sc_sha_tlu,  &sc_sha_context_tlu, output, out_size);
	sc_mbedtls_sha1_free( &sha1_ctxlu );
	sc_mbedtls_sha256_free(&sha2_ctxlu);
	sc_sha_uninit(&sc_sha_tlu);
	return ret;

}





uint32_t initSig(Sig *sig)
{
	uint32_t ret=0;

	mbedtls_mpi_init(&(sig->R));
	mbedtls_mpi_init(&(sig->S));

	return ret;

}


uint32_t freeSig(Sig *sig)
{
	uint32_t ret=0;

	mbedtls_mpi_free(&(sig->R));
	mbedtls_mpi_free(&(sig->S));

	return ret;

}





uint32_t readSig(Sig *sig, const unsigned char *r,size_t rsize,const unsigned char *s,size_t ssize)
{
	uint32_t ret=0;
	mbedtls_mpi_read_binary(&(sig->R), r, rsize);
	mbedtls_mpi_read_binary(&(sig->S), s, ssize);
	return ret;

}



uint32_t writeSig(Sig *sig, unsigned char *r,size_t rsize,unsigned char *s,size_t ssize)
{
	uint32_t ret=0;
	mbedtls_mpi_write_binary(&(sig->R), r, rsize);
	mbedtls_mpi_write_binary(&(sig->S), s, ssize);
	return ret;

}


uint32_t DerencodeSig(uint8_t *signature, uint32_t signaturesize, unsigned char *buffer, 
				uint32_t buffersize,unsigned char **derdata, uint32_t *derdatasize)
{
	uint32_t ret=0;
	uint8_t R[32]= {0};
	uint8_t S[32]= {0};
	memcpy(R, signature, 32);
	memcpy(S, signature+32, 32);
	Sig sigStruct;
	initSig(&sigStruct);
	readSig(&sigStruct, (const unsigned char *)R,32,(const unsigned char *)S,32);
	unsigned char *p = buffer+buffersize;
	unsigned char *start = buffer;

	// 编码原始数据
	int  written_raw_bytes=mbedtls_asn1_write_mpi(&p, start, &(sigStruct.S));
	if (written_raw_bytes < 0) {
		printf("Error writing ASN.1 raw data: %d\n", written_raw_bytes);
		return 1;
	}
	written_raw_bytes=mbedtls_asn1_write_mpi(&p, start, &(sigStruct.R));
	if (written_raw_bytes < 0) {
		printf("Error writing ASN.1 raw data: %d\n", written_raw_bytes);
		return 1;
	}
	int written_len_bytes=buffersize-(p-start);
	int written_len_ret = mbedtls_asn1_write_len(&p, start, written_len_bytes);
	if (written_len_ret < 0) {
		printf("Error writing ASN.1 length field: %d\n", written_len_ret);
		return 1;
	}
	int written_tag_ret = mbedtls_asn1_write_tag(&p, start, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE);
	if (written_tag_ret < 0) {
		printf("Error writing ASN.1 tag: %d\n", written_tag_ret);
		return 1;
	}
	*derdata=p;
	*derdatasize=buffersize-(p-start);
	freeSig(&sigStruct);
	return ret;
}














