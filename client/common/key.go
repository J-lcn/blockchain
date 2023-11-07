package common

import (
	//"crypto/ecdsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
	"io/ioutil"
	//"reflect"
	"strings"
)

func Parsekey() ([]byte,[]byte) {

	privateKeyFile := "/root/lujie/blockchain/client/common/SignKey.key"
	privateKeyPEM, err := ioutil.ReadFile(privateKeyFile)
	if err != nil {
		fmt.Println("Error reading private key file:", err)
		
	}

	// 解析PEM格式的私钥
	block, _ := pem.Decode(privateKeyPEM)
	if block == nil {
		fmt.Println("Error decoding PEM block")
		
	}

	// 解析DER编码的ECDSA私钥
	privateKey, err := x509.ParseECPrivateKey(block.Bytes)
	if err != nil {
		fmt.Println("Error parsing private key:", err)
		
	}

	// 获取ECDSA私钥的D值
	privateKeyD := privateKey.D.Bytes()
	
	// 构建[]byte{0x12, 0x3e, ...}格式的字符串
	var hexBytes strings.Builder
	hexBytes.WriteString("[]byte{")
	for _, b := range privateKeyD {
		hexBytes.WriteString(fmt.Sprintf("0x%02x, ", b))
	}
	hexBytes.WriteString("}")

	// 获取公钥的X和Y坐标
	publicKeyX := privateKey.PublicKey.X.Bytes()
	publicKeyY := privateKey.PublicKey.Y.Bytes()

	// 将公钥的X和Y坐标连接到同一个字节序列中
	var combinedBytes [64]byte
	copy(combinedBytes[0:32], publicKeyX[:])
	copy(combinedBytes[32:64], publicKeyY[:])
	

	// 将数组转换为切片
	publicKeyBytes := combinedBytes[:]
	
	
	return privateKeyD,publicKeyBytes


}

