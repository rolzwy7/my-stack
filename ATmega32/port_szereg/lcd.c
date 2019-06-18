/*
    Funkcje do obslugi wyswietlacza alfanumerycznego LCD

    * wyswietlacz podlaczony do portu D
    * tryb 4-bitowy
    * linie danych DB7-DB4 dolaczone do PD7-PD4
    * linie sterujace E -> PD2, RS -> PD3

 */

#include "lcd.h"

void _LCD_OutNibble(unsigned char nibbleToWrite)
{
    if(nibbleToWrite & 0x01)
        LCD_DB4_PORT |= LCD_DB4;
    else
        LCD_DB4_PORT  &= ~LCD_DB4;

    if(nibbleToWrite & 0x02)
        LCD_DB5_PORT |= LCD_DB5;
    else
        LCD_DB5_PORT  &= ~LCD_DB5;

    if(nibbleToWrite & 0x04)
        LCD_DB6_PORT |= LCD_DB6;
    else
        LCD_DB6_PORT  &= ~LCD_DB6;

    if(nibbleToWrite & 0x08)
        LCD_DB7_PORT |= LCD_DB7;
    else
        LCD_DB7_PORT  &= ~LCD_DB7;
}

void _LCD_Write(unsigned char dataToWrite)
{
    LCD_E_PORT |= LCD_E;
    _LCD_OutNibble(dataToWrite >> 4);
    LCD_E_PORT &= ~LCD_E;
    LCD_E_PORT |= LCD_E;
    _LCD_OutNibble(dataToWrite);
    LCD_E_PORT &= ~LCD_E;
    _delay_us(50);
}

void LCD_WriteCommand(unsigned char commandToWrite)
{
    LCD_RS_PORT &= ~LCD_RS;
    _LCD_Write(commandToWrite);
}

void LCD_WriteData(unsigned char dataToWrite)
{
    LCD_RS_PORT |= LCD_RS;
    _LCD_Write(dataToWrite);
}

void LCD_WriteText(char *text)
{
    while(*text) LCD_WriteData(*text++);
}

void LCD_GoTo(unsigned char x, unsigned char y)
{
    LCD_WriteCommand(HD44780_DDRAM_SET | (x + (0x40 * y)));
}

void LCD_Clear(void)
{
    LCD_WriteCommand(HD44780_CLEAR);
    _delay_ms(2);
}

void LCD_Home(void)
{
    LCD_WriteCommand(HD44780_HOME);
    _delay_ms(2);
}

void LCD_Init(void)
{
    uint8_t i;
    LCD_DB4_DIR |= LCD_DB4; // Konfiguracja kierunku pracy wyprowadze�
    LCD_DB5_DIR |= LCD_DB5; //
    LCD_DB6_DIR |= LCD_DB6; //
    LCD_DB7_DIR |= LCD_DB7; //
    LCD_E_DIR   |= LCD_E;   //
    LCD_RS_DIR  |= LCD_RS;  //
    _delay_ms(15);          // oczekiwanie na ustalibizowanie si� napiecia zasilajacego
    LCD_RS_PORT &= ~LCD_RS; // wyzerowanie linii RS
    LCD_E_PORT &= ~LCD_E;   // wyzerowanie linii E

    for(i = 0; i < 3; i++)  // trzykrotne powt�rzenie bloku instrukcji
    {
        LCD_E_PORT |= LCD_E;    //  E = 1
        _LCD_OutNibble(0x03);   // tryb 8-bitowy
        LCD_E_PORT &= ~LCD_E;   // E = 0
        _delay_ms(5);           // czekaj 5ms
    }

    LCD_E_PORT |= LCD_E;    // E = 1
    _LCD_OutNibble(0x02);   // tryb 4-bitowy
    LCD_E_PORT &= ~LCD_E;   // E = 0

    _delay_ms(1); // czekaj 1ms
    LCD_WriteCommand(HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT); // interfejs 4-bity, 2-linie, znak 5x7
    LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF); // wylaczenie wyswietlacza
    LCD_WriteCommand(HD44780_CLEAR); // czyszczenie zawartosci pamieci DDRAM
    _delay_ms(2);
    LCD_WriteCommand(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);// inkrementaja adresu i przesuwanie kursora
    LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK); // wlacz LCD, bez kursora i mrugania
}
