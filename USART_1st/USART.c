#include<avr/io.h>

#define USART0 0
#define USART1 1

main() {
	USART_init(0,8);

	USART0_send('S');

	USART0_recive();
}



// 프레임 포멧 설정
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

// 폴링방식 문자열 송신
void USART0_send(char data){
	while (!(UCSR0A & (1 << UDRE0)) ); // UDR 레지스터가 빌 때까지 폴링
	UDR0 = data; // UDR 레지스터에 값을 기록
}

// 폴링방식 문자열 수신
char USART0_receive(){
	while (!(UCSR0A & (1 << RXC0)) ); // UDR 레지스터에 문자 수신 검사
	return UDR0;
}
