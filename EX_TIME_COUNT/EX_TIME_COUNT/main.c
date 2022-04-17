/*
 * EX_TIME_COUNT.c
 *
 * Created: 2021-12-03 오전 11:19:34
 * Author : USER
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

//제어관련 정의

//LED 제어를 위한 정의
#define DDR_LED         DDRD
#define PORT_LED      PORTD

//interrupt 제어를 위한 정의
#define CPU_CLOCK      16000000      //CPU Clock = 16MHz
#define TICK_PER_SEC   1000         //1 Sec = 1000ms
#define PRESCALER      64            //Prescaler = 64
#define TCNT_VALUE      (CPU_CLOCK/TICK_PER_SEC/PRESCALER)

//interrupt 제어 위한 전역변수 선언
volatile unsigned int tickCnt;

//Timer/Counter0 초기화 함수
void init_TimerCounter()
{
	
	TCCR0 = (1<<CS02);         //Normal Mode, Not used OC0, 64 Prescale
	TCNT0 = 256 - TCNT_VALUE;   //TCNT0 초기 값 설정
	TIMSK = (1<<TOIE0);         //Overflow Interrupt Enable

}

void Delay_ms(unsigned int mesc){
	tickCnt = 0;
	while(tickCnt < mesc);
}

ISR(SIG_OVERFLOW0){
	tickCnt++;
	TCNT0 = 256 - TCNT_VALUE;
}

int main(void)
{
	DDR_LED |= 0xF0;
	PORT_LED |= 0xF0;
	
	init_TimerCounter();
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		PORT_LED &= ~(0xF0);
		Delay_ms(1000);
		
		PORT_LED |= 0xF0;
		Delay_ms(1000);
    }
}

//TIMER0_OVF_vect : Timer0 Overflow Interrupt Vector
