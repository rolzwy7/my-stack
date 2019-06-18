#ifndef MAIN_H
#define MAIN_H

#define F_CPU 16000000UL

#define LCD_RS_DIR		DDRD
#define LCD_RS_PORT    	PORTD
#define LCD_RS         	(1 << PD3)

#define LCD_E_DIR      	DDRD
#define LCD_E_PORT      PORTD
#define LCD_E         	(1 << PD2)

#define LCD_DB4_DIR     DDRD
#define LCD_DB4_PORT   	PORTD
#define LCD_DB4         (1 << PD4)

#define LCD_DB5_DIR     DDRD
#define LCD_DB5_PORT   	PORTD
#define LCD_DB5         (1 << PD5)

#define LCD_DB6_DIR     DDRD
#define LCD_DB6_PORT   	PORTD
#define LCD_DB6         (1 << PD6)

#define LCD_DB7_DIR     DDRD
#define LCD_DB7_PORT   	PORTD
#define LCD_DB7         (1 << PD7)

#endif//MAIN_H
