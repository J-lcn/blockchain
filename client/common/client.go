



package common


import (
	
	"fmt"
	
	sdk "chainmaker.org/chainmaker/sdk-go/v2"
	
)


const (
	sdkConfigOrg1ClientPath = "../config/sdk_config.yml"
	
	
	
)


//创建客户端函数
func Client(data []byte) {
	
	defer func() {
			// 在 defer 中使用 recover 捕获 panic
			if r := recover(); r != nil {
				// 处理 panic，这里可以打印日志等
				fmt.Println("Goroutine recovered:", r)
			}
		}()




	clientlu := NewChainClientbyOption()

	fmt.Println("starting up chain: ok")
	TxRequest:=Blockchainpb(data)
	_,err:=clientlu.SendTxRequest(TxRequest, -1,true)
	if err != nil {
		fmt.Println("Error SendTxRequest:", err)
		return
	}
	fmt.Println("ending up chain: ok")
	


	
	
	


}


//创建客户端函数
func NewChainClientlu() *sdk.ChainClient {
	client, err := sdk.NewChainClient(sdk.WithConfPath(sdkConfigOrg1ClientPath))
	if err != nil {
		panic(err)
	}
	err = client.CheckNewBlockChainConfig()
	if err != nil {
		panic(err)
	}
	return client
}






//创建客户端函数
func NewChainClientbyOption() *sdk.ChainClient {
	node := sdk.NewNodeConfig(
				// 节点地址，格式：127.0.0.1:12301
				sdk.WithNodeAddr("192.168.43.88:21101"),
				
				// 节点连接数
				sdk.WithNodeConnCnt(10),
				// 节点是否启用TLS认证
				sdk.WithNodeUseTLS(true),
				// 根证书路径，支持多个
				sdk.WithNodeCAPaths([]string{"/root/lujie/blockchain/client/config/"}),
				// TLS Hostname
				sdk.WithNodeTLSHostName("chainmaker.org"),
			)
	client, err := sdk.NewChainClient(
		sdk.AddChainClientNodeConfig(node),
		sdk.WithUserKeyFilePath("/root/lujie/blockchain/client/config/TlsKey.key"),
		sdk.WithUserCrtFilePath("/root/lujie/blockchain/client/config/TlsCert.crt"),
		sdk.WithUserSignKeyFilePath("/root/lujie/blockchain/client/config/SignKey.key"),
		sdk.WithUserSignCrtFilePath("/root/lujie/blockchain/client/config/SignCert.crt"),
		sdk.WithChainClientOrgId("luorg1"),
		sdk.WithChainClientChainId("chain01"),
		sdk.WithEnableTxResultDispatcher(true),
		sdk.WithRetryLimit(20),
		sdk.WithRetryInterval(2000),
	)
	if err != nil {
		panic(err)
	}
	err = client.CheckNewBlockChainConfig()
	if err != nil {
		panic(err)
	}
	return client
}



