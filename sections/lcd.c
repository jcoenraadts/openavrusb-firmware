#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>

#include <util/delay.h>

#include "hd44780.h"
#include "lcd.h"

//LCD section is 0x1C
void instrCall_LCD(char instruction, char* datain, char dataLength)
{
  switch (instruction)
  {
  case LCD_INIT:
    {
      lcd_init();
      break;
    }
  case LCD_WRITE:
    {
      lcd_putString(datain, dataLength);
      break;
    }
  case LCD_CLEAR:
    {
      lcd_clear();
      break;
    }
  }
}

void lcd_init(void)
{

  hd44780_init();

  /*
   * Clear the display.
   */
  hd44780_outcmd(HD44780_CLR);
  hd44780_wait_ready();

  /*
   * Entry mode: auto-increment address counter, no display shift in
   * effect.
   */
  hd44780_outcmd(HD44780_ENTMODE(1, 0));
  hd44780_wait_ready();

  /*
   * Enable display, activate non-blinking cursor.
   */
  hd44780_outcmd(HD44780_DISPCTL(1, 0, 0));
  hd44780_wait_ready();

}

void lcd_putchar(char c)
{
  static bool nl_seen;

  if (nl_seen && c != '\n')
    {
      /*
       * First character after newline, clear display and home cursor.
       */
      hd44780_wait_ready();
      hd44780_outcmd(HD44780_CLR);
      hd44780_wait_ready();
      hd44780_outcmd(HD44780_HOME);
      hd44780_wait_ready();
      hd44780_outcmd(HD44780_DDADDR(0));

      nl_seen = false;
    }
  if (c == '\n')
    {
      nl_seen = true;
    }
  else
    {
      hd44780_wait_ready();
      hd44780_outdata(c);
    }

  return;
}

void lcd_putString(char* string, char length)
{
  char i;
  hd44780_outcmd(string[0]);     //first byte delivered is the cursor position 0x80 line 1, 0xC0, line 2
  for(i = 1; i < length; i++)
    lcd_putchar(string[i]);
}

void lcd_clear()
{
  hd44780_outcmd(HD44780_CLR);
  hd44780_wait_ready();
}
