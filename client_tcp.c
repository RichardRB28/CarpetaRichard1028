/*Funcionamiento del codigo
Este codigo debe recolectar la información del sensor, convertirla a decimal
y enviarla a un puerto y una direccion ip, se debe confirgurar el modulo wifi, socket
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

//Funcion la cual re|cibe un dato en decimal y retorna una valor de cadena
int main(){
    //----------------  CONFIGURACION SOCKET --------------------------//  
    //unsigned char cont_1[10]="Embebidos\r\n";
    int deci=500;
    int uni=0;
    int dec=0;
    int cent=0;
    char dato_char[3];
    int sock = socket(PF_INET, SOCK_STREAM, 0);// TCP
    struct sockaddr_in server;// a donde se va a conectar
    server.sin_family = PF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // direccion ip donde se van a dirigir los datos
    server.sin_port = htons(12001);// puerto donde envia dichos datos

    //funcion connect le indica al programa que debe mandar una señal de sincronismo
    // desde esperar y recibe tres parametros, socket creado, casting, tamaño de la estructura
    // activa la conexión, si es correcta envia un numero mayor que 0
    
    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("error de conexión\r\n");
        close(sock);
        return(-1);
        }
        printf("Esp32 Conectada correctamente\r\n");

//---------------------Convertir de entero a caracter------------//   
    cent=(deci/100);
    dec=(deci-(cent*100))/10;
    uni=deci-(dec*10)-(cent*100);

     dato_char[0]= cent+48;
     dato_char[1]= dec+48;
     dato_char[2]=uni+48;
        
        if (send(sock,dato_char,sizeof(dato_char),0)<0){
        printf("No se envio el mensaje correctamente");
        }
        else{
        printf("Mensaje enviado correctamente\r\n");
        }
        
       //sleep(5);// retardo 
        close(sock);
        return(0);
}