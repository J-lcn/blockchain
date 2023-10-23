
#include "blockchainpb.h"
#include "app_main.h"















int blockchainpb(void * srcdata,uint32_t srcdatasize, char *srcdataname, uint32_t srcdatanamesize, char *enckey, 
					const uint8_t *prikey, uint32_t prikey_len, uint8_t *buffer, uint32_t buffersize, 
							uint32_t *messagesize, char *tx_idparm, uint32_t tx_idsize, int64_t  timestampparm,char *idp,uint32_t idpsize) {
    	

	/*       初始化                   */
    	pb_size_t message_length;
	
	uint32_t encdatasize=0;
	char encdata[40]={0};
	
	
	/*       加密                   */
	blockchainencrypt(enckey, srcdata, (void *)encdata, srcdatasize, &encdatasize);
	
	TxRequest TxRequestpb=TxRequest_init_zero;
	TxRequestpb.has_payload=true;
	/*       构造交易体                   */
	Payload payloadpb=Payload_init_zero;
	memcpy(payloadpb.chain_id,"chain01",strlen("chain01"));
	payloadpb.tx_type=TxType_INVOKE_CONTRACT;
	memcpy(payloadpb.tx_id,tx_idparm,tx_idsize);
	
	
	payloadpb.timestamp=timestampparm;
	//payloadpb.expiration_time=2000;
	memcpy(payloadpb.contract_name,"evidence",strlen("evidence"));
	memcpy(payloadpb.method,"Evidence",strlen("Evidence"));

	payloadpb.parameters_count=3;

	memcpy(payloadpb.parameters[0].key,"id",strlen("id"));
	payloadpb.parameters[0].value.size=idpsize;
	memcpy(payloadpb.parameters[0].value.bytes,idp,idpsize);



	uint8_t chainhash[32];
	memset(chainhash,0,32);
	uint32_t chainhash_size=0;
	blockchainECChash((const void *)payloadpb.tx_id,tx_idsize,(void *)chainhash,&chainhash_size);


	char* hexchainhash = (char*)malloc(32);
	for (int i = 0; i < 16; ++i) {
        sprintf(hexchainhash + 2 * i, "%02X", chainhash[i]);
   	 }
	
	


	memcpy(payloadpb.parameters[1].key,"hash",strlen("hash"));
	payloadpb.parameters[1].value.size=chainhash_size;
	memcpy(payloadpb.parameters[1].value.bytes,hexchainhash,chainhash_size);

	memcpy(payloadpb.parameters[2].key,"metadata",strlen("metadata"));
	payloadpb.parameters[2].value.size=17;
	memcpy(payloadpb.parameters[2].value.bytes,"{\"Tempment\":\"33\"}",17);

	payloadpb.sequence=21;
	payloadpb.has_limit=true;
	payloadpb.limit.gas_limit=3998897866;

	

	/*       序列化交易体                   */


	pb_ostream_t payloadlu = pb_ostream_from_buffer(buffer, buffersize);
	pb_encode(&payloadlu, Payload_fields, &payloadpb);
        message_length = payloadlu.bytes_written;


	/*       交易体签名                   */


	printf("Payloadsize:%d\n",message_length);
	printf("Payload:\n");
	for(int i=0;i<message_length;i++){
	printf("0x%02x, ",buffer[i]);
	}
	printf("\n");
	printf("Payload:\n");
	uint8_t signature[64]={0};
	uint8_t R[32]={0};
	uint8_t S[32]={0};
	uint32_t sig_size=0;	
	blockchainECCsign(prikey, prikey_len,(const void *)buffer, message_length, signature, &sig_size);
	memcpy(R, signature, 32);
	memcpy(S, signature+32, 32);
	
	//////////////////////////////////////////////
	printf("R:\n");
	for(int i=0;i<32;i++){
	printf("%02x",R[i]);
	}
	printf("\n");
	printf("S:\n");
	for(int i=0;i<32;i++){
	printf("%02x",S[i]);
	}
	printf("\n");
	printf("sig_size:%d\n",sig_size);
	printf("signature:\n");
	for(int i=0;i<sig_size;i++){
	printf("%02x",signature[i]);
	}
	printf("\n");
	printf("sig_size:%d\n",sig_size);
	printf("signature:\n");
	for(int i=0;i<sig_size;i++){
	printf("0x%02x, ",signature[i]);
	}
	printf("\n");
	//////////////////////////////////////////////
	
		/*       构造请求其他成员                   */



	unsigned char derbuffer[200]={0};
	uint32_t derbuffersize=200;
	unsigned char *dersignature=NULL;
	uint32_t dersignaturesize=0;
	DerencodeSig(signature, sig_size, derbuffer, derbuffersize, &dersignature, &dersignaturesize);

	
	//////////////////////
	printf("dersignaturesize:%d\n",dersignaturesize);
	printf("dersignature:\n");
	for(int i=0;i<dersignaturesize;i++){
	printf("%02x",dersignature[i]);
	}
	printf("\n");
	///////////////////////////

	uint8_t certhash[32]={183,251,49,202,40,188,135,2,163,146,14,85,56,198,205,4,3,138,113,154,70,90,234,36,6,201,99,248,188,13,55,226};

	TxRequestpb.payload=payloadpb;
	TxRequestpb.has_sender=true;
	TxRequestpb.sender.has_signer=true;
	memcpy(TxRequestpb.sender.signer.org_id,"luorg1",strlen("luorg1"));
	TxRequestpb.sender.signer.member_type=MemberType_CERT_HASH;
	TxRequestpb.sender.signer.member_info.size=32;
	memcpy(TxRequestpb.sender.signer.member_info.bytes,certhash,32);
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

	pb_ostream_t stream = pb_ostream_from_buffer(buffer, buffersize);
	pb_encode(&stream, TxRequest_fields, &TxRequestpb);
        message_length = stream.bytes_written;
	*messagesize=message_length;
	
	return 0;
}



























