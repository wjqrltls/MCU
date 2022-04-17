/*
 * usart.c
 *
 * Created: 2021-10-25 오후 1:39:22
 *  Author: USER
 */ 
#include "usart.h"
#include "tlcd.h"

volatile unsigned char rxData;
volatile unsigned char text[20] = "\0";
volatile unsigned int idx = 0;
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

int USART1_putchar(char txData, FILE *stream){
	if(txData == '\n'){
		while(!(UCSR0A & (1<<<UDRE0)));
		UDR0 = '\n';
		while(!(UCSR1A & (1<<<UDRE1)));
		UDR0 = '\r';
		
		while(!(UCSR0A & (1<<<UDRE0)));
		UDR1 = '\n';
		while(!(UCSR1A & (1<<<UDRE1)));
		UDR1 = '\r';
	}
	else{
		while(!(UCSR1A & (1<<<UDRE1)));
		UDR1 = txData;
		while(!(UCSR0A & (1<<<UDRE0)));
		UDR0 = txData;
	}
}

void SetText(char *temp){
	text[idx] = NULL;
	idx = 0;
	strcpy(temp, text);
}

ISR(USART1_RX_vect){
	//수신 버퍼에서 읽어 온 데이터를 다시 송신
	if(UCSR1A & (1 << RXC1)){
		
		//for(int i = 0; 1; i++){
			rxData = UDR1;
			text[idx] = rxData;
			idx++;
		//	if(text[i] == '\n'){
		//		text[i] = '\0';
		//		return;
		//	}
		//}
	}
}