/*
 * interrupt.c
 *
 * Created: 2021-10-18 오후 1:26:41
 * Author : USER
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SEG_DDR DDRB
#define SEG_PORT PORTB

int number[10][8] = {
	{0,1,1,0,0,0,0,0},
	{1,1,0,1,1,0,1,0},
	{1,1,1,1,0,0,1,0},
	{0,1,1,0,0,1,1,0},
	{1,0,1,1,0,1,1,0},
	{1,0,1,1,1,1,1,0},
	{1,1,1,0,0,1,0,0},
	{1,1,1,1,1,1,1,0},
	{1,1,1,1,0,1,1,0},
	{1,1,1,1,1,1,0,0}
};

void init_EINT(){
	EICRA |= (1 << ISC01) | (1 << ISC00);
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC11) | (1 << ISC10);
	EIMSK |= (1 << INT1);
}

void clear(){
	for(int i = 0; i < 8; i++){
		SEG_PORT &= ~(1 << i);
	}
}

ISR(INT0_vect){
	for(int i = 0; i < 10; i++){
		clear();
		for(int j = 0; j < 8; j++){
			SEG_PORT |= (number[i][j] << j);
		}
		_delay_ms(300);
	}		
}

ISR(INT1_vect){
	clear();
}

int main(void)
{
	for(int i = 0; i < 8; i++){
		SEG_DDR	|= (1 << i);
	}
	init_EINT();
	sei();

    /* Replace with your application code */
    while (1) 
    {
		
    }
}
