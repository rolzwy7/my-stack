void Fun_LCD_Write (uint8_t ParByte);

void Fun_WriteCharFontToCGRAM (const uint8_t* ParPatern, uint8_t ParAddress);

void Fun_LCD_Init (void);

void Fun_LCD_SetDDRAMAddress (int8_t ParLine, int8_t ParPosition);
	
void Fun_DisplayStringAtPossition (char* Par_Ptr, uint8_t Par_ByteCount, int8_t ParLine, int8_t ParPosition);

void Fun_ShiftDisplayWindow (uint8_t ParDirection);


