/*
crear socket:
debido a que el comando nos retorna un numero entero inicializaremos de la siguiente forma
int nombe=socket(protocol_family,type,protocolo-0)
PF_INET= fijo

type
SOCK_STREAM TCP
SOCK_DGRAM  UDP

protocol-0=fijo

direccion de retorno o loop back 127.0.0.1 usar nuestro equipo para pruebas
htons transforma el numero del puerto que es un entero al numero aceptado por internet
1 creamos el socket
2 creamos estructura tipo sock addres in
3 llenamos los campos, protocolo, ip, puerto

conectamos:
connect(socket(creado_funcion),(struct sockaddr*)&server(estructura_creada),sizeof(server(estructura_creada)))
(struct sockaddr*)----> la usamos para convertir del formato sockaddr a sockaddr_in, se hace un casting
convertir un tipo de dato a otro

si la conexion da un numero mayor que cero significa que fue correcta
sino significa que no hubo conexion exitosa

send(nombre_socket,mensaje a enviar,tamañodelmensaje,flag=0)
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>//libreria para el retardo
//----------------configuramos hacia donde queremos enviar la información cliente-----------------------------//
int main(){
unsigned char msj[]="ESP32 enlazada\r\n";
unsigned char recib[20];

int sock=socket(PF_INET,SOCK_STREAM,0);//nombre del socket

struct sockaddr_in server;//estructura tipo sockaddr_in nombre
server.sin_family=PF_INET;//settear protocolo
server.sin_addr.s_addr=inet_addr("127.0.0.1");// trasforma la dirección ip a entero que sera usado en la estructura
server.sin_port=htons(12000);//escucha por el puerto 12000

if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0){

    printf("Error de conexion\n\r");
    close(sock);// cerramos el socket para evitar usar recurso de la maquina
    return(-1);
    }
    
    printf("ESP32 enlazada\n\r");
    //while(1){
    send(sock,msj,sizeof(msj),0);
    //x=read(sock,recib,sizeof(recib),0);// 
    //sleep(5);//segundos
    //}
    //printf("%s",x);
    close(sock);
    return(0);}