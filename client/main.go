/*
Copyright (C) BABEC. All rights reserved.
Copyright (C) THL A29 Limited, a Tencent company. All rights reserved.

SPDX-License-Identifier: Apache-2.0
*/

package main

import (
	lcc"github.com/J-lcn/blockchain/common"
	"fmt"
	
	//"log"
)



func main() {

	

	

	fmt.Println("Program start")
	
	

	dataChan := make(chan []byte)
	ipport:="192.168.43.88:8839"
	// 启动服务器在一个新的goroutine中异步执行
	go lcc.RunServer(dataChan,ipport)
	// 主goroutine中的其他代码，可以继续执行其他逻辑

	// 等待接收数据
	
	data, ok := <-dataChan
	if !ok {
		fmt.Println(data)
		fmt.Println("Program end")
		} 
		
	fmt.Println(data)


	

	
}



