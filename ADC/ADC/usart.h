/*
 * usart.h
 *
 * Created: 2021-10-25 오후 1:40:08
 *  Author: USER
 */ 


#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BAUD_RATE 51

void USART_Init();

void USART_Transmitter(unsigned char txData);

ISR(USART1_RX_vect);

#endif /* USART_H_ */