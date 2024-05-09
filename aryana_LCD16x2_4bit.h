//v0.1  @aryana_Bakhshandeh (pure shahpur)  

//PA0 - PA3 = D4- D7
//PA4 = RS
//PA5 =RW
//PA6 = EN

#define LCD_port 'A'
#define LCD_RS_pin 4
#define LCD_RW_pin 5
#define LCD_EN_pin 6



int String_length(char string[]) {
    int i;
    int count = 0;
    for (i = 0; string[i] != '\0'; i++) {
        count++;
    }
    return count;
}


void LCD_GPIO_Init(void)
{

	sysTickDelay_ms(1000);
    aryana_GPIOx_Enable(LCD_port);
    for(int i=0;i<=6;i++)
    {
        aryana_GPIOx_PINiSetMode_OUT(LCD_port,i);
    }
    //set EN and RW to low;
    aryana_GPIOx_PINi_Low(LCD_port,LCD_EN_pin);
    aryana_GPIOx_PINi_Low(LCD_port,LCD_RW_pin);


}



void LCD_4UpperBitsWrite(char data ,int RS)// set RS  1(data) or 0(command)
{
    //Command or Data Mode:
    if(RS==0)
        aryana_GPIOx_PINi_Low(LCD_port,LCD_RS_pin);
    else
        aryana_GPIOx_PINi_High(LCD_port,LCD_RS_pin);
    // set data to lcd pins
    char Data4Bit = data & 0xF0;// high bits
    Data4Bit= ( (Data4Bit >> 4) & 0x0F ); // shift 4 bits to right and keep lower bits;
    
    for(int i=0;i<=3;i++)
    {
        int bit=1;
        int bitPositionValue=1;
        for(int j=0;j<i;j++){
            bitPositionValue=bitPositionValue*2;
        }
        if((Data4Bit & bitPositionValue)==0)
        {bit=0;}
        aryana_GPIOx_PINi_Write(LCD_port,i,bit);
    }
    aryana_GPIOx_PINi_High(LCD_port,LCD_EN_pin);
    sysTickDelay_us(3);
    aryana_GPIOx_PINi_Low(LCD_port,LCD_EN_pin);
    sysTickDelay_us(3);

}

void LCD_command(unsigned char command)
{
	 LCD_4UpperBitsWrite(command,0);
	 sysTickDelay_ms(1);
	 LCD_4UpperBitsWrite((command<<4),0);
	 sysTickDelay_ms(1);
}
void LCD_data_Character(unsigned char command)
{
	LCD_4UpperBitsWrite(command,1);
	sysTickDelay_ms(1);
	LCD_4UpperBitsWrite(command<< 4,1);
	sysTickDelay_ms(1);
}
void LCD_data_String(char string[])
{
	int index=0;
	for(index=0 ; index <String_length(string);index++ )
		LCD_data_Character(string[index]);

}

void LCD_Initialaze(){

// initialize GPIO
	LCD_GPIO_Init();
    sysTickDelay_ms(1000);
// 4 bit mode
	LCD_4UpperBitsWrite(0x20,0);
	sysTickDelay_ms(1);
// Clear display
	LCD_command(0x01);
// return home
	LCD_command(0x02);
// display on - no cursor
	LCD_command(0x0C);

}


// how to use:
/*
#include <stm32f4xx.h>
#include "aryana_GPIO.h"
#include "aryana_SysTickDelay.h"
#include "aryana_LCD16x2_4bit.h"
int main(void)
{
	LCD_Initialaze();
	// write data -------
	LCD_data_Character('H'); //H
	LCD_data_Character(0x49); //I
	LCD_data_String(" Pussy");
	while(1)
	{

	}
	return 0;
}
*/