//https://youtu.be/KeovjkiH5pk video


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include "lcd.h"

#pragma config FOSC = HS//Oscilador externo HS High speed 8 Mhrz
#pragma config WDTE = OFF 
#pragma config PWRTE = OFF 
#pragma config MCLRE = ON
#pragma config CP = OFF 
#pragma config CPD = OFF 
#pragma config BOREN = OFF 
#pragma config IESO = OFF//Arranca con el oscilador interno y luego pasa al externo
#pragma config FCMEN = OFF
#pragma config LVP = OFF 
#pragma config DEBUG = OFF 
 
#define _XTAL_FREQ 8000000         //cristal osciliador

//------------------------------CONFIGURANDO RELOJ, V REFERENCIA------------------------//
void Inicializar_ADC()
{
    ADCON0 = 0x81;                  //configurar canales Fosc/32 y BIT0(Habilitado conv A/D)
    ADCON1 = 0X80;                  //seleccion voltaje de referencia vcc y tierra , justificado a la izquierda
}
//-------------------------CONFIGURANDO CANAL--------------------------//
unsigned int Leer_ADC(unsigned char canal)
{
                                    //14 canales o pines que pueden ser usados como entrada analogica
    if(canal > 13)                  //si canal es mayor que 13 retornar 0
        return 0;
    
    ADCON0 &= 0xC5;                  //limpiar la seleccion de los bits OPERACION OR  
    ADCON0 |=canal<<2;              // se establecen los bits CHS3,CHS2,CHS1 Y CHS0 OPERACION AND     
    __delay_ms(2);                   //tiempo de adquisicion
   
    GO_nDONE = 1;                    //inicializar la conversion ADC
    while(GO_nDONE);                 //esperar a que la conversion se complete
     return ((ADRESH<<8)+ADRESL); //retornar resultado
}

int main ( void ){
    
    unsigned int num_ADC_ingreso=0; 
    int uni=0;
    int dec=0;
    int cent=0;
    int temp_max=0;
    int temp_min=0;
    char dato_char[3];
    float conv=0.0;
    int conv_int=0;
 
    //------------------------------Configuracion de registros por puertos--------------------// 
    PORTD=0x00;
    TRISD=0xBF;        
 
    
    PORTA  = 0x00;                  // inician en 0 v 
    TRISA  = 0x01;                  //1 entrada pin Y 0 SALIDA puerto A
    ANSEL  = 0x01;                  //ANALOGO PIN 0 PUERTO A
  
    

    LCD lcd = { &PORTC, 1, 2, 3, 4, 5, 6}; // PORT, RS, EN, D4, D5, D6, D7
        
                  
     //while(1){                 
    
    Inicializar_ADC();              //inicializando conv a/d
    LCD_Init(lcd);                  //inicializando LCD
    LCD_Clear();                    //limpiar lcd
 //-----------------------------------------Boton encendido----------------------------//   
      
    
    if(RD7==1){
    __delay_ms(10);
   if(RD7==1){
  
     
       LCD_Set_Cursor(0,0);
     LCD_putrs("Bienvenido"); 
     LCD_Set_Cursor(1,0);
   __delay_ms(1000);
    LCD_Clear();
    
    
        LCD_Set_Cursor(0,0);
        LCD_putrs("Escoja nivel de"); 
       LCD_Set_Cursor(1,0);
        LCD_putrs("coccion");
        __delay_ms(2000);
        LCD_Clear();
        
        
        LCD_Set_Cursor(0,0);
        LCD_putrs("Temperatura:"); 
        LCD_Set_Cursor(1,0);
        LCD_putrs("coccion:"); 
        

    //-------------------------------CONFIGURANDO BOTONES DE SELECCION DE COCCION---------------------//
     /*Bucle 1 mientras nose presione ningun bottón de seleccion de temperatura y se acepte
      el valor, no continuará con el siguiente bucle
      */ 
        RD6=0; 
       while(1){      
     
     if(RD0==1){
    __delay_ms(10);
    if(RD0==1){ 
    LCD_Set_Cursor(1,8);
    LCD_putrs("blue    ");
    temp_max=38;;
    temp_min=26;
    
    }
       }
                
  
     if(RD1==1){
    __delay_ms(10);
    if(RD1==1){
        LCD_Set_Cursor(1,8);
        LCD_putrs("rare    ");
        temp_max=51;
        temp_min=49;
        
        
     }
       }
 
     if(RD2==1){
        __delay_ms(10);
        if(RD2==1){
        LCD_Set_Cursor(1,8);
         LCD_putrs("Med.Rare");
        temp_max=57;
        temp_min=55;
        
        }
     }
          
    if(RD3==1){
        __delay_ms(10);
        if(RD3==1){
        LCD_Set_Cursor(1,8);
          LCD_putrs("Medium   ");
        temp_max=63;
        temp_min=60;
        
        }
    }
          
    if(RD4==1){
        __delay_ms(10);
        if(RD4==1){
        LCD_Set_Cursor(1,8);
        LCD_putrs("Med.well");
        temp_max=69;
        temp_min=65;
        
        }
    }
          
    if(RD5==1){
        __delay_ms(10);
        if(RD5==1){
        LCD_Set_Cursor(1,8);
        LCD_putrs("Welldone");
        temp_max=71;
        temp_min=70;
       
        }
    }
     
     if(RD7==1){
         __delay_ms(10);
         if(RD7==1){
             break;
        }
     }
     
     }//cierre while 1 
 
        
        while(1){
        /*
         Bucle numero 2: 
        
        - despues de seleccionar el grado de coccion inicializa el conversor y hace el porcedimiento respectivo 
        hasta que se cuempla la condicion de la temperatura maxima
        
        - num_ADC es el valor que por defecto escoge el conversor 2 elevado a la 10 es 1024 de 0 a 1023
       luego convertiremos de ese dato a numero entero para poder operarlo en la lcd y en los condicionales
       de rangos de temperatura
       */     
           
     
        //------------------LEER TEMPERATURA Y CONVERTIRLA DECIMAL-----------------------------//   
        num_ADC_ingreso = Leer_ADC(0);//LEER EL CANAL 0  EN  ADC
        conv=(0.489*num_ADC_ingreso);//0.488----------CONV DECIMAL
        conv_int=conv;num_ADC_ingreso 
        
   
  //---------------------CONVERTIR A UNIDADES, DECENAS Y CENTENAS---------------------------------//  
                cent=(conv_int/100);
                dec=(conv_int -(cent*100))/10;
                uni=conv_int -(dec*10)-(cent*100);
                
                dato_char[0]= cent+48;
                dato_char[1]= dec+48;
                dato_char[2]=uni+48;
               
                LCD_Set_Cursor(0,13);
                LCD_putrs(dato_char);
                        
//-------------------------CONDICIONES PARA CONTROLAR LOS RANGOS DE TEMPERATURA------------------------//          
                  
                
                if(conv_int<temp_min){
                    RD6=0;
                    }
                
                 if(conv_int>=temp_min && conv_int<=temp_max){
                   RD6=1;
                   __delay_ms(1000);
                   RD6=0;
                   __delay_ms(500);
                   }
                  
                if(conv_int>temp_max){
                    RD6=1;
                    __delay_ms(10000);
                    break;
                   }
                
                 
                
         
        } //cierre while 2   
          

   }   
    }    
       
    else{
    LCD_Set_Cursor(1,0);
    LCD_putrs("OFF DEVICE..."); 

   }
//}

}//CIERRE MAIN
               