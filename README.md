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
    2.1.1 <a href="#gpio-example"><b >gpio example program</b> </a>
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

1. kenable GPIOx by aryana_GPIOx_Enable(char PortName)
2. set GPIOx Pin i as input or out put
3. use any funtcion as you need... :)

- **GPIO example**
  
```c++
aryana_GPIOx_PINi_Write(char PortName,unsigned int pin,int bit)
```
### ADC

#### ADC example

### Delay

### Lcd16x2

#### LCD example

### KeyPad 

#### KeyPad Example




