// analog channel on pin PA0
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "module_LCD.h"

char
	VAR_String1[5];
volatile uint16_t VAR_ADC_Code = 0;
volatile uint8_t VAR_Flag_NewData = 0;
float
	VAR_Voltage = 0.0;

void Fun_ADC_Init (void) {
	DDRA &= ~(1<<PA0);
	ADMUX = (1<<REFS1) | (1<<REFS0) // internal 2.56V
			| (1<<ADLAR)
			| (0<<MUX4) | (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0);
	ADCSRA = (1<<ADEN)
			| (1<<ADIE) // interrupt
			| (1<<ADATE) // trigger enable
			| (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
	SFIOR |= (1<<ADTS2) | (0<<ADTS1) | (1<<ADTS0);
	
	// T1
	TCCR1A = (0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0)
			| (0<<FOC1A) | (0<<FOC1B) | (0<<WGM11) | (0<<WGM10);
	TCCR1B = (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
	
	OCR1B = OCR1A = (F_CPU/1024L); // /2 -> 0.5s [?] | *1 -> 1s [k]
}
	
void Fun_ADC_StartConversion(void) {
	ADCSRA |= (1<<ADSC);
}

void Fun_ADCCode2String(uint16_t ParCode, char* ParStringPtr) {
	*ParStringPtr++ = ParCode / 10000 + '0'; ParCode %= 10000;
	*ParStringPtr++ = ParCode / 1000  + '0'; ParCode %= 1000;
	*ParStringPtr++ = ParCode / 100   + '0'; ParCode %= 100;
	*ParStringPtr++ = ParCode / 10    + '0'; ParCode %= 10;
	*ParStringPtr = ParCode           + '0';
	
}

void Fun_Voltage2String(float ParVoltage, char* ParStringPtr){
	uint16_t LocVar_UInt;
	LocVar_UInt = (uint16_t)(ParVoltage * 1000.0);
	
	*ParStringPtr++ = LocVar_UInt / 1000 + '0'; LocVar_UInt %= 1000;
	*ParStringPtr++ = '.';
	*ParStringPtr++ = LocVar_UInt / 100 + '0'; LocVar_UInt %= 100;
	*ParStringPtr++ = LocVar_UInt / 10 + '0'; LocVar_UInt %= 10;
	*ParStringPtr++ = LocVar_UInt + '0';
	
	
}

int main(void) {
	Fun_LCD_Init();
	Fun_DisplayStringAtPossition ("ADCcode:", 8, 1, 0);
	Fun_DisplayStringAtPossition ("Voltage:", 8, 2, 0);
	
	Fun_ADC_Init();
	sei();
	Fun_ADC_StartConversion ();
	
	while (1) {	
		if(VAR_Flag_NewData) {
			Fun_ADCCode2String(VAR_ADC_Code, VAR_String1);
			Fun_DisplayStringAtPossition(VAR_String1, 5, 1, 9);
			VAR_Voltage = 2.56 * (float)VAR_ADC_Code / (float)UINT16_MAX;
			Fun_Voltage2String(VAR_Voltage, VAR_String1);
			Fun_DisplayStringAtPossition(VAR_String1, 5, 2, 9);
			VAR_Flag_NewData = 0;
			
			//Fun_ADC_StartConversion();
		}
	}

	return 0;
}

ISR (ADC_vect) {
	VAR_ADC_Code = ADC;
	VAR_Flag_NewData = 1;	
	
	TIFR &= ~(1<<OCF1A);
}


/*
// analog channel on pin PA0
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "module_LCD.h"

char
VAR_String1[5];
volatile uint16_t VAR_ADC_Code = 0;
volatile uint8_t VAR_Flag_NewData = 0;
float
VAR_Voltage = 0.0;

void Fun_ADC_Init (void) {
	DDRA &= ~(1<<PA0);
	ADMUX = (1<<REFS1) | (1<<REFS0) // internal 2.56V
	| (1<<ADLAR)
	| (0<<MUX4) | (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0);
	ADCSRA = (1<<ADEN)
	| (1<<ADIE)
	| (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
}

void Fun_ADC_StartConversion(void) {
	ADCSRA |= (1<<ADSC);
}

void Fun_ADCCode2String(uint16_t ParCode, char* ParStringPtr) {
	*ParStringPtr++ = ParCode / 10000 + '0'; ParCode %= 10000;
	*ParStringPtr++ = ParCode / 1000  + '0'; ParCode %= 1000;
	*ParStringPtr++ = ParCode / 100   + '0'; ParCode %= 100;
	*ParStringPtr++ = ParCode / 10    + '0'; ParCode %= 10;
	*ParStringPtr = ParCode           + '0';
	
}

void Fun_Voltage2String(float ParVoltage, char* ParStringPtr){
	uint16_t LocVar_UInt;
	LocVar_UInt = (uint16_t)(ParVoltage * 1000.0);
	
	*ParStringPtr++ = LocVar_UInt / 1000 + '0'; LocVar_UInt %= 1000;
	*ParStringPtr++ = '.';
	*ParStringPtr++ = LocVar_UInt / 100 + '0'; LocVar_UInt %= 100;
	*ParStringPtr++ = LocVar_UInt / 10 + '0'; LocVar_UInt %= 10;
	*ParStringPtr++ = LocVar_UInt + '0';
	
	
}

int main(void)
{
	Fun_LCD_Init();
	Fun_DisplayStringAtPossition ("ADCcode:", 8, 1, 0);
	Fun_DisplayStringAtPossition ("Voltage:", 8, 2, 0);
	
	Fun_ADC_Init();
	sei();
	Fun_ADC_StartConversion ();
	
	while (1) {
		if(VAR_Flag_NewData) {
			Fun_ADCCode2String(VAR_ADC_Code, VAR_String1);
			Fun_DisplayStringAtPossition(VAR_String1, 5, 1, 9);
			VAR_Voltage = 2.56 * (float)VAR_ADC_Code / (float)UINT16_MAX;
			Fun_Voltage2String(VAR_Voltage, VAR_String1);
			Fun_DisplayStringAtPossition(VAR_String1, 5, 2, 9);
			VAR_Flag_NewData = 0;
			
			Fun_ADC_StartConversion();
		}
	}

	return 0;
}

ISR (ADC_vect) {
	VAR_ADC_Code = ADC;
	VAR_Flag_NewData = 1;
}
*/