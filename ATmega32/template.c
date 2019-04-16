#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

// PORTB - steruje ktory wyswietlacz ma sie swiecic
// PORTA - zaswieca wyswietlacze

// 7seg codes
uint8_t seg7[] = {
	0b11000000,
	0b11111001,
	0b10100100,
	0b10110000,
	0b10011001,
	0b10010010,
	0b10000010,
	0b11111000,
	0b10000000,
	0b10010000
};

// Dynamic 7seg
volatile uint8_t LED[4];
// Button state
volatile uint8_t key_1_state = 0;
// 0 - sprawdza czy wcisniety
// 1 - sprawdza czy na pewno wcisniety
// 2 - wcisniety
// 3 - sprawdza czy odcisniety
// 4 - sparwdza czy na pewno odcisniety

// displayed number
uint16_t segs = 1234;

ISR(TIMER0_COMP_vect) {
	static uint8_t cnt = 0;

	// dynamiczne wyswietlanie (4 disp)
	PORTB |= 0x0F; // to jest potrzebne tak btw?
	PORTA = LED[cnt];
	PORTB &= ~(1 << cnt);
	if(++cnt > 3) {
		cnt = 0;
	}
	// dynamiczne wyswietlanie (4 disp) - End

	// Obsługa przycisku 1
	uint8_t key_1_addr = 0x01;
	switch (key_1_state) {
		case 0:
			key_1_state = ((PINC & key_1_addr) == 0) ? 1 : 0;
			break;
		case 1:
			key_1_state = ((PINC & key_1_addr) == 0) ? 2 : 0;
			// ...
			break;
		case 2:
			break;
		case 3:
			key_1_state = ((PINC & key_1_addr) != 0) ? 4 : 3;
			break;
		case 4:
			key_1_state = ((PINC & key_1_addr) != 0) ? 0 : 3;
			// ...
			break;
		default:
			key_1_state = 0;
			break;
	}
	// Obsługa przycisku 1 - End
}

int main(void) {
	// init - start
	TCCR0 |= (1 << WGM01);
	TCCR0 |= (1 << CS02) | (1 << CS00);
	OCR0 = 50;
	TIMSK |= (1 << OCIE0);
	sei();
	// init - end

	DDRA = 0xFF;
	PORTA = 0b00000000;

	DDRB = 0x0F; // 4 bity na output

	// DDRC = 0x0 - default(?)
	PORTC |= 0b00000001;

	while (1) {
		// wyswietla liczbe 'segs' (DEC) na wysiwetlaczach
		uint16_t temp = segs;
		LED[0] = seg7[temp/1000]; temp = temp % 1000;
		LED[1] = seg7[temp/100]; temp = temp % 100;
		LED[2] = seg7[temp/10]; temp = temp % 10;
		LED[3] = seg7[temp];

		// wciskanie przycisku
		if(key_1_state == 2) {
			segs++;
			key_1_state = 3;
		}

	}

}
