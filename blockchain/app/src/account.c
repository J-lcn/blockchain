
#include "account.h"
#include "app_main.h"







uint32_t genkey(uint8_t *prikey,uint32_t *prikeylen, uint8_t *pubkey,uint32_t *pubkeylen)
{
	uint32_t ret=0;
	sc_ecdh_t ecdh;
	sc_ecdh_init(&ecdh, 0);
	sc_curve_type_t type=SC_CURVES_SECP521R1;
	sc_ecdh_load_curve(&ecdh, type);
	sc_ecdh_gen_keypair(&ecdh, prikey, pubkey);
	*prikeylen=32;
	*pubkeylen=64;
	sc_ecdh_uninit(&ecdh);

	return ret;
}






uint32_t NewAccount()
{
	uint32_t ret=0;
	

	uint8_t prikey[32]={0};
	uint8_t pubkey[64]={0};
	uint32_t prikeylen=0;
	uint32_t pubkeylen=0;
	genkey(prikey,&prikeylen, pubkey,&pubkeylen);


	printf("Start GenAcount...\n");
	request requestlu;
	char *name="genAcount";
	requestlu.server_name=(unsigned char *)name;
	requestlu.server_namelen=strlen(name);
	
	requestlu.buffer=pubkey;
	requestlu.bufferlen=pubkeylen;
	response responselu;
	responselu.buffer=(unsigned char *)malloc(128);
	responselu.bufferlen=128;
	Rpcblockchain(&requestlu, &responselu);

	Account account;
	InitAccount(&account);
	memcpy(account.prikey,responselu.buffer,32);
	memcpy(account.pubkey,responselu.buffer+32,64);
	memcpy(account.certhash,responselu.buffer+96,32);
	char key[]= {0x1b, 0xe1, 0xb2, 0x94, 0xaa, 0xfa, 0xab, 0xc6, 0x53, 0xea, 0x24, 0xf9, 0x1a, 0xbf, 0xc9, 0x48};
	memcpy(account.aesprikey,key,16);
	setAccount(&account);
	
	free(responselu.buffer);
	return ret;
}




void InitAccount(Account *account){
		
	
	account->prikeysize = 32;
	account->pubkeysize = 64;
	account->certhashsize = 32;
	account->aesprikeysize = 16;

}
	

void getAccount(Account *account){
	
	

	int base64len=100;
	char base64value[100]={0};
	char databyte[100]={0};
	size_t datalen=100;

	aos_kv_getstring("prikey", base64value, base64len);
	sc_base64_dec((const char *)base64value, strlen(base64value), (void *)databyte, &datalen);
	memcpy(account->prikey,databyte,datalen);

	base64len=100;
	datalen=100;
	aos_kv_getstring("certhash", base64value, base64len);
	sc_base64_dec((const char *)base64value, strlen(base64value), (void *)databyte, &datalen);
	memcpy(account->certhash,databyte,datalen);

	base64len=100;
	datalen=100;
	aos_kv_getstring("pubkey", base64value, base64len);
	sc_base64_dec((const char *)base64value, strlen(base64value), (void *)databyte, &datalen);
	memcpy(account->pubkey,databyte,datalen);

	base64len=100;
	datalen=100;
	aos_kv_getstring("aesprikey", base64value, base64len);
	sc_base64_dec((const char *)base64value, strlen(base64value), (void *)databyte, &datalen);
	memcpy(account->aesprikey,databyte,datalen);

}



void setAccount(Account *account){

	size_t base64len=100;
	char base64value[100]={0};
	char databyte[100]={0};
	

	
	memcpy(databyte,account->prikey,account->prikeysize);
	sc_base64_enc((const void *)databyte, account->prikeysize, base64value, &base64len);
	aos_kv_setstring("prikey", (const char *)base64value);
	

	base64len=100;
	
	memcpy(databyte,account->certhash,account->certhashsize);
	sc_base64_enc((const void *)databyte, account->certhashsize, base64value, &base64len);
	aos_kv_setstring("certhash", (const char *)base64value);

	base64len=100;
	
	memcpy(databyte,account->pubkey,account->pubkeysize);
	sc_base64_enc((const void *)databyte, account->pubkeysize, base64value, &base64len);
	aos_kv_setstring("pubkey", (const char *)base64value);

	base64len=100;
	
	memcpy(databyte,account->aesprikey,account->aesprikeysize);
	sc_base64_enc((const void *)databyte, account->aesprikeysize, base64value, &base64len);
	aos_kv_setstring("aesprikey", (const char *)base64value);

}


















