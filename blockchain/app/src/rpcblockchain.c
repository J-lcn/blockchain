



#include "rpcblockchain.h"
#include "app_main.h"








int Rpcblockchain(request *req, response *res)
{
	unsigned char buf[1000];
	memset(buf,0,1000);
	unsigned char *start=buf;
	unsigned char *p=buf+1000;
	if(mbedtls_asn1_write_raw_buffer(&p, start,req->buffer,req->bufferlen)<0){
	printf("raw_buffer fail\n");	
	}
	if(mbedtls_asn1_write_len( &p, start,req->bufferlen)<0){
	printf("mbedtls_asn1_write_len fail\n");	
	}
	if(mbedtls_asn1_write_tag( &p, start,MBEDTLS_ASN1_OCTET_STRING)<0){
	printf("mbedtls_asn1_write_tag fail\n");
	}
	if(mbedtls_asn1_write_raw_buffer(&p, start,req->server_name,req->server_namelen)<0){
	printf("mbedtls_asn1_write_raw_buffer fail\n");	
	}
	if(mbedtls_asn1_write_len( &p, start,req->server_namelen)<0){
	printf(" mbedtls_asn1_write_len fail\n");	
	}
	if(mbedtls_asn1_write_tag( &p, start,MBEDTLS_ASN1_PRINTABLE_STRING)<0){
	printf("mbedtls_asn1_write_tag fail\n");	
	}
	if(mbedtls_asn1_write_len( &p, start,sizeof(buf)-(p-start))<0){
	printf("mbedtls_asn1_write_len fail\n");	
	}
	if(mbedtls_asn1_write_tag( &p, start,MBEDTLS_ASN1_CONSTRUCTED|MBEDTLS_ASN1_SEQUENCE)<0){
	printf("mbedtls_asn1_write_tag fail\n");	
	}
	uint32_t datasize=sizeof(buf)-(p-start);
	uint8_t receivedata[1000];
	memset(receivedata,0,1000);
	uint32_t receivedatasize=0;
	blockchainsend(p,datasize, receivedata,&receivedatasize);
	
	p=receivedata;
	const unsigned char *end=p+receivedatasize;
	size_t len=0;
	
	int expectedtag=MBEDTLS_ASN1_CONSTRUCTED|MBEDTLS_ASN1_SEQUENCE;
	if(mbedtls_asn1_get_tag( &p, end,&len,expectedtag)!=0){
	printf("mbedtls_asn1_get_tag fail\n");	
	}
	expectedtag=MBEDTLS_ASN1_OCTET_STRING;
	if(mbedtls_asn1_get_tag( &p, end,&len,expectedtag)!=0){
	printf("mbedtls_asn1_get_tag fail\n");	
	}
	memcpy(res->buffer,p,len);
	res->bufferlen=len;
	return 0;
}






















