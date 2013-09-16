#ifndef _LCD_H_
#define _LCD_H_

#define LCD_WRITE 0x10
#define LCD_READ 0x11
#define LCD_INIT 0x12
#define LCD_CLEAR 0x13

void lcd_init(void);
void lcd_putchar(char c);
void lcd_clear();
void instrCall_LCD(char instruction, char* data, char dataLength);
void lcd_putString(char* string, char length);

#endif
