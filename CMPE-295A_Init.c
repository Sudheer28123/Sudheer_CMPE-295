/*
===============================================================================
 Name        : CMPE-295A_Init.c
 Version     : 1.0
 Author      : Sudheer Doddapaneni
 Description : Master's Project
 References  : Jackson Zhao
===============================================================================
*/

#include<lpc17xx.h>
#include <stdio.h>

/* Numerical constants corresponding to Bit positions of ADCR and ADGR registers */
#define SBIT_BURST      16u
#define SBIT_START      24u
#define SBIT_PDN        21u
#define SBIT_EDGE       27u
#define SBIT_DONE       31u
#define SBIT_RESULT     4u
#define SBIT_CLCKDIV    8u

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
	/* Enable CLOCK for internal ADC controller */
    LPC_SC->PCONP |= (1 << 12);

    /*Set the clock and Power ON ADC module*/
    LPC_ADC->ADCR = ((1<<SBIT_PDN) | (10<<SBIT_CLCKDIV));

    /* Select the P0_23 AD0[0] for ADC function */
    LPC_PINCON->PINSEL1|= 0x01<<14;

	/* Select Channel 0 by setting 0th bit of ADCR */
    LPC_ADC->ADCR  |= 0x01;
}

/*Main function*/
int main()
{
    uint16_t adcData;

    //Clock and PLL configuration
    SystemInit();

    /*Initialize the ADC controller*/
    InitADC();

    while(1)
    {

        /*Start ADC conversion*/
        LPC_ADC->ADCR |= (1<<SBIT_START);

        /* Time delay to allow the ADC channel voltage to stabilize*/
        DELAY_us(500);

        /* wait till conversion completes i.e 'DONE' bit is set*/
        while(((LPC_ADC->ADGDR >> SBIT_DONE) & 1)==0);

        /*Read the 12bit ADC data from ADGDR register*/
        adcData = (LPC_ADC->ADGDR >> SBIT_RESULT) & 0xfff;

        /*Print the ADC result*/
        printf("ADC result: %d\n",adcData);

    }

    return 0;
}
