package common
import (
	"crypto/ecdsa"
	"crypto/elliptic"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"math/big"
)

func verifySignature(publicKeyX, publicKeyY, r, s string, message string) bool {
	// 解码16进制字符串为字节数组
	publicKeyXBytes, _ := hex.DecodeString(publicKeyX)
	publicKeyYBytes, _ := hex.DecodeString(publicKeyY)
	rBytes, _ := hex.DecodeString(r)
	sBytes, _ := hex.DecodeString(s)
	messageBytes := []byte(message)

	// 将字节数组转换为大整数
	publicKeyXInt := new(big.Int).SetBytes(publicKeyXBytes)
	publicKeyYInt := new(big.Int).SetBytes(publicKeyYBytes)
	rInt := new(big.Int).SetBytes(rBytes)
	sInt := new(big.Int).SetBytes(sBytes)

	// 使用 secp256r1 曲线
	curve := elliptic.P256()

	// 设置公钥
	publicKey := &ecdsa.PublicKey{
		Curve: curve,
		X:     publicKeyXInt,
		Y:     publicKeyYInt,
	}

	// 计算消息的哈希值
	msgHash := sha256.Sum256(messageBytes)

	// 使用公钥、消息哈希、r 和 s 验证签名
	return ecdsa.Verify(publicKey, msgHash[:], rInt, sInt)
}

func Verify() {
	// 替换以下16进制字符串为实际的公钥、r 和 s 值
	publicKeyX := "850e469481c2791b9ce944427c46bb78d4c7358317255cef4d63fc932ed6f105" // 公钥的X坐标16进制字符串
	publicKeyY := "3586d3adaa3551d8c668ab1e279818853d6f027204b00d8a5b836de9314267e2" // 公钥的Y坐标16进制字符串
	r := "d7d01c188a0e73e53cc24614cbfa6c3ae7883922a859dabe8246f48e515da7f6"          // 签名的r值16进制字符串
	s := "54715740993ac536a9cf5062ffc69153ab0ee315748aeca701539fe0a1dc958c"          // 签名的s值16进制字符串

	// 替换以下消息为实际的消息
	message :=[]byte{
			0x0a, 0x07, 0x63, 0x68, 0x61, 0x69, 0x6e, 0x30, 0x31, 0x1a, 0x20, 0x31, 0x37, 0x38, 0x65, 0x32, 0x63, 0x36, 0x39, 0x38, 0x32, 0x63, 0x64, 0x66, 0x32, 0x64, 0x31, 0x63, 0x61, 0x31, 0x37, 0x36, 0x62, 0x39, 0x62, 0x39, 0x66, 0x38, 0x65, 0x65, 0x65, 0x64, 0x30, 0x20, 0x14, 0x32, 0x08, 0x65, 0x76, 0x69, 0x64, 0x65, 0x6e, 0x63, 0x65, 0x3a, 0x08, 0x45, 0x76, 0x69, 0x64, 0x65, 0x6e, 0x63, 0x65, 0x42, 0x12, 0x0a, 0x09, 0x66, 0x69, 0x6c, 0x65, 0x5f, 0x68, 0x61, 0x73, 0x68, 0x12, 0x05, 0x74, 0x65, 0x73, 0x74, 0x31}
	messageStr := string(message)
	// 验证签名
	if verifySignature(publicKeyX, publicKeyY, r, s, messageStr) {
		fmt.Println("Signature is valid.")
	} else {
		fmt.Println("Signature is invalid.")
	}
}

