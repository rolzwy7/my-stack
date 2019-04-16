#include <avr/io.h>
#define F_CPU 16000000UL
//#include <util/delay.h>
#include <avr/interrupt.h>

ISR(TIMER0_COMP_vect) {
	static uint8_t cnt = 0;
	
	if(++cnt > 10) {
		cnt = 0;
		if((PORTA & 0x80) == 0) {
			PORTA = (PORTA << 1) | 0x01;
			} else {
			PORTA = (PORTA << 1) & ~0x01;
		}
	}

}

int main(void) {
	// init - start
	TCCR0 |= (1 << WGM01);
	TCCR0 |= (1 << CS02) | (1 << CS00);
	OCR0 = 250;
	TIMSK |= (1 << OCIE0);
	sei();
	// init - end
	
	DDRA = 0b11111111; // output (PORTA)
	PORTA = 0b00000000; // all LEDs off
	while(1) {
		//_delay_ms(500);
	}
}


