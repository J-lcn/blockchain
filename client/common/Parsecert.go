package common

import (
	"crypto/x509"
	//"encoding/base64"
	"encoding/pem"
	//"crypto/ecdsa"
	"crypto/sha256"
	"fmt"
	//"encoding/hex"
	"os"
	//"math/big"
	//"strings"
)

func Parsecertrethash()[32]byte {
	// 读取证书文件
	certFile, err := os.ReadFile("/root/lujie/blockchain/client/common/SignCert.crt")
	if err != nil {
		fmt.Println("Error parsing certFile:", err)
		
	}
	//return certFile


	if err != nil {
		fmt.Println("Error reading certificate file:", err)
		
	}
	// 解码证书
	block, _ := pem.Decode(certFile)
	if block == nil {
		fmt.Println("Failed to parse certificate")
		
	}
	// 解析X.509证书
	cert, err := x509.ParseCertificate(block.Bytes)
	if err != nil {
		fmt.Println("Error parsing certificate:", err)
		
	}
	hash := sha256.Sum256(cert.Raw)
	return hash


}

