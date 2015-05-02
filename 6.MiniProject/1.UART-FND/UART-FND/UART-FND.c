#include <avr/io.h>
#include <util/delay.h>
#include <ctype.h>
#include <stdlib.h>

#define USART0 0
#define USART1 1

// 프레임 포맷 설정
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

//폴링을 이용한 문자 송신
void USART0_send(char data){
	while (!(UCSR0A & (1 << UDRE0)) ); // UDR 레지스터가 빌 때까지 폴링
	UDR0 = data;			   // UDR 레지스터에 값을 기록
}

//폴링을 이용한 문자 수신
char USART0_receive(){
	while (!(UCSR0A & (1 << RXC0)) ); // UDR 레지스터에 문자 수신 검사
	return UDR0;
}

void fnd(int num);

int main() {

	int SEG[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D, 0x74, 0x30, 0x1E, 0x75, 0x38, 0x15, 0x37, 0x3F, 0x73, 0x67, 0x33, 0x6D, 0x78, 0x3E, 0x2E, 0x2A, 0x76, 0x62, 0x4B};
	
	USART_init(0,8);
	DDRA=0xFF;

	unsigned char text[]="Start USART \r\n";
	unsigned char i=0;
	unsigned char str;
	int num;

	DDRC = 0xFF;
	DDRG = 0xFF;

	while(text[i] != '\0') {
		USART0_send(text[i++]);
	}
	
	while(1) {
		str=USART0_receive();
		USART0_send(str);
		
		num = str;	//	char => int
		if(num>47 && num <58) {
			num = num - 48;
			fnd(SEG[num]);
		}	//	0~9
		
		else if(num>64 && num<91) {
			num = num - 55;
			fnd(SEG[num]);
		}	//	Upper Case Alphabet
		
		else if(num>96 && num<123) {
			num = num - 87;
			fnd(SEG[num]);
		}	//	Lower Case Alphabet
	}
}

void fnd(int num) {
	PORTG = 0x01;
	PORTC = num;
}