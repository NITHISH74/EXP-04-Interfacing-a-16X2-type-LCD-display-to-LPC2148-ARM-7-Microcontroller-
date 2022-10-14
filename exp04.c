#include<lpc214x.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
void delay_ms(uint16_t j)    /* Function delay in milliseconds*/
{
	uint16_t x,i;
	for(i=0;i<j;i++)
	{
		for(x=0;x<6000;x++);     /*loop to generate 1 ms delay with Cclk = 600Mhz*/
	}
}
void LCD_CMD(char command)
{
	IO0PIN = ((IO0PIN & 0xFFFF00FF) |(command<<8));
	IO0SET = 0x00000040;    /*EN=1*/
	IO0CLR = 0x00000030;    /*RS=0,RW=0*/
	delay_ms(2);
	IO0CLR = 0x00000040;      /*EN=0,RS AND RW UNCHANGED(RS=RW=0)*/
	delay_ms(5);
}
void LCD_INIT(void)
{
	IO0DIR = 0x0000FFF0;     /*P0.8 TO P0.15 LCD DATA*/
	delay_ms(20);
	LCD_CMD(0x38);     /*INITIALIZE LCD*/
	LCD_CMD(0x0c);     /*DISPLAY ON CURSOR OFF*/  
	LCD_CMD(0x06);      /*AUTO INCREMENT CURSOR*/
	LCD_CMD(0x01);        /*DISPLAY CLEAR*/
	LCD_CMD(0x80);       /*FIRST LINE FIRST POSITION*/
}
void LCD_STRING(char*msg)
{
	uint8_t i=0;
	while(msg[i]!=0)
	{
		IO0PIN = ((IO0PIN & 0xFFFF00FF) | (msg[i]<<8));
		IO0SET = 0x00000050;   /*RS =1 , EN = 1*/
		IO0CLR = 0x00000020;     /* RW=0*/
		delay_ms(2);
		IO0CLR = 0x00000040;     /* EN=0,RS & RW UNCHANGED (RS=1,RW=0)*/
		delay_ms(5);
		i++;
	}
}
void LCD_CHAR(char msg)
{
	IO0PIN = ((IO0PIN & 0xFFFF00FF) | (msg<<8));
	IO0SET = 0x00000050;     /*RS =1 , EN = 1*/
	IO0CLR = 0x00000020;    /* RW=0*/
	delay_ms(2);
	IO0CLR = 0x00000040;       /* EN=0,RS & RW UNCHANGED (RS=1,RW=0)*/
	delay_ms(5);
}
int main(void)
{
	/*uint8_t j;
  j=0;
	char val_j[3];*/
	LCD_INIT();
	LCD_STRING("WELCOME TO AI&DS");
	LCD_CMD(0xC0);
		LCD_STRING("NITHISHWAR S");

	return 0;
}
