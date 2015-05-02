#include <avr/io.h>
#include <avr/interrupt.h>

#define	F_CPU	16000000UL
#define	PRESCALE	256L
#define	PULSE_PER_OVERFLOW	256L
#define	MS_OVERFLOW_CYCLE	((double)(PULSE_PER_OVERFLOW * PRESCALE) / (double)((double)F_CPU/1000.0))

volatile unsigned long timer0;
volatile unsigned long req_timer0;

ISR(TIMER0_OVF_vect){
	timer0++;

	if (req_timer0 > 0){
		req_timer0--;
	}
}

unsigned long ms_req_timer0(unsigned long ms_interval){
	return (ms_interval <= 0.0) ? 0 : (unsigned long)(ms_interval / MS_OVERFLOW_CYCLE);
}

int main(void){
	DDRA |= 1 << PA0;

	TCCR0 |= 1 << CS02 | 1 << CS01;	// 클럭 소스 / 128, normal mode
	TIMSK |= 1 << TOIE0;			// Timer0 overflow interrupt 활성화

	sei();							// 전역 인터럽트 활성화

	while(1){						// 1초 주기로 LED 점등
		if (req_timer0 == 0){
			req_timer0 = ms_req_timer0(500);
			PORTA ^= 1 << PA0;
		}
	}
	return 0;
}