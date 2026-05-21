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

    client_socket=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
    server_addr.sin_addr.s_addr=inet_addr("192.168.1.101");
    connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));
    printf("Connected to server...\n");
    while(1){
        printf("Enter a message to send to the server: ");
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
        send(client_socket,buffer,sizeof(buffer),0);
        printf("Message sent to server: %s\n",buffer);
    }
    printf("Enter a message to send to the server: ");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
    send(client_socket,buffer,sizeof(buffer),0);
    printf("Message sent to server: %s\n",buffer);
    close(client_socket);
    exit(0);
}
