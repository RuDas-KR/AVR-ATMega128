#include<avr/io.h>

int main() {
	
	DDRA = 0x81;	//Port A�� ���κи� ���(Switch)
	DDRB = 0xFF;	//Port B�� ���κ� ���(LED)

	PORTB = 0x80;	//10000000 (LED)

	while(1) {
		if(PINA & 0x80) {
			if(PORTB = 0x01)
				PORTB = (1<<PORTB);
		}

		if(PINA & 0x01) {
			if(PORTB = 0x80)
				PORTB = (1>>PORTB);
		}
	}

	return 0;
}
