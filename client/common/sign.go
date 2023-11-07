package common

import (
	"crypto/ecdsa"
	"crypto/elliptic"
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"math/big"
)

func Sign() {
	// 你的私钥字符串
	privateKeyHex := "e287f8b4bdbfc99d097f482b96596453eb5d52c36c104224fc6ee68edaee1dee"

	// 解码16进制私钥字符串为字节数组
	privateKeyBytes, err := hex.DecodeString(privateKeyHex)
	if err != nil {
		fmt.Println("Error decoding private key:", err)
		return
	}

	// 将私钥字节数组转换为big.Int类型
	privateKeyInt := new(big.Int).SetBytes(privateKeyBytes)

	// 生成ECDSA私钥
	privateKey := new(ecdsa.PrivateKey)
	privateKey.PublicKey.Curve = elliptic.P256() // 使用P-256曲线
	privateKey.D = privateKeyInt                   // 设置私钥整数
	privateKey.PublicKey.X, privateKey.PublicKey.Y = privateKey.PublicKey.Curve.ScalarBaseMult(privateKey.D.Bytes())

	fmt.Println("Public Key X (hex):", fmt.Sprintf("%x", privateKey.PublicKey.X.Bytes()))
	fmt.Println("Public Key Y (hex):", fmt.Sprintf("%x", privateKey.PublicKey.Y.Bytes()))

	// 选择消息
	message := "hhdfndslkfhdsafhdsjfbdfbdsftbdncfbsdkroiehwinfdjklfcmfherjkrfntwouiytr"

	// 计算消息的SHA-256哈希值
	hash := sha256.Sum256([]byte(message))

	fmt.Println("SHA-256 Hash (hex):", fmt.Sprintf("%x", hash[:]))
	fmt.Println("SHA-256 Hash Length (bytes):", len(hash))

	// 使用私钥对消息进行签名
	r, s, err := ecdsa.Sign(rand.Reader, privateKey, hash[:])
	if err != nil {
		fmt.Println("Error signing message:", err)
		return
	}

	// 打印签名的r和s值
	fmt.Println("Signature R (hex):", fmt.Sprintf("%x", r))
	fmt.Println("Signature S (hex):", fmt.Sprintf("%x", s))

	// 验证签名
	if ecdsa.Verify(&privateKey.PublicKey, hash[:], r, s) {
		fmt.Println("Signature verified successfully.")
	} else {
		fmt.Println("Failed to verify signature.")
	}
}

