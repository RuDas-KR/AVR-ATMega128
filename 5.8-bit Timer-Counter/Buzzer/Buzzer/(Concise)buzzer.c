#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
	DDRB |= 1 << PB4;

	TCCR0 |= 1 << WGM01 | 1 << CS02 | 1 << CS01 | 1 << COM00;
	OCR0 = 70;

	while(1);
}
