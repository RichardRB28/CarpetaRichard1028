// SE HACE EN C, recibe un numero el cual es equivalente a la temperatura
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

int main(){
    char buffer[3]={0};
    int descriptor;
    struct sockaddr_in server;
    struct sockaddr client;
    //-------------creamos el socket---------------// 
    //Retorna numero identificador del socket
    int sock = socket(PF_INET, SOCK_STREAM, 0);// PF_INET-->PROTOCOLO    SOCK_STREAM---> TCP
    int sock_client;// identificador del socket cliente
    
    server.sin_family = PF_INET;
    server.sin_addr.s_addr = INADDR_ANY;// Cualquier cliente se puede conectar 
    server.sin_port = htons(12001); //puerto de escucha
    
    bind(sock, (struct sockaddr*)&server, sizeof(server));
    listen(sock, 1); // escucha en el socket 
    printf("esperando conexiones...\r\n");
    sock_client = accept(sock, &client, &descriptor);
    
    if(recv(sock_client,buffer, sizeof(buffer),0)>0){
    printf("Mensaje No fue recibido");
    }
    printf("Mensaje recibido");
    printf("%s%n",buffer);
    memset(buffer, 0, sizeof(buffer));
    printf("Cliente conectado\r\n");
    close(sock);
    return(0);
}