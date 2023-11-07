

package common
import (
	"fmt"
	"net"
	//"encoding/binary"
	//"strconv"
	"time"
	// 其他需要的包...
)



func RunServer(dataChan chan<- []byte,ipport string) {
	listener, err := net.Listen("tcp", ipport)
	if err != nil {
		fmt.Println("Error listening:", err)
		close(dataChan)
		return
	}
	defer listener.Close()

	fmt.Println("Server listening on ",ipport)

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("Error accepting connection:", err)
			close(dataChan)
			return
		}
		
		remoteAddr := conn.RemoteAddr().String()
		fmt.Println("Accepted connection from:", remoteAddr)
		go handleConnection(conn, dataChan)
	}

	// 当所有连接处理完成后，关闭通道
	close(dataChan)
}

func handleConnection(conn net.Conn, dataChan chan<- []byte) {
	defer conn.Close()
	




	// 启用Keep-Alive功能
	tcpConn, ok := conn.(*net.TCPConn)
	if !ok {
		fmt.Println("Error: Not a TCP connection")
		return
	}

	err := tcpConn.SetKeepAlive(true)
	if err != nil {
		fmt.Println("Error setting Keep-Alive:", err)
		return
	}

	// 设置Keep-Alive探测包的发送间隔（可选）
	err = tcpConn.SetKeepAlivePeriod(time.Second * 30) // 设置间隔为30秒
	if err != nil {
		fmt.Println("Error setting Keep-Alive period:", err)
		return
	}



	buffer := make([]byte, 1024)
	for{
	datasize, err := conn.Read(buffer)
	if err != nil {
		fmt.Println("Error reading:", err)
		
		return
	}

	receivedData := buffer[:datasize]

	flag:=receivedData[0]


	switch flag {
	    case 0:
		
		 go Client(receivedData[1:]) 
		response :=[]byte("blockchain: ok")
		fmt.Println(response)
		_, err = conn.Write(response)
		if err != nil {
			fmt.Println("Error writing response:", err)
			
			return
		}	



	    case 1:
		response := GenAcount()
		fmt.Println("GenAccount: ok")
		_, err = conn.Write(response)
		if err != nil {
			fmt.Println("Error writing response:", err)
			
			return
		}
	    case 3:
		dataChan <- receivedData
	    default:
		return
        
	}

	
}

		fmt.Println("connect close!")

}


