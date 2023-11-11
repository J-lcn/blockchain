package common

import (
	//"fmt"
	"chainmaker.org/chainmaker/pb-go/v2/common"
	//pb"github.com/J-lcn/blockchain/pb"
	"github.com/golang/protobuf/proto"
	//"encoding/json"
	//"bytes"
	"log"
)

func Blockchainpb(data []byte) *common.TxRequest{

	// 反序列化操作
	newPerson := &common.TxRequest{}

	

	err := proto.Unmarshal(data, newPerson)
	if err != nil {
		log.Fatal("unmarshaling error: ", err)
	}

	
	return newPerson
	
}

