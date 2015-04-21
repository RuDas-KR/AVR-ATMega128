#include <avr/io.h>
#include <avr/interrupt.h>

#define	F_CPU	16000000UL
#define	PRESCALE	256L
#define	PULSE_PER_OVERFLOW	256L
#define	MS_OVERFLOW_CYCLE	((double)(PULSE_PER_OVERFLOW * PRESCALE) / (double)((double)F_CPU/1000.0))

volatile unsigned long timer0;
volatile unsigned long req_timer0;

ISR(TIMER0_COMP_vect) {
	timer0++;

	if (req_timer0 > 0){
		req_timer0--;
	}
}

unsigned long ms_req_buzzer(unsigned long ms_freq) {
	return (F_CPU / (2*PRESCALE*ms_freq)) - 1;
}


int main(void){
	DDRB |= 1 << PB4;

	TCCR0 |= 1 << WGM01;			// Setup CTC Mode
	TCCR0 |= 1 << CS02 | 1 << CS01;	// 클럭 소스 / 128, normal mode
	TIMSK |= 1 << OCIE0;			// Timer0 Compare Match interrupt 활성화

	sei();							// 전역 인터럽트 활성화

	while(1){
		if (req_timer0 == 0){
			req_timer0 = ms_req_buzzer(440);
			PORTB ^= 1 << PB4;
		}
	}
	return 0;
}