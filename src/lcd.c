#include "Arduino.h"
#include "lcd.h"

void lcd_write_char(char character)
{
  int i ;
  lcd_write_cmd(HIGH, 0x00);
  for (i = 0; i < 5; i++)
  {
    lcd_write_cmd(HIGH, ASCII[character - 0x20][i]);
  }
  lcd_write_cmd(HIGH, 0x00);
}

void lcd_clear_display(void)
{
  int i ;
  for (i = 0; i < LCD_X * LCD_Y / 8; i++)
  {
    lcd_write_cmd(HIGH, 0x00);
  }
}

void lcd_clear_row(int y)
{
  int i ;
  lcd_pos(0, y) ;
  for (i = 0 ; i < LCD_X ; i++) {
    lcd_write_cmd(HIGH, 0x00) ;
  }
}

void lcd_pos(int x, int y)
{
  lcd_write_cmd(LOW, 0x80 | x);  // Column.
  lcd_write_cmd(LOW, 0x40 | y);  // Row.  
}

void lcd_init(void)
{
  pinMode(LCD_SCE, OUTPUT);
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_DC, OUTPUT);
  pinMode(LCD_MOSI, OUTPUT);
  pinMode(LCD_SCLK, OUTPUT);
  digitalWrite(LCD_RST, LOW);
  digitalWrite(LCD_RST, HIGH);
  lcd_write_cmd(LOW, 0x21 );  // LCD Extended Commands.
  lcd_write_cmd(LOW, 0xB1 );  // Set LCD Vop (Contrast). 
  lcd_write_cmd(LOW, 0x04 );  // Set Temp coefficent. //0x04
  lcd_write_cmd(LOW, 0x14 );  // LCD bias mode 1:48. //0x13
  lcd_write_cmd(LOW, 0x20 );  // LCD Basic Commands
  lcd_write_cmd(LOW, 0x0C );  // LCD in normal mode.
}

void lcd_write_str(char *characters)
{
  while (*characters)
  {
    lcd_write_char(*characters++);
  }
}

void lcd_write_cmd(byte dc, byte data)
{
  digitalWrite(LCD_DC, dc);
  digitalWrite(LCD_SCE, LOW);
  shiftOut(LCD_MOSI, LCD_SCLK, MSBFIRST, data);
  digitalWrite(LCD_SCE, HIGH);
}

void lcd_print_float(double d)
{
  static int row = 1 ;
  static char buf[12] ;
  lcd_clear_row(row) ;
  lcd_pos(0, row) ;
  dtostrf(d, 1, 7, buf) ;
  lcd_write_str(buf) ;
  row = row == 4 ? 1 : row + 1 ;
}
