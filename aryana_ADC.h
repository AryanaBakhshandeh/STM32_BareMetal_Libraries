//v0.1  @aryana_Bakhshandeh (pure shahpur)  


void pa1_adc_init(void)
{
    /***    GPIOA   ***/ 
    /* enable gpio */
    RCC->AHB1ENR |= (1U<<0);
    /* set mode pa1  to Analog*/
    GPIOA->MODER=| (3U<<2);

    /***    config ADC module   ***/
    //enable adc
    RCC->APB2ENR |=(1U<<8);
    //conversion sequence start
    ADC1->SQR3 =(1U<<0); //(chanel 1)
    //conversion sequence Lenght
    ADC1->SQR1 = 0x00; //or 0U ? 
    // enable adc module 
    ADC1->CR2 |= 0b01; // or 1U ?

}


void start_convertion()
{
   /*start adc conversion*/
   ADC1->CR2 |= (1U<<30);
}
uint32_t adc_read()
{
     /*wait for conversion to be complited*/
    while(!(ADC1->SR & SR_EOC))

    /*Read cpmverted result*/
    return (ADC1->DR);
}
