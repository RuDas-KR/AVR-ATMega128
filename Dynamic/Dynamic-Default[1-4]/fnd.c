#include <avr/io.h>
#include <util/delay.h>

void fnd(int port, int num);

int main() {

	int SEG[4] = {0x06, 0x5B, 0x4F, 0x66};
	int SELECT[4] = {0x08, 0x04, 0x02, 0x01};
	int i;

	DDRC = 0xFF;
	DDRG = 0xFF;
	
	while(1) {
		fnd(SELECT[0], SEG[0]);
		fnd(SELECT[1], SEG[1]);
		fnd(SELECT[2], SEG[2]);
		fnd(SELECT[3], SEG[3]);
	}

}

void fnd(int port, int num) {
	PORTG = port;
	PORTC = num;
	_delay_ms(30);
}
