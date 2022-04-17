/*
 * main.c
 *
 * Created: 2021-11-05 오전 9:48:24
 *  Author: USER
 */ 
#include "util/delay.h"
#include "tlcd.h"
#include "usart.h"
#include <stdio.h>

#define PIR_LED_DDR DDRC

#define SENSOR_PIN PINC
#define LED_PORT PORTC

#define PIR_PIN 0
#define RED_PORT 2
#define GREEN_PORT 3
#define SWITCH_PIN 4

void sensor_INIT(){
	PIR_LED_DDR &= (1 << PIR_PIN) | (1 << SWITCH_PIN);
	PIR_LED_DDR |= (1 << RED_PORT) | (1 << GREEN_PORT);
}

int main(){
	sensor_INIT();
	USART_Init();
	TXT_LCD_Init();

	int n = 0;
	char num[10];
	
	char mess[5][6] = {"aaaaa", "bbbbb", "ccccc", "ddddd", "eeeee"};
	char mes[20] = "";
	
	int intruder = 0;
	
	//SendText(DDRAM_ADDR | 0x40, "123456789");
	sei();
	while(1){
		SendCommand(CMD_CLEAR_DISPLAY);
		_delay_us(2000);
		sprintf(num, "%d", n);
		SendText(DDRAM_ADDR | 0x00, num);
		SendText(DDRAM_ADDR | 0x05, mess[n % 5]);
		n++;
		n %= 101;
		SetText(mes);
		if(mes[0] != NULL){
			SendText(DDRAM_ADDR | 0x40, mes);
		}
		if(SENSOR_PIN & (1 << PIR_PIN)){
			intruder = 1;
		}
		if(SENSOR_PIN & (1 << SWITCH_PIN)){
			intruder = 0;
		}
		if(intruder){
			SendText(DDRAM_ADDR | 0x4F, "1");
		}
		else{
			SendText(DDRAM_ADDR | 0x4F, "0");
		}
		
		_delay_ms(1000);
	}
}