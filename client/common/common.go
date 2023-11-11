


package common


import (
	"bytes"
	"fmt"
	"encoding/json"
	"crypto/sha256"
	"encoding/hex"
	
)





//格式化打印结构体函数
func FormatthePrintStructure(structure interface{}) {
	fmt.Printf("*******************开始打印相关信息**********************************************************************************************\n")
	//	structVal := reflect.ValueOf(structure)
	bs, _ := json.Marshal(structure)
	var out bytes.Buffer
	json.Indent(&out, bs, "", "\t")
	fmt.Printf("Info:%+v\n", out.String())
	fmt.Printf("*******************结束打印**********************************************************************************************\n")

}


func Hash256(src []byte) {
	

	// 计算SHA-256哈希值
	hash := sha256.New()
	hash.Write(src)
	hashInBytes := hash.Sum(nil)
	// 将哈希值转换为十六进制字符串
	hashString := hex.EncodeToString(hashInBytes)

	// 打印SHA-256哈希值
	fmt.Println("SHA-256哈希值：", hashString)
}



func GenAcount() []byte {
	

	pri,pub := Parsekey()
	certhash:=Parsecertrethash()
	var combinedBytes [128]byte
	copy(combinedBytes[0:32], pri[:])
	copy(combinedBytes[32:96], pub[:])
	copy(combinedBytes[96:128], certhash[:])

	// 将数组转换为切片
	acountBytes := combinedBytes[:]
	
	

	
	return acountBytes


}






