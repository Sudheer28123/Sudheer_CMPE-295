/*
 ===============================================================================
 Name        : CMPE-295A_Init.c
 Version     : 1.1
 Author      : Sudheer Doddapaneni
 Description : Master's Project
 References  : Jackson Zhao
 ===============================================================================
 */

#include<lpc17xx.h>
#include <stdio.h>

/* Numerical constants corresponding to Bit positions of ADC registers */
#define BURST_BIT      16u
#define START_BIT      24u
#define PDN_BIT        21u
#define EDGE_BIT       27u
#define DONE_BIT       31u
#define RESULT_BIT     4u
#define CLCKDIV_BIT    8u
#define ADC_RES		   4095u
#define VOLTAGE_RANGE  3.3

/*Function to provide delay when needed*/
void DELAY_us(int len)
{
    for(int p=0;p<len;p++)
    {
        for(int k=0;k<1000;k++)
        {
            
        }
    }
}

/*ADC Initialization function*/
void InitADC(void)
{
    /* Enable CLOCK for ADC peripheral controller */
    LPC_SC->PCONP |= (1 << 12);
    
    /*Set the clock and Power ON ADC module*/
    LPC_ADC->ADCR = ((1<<PDN_BIT) | (10<<CLCKDIV_BIT));
    
    /* Select the Port0 Pin23 (P0_23) AD0[0] (J6_15) for ADC function */
    LPC_PINCON->PINSEL1|= 0x01<<14;
    
    /* Select ADC Channel 0 by setting 0th bit of ADCR */
    LPC_ADC->ADCR  |= 0x01;
}

/*Main function*/
int main()
{
    uint16_t adcData;
    float adc_voltage=0;
    
    //Clock and PLL configuration
    SystemInit();
    
    /*Initialize the ADC controller*/
    InitADC();
    
    while(1)
    {
        
        /*Start ADC conversion*/
        LPC_ADC->ADCR |= (1<<START_BIT);
        
        /* Time delay to allow the ADC channel voltage to stabilize*/
        DELAY_us(500);
        
        /* wait till conversion completes i.e 'DONE' bit is set*/
        while(((LPC_ADC->ADGDR >> DONE_BIT) & 1)==0);
        
        /*Read the 12bit ADC data from ADGDR register*/
        adcData = (LPC_ADC->ADGDR >> RESULT_BIT) & 0xfff;
        
        /*Convert the ADC data into corresponding voltage*/
        adc_voltage = (adcData*VOLTAGE_RANGE) /ADC_RES ;
        
        /*Print the ADC result*/
        printf("ADC result: %4d\t ADC voltage: %fV\n",adcData, adc_voltage);
        
    }
    
    return 0;
}
