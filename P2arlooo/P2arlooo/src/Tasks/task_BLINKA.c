/*
* task_BLINKA.c
*
* Created: 2017-04-15 13:03:31
*  Author: Elias Hussein
*/
#include <asf.h>
#include "task_BLINKA.h"

#define Blinkared PIO_PB26_IDX
#define Blinkayellow PIO_PA14_IDX
void task_BLINKA(void *pvParameters)
{
	xSemaphoreHandle signal_semafor = 0;
	signal_semafor = xSemaphoreCreateMutex();
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 100;
	xLastWakeTime = xTaskGetTickCount(); /* Initialise the xLastWakeTime variable with the current time. */
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /*Wait for the next cycle. */
		if(xSemaphoreTake(signal_semafor,1000)){
			ioport_set_pin_level(Blinkared,HIGH);
			delayMicroseconds(100000);
			ioport_set_pin_level(Blinkared,LOW);
			delayMicroseconds(100000);
			ioport_set_pin_level(Blinkayellow,HIGH);
			delayMicroseconds(100000);
			ioport_set_pin_level(Blinkayellow,LOW);
			delayMicroseconds(100000);
			xSemaphoreGive(signal_semafor);
		}
		else{
			printf("Failed");
		}
		vTaskDelay(xTimeIncrement);
	}
	vTaskDelete( NULL );  // F�r en clean exit av tasken ( Kanske ej beh�vs)
}