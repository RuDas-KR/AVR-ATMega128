#include<avr/io.h>

int main() {
	
	DDRA = 0x81;
	DDRB = 0xFF;

	PORTB = 0x80;

	while(1) {
		if(PINA & 0x80) {
			if(PORTB != 0x80)
				PORTB = (1<<PORTB);
		}

		if(PINA & 0x01) {
			if(PORTB != 0x01)
				PORTB = (1>>PORTB);
		}
	}

	return 0;
}
