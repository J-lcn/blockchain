

/*
 * 文件名: blockchainpb.c
 * 作者: lujie
 * 日期: 2023-10-23
 * 描述: 
 */









#include "blockchainpb.h"
#include "app_main.h"
#include <time.h>

int blockchainpb(Srcmessage *meg, Receivemessage *recmeg )
{


	/*       初始化                   */
	pb_size_t message_length;
	srand(time(NULL));
	uint32_t encdatasize=0;
	char encdata[40]= {0};

	Account account;
	InitAccount(&account);
	getAccount(&account);
	/*       加密                   */
	blockchainencrypt(account.aesprikey, meg->srcdata, (void *)encdata, meg->srcdatasize, &encdatasize);
	TxRequest TxRequestpb=TxRequest_init_zero;
	TxRequestpb.has_payload=true;
	/*       构造交易体                   */
	Payload payloadpb=Payload_init_zero;
	memcpy(payloadpb.chain_id,"chain01",strlen("chain01"));
	payloadpb.tx_type=TxType_INVOKE_CONTRACT;
	uint8_t tx_idbuf[16]={0};
	for(int i=0; i<16; i++) {
		tx_idbuf[i]=(uint8_t)(rand() % 256);
	}
	char tx_id[32]={0};
	for(int i=0; i<16; i++) {
		sprintf(&tx_id[i * 2], "%02x", tx_idbuf[i]);
	}
	memcpy(payloadpb.tx_id,tx_id,sizeof(tx_id));
	time_t currentTime;
	time(&currentTime);  
	payloadpb.timestamp=(int64_t)currentTime;
	//payloadpb.expiration_time=2000;
	memcpy(payloadpb.contract_name,"evidence",strlen("evidence"));////1
	memcpy(payloadpb.method,"Evidence",strlen("Evidence"));//////2

	payloadpb.parameters_count=3;
	uint8_t id[32]={0};
	sc_rng_get_multi_word((uint32_t *)id, 8);
	memcpy(payloadpb.parameters[0].key,"id",strlen("id"));
	payloadpb.parameters[0].value.size=32;
	memcpy(payloadpb.parameters[0].value.bytes,id,32);
	uint8_t hash[32]={0};
	sc_rng_get_multi_word((uint32_t *)hash, 8);
	memcpy(payloadpb.parameters[1].key,"hash",strlen("hash"));
	payloadpb.parameters[1].value.size=32;
	memcpy(payloadpb.parameters[1].value.bytes,hash,32);

	memcpy(payloadpb.parameters[2].key,"metadata",strlen("metadata"));
	payloadpb.parameters[2].value.size=17;
	memcpy(payloadpb.parameters[2].value.bytes,"{\"Tempment\":\"33\"}",17);

	payloadpb.sequence=21;
	payloadpb.has_limit=true;
	payloadpb.limit.gas_limit=3998897866;
	

	/*       序列化交易体                   */
	
	pb_ostream_t payloadlu = pb_ostream_from_buffer(recmeg->buffer, recmeg->buffersize);
	pb_encode(&payloadlu, Payload_fields, &payloadpb);
	message_length = payloadlu.bytes_written;


	/*       交易体签名                   */
	
	uint8_t signature[64]= {0};
	uint8_t R[32]= {0};
	uint8_t S[32]= {0};
	uint32_t sig_size=0;
	

	
	blockchainECCsign(account.prikey, account.prikeysize,(const void *)recmeg->buffer, message_length, signature, &sig_size);
	memcpy(R, signature, 32);
	memcpy(S, signature+32, 32);

	/*       构造请求其他成员                   */
	printf("der encodes the signature...\n");
	unsigned char derbuffer[200]= {0};
	uint32_t derbuffersize=200;
	unsigned char *dersignature=NULL;
	uint32_t dersignaturesize=0;
	DerencodeSig(signature, sig_size, derbuffer, derbuffersize, &dersignature, &dersignaturesize);

	
	TxRequestpb.payload=payloadpb;
	TxRequestpb.has_sender=true;
	TxRequestpb.sender.has_signer=true;
	memcpy(TxRequestpb.sender.signer.org_id,"luorg1",strlen("luorg1"));
	TxRequestpb.sender.signer.member_type=MemberType_CERT_HASH;
	TxRequestpb.sender.signer.member_info.size=32;
	memcpy(TxRequestpb.sender.signer.member_info.bytes,account.certhash,32);
	TxRequestpb.sender.signature.size=dersignaturesize;
	memcpy(TxRequestpb.sender.signature.bytes,dersignature,dersignaturesize);

	/*

		TxRequestpb.endorsers_count=1;
		TxRequestpb.endorsers[0].has_signer=true;
		memcpy(TxRequestpb.endorsers[0].signer.org_id,"luorg1",strlen("luorg1"));
		TxRequestpb.endorsers[0].signer.member_type=MemberType_CERT_HASH;
		TxRequestpb.endorsers[0].signer.member_info.size=32;
		memcpy(TxRequestpb.endorsers[0].signer.member_info.bytes,certhash,32);
		TxRequestpb.endorsers[0].signature.size=sig_size;
		memcpy(TxRequestpb.endorsers[0].signature.bytes,signature,sig_size);

		TxRequestpb.endorsers[1].has_signer=true;
		memcpy(TxRequestpb.endorsers[1].signer.org_id,"luorg1",strlen("luorg1"));
		TxRequestpb.endorsers[1].signer.member_type=MemberType_CERT_HASH;
		TxRequestpb.endorsers[1].signer.member_info.size=32;
		memcpy(TxRequestpb.endorsers[1].signer.member_info.bytes,certhash,32);
		TxRequestpb.endorsers[1].signature.size=sig_size;
		memcpy(TxRequestpb.endorsers[1].signature.bytes,signature,sig_size);

		TxRequestpb.endorsers[2].has_signer=true;
		memcpy(TxRequestpb.endorsers[2].signer.org_id,"luorg1",strlen("luorg1"));
		TxRequestpb.endorsers[2].signer.member_type=MemberType_CERT_HASH;
		TxRequestpb.endorsers[2].signer.member_info.size=32;
		memcpy(TxRequestpb.endorsers[2].signer.member_info.bytes,certhash,32);
		TxRequestpb.endorsers[2].signature.size=sig_size;
		memcpy(TxRequestpb.endorsers[2].signature.bytes,signature,sig_size);

		TxRequestpb.has_payer=true;
		TxRequestpb.payer.has_signer=true;
		memcpy(TxRequestpb.payer.signer.org_id,str,strlen(str));
		TxRequestpb.payer.signer.member_type=MemberType_PUBLIC_KEY;
		TxRequestpb.payer.signer.member_info.size=5;
		memcpy(TxRequestpb.payer.signer.member_info.bytes,strtest,sizeof(strtest));
		TxRequestpb.payer.signature.size=sig_size1;
		memcpy(TxRequestpb.payer.signature.bytes,signature1,sizeof(signature1));

	*/
	/*  序列化Txrequest    */
	pb_ostream_t stream = pb_ostream_from_buffer(recmeg->buffer, recmeg->buffersize);
	pb_encode(&stream, TxRequest_fields, &TxRequestpb);
	message_length = stream.bytes_written;
	recmeg->messagesize=message_length;

	return 0;
}

























