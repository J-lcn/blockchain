package common

import (
	"crypto/ecdsa"
	"crypto/elliptic"
	"crypto/rand"
	"crypto/sha256"
	"fmt"
	"encoding/hex"
	"math/big"
	//"bytes"
	//"encoding/json"
)

func Genkeyp256() {
	// 选择 P-521 曲线
	curve := elliptic.P256()

	// 生成 ECDSA 密钥对
	privateKey, err := ecdsa.GenerateKey(curve, rand.Reader)
	if err != nil {
		fmt.Println("Error generating private key:", err)
		return
	}
	FormatthePrintStructure(privateKey)
	// 获取公钥的 x 和 y 坐标
	publicKeyX := privateKey.PublicKey.X.Bytes()
	publicKeyY := privateKey.PublicKey.Y.Bytes()

	// 打印私钥、公钥的 x 和 y 坐标
	fmt.Println("Private Key (hex):", fmt.Sprintf("%x", privateKey.D))
	fmt.Println("Public Key X (hex):", fmt.Sprintf("%x", publicKeyX))
	fmt.Println("Public Key Y (hex):", fmt.Sprintf("%x", publicKeyY))

	// 示例消息
	message := "hhdfndslkfhdsafhdsjfbdfbdsftbdncfbsdkroiehwinfdjklfcmfherjkrfntwouiytr"

	// 计算消息的 SHA-256 哈希值
	hash := sha256.Sum256([]byte(message))

	// 使用私钥对消息进行签名
	r, s, err := ecdsa.Sign(rand.Reader, privateKey, hash[:])
	if err != nil {
		fmt.Println("Error signing message:", err)
		return
	}

	// 打印签名的 r 和 s 值
	fmt.Println("Signature R (hex):", fmt.Sprintf("%x", r))
	fmt.Println("Signature S (hex):", fmt.Sprintf("%x", s))

	// 验证签名
	if ecdsa.Verify(&privateKey.PublicKey, hash[:], r, s) {
		fmt.Println("Signature verified successfully.")
	} else {
		fmt.Println("Failed to verify signature.")
	}
}


func GeneratepubkeybyD(privateKeyHex string) {
	// 你的私钥D值（十六进制字符串表示）

	// 将私钥D值解析为big.Int
	privateKeyBytes, err := hex.DecodeString(privateKeyHex)
	if err != nil {
		fmt.Println("Error decoding private key hex:", err)
		return
	}
	privateKey := new(big.Int).SetBytes(privateKeyBytes)

	// 使用secp256r1曲线生成ecdsa.PrivateKey
	curve := elliptic.P256()
	x, y := curve.ScalarBaseMult(privateKey.Bytes())
	publicKey := ecdsa.PublicKey{
		Curve: curve,
		X:     x,
		Y:     y,
	}

	// 打印生成的ECC公钥
	fmt.Println("Generated ECC Public Key:")
	fmt.Printf("X: %x\n", publicKey.X)
	fmt.Printf("Y: %x\n", publicKey.Y)
}





