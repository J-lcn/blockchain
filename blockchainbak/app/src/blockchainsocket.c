




#include"blockchainsocket.h"



void blockchainsend(char *src_host,char * src_port,char *des_host,char * des_port,void *datain,uint32_t datasize){


    char *deshost = des_host;
    int desport = atoi(des_port);


    int srcport = atoi(src_port);
    int _socket=socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(srcport);
    const char *src=src_host;
    in_addr_t dst;
    inet_pton(AF_INET,src,&dst);
    addr.sin_addr.s_addr=dst;
    
    socklen_t addrlen=sizeof(addr);
    bind(_socket,(struct sockaddr *)&addr,addrlen);
    
    struct sockaddr_in addrserver;
    addrserver.sin_family=AF_INET;
    addrserver.sin_port=htons(desport);
    addrserver.sin_addr.s_addr=inet_addr(deshost);
    socklen_t addrlenserver=sizeof(addrserver);
    connect(_socket,(struct sockaddr *)&addrserver,addrlenserver);
    
    const char *data=(const char *)datain;
    send(_socket,data,datasize,0);
    
    char mem[50];
    read(_socket,mem,sizeof(mem));
    printf(mem);
    close(_socket);
   
    

}


























