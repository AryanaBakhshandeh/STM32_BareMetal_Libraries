# STM32_BareMetal_Libraries
<h1>Table of contents</h1>

<ol dir="auto">
  <li>
    <a href="#about">About</a>
  </li>
  <li> 
    <a href="#how-to-use-libraries">How to use Libraries </a>
    <br>
    2.1 <a href="#gpio"><b >GPIO</b> </a>
    <br>
    2.2 <a href="#adc-example"> <b>ADC</b> </a>
    <br>
    2.3 <a href="#delay"><b>Delay</b></a>
    <br>
    2.4 <a href="#lcd16x2"><b>Lcd16x2</b></a>
    <br>
    2.5 <a href="#keypad"><b>KeyPad</b> </a>
  </li>
</ol>

## About

There you can find Libraries for your STM32 projects that is written in bare-metal method. <br>
I'm still working on this ... <br>

currently you can find these libraries in my repository:
<ul>
  <li >aryana_GPIO.h</li>
  <li>aryana_ADC.h</li>
  <li>aryana_SysTickDelay.h</li>
  <li>aryana_LCD16x2_4bit.h</li>
  <li>aryana_Keypad4x4.h</li>
</ul>

In the following ,you can find the instructions about each libraries that i wrote. so fill free to look at them ...

## How to use Libraries
at first , you must include your propper stm32fyxx.h library to your project. <br>( for example if you use stm32f401re you should include stm32f4xx.h)


### GPIO
- **this library has the following functions:** 


1. enable Portx's clock
```c++
aryana_GPIOx_Enable(char PortName) 
```
  2. Set Port x Pin i as Input
```c++
 aryana_GPIOx_PINiSetMode_INPUT(char PortName,unsigned int pin)
```  
  3. Set Port x Pin i as Output
```c++
aryana_GPIOx_PINiSetMode_OUT(char PortName,unsigned int pin) 
```  
  4. Set Port x Pin i Low (0)
```c++
 aryana_GPIOx_PINi_Low(char PortName,unsigned int pin)
```
  5.  Set Port x Pin i High (1)
```c++
aryana_GPIOx_PINi_High(char PortName,unsigned int pin)
```
  6. set value of Port x pin i 0 or 1
```c++
aryana_GPIOx_PINi_Write(char PortName,unsigned int pin,int bit)
```
  7.   read entire Portx's value and write it to {int* PortInputValue_Array} 
```c++
aryana_GPIOx_Read(char PortName,int* PortInputValue_Array)
```

- **HOW TO USE**

1. enable GPIOx by aryana_GPIOx_Enable(char PortName)
2. set GPIOx Pin i as input or out put
3. use any funtcion as you need... :)

- **GPIO example**
***Blinking LED***
```c++
#include <stm32f4xx.h>
#include <aryana_GPIO.h>

#define LED_PORT 'A'
#define LED_PIN 2


int main(void)
{
  aryana_GPIOx_Enable(LED_PORT) ;
  aryana_GPIOx_PINiSetMode_OUT(LED_PORT,LED_PIN)'
  while(1)
  {
      aryana_GPIOx_PINi_High(LED_PORT,LED_PIN);
      for(int i=0;i<6000 <i++);
      aryana_GPIOx_PINi_LOW(LED_PORT,LED_PIN);
      for(int i=0;i<6000 <i++);
  }
}

```

### ADC


### Delay
- **this library has the following functions:** 
1.
```c++
sysTickDelay_ms(int delay_ms)
```
2. 
```c++
sysTickDelay_us(int delay_us)
```
### Lcd16x2

- **this library has the following functions:** 
1. config LCD's GPIO pins and turn it on in 4 bit mod 
  ```c++
  LCD_Initialaze();
  ```
2. send command to LCD
  ```c++
  LCD_command(unsigned char command);
  ```
3. send single character to LCD
  ```c++
  LCD_data_Character(unsigned char command)
  ```
4.send string to LCD 
  ```c++
   LCD_data_String(char string[]);
  ```

- **HOW TO USE**
1. first edit the following macros to match the Hardware

```c++
#define LCD_port 'A'
#define LCD_RS_pin 4
#define LCD_RW_pin 5
#define LCD_EN_pin 6
```

2. use LCD_Initialize() function to config GPIO and Run LCD in 4 bit mode
3.  use LCD_command or LCD_Data functions as you wish... :)

### KeyPad 
**this library has the following functions:**
1. initialize KeyPad 
```c
KeyPad_Init(void) 
```
2. listen to the KeyPad . if any keys is pressed by the user , ***KeyPad_flag*** will become 1  .
```c
KeyPad_Listen_InsideLoop()
```
3.find the Row And Col of the Keypad's key that is pressed. the row and col value is stord in these variables : int ***KeyPad_PressedRow*** ***int KeyPad_PressedCol***
<br>*use this function after ***KeyPad_Listen_InsideLoop()*** as the example .
```c
KeyPad_RowColFinder()
```

- **HOW TO USE**
1. first edit the following macros and array to match the Hardware
```c++
#define KeyPad_port 'C'  // 'A' or 'B' or 'C' or 'D'
#define KeyPad_row1Pin 0
#define KeyPad_row2Pin 1
#define KeyPad_row3Pin 2
#define KeyPad_row4Pin 3

#define KeyPad_col1Pin 4
#define KeyPad_col2Pin 5
#define KeyPad_col3Pin 6
#define KeyPad_col4Pin 7


char KeyPad_ArrayCharacters[16] = {'1', '2', '3', 'A',
                                   '4', '5', '6', 'B',
                                   '7', '8', '9', 'C',
                                   '*', '0', '#', 'D'};

```
2. initialize KeyPad 
```c
KeyPad_Init(void) 
```
3. do as the following example. 

**example**
```c++
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

```


