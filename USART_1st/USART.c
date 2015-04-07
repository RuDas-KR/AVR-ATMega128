#include<avr/io.h>
#include<util/delay.h>

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

void USART0_send(char data){
	while (!(UCSR0A & (1 << UDRE0)) );
	UDR0 = data;
}


char USART0_receive(){
	while (!(UCSR0A & (1 << RXC0)) );
	return UDR0;
}

int main() {
	USART_init(0,8);
	DDRA=0xFF;

	unsigned char text[]="Start USART \r\n";
	unsigned char i=0;
	unsigned char str;

	while(text[i] != '\0') {
		USART0_send(text[i++]);
	}

	while(1) {
		str=USART0_receive();
		USART0_send(str);
	
		if(str=='1') {
			PORTA=0x80;
			_delay_ms(500);
			PORTA=0x00;
		}
		else if(str=='2') {
			PORTA=0x40;
			_delay_ms(500);
			PORTA=0x00;
		}
		else if(str=='3') {
			PORTA=0x20;
			_delay_ms(500);
			PORTA=0x00;
		}
		else if(str=='4') {
			PORTA=0x10;
			_delay_ms(500);
			PORTA=0x00;
		}
		else if(str=='5') {
			PORTA=0x08;
			_delay_ms(500);
			PORTA=0x00;
		}
		else if(str=='6') {
			PORTA=0x04;
			_delay_ms(500);
			PORTA=0x00;
		}
		else if(str=='7') {
			PORTA=0x02;
			_delay_ms(500);
			PORTA=0x00;
		}
		else if(str=='8') {
			PORTA=0x01;
			_delay_ms(500);
			PORTA=0x00;
		}
	}
}
