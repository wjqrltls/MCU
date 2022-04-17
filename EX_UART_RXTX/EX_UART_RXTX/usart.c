/*
 * usart.c
 *
 * Created: 2021-10-25 오후 1:39:22
 *  Author: USER
 */ 
#include "usart.h"

volatile unsigned char rxData;

void USART_Init(){ //통신 관련 설정
	UBRR1H = (unsigned char) BAUD_RATE >> 8;
	UBRR1L = (unsigned char) BAUD_RATE;
	
	UCSR1B = (1 << RXCIE1) | (1 << TXEN1) | (1 << RXEN1);
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

void USART_Transmitter(unsigned char txData){
	while(!(UCSR1A & (1 << UDRE1))); //버퍼가 빌 때 까지 대기
	UDR1 = txData;
}

ISR(USART1_RX_vect){
	//수신 버퍼에서 읽어 온 데이터를 다시 송신
	if(UCSR1A & (1 << RXC1)){
		rxData = UDR1;
		USART_Transmitter(rxData);
	}
}