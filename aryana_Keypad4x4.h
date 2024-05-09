//v0.1  @aryana_Bakhshandeh (pure shahpur)  

/* define :
 aryana_GPIO.h
 aryana_SysTickDelay.h
*/

/*
array {   '1' , '2' , '3' , 'A',
          '4' , '5' , '6' , 'B',
          '7' , '8' , '9' , 'C',
          '*' , '0' , '#' , 'D'  }
*/
// please just set  KeyPad_port to  your preference ! if you want to change Pins , you Must change << KeyPad_Listen_InsideLoop() >>  as well !
#define KeyPad_port 'C'  // 'A' or 'B' or 'C' or 'D'
// Dont change Pin maps !! if you want to , you must change << KeyPad_Listen_InsideLoop() >> function  Completely !!
//honestly im working on it , til tonight maybe ? or til next 3 days ?
#define KeyPad_row1Pin 0
#define KeyPad_row2Pin 1
#define KeyPad_row3Pin 2
#define KeyPad_row4Pin 3

#define KeyPad_col1Pin 4
#define KeyPad_col2Pin 5
#define KeyPad_col3Pin 6
#define KeyPad_col4Pin 7

int KeyPad_flag = 0; // is Any key pressd ?
int KeyPad_PressedRow = 0;
int KeyPad_PressedCol = 0;
int KeyPad_PortX_Value[16] = {0};
int keyPad_KeyPadRowsValue[4]={0}; //value of KeyPad_row1Pin ~ KeyPad_row4Pin
char KeyPad_ArrayCharacters[16] = {'1', '2', '3', 'A',
                                   '4', '5', '6', 'B',
                                   '7', '8', '9', 'C',
                                   '*', '0', '#', 'D'};



void KeyPad_ResetPins()
{
     aryana_GPIOx_PINi_High(KeyPad_port, KeyPad_col1Pin);
     aryana_GPIOx_PINi_High(KeyPad_port, KeyPad_col2Pin);
     aryana_GPIOx_PINi_High(KeyPad_port, KeyPad_col3Pin);
     aryana_GPIOx_PINi_High(KeyPad_port, KeyPad_col4Pin);
}
void KeyPad_Init(void)
{

     // AHB1ENR
     aryana_GPIOx_Enable(KeyPad_port);
     // moder
     aryana_GPIOx_PINiSetMode_INPUT(KeyPad_port, KeyPad_row1Pin);
     aryana_GPIOx_PINiSetMode_INPUT(KeyPad_port, KeyPad_row2Pin);
     aryana_GPIOx_PINiSetMode_INPUT(KeyPad_port, KeyPad_row3Pin);
     aryana_GPIOx_PINiSetMode_INPUT(KeyPad_port, KeyPad_row4Pin);
     aryana_GPIOx_PINiSetMode_OUT(KeyPad_port, KeyPad_col1Pin);
     aryana_GPIOx_PINiSetMode_OUT(KeyPad_port, KeyPad_col2Pin);
     aryana_GPIOx_PINiSetMode_OUT(KeyPad_port, KeyPad_col3Pin);
     aryana_GPIOx_PINiSetMode_OUT(KeyPad_port, KeyPad_col4Pin);
     // ODR
     KeyPad_ResetPins();
}



int KeyPad_Listen_InsideLoop()
{
      // ???? how to program this mother Fuzzer to define pins as we wish ?  ¬_¬ ?? ( to be able to set pins as we wish )
     //..
     //..
     //..
     // Ok I got it...   ^_~
     KeyPad_flag = 0;
     aryana_GPIOx_Read(KeyPad_port, KeyPad_PortX_Value);
     keyPad_KeyPadRowsValue[0]= KeyPad_PortX_Value[KeyPad_row1Pin];
     keyPad_KeyPadRowsValue[1]= KeyPad_PortX_Value[KeyPad_row2Pin];
     keyPad_KeyPadRowsValue[2]= KeyPad_PortX_Value[KeyPad_row3Pin];
     keyPad_KeyPadRowsValue[3]= KeyPad_PortX_Value[KeyPad_row4Pin];
     for (int i = 0; i < 4; i++) // pin i=0 to 3 means   row 1 to row 4
     {
          if (keyPad_KeyPadRowsValue[i] == 1)
          {
               KeyPad_flag = 1;
               return i;
          }
     }
}

