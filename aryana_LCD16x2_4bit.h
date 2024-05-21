//v0.1  @aryana_Bakhshandeh (pure shahpur)  

//PA0 - PA3 = D4- D7
//PA4 = RS
//PA5 =RW
//PA6 = EN


/*		-=========	Commands !============================================================
1	            Function Set: 8-bit, 1 Line, 5x7 Dots                       	0x30	48
2	            Function Set: 8-bit, 2 Line, 5x7 Dots                       	0x38	56
3	            Function Set: 4-bit, 1 Line, 5x7 Dots                       	0x20	32
4	            Function Set: 4-bit, 2 Line, 5x7 Dots                       	0x28	40
5	            Entry Mode	                                                    0x06	6
6	            Display off Cursor off
                (clearing display without clearing DDRAM content)	            0x08	8

7	            Display on Cursor on	                                        0x0E	14
8	            Display on Cursor off	                                        0x0C	12
9	            Display on Cursor blinking	                                    0x0F	15
10	            Shift entire display left	                                    0x18	24
11	            Shift entire display right	                                    0x1C	30
12	            Move cursor left by one character	                            0x10	16
13	            Move cursor right by one character	                            0x14	20
14	            Clear Display (also clear DDRAM content)	                    0x01	1
15	            Set DDRAM address or coursor position on display        0x80 + address*	      128 + address*
16	            Set CGRAM address or set pointer to CGRAM location	    0x40 + address**	  64 + address**


Sr.No.	Hex Code	Command to LCD instruction Register
1	    01	        Clear display screen
2	    02	        Return home
3	    04	        Decrement cursor (shift cursor to left)
4	    06	        Increment cursor (shift cursor to right)
5	    05	        Shift display right
6	    07	        Shift display left
7	    08	        Display off, cursor off
8	    0A	        Display off, cursor on
9	    0C	        Display on, cursor off
10	    0E	        Display on, cursor blinking
11	    0F	        Display on, cursor blinking
12	    10	        Shift cursor position to left
13	    14	        Shift the cursor position to the right
14	    18	        Shift the entire display to the left
15	    1C	        Shift the entire display to the right
16	    80	        Force cursor to the beginning ( 1st line)
17	    C0	        Force cursor to the beginning ( 2nd line)


*/

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
	LCD_command(0x28);

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
