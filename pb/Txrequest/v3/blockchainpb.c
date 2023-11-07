



#include "blockchainpb.h"

int blockchainpb(void * data,uint32_t datasize) {

 
    uint8_t buffer[1280];
	memcpy(buffer,0,1280);
    pb_size_t message_length;
    bool status;

    
   
    {
        
        //pb_byte_t bytesPayload[10]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	KeyValuePair_value_t KeyValuePair_Value_tPayload={
	.size = 10,
	.bytes ={1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	};

	//KeyValuePair_Value_tPayload.size=10;
	//memcpy(KeyValuePair_Value_tPayload.bytes, bytesPayload, sizeof(bytesPayload));
	//KeyValuePair_Value_tPayload.bytes=bytesPayload;



	char ParameterspbString[] = "Key-Value"; // 声明一个字符串
	KeyValuePair Parameterspb=KeyValuePair_init_zero;
	memcpy(Parameterspb.key, ParameterspbString,strlen(ParameterspbString));
	//Parameterspb.Key="Key-Value";
	Parameterspb.value=KeyValuePair_Value_tPayload;

	

	Limit LimitPayload=Limit_init_zero;
	LimitPayload.gas_limit=1000;


	char ChainIdString[] = "Ch";
	char TxIdString[] = "TxIdpb";
	char ContractNameString[] = "ContrName";
	char MethodpbString[] = "Methodpb";

	Payload Payloadpb=Payload_init_zero;
	//Payloadpb.ChainId={'a','b'};
	memcpy(Payloadpb.chain_id,TxIdString,strlen(TxIdString));

	//Payloadpb.ChainId="ChainIdpb";
	Payloadpb.tx_type=21;

	memcpy(Payloadpb.tx_id, TxIdString,strlen(TxIdString));
	//Payloadpb.TxId="TxIdpb";
	Payloadpb.timestamp=12;
	Payloadpb.expiration_time=13;
	memcpy(Payloadpb.contract_name, ContractNameString,strlen(ContractNameString));
	//Payloadpb.ContractName="ContrName";
	memcpy(Payloadpb.method, MethodpbString,strlen(MethodpbString));
	//Payloadpb.Method="Methodpb";
	Payloadpb.parameters_count=1;

	Payloadpb.parameters[0]=Parameterspb;
	Payloadpb.sequence=14;
	Payloadpb.has_limit=true;
	Payloadpb.limit=LimitPayload;





	Member_member_info_t Member_member_info_tSender={\
	.size = 10,
	.bytes ={1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	};
	EndorsementEntry_signature_t EndorsementEntry_signature_tSender={\
	.size = 10,
	.bytes ={1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	};
	char SignerSenderString[] = "OrgId";
	Member SignerSender=Member_init_zero;
	memcpy(SignerSender.org_id, SignerSenderString,strlen(SignerSenderString));
	//SignerSender.OrgId="OrgId";
	SignerSender.member_type=2;
	SignerSender.member_info=Member_member_info_tSender;

	EndorsementEntry Senderpb=EndorsementEntry_init_zero;
	Senderpb.has_signer=true;
	Senderpb.signer=SignerSender;
	Senderpb.signature=EndorsementEntry_signature_tSender;


	////////////////////////
	char SignerEndorsers3String[] = "OrgId";
	Member SignerEndorsers3=Member_init_zero;
	memcpy(SignerEndorsers3.org_id, SignerEndorsers3String,strlen(SignerEndorsers3String));
	//SignerEndorsers3.OrgId="OrgId";
	SignerEndorsers3.member_type=2;
	SignerEndorsers3.member_info=Member_member_info_tSender;

	EndorsementEntry Endorsers3pb=EndorsementEntry_init_zero;
	Endorsers3pb.has_signer=true;
	Endorsers3pb.signer=SignerEndorsers3;
	Endorsers3pb.signature=EndorsementEntry_signature_tSender;

	///////////////////////////


	Member SignerEndorsers2=Member_init_zero;
	memcpy(SignerEndorsers2.org_id, SignerEndorsers3String,strlen(SignerEndorsers3String));
	//SignerEndorsers2.OrgId="OrgId";
	SignerEndorsers2.member_type=2;
	SignerEndorsers2.member_info=Member_member_info_tSender;

	EndorsementEntry Endorsers2pb=EndorsementEntry_init_zero;
	Endorsers2pb.has_signer=true;
	Endorsers2pb.signer=SignerEndorsers2;
	Endorsers2pb.signature=EndorsementEntry_signature_tSender;

	////////////////////////////////////


	Member SignerEndorsers1=Member_init_zero;
	memcpy(SignerEndorsers1.org_id, SignerEndorsers3String,strlen(SignerEndorsers3String));
	//SignerEndorsers1.OrgId="OrgId";
	SignerEndorsers1.member_type=2;
	SignerEndorsers1.member_info=Member_member_info_tSender;

	EndorsementEntry Endorsers1pb=EndorsementEntry_init_zero;
	Endorsers1pb.has_signer=true;
	Endorsers1pb.signer=SignerEndorsers1;
	Endorsers1pb.signature=EndorsementEntry_signature_tSender;

	Member SignerPayer=Member_init_zero;
	memcpy(SignerPayer.org_id, SignerEndorsers3String,strlen(SignerEndorsers3String));
	
	SignerPayer.member_type=2;
	SignerPayer.member_info=Member_member_info_tSender;

	EndorsementEntry Payerpb=EndorsementEntry_init_zero;
	Payerpb.has_signer=true;
	Payerpb.signer=SignerPayer;
	Payerpb.signature=EndorsementEntry_signature_tSender;


	TxRequest TxRequestpb=TxRequest_init_zero;
	TxRequestpb.has_payload=true;
	TxRequestpb.payload=Payloadpb;
	TxRequestpb.has_sender=true;
	TxRequestpb.sender=Senderpb;
	TxRequestpb.endorsers_count=3;

	TxRequestpb.endorsers[0]=Endorsers1pb;
	//memcpy(&TxRequestpb.endorsers[0], &Endorsers1pb,sizeof(Endorsers1pb));

	TxRequestpb.endorsers[1]=Endorsers2pb;
	TxRequestpb.endorsers[2]=Endorsers3pb;
	TxRequestpb.has_payer=true;

	TxRequestpb.payer=Payerpb;
        

        
        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
        
        
        status = pb_encode(&stream, KeyValuePair_fields, &KeyValuePair_Value_tPayload);
        //message_length = stream.bytes_written;
        
       //printf("status:%d\n",status);

    

    }
    
    
    
    {
/*
       
        TxRequest message = TxRequest_init_zero;
       
        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);
        
        
        status = pb_decode(&stream, TxRequest_fields, &message);
        

*/
       
	printf("Your lucky number was!\n");
        //printf("Your lucky number was %d!\n", (int32_t)message.payload.tx_type);
    }
return 0;
}

