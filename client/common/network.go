package common


import (
	"fmt"
	"net"
	"encoding/asn1"
	"time"
)

type Request struct {
	ServerName    string
	Buffer        []byte
}
type Response struct {
	Buffer        []byte
}
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
		
		go handleConnection(conn)
	}

	
	close(dataChan)
}

func handleConnection(conn net.Conn) {
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
		
		var Requestlu Request
		_, err = asn1.Unmarshal(receivedData, &Requestlu)
		if err != nil {
			fmt.Println("ASN.1 decoding failed:", err)
			return
		}

		
		switch Requestlu.ServerName {
		    case "blockchain":
			
			 go Client(receivedData[1:]) 
			response :=Response{
				Buffer:	[]byte("uping   blockchain"),
			}
		
			asn1response, err := asn1.Marshal(response)
			if err != nil {
				fmt.Println("ASN.1 encoding failed:", err)
				return
			}
			_, err = conn.Write(asn1response)
			if err != nil {
				fmt.Println("Error writing response:", err)
				return
			}	



		    case "genAcount":
			genresponse := GenAcount()

			response :=Response{
				Buffer:	genresponse,
			}
		
			asn1response, err := asn1.Marshal(response)
			if err != nil {
				fmt.Println("ASN.1 encoding failed:", err)
				return
			}
			_, err = conn.Write(asn1response)
			if err != nil {
				fmt.Println("Error writing response:", err)
				return
			}	

		    default:
			return
		
		}

	
	}

		fmt.Println("connect close!")

}


