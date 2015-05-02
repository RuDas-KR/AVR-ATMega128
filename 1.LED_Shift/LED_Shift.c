#include<avr/io.h>

int main() {
	
	DDRA = 0x81;	// 스위치의 0번과 7번을 사용
	DDRB = 0xFF;	// LED는 모두 사용

	PORTB = 0x80;	// LED 초기설정으로 7번만 켬

	while(1) {
		if(PINA & 0x80) {	// PINA와 16진수인 0x80을 비교
			if(PORTB != 0x80)	// PORTB와 0x80을 비교하여 같지 않을경우.
				PORTB = (1<<PORTB); // PORTB의 현재 비트에서 왼쪽으로 한비트만 이동
		}

		if(PINA & 0x01) {	// PINA와 16진수인 0x01을 비교
			if(PORTB != 0x01)	// PORTB와 0x01을 비교하여 같지 않을경우.
				PORTB = (1>>PORTB);	// PORTB의 현재 비트에서 오른쪽으로 한비트만 이동
		}
	}

	return 0;
}
