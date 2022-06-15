#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

xQueueHandle cola;

typedef struct main
{
	char task;
	char dato;
} pkt;


void Delay_ms(int ms){
	vTaskDelay(ms/portTICK_PERIOD_MS);
}

void task1(){
	pkt dato1;
	dato1.dato = 1;
	dato1.task = 1;
	while(1){
		if(xQueueSend(cola, &dato1, 0))printf("Dato 1 desde task 1 OK\r\n"); else printf("ERR 1\r\n");
		Delay_ms(1000);
		dato1.dato++;
	}
}

void task2(){
	pkt dato1;
	dato1.dato = 10;
	dato1.task = 2;
	while(1){
		if(xQueueSend(cola, &dato1, 0))printf("Dato desde task 2 OK\r\n"); else printf("ERR 1\r\n");
		Delay_ms(1000);
		dato1.dato++;
	}
}

void task3(){
	pkt dato_rec;
	while(1){
		xQueueReceive(cola, &dato_rec , portMAX_DELAY);
		printf("dato recibido %d desde task:%d\r\n", dato_rec.dato, dato_rec.task);
	}
}

void app_main()
{
	cola = xQueueCreate(3, sizeof(pkt));
	xTaskCreate(task1, "task1", 2000, NULL, 2, NULL);
	xTaskCreate(task2, "task2", 2000, NULL, 2, NULL);
	xTaskCreate(task3, "task3", 2000, NULL, 3, NULL);
}