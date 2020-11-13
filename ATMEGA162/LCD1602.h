/*
 * LCD1602.h
 *
 * Created: 2020-07-07 오후 12:02:04
 *  Author: ghhan
 */ 


#ifndef LCD1602_H_
#define LCD1602_H_


unsigned char LCD_rCommand(void);
char LCD_BusyCheck(unsigned char temp);
void LCD_wCommand(char cmd);
void LCD_wBCommand(char cmd);
void LCD_Init(void);
void LCD_wData(unsigned char dat);
int LCD_wString(char *str);

void LCD_wData_TEST(unsigned char dat);
int LCD_wString_TEST(char *str);


#endif /* LCD1602_H_ */