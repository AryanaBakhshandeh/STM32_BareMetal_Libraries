//v0.1  @aryana_Bakhshandeh (pure shahpur)  
#define sysFreq_Mhz 16  // by default it is 16 MHZ
#define CTRL_ENABLE      (1U<<0)
#define CTRL_CLKSRC      (1U<<2)
#define CTRL_COUNTFLAG   (1U<<16)
void sysTickDelay_us(int delay_us) // example : sysTickDelay_us(2);  ->delays 2us
{
    //reload with number of clock per ms 
        // 1s -> 16 000 000 clocks  => 10 clock -> 625nS   => delay = n_Clock *62.5nS  = n_clock/Freq       =>     delay *Freq =number of Clock =systick reload value
        //1us *16M= 16 clock
    SysTick->LOAD = 16;
    
    //clear systick current value register
    SysTick->VAL=0;

    //Enable sustick and select internal clk src
    SysTick->CTRL= CTRL_ENABLE |CTRL_CLKSRC;

    for(int i=0; i<delay_us ;i++){
        // wait until countflag is set
        while( (SysTick->CTRL & CTRL_COUNTFLAG)== 0 ){}

    }
    SysTick->CTRL=0;
}

void sysTickDelay_ms(int delay_ms) // example : sysTickDelay_ms(2);  ->delays 2 ms
{
    //reload with number of clock per ms 
        // 1s -> 16 000 000 clocks  => 10 clock -> 625nS   => delay = n_Clock *62.5nS  = n_clock/Freq       =>     delay *Freq =number of Clock =systick reload value
        //1ms *16M= 16000 clock
    SysTick->LOAD = 16000; //fekr konam error e type casting bede
    
    //clear systick current value register
    SysTick->VAL=0;

    //Enable sustick and select internal clk src
    SysTick->CTRL= CTRL_ENABLE |CTRL_CLKSRC;

    for(int i=0; i<delay_ms ;i++){
        // wait until countflag is set
        while( (SysTick->CTRL & CTRL_COUNTFLAG)== 0 ){}

    }
    SysTick->CTRL=0;
}