void KeyPad_RowColFinder()
{
     if (KeyPad_flag == 1)
     {
          // check col0;
          aryana_GPIOx_PINi_High(KeyPad_port, KeyPad_col1Pin);
          aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col2Pin);
          aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col3Pin);
          aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col4Pin);
          KeyPad_flag = 0;
          int RowHolder = KeyPad_Listen_InsideLoop();
          if (KeyPad_flag == 1)
          {
               KeyPad_PressedRow = RowHolder; // char[0][RowHolder] (rowHolder[0~3])
               KeyPad_PressedCol = 0;
          }
          else
          {
               // check col1;
               aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col1Pin);
               aryana_GPIOx_PINi_High(KeyPad_port, KeyPad_col2Pin);
               aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col3Pin);
               aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col4Pin);
               KeyPad_flag = 0;
               RowHolder = KeyPad_Listen_InsideLoop();
               if (KeyPad_flag == 1)
               {
                    KeyPad_PressedRow = RowHolder; // char[1][row]]
                    KeyPad_PressedCol = 1;
               }
               else
               {
                    // check col2;
                    aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col1Pin);
                    aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col2Pin);
                    aryana_GPIOx_PINi_High(KeyPad_port, KeyPad_col3Pin);
                    aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col4Pin);
                    KeyPad_flag = 0;
                    RowHolder = KeyPad_Listen_InsideLoop();
                    if (KeyPad_flag == 1)
                    {
                         KeyPad_PressedRow = RowHolder; // char[2][row]]
                         KeyPad_PressedCol = 2;
                    }
                    else
                    {
                         // check col2;
                         aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col1Pin);
                         aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col2Pin);
                         aryana_GPIOx_PINi_Low(KeyPad_port, KeyPad_col3Pin);
                         aryana_GPIOx_PINi_High(KeyPad_port, KeyPad_col4Pin);
                         KeyPad_flag = 0;
                         RowHolder = KeyPad_Listen_InsideLoop();
                         if (KeyPad_flag == 1)
                         {
                              KeyPad_PressedRow = RowHolder; // char[1][row]]
                              KeyPad_PressedCol = 3;
                         }
                    }
               }
          }

          sysTickDelay_ms(100);
          // finished proccess , now reset output pins to start listining again
          KeyPad_ResetPins();
     }
}
//==============================================================================================
//==============================================================================================
//==============================================================================================
//==============================================================================================
// how to use this Lib ?//================================================
//======================================================
//======================================================
//======================================================
//=========================================
//=========================================
//=========================================
/*
     #include <stm32f4xx.h>
     #include "aryana_GPIO.h"
     #include "aryana_SysTickDelay.h"
     #include "aryana_Keypad4x4.h"
     #include "aryana_LCD16x2_4bit.h"
     int main()
     {
          LCD_Initialaze();
          KeyPad_Init();
          while (1)
          {
               KeyPad_Listen_InsideLoop();
               KeyPad_RowColFinder();
               //now col and row is been found ... do your things....
               if(KeyPad_flag==1){
                    LCD_data_Character(KeyPad_ArrayCharacters[(4*KeyPad_PressedRow) + (KeyPad_PressedCol)]);
                    KeyPad_flag=0;
                    sysTickDelay_ms(2000);
               }
               ////-----------------------------------------------
               KeyPad_ResetPins();
          }
     }



//==============================================================================================
//==============================================================================================
//==============================================================================================
//==============================================================================================
// example of Keypad algoritm  without Library//================================================
//======================================================
//======================================================
//======================================================
//=========================================
//=========================================
//=========================================

#include <stm32f4xx.h>

#include <aryana_GPIO.h>
#include <aryana_SysTickDelay.h>


int KeyPad_PressedRow=0;
int KeyPad_PressedCol=0;
int PortC_Value[16] = {0};


int main(void)
{
     aryana_GPIOx_Enable('A'); //test Row
     aryana_GPIOx_Enable('B'); // test Col

     GPIOA->MODER =0b01010101010101010101010101010101;
     GPIOB->MODER =0b01010101010101010101010101010101;
     // keypad init
     aryana_GPIOx_Enable('C');
     GPIOC->MODER =0b01010101010101010101010100000000; // C as output     0,1,2,3 input  (4,5,6,7  output=1)
     aryana_GPIOx_PINi_Write('C', 15, 0);
     aryana_GPIOx_PINi_Write('C', 4, 1);
     aryana_GPIOx_PINi_Write('C', 5, 1);
     aryana_GPIOx_PINi_Write('C', 6, 1);
     aryana_GPIOx_PINi_Write('C', 7, 1);

     int KeyPad_flag = 0;
     int lastFlag=0;
     while (1)
     {

          KeyPad_flag=0;
         KeyPad_Listen_InsideLoop();


          if (KeyPad_flag == 1)
          {
               // check col0;
               aryana_GPIOx_PINi_High('C', 4);
               aryana_GPIOx_PINi_Low('C', 5);
               aryana_GPIOx_PINi_Low('C', 6);
               aryana_GPIOx_PINi_Low('C', 7);
               KeyPad_flag = 0;
               int RowHolder = KeyPad_Listen_LoopMode(&KeyPad_flag);
               if (KeyPad_flag == 1)
               {
                    KeyPad_PressedRow=RowHolder ; // char[0][RowHolder] (rowHolder[0~3])
                    KeyPad_PressedCol=0;

               }
               else
               {
                    // check col1;
                    aryana_GPIOx_PINi_Low('C', 4);
                    aryana_GPIOx_PINi_High('C', 5);
                    aryana_GPIOx_PINi_Low('C', 6);
                    aryana_GPIOx_PINi_Low('C', 7);
                    KeyPad_flag = 0;
                    RowHolder = KeyPad_Listen_LoopMode(&KeyPad_flag);
                    if (KeyPad_flag == 1)
                    {
                         KeyPad_PressedRow=RowHolder ; // char[1][row]]
                         KeyPad_PressedCol=1;
                    }
                    else{
                              // check col2;
                         aryana_GPIOx_PINi_Low('C', 4);
                         aryana_GPIOx_PINi_Low('C', 5);
                         aryana_GPIOx_PINi_High('C', 6);
                         aryana_GPIOx_PINi_Low('C', 7);
                         KeyPad_flag = 0;
                         RowHolder = KeyPad_Listen_LoopMode(&KeyPad_flag);
                         if (KeyPad_flag == 1)
                         {
                              KeyPad_PressedRow=RowHolder ; // char[2][row]]
                              KeyPad_PressedCol=2;
                         }
                         else{
                                   // check col2;
                              aryana_GPIOx_PINi_Low('C', 4);
                              aryana_GPIOx_PINi_Low('C', 5);
                              aryana_GPIOx_PINi_Low('C', 6);
                              aryana_GPIOx_PINi_High('C', 7);
                              KeyPad_flag = 0;
                              RowHolder = KeyPad_Listen_LoopMode(&KeyPad_flag);
                              if (KeyPad_flag == 1)
                              {
                                   KeyPad_PressedRow=RowHolder ; // char[1][row]]
                                   KeyPad_PressedCol=3;
                              }
                         }
                    }
               }
               aryana_GPIOx_PINi_Write('A',KeyPad_PressedRow,1);
               aryana_GPIOx_PINi_Write('B',KeyPad_PressedCol,1);
               sysTickDelay_ms(1000);
               //finished proccess , now reset output pins to start listining again
               aryana_GPIOx_PINi_Write('C', 4, 1);
               aryana_GPIOx_PINi_Write('C', 5, 1);
               aryana_GPIOx_PINi_Write('C', 6, 1);
               aryana_GPIOx_PINi_Write('C', 7, 1);

          }
          else{
               aryana_GPIOx_PINi_Write('A',KeyPad_PressedRow,0);
               aryana_GPIOx_PINi_Write('B',KeyPad_PressedCol,0);
               lastFlag=0; //not pressed


          }


     }
     return 0;
}
     int KeyPad_Listen_LoopMode(int *flag)
     {
          *flag = 0;
          aryana_GPIOx_Read('C', PortC_Value);
          for (int i = 0; i < 4; i++)
               if (PortC_Value[i] == 1)
               {
                    *flag = 1;
                    return i;
               }
     }

     // read port b
     //		while(1)
     //		{
     //			aryana_GPIOx_Read('B',PortB_Value);
     //			for(int i =0 ; i<16 ; i++)
     //				aryana_GPIOx_PINi_Write('C',i,PortB_Value[i]); // example : GPIOx_PINi_LOW('A',2) -> sets PA2 to low ,that is, it resets PA2
     //
     //			sysTickDelay_ms(100);
     //			listining
     //
     //		}

*/
