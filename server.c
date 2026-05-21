#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef struct {

}sockaddr;
int main(){
    int server_socket , client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];

    server_socket=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));
    listen(server_socket,5);
    printf("Server is listening on port 8080...\n");
    addr_size=sizeof(client_addr);
        client_socket=accept(server_socket,(struct sockaddr*)&client_addr,&addr_size);
        printf("Client connected: %s\n",inet_ntoa(client_addr.sin_addr));
    while(1){
        recv(client_socket,buffer,sizeof(buffer),0);
        printf("Received message: %s\n",buffer);
    }
    close(client_socket);   
    exit(0);
}
