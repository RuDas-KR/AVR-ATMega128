#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define USART0 0
#define USART1 1

void USART_init(unsigned char ch, unsigned int ubrr_baud)
{
	if (ch == USART0) {
		UCSR0B |= 1 << RXEN0 | 1 << TXEN0;
		UBRR0H = ubrr_baud >> 8;
		UBRR0L = ubrr_baud;
	}

	else if (ch == USART1){
		UCSR1B |= 1 << RXEN1 | 1 << TXEN1;
		UBRR1H = ubrr_baud >> 8;
		UBRR1L = ubrr_baud;
	}
}

//폴링을 이용한 문자 수신
char USART0_receive(){
	char i;
	for (i=0; i<5; i++) {
		if((UCSR0A & (1 << RXC0))) {
			return UDR0;
		}
	}
	return '\0';
}

//폴링을 이용한 문자 송신
void USART0_send(char data){
	while (!(UCSR0A & (1 << UDRE0)) ); // UDR 레지스터가 빌 때까지 폴링
	UDR0 = data;			   // UDR 레지스터에 값을 기록
}

void tx0_str(char *s) {
	while (*s) {
		USART0_send(*s++);
	}
}

int main(void) {
	unsigned char ch, i;
	int rx[4] = {};
	int SEG[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D, 0x74, 0x30, 0x1E, 0x75, 0x38, 0x15, 0x37, 0x3F, 0x73, 0x67, 0x33, 0x6D, 0x78, 0x3E, 0x2E, 0x2A, 0x76, 0x62, 0x4B};
	int SELECT[4] = {0x01, 0x02, 0x04, 0x08};
	
	USART_init(0,8);
	
	DDRC = 0xFF;
	DDRG = 0xFF;
	
	while(1) {
		if(UCSR0A & 0x80) {
			ch = USART0_receive();
			USART0_send(ch);
			if      (ch > 47 && ch < 58 )  ch = ch - 48;	//	0-9 seg-data
			else if (ch > 64 && ch < 91 )  ch = ch - 55;	//	Upper Case Alphabet seg-data
			else if (ch > 86 && ch < 123) ch = ch - 87;	//	Lower Case Alphabet seg-data
			else ch = 0;
			rx[3] = rx[2];		rx[2] = rx[1];		rx[1] = rx[0];		rx[0] = ch;
		}
		
		for(i=0; i<4; i++) {
			PORTG = SELECT[i];
			PORTC = SEG[rx[i]];
			_delay_ms(4);
		}
	}
}