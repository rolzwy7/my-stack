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
volatile uint8_t key_state = 0;
// 0 - sprawdza czy wcisniety
// 1 - sprawdza czy na pewno wcisniety
// 2 - wcisniety
// 3 - sprawdza czy odcisniety
// 4 - sparwdza czy na pewno odcisniety

// displayed number
uint16_t segs = 5678;

ISR(TIMER0_COMP_vect) {
	static uint8_t cnt = 0;


	PORTB |= 0x0F;
	PORTA = LED[cnt];
	PORTB &= ~(1 << cnt);

	// 4 wyswietlacze
	if(++cnt > 3) {
		cnt = 0;
	}

	// Obsługa przycisku
	switch (key_state) {
		case 0:
			if((PINC & 0x01) == 0) key_state = 1;
			break;

		case 1:
			if((PINC & 0x01) == 0)
				key_state = 2;
			else
				key_state = 0;
			break;

		case 2: break;

		case 3:
			//
			if((PINC & 0x01) != 0) key_state = 4;
			break;

		case 4:
			//
			if((PINC & 0x01) != 0)
			key_state = 0;
			else
			key_state = 3;
			break;

		default:
			key_state=0;
			break;
	}

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

	DDRB = 0x0F;

	PORTC |= 0b00000001;

    while (1) {
		uint16_t temp = segs;

		// wyswietla liczbe segs na wysiwetlaczach
		LED[0] = seg7[temp/1000]; temp = temp % 1000;
		LED[1] = seg7[temp/100]; temp = temp % 100;
		LED[2] = seg7[temp/10]; temp = temp % 10;
		LED[3] = seg7[temp];

		//
		if(key_state == 2) {
			segs++;
			key_state = 3;
		}

    }

}
