//     Connections: DataBus 7..0 -> PB7..0, RS -> PD7, E -> PD6

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define DEFSEQ_ConfigPortAsOutput(PortName, IniVal) DDR ## PortName=0xFF;\
PORT ## PortName=IniVal;
#define DEFSEQ_ConfigPortPinAsOutput(PortName, PinNo) DDR ## PortName|=(1<<PinNo);

#define DEFSIG_LCD_RS_Command	PORTD&=~(1<<PD7)
#define DEFSIG_LCD_RS_Data		PORTD|=(1<<PD7)
#define DEFSIG_LCD_E_Low		PORTD&=~(1<<PD6)
#define DEFSIG_LCD_E_High		PORTD|=(1<<PD6)

#define DEFCMD_LCD_FunctionSet	(1<<5)
#define DEFSET_LCD_DataLenght8	(1<<4)
#define DEFSET_LCD_2Lines		(1<<3)
#define DEFSET_LCD_FontSize5x8	(0<<2)

#define DEFCMD_LCD_ClearDisplay	(1<<0)

#define DEFCMD_LCD_ReturnHome	(1<<1)

#define DEFCMD_LCD_DisplayControl (1<<3)
#define DEFSET_LCD_DisplayOn	(1<<2)
#define DEFSET_LCD_CursorOn		(1<<1)
#define DEFSET_LCD_CursorOff	(0<<1)
#define DEFSET_LCD_BlinkingOn	(1<<0)
#define DEFSET_LCD_BlinkingOff	(0<<0)

#define DEFCMD_LCD_SetDDRAMAddress (1<<7)

#define DEFCMD_LCD_CurDispShift	(1<<4)
#define DEFSET_LCD_DisplayShift	(1<<3)
#define DEFSET_LCD_CursorShift	(0<<3)
#define DEFSET_LCD_ShiftRight	(1<<2)
#define DEFSET_LCD_ShiftLeft	(0<<2)

#define DEFCMD_LCD_EntryMode	(1<<2)
#define DEFSET_LCD_CursorMoveDirInc (1<<1)
#define DEFSET_LCD_CursorMoveDirDec (0<<1)
#define DEFSET_LCD_DispCursorSimShift (1<<0)

#define DEFCMD_LCD_SetCGRAMAddress (1<<6)

#define DEFVAL_CharSi	0
#define DEFVAL_CharCi	1

const uint8_t
Const_CharSi[8] =	{0b00001000,
	0b00000100,
	0b00001110,
	0b00010000,
	0b00001110,
	0b00000001,
	0b00011110,
0b0000000},
Const_CharCi[8] =	{0b00001000,
	0b00000100,
	0b00001110,
	0b00010000,
	0b00010000,
	0b00010001,
	0b00001110,
0b0000000};


void Fun_LCD_Write (uint8_t ParByte) {

	PORTB = ParByte;
	DEFSIG_LCD_E_High;
	_delay_us(10);
	DEFSIG_LCD_E_Low;
}

void Fun_WriteCharFontToCGRAM (const uint8_t* ParPatern, uint8_t ParAddress)
{
	DEFSIG_LCD_RS_Command;
	Fun_LCD_Write (DEFCMD_LCD_SetCGRAMAddress | (ParAddress<<3));
	_delay_us(40);	// delay more than 37 us
	DEFSIG_LCD_RS_Data;
	uint8_t
	LocVAR_Index;
	for (LocVAR_Index = 0; LocVAR_Index < 8; LocVAR_Index ++)	{
		Fun_LCD_Write(ParPatern[LocVAR_Index]);
		_delay_us(40);
	}
}

void Fun_LCD_Init (void) {

	// interface configuration
	DEFSEQ_ConfigPortAsOutput (B, 0); // DataBus 7..0 -> PB7..0
	DEFSEQ_ConfigPortPinAsOutput (D, 7);
	DEFSEQ_ConfigPortPinAsOutput (D, 6);
	DEFSIG_LCD_E_Low;
	// reset sequence
	DEFSIG_LCD_RS_Command;
	_delay_ms(41);	// delay more than 40 ms
	Fun_LCD_Write (0b00110000);
	_delay_ms(5);	// delay more than 4.1 ms
	Fun_LCD_Write (0b00110000);
	_delay_us(110);	// delay more than 100 us
	Fun_LCD_Write (0b00110000);
	_delay_us(110);	// delay more than 100 us
	// display configuration
	DEFSIG_LCD_RS_Command;
	Fun_LCD_Write (DEFCMD_LCD_FunctionSet
	|DEFSET_LCD_DataLenght8
	|DEFSET_LCD_2Lines
	|DEFSET_LCD_FontSize5x8);
	_delay_us(40);	// delay more than 37 us
	Fun_LCD_Write (DEFCMD_LCD_DisplayControl
	|DEFSET_LCD_DisplayOn
	|DEFSET_LCD_CursorOff
	|DEFSET_LCD_BlinkingOff);
	_delay_us(40);	// delay more than 37 us
	Fun_LCD_Write (DEFCMD_LCD_ClearDisplay);
	_delay_us(40);	// delay more than 37 us
	Fun_LCD_Write (DEFCMD_LCD_ReturnHome);
	_delay_ms(2);	// delay more than 1.5ms
	Fun_LCD_Write (DEFCMD_LCD_EntryMode
	|DEFSET_LCD_CursorMoveDirInc);
	_delay_us(40);	// delay more than 37 us
	Fun_LCD_Write (DEFCMD_LCD_SetDDRAMAddress|0x00);
	_delay_us(40);	// delay more than 37 us
	
	Fun_WriteCharFontToCGRAM (Const_CharSi, DEFVAL_CharSi);
	Fun_WriteCharFontToCGRAM (Const_CharCi, DEFVAL_CharCi);
}

void Fun_LCD_SetDDRAMAddress (int8_t ParLine, int8_t ParPosition) {
	
	DEFSIG_LCD_RS_Command;
	Fun_LCD_Write (DEFCMD_LCD_SetDDRAMAddress
	|((ParLine==1?0x0:0x40)+ParPosition));
	_delay_us(40);	// delay more than 37 us
}

void Fun_DisplayStringAtPossition (char* Par_Ptr, uint8_t Par_ByteCount,
int8_t ParLine, int8_t ParPosition)  {
	
	// setting the position
	if ((ParLine!=-1) && (ParPosition!=-1))	{
		DEFSIG_LCD_RS_Command;
		Fun_LCD_Write (DEFCMD_LCD_SetDDRAMAddress
		|((ParLine==1?0x0:0x40)+ParPosition));
		_delay_us(40);	// delay more than 37 us
	}
	// contents sending
	DEFSIG_LCD_RS_Data;
	while (Par_ByteCount --)	{
		Fun_LCD_Write (*Par_Ptr++);
		_delay_us(40);	// delay more than 37 us
	}
}

void Fun_ShiftDisplayWindow (uint8_t ParDirection) {
	DEFSIG_LCD_RS_Command;
	Fun_LCD_Write (DEFCMD_LCD_CurDispShift
	|DEFSET_LCD_DisplayShift
	|ParDirection);
}


