#define F_CPU 16000000UL
#include "main.h"
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define USART_BD 9600
#define BD_PRESCALE (((F_CPU / (USART_BD * 16UL))) -1)

/*
void USART_Init(uint16_t baud) {
	UBRRH = (uint8_t)(baud >> 8);
	UBRRL = (uint8_t)(baud);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	
	UCSRB = (1 << TXEN) | (1 << RXEN);
}
*/

void USART_Init_ISR(uint16_t baud) {
	
	
	UBRRH = (uint8_t)(baud >> 8);
	UBRRL = (uint8_t)(baud);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UCSRB = (1 << TXEN) | (1 << RXEN);
	
	UCSRB |= (1 << RXCIE);
	sei();
}

void USART_Transmit(uint8_t data) {
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}

int8_t USART_Receive(void) {
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}

volatile uint8_t RX_data;
volatile uint8_t RX_data_ready = 0;

ISR(USART_RXC_vect) {
	RX_data = UDR;
	RX_data_ready = 1;
}

volatile uint8_t TX_data[] = "Hello World";

ISR(USART_UDRE_vect) {
	static uint8_t TX_data_ptr = 0;
	if(TX_data[TX_data_ptr] != 0) {
		UDR = TX_data[TX_data_ptr++];
	} else {
		UCSRB &= ~(1 << UDRIE);
		TX_data_ptr = 0;
	}
}

int main(void) {
	
	USART_Init_ISR(BD_PRESCALE);
	LCD_Init();
	
    while (1) {
		while(RX_data_ready == 0);
		
		if (RX_data == 'b')
			UCSRB |= (1 << UDRIE);
		else
			LCD_WriteData(RX_data);
		
		RX_data_ready = 0;
		//_delay_ms(500);
    }
}

