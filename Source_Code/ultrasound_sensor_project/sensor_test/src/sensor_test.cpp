/*
 ===============================================================================
 Name        : sensor_test.cpp
 Version     : 1.1
 Author      : Sujeeth Krishna Emmadi
 Description : Master's Project
 ===============================================================================
 */

#include<lpc17xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#define ULT_ADC false
#define ULT_PW	true


/********ADC Method*********/

/* Numerical constants corresponding to Bit positions of ADC registers */
#define BURST_BIT      16u
#define START_BIT      24u
#define PDN_BIT        21u
#define EDGE_BIT       27u
#define DONE_BIT       31u
#define RESULT_BIT     4u
#define CLCKDIV_BIT    8u
#define ADC_RES		   80u
#define VOLTAGE_RANGE  3.3
#define AVG_INTERVAL   60

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
    LPC_ADC->ADCR = (1<<PDN_BIT);

    /* Select the Port0 Pin23 (P0_23) AD0[0] (J6_15) for ADC function */
    LPC_PINCON->PINSEL1|= 0x01<<14;

    /* Select ADC Channel 0 by setting 0th bit of ADCR */
    LPC_ADC->ADCR  |= 0x01;
}

/*ADC execution function*/
void ultADC()
{
    uint16_t adcData;
    float adc_voltage=0;
    float inches = 0, cm = 0;

    /*Initialize the ADC controller*/
    InitADC();

    while(1)
    {
    	//Re-initialize variables at the start of every loop
    	//sum = 0;
    	cm = 0;
    	inches = 0;

    	/*AVG_INTERVAL number of loops to determine the average of the distance measured to increase accuracy*/
    	//for(int i = 0; i < AVG_INTERVAL; i++)
    	//{
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

    		        /*add all the adc_voltages for average*/
    		      //  sum += adc_voltage;
    	//}

    	/*average distance in inches*/
    	//inches = sum/AVG_INTERVAL;
    	inches = adc_voltage;

    	/*average distance in centimeters*/
    	cm = inches*2.54 + 5;

        /*Print the distance*/
        printf(" Dist: %fcm\n", cm);
        DELAY_us(1000);
    }
}

/*************Pulse-Width Calculation Method**************/

//Bits to set up Timer0 and Timer1
#define SBIT_TIMER0  1
#define SBIT_TIMER1	 2

//Bits to set in MCR that generate interrupt and clear MR0 register
#define SBIT_MR0I    0
#define SBIT_MR0R    1

//Bit to enable counter
#define SBIT_CNTEN   0

//Bits to enable pclks
#define PCLK_TIMER0  2
#define PCLK_TIMER1	 4

int start_time = 0, stop_time = 0, pulse_width = 0;
float inches = 0;
bool flag1 = true, flag2 = false, flag3 = false, rflag = true;

unsigned int getPrescalarForUs(uint8_t timerPclkBit)
{
    unsigned int pclk,prescalarForUs;
    pclk = (LPC_SC->PCLKSEL0 >> timerPclkBit) & 0x03; /* get the pclk info for required timer */

    switch ( pclk )                                   /* Decode the bits to determine the pclk*/
    {
    case 0x00:
        pclk = SystemCoreClock/4;
        break;

    case 0x01:
        pclk = SystemCoreClock;
        break;

    case 0x02:
        pclk = SystemCoreClock/2;
        break;

    case 0x03:
        pclk = SystemCoreClock/8;
        break;
    }

    prescalarForUs =pclk/1000000 - 1;                 /* Prescalar for 1us (1000000Counts/sec) */

    return prescalarForUs;
}

extern "C"
{
	void TIMER0_IRQHandler(void)
	{
		unsigned int isrMask;

		isrMask = LPC_TIM0->IR;
		LPC_TIM0->IR = isrMask;         /* Clear the Interrupt Bit */

		flag2 = true;
	}
}

//delay_us(int d_time) provides a delay in d_time us
void delay_us(int d_time)
{
	LPC_SC->PCONP |= (1 << SBIT_TIMER0); 					  /* Power ON Timer0 */

	LPC_TIM0->MCR  |= (1 << SBIT_MR0I);     			  /* Clear TC on MR0 match and Generate Interrupt*/
	LPC_TIM0->MCR  |= (1 << SBIT_MR0R);
	LPC_TIM0->PR   = getPrescalarForUs(PCLK_TIMER0);      /* Prescalar for 1us */
	LPC_TIM0->MR0  = d_time;                 			  /* Load timer value to generate d_time us delay*/
	LPC_TIM0->TCR  |= (1 <<SBIT_CNTEN);                    /* Start timer by setting the Counter Enable*/
	NVIC_EnableIRQ(TIMER0_IRQn);                          /* Enable Timer0 Interrupt */
}

extern "C"
{
void EINT3_IRQHandler(void)
{
	LPC_GPIOINT -> IO2IntClr |= (1 << 11);	//clear interrupt

	if(rflag)	//enters under rising edge condition
	{
		rflag = false;
		start_time = LPC_TIM1 -> TC;
	}else		//enters under falling edge condition
	{
		LPC_GPIO1 -> FIOCLR = (1 << 31); 	//make trigger level go LOW
		rflag = true;
		flag3 = true;
		stop_time = LPC_TIM1 -> TC;
	}
}
}

void ultPW()
{
	while(1)
	{
		if(flag1)
		{
			flag1 = false;	//does not re-enter until current sensor trigger cycle is completed

			start_time = 0;
			stop_time = 0;

			//setup TIMER1 for determining pulse width
			LPC_SC->PCONP |= (1<<SBIT_TIMER1); 					  /* Power ON Timer1 */
			LPC_TIM1->PR   = getPrescalarForUs(PCLK_TIMER1);      /* Prescalar for 1us */
			LPC_TIM1->TCR  |= (1 << SBIT_CNTEN);                    /* Start timer by setting the Counter Enable*/

			//sensor trigger
			LPC_GPIO1 -> FIODIR |= (1 << 31);
			LPC_GPIO1 -> FIOCLR = (1 << 31);
			LPC_GPIO1 -> FIOSET = (1 << 31);
			delay_us(100);
		}

			if(flag2)
			{
				flag2 = false;

				//setting up GPIO pin as input
				LPC_GPIO2 -> FIODIR &= ~(1 << 11);
				LPC_GPIOINT -> IO2IntClr |= (1 << 11);	//clear interrupt
				LPC_GPIOINT -> IO2IntEnR |= (1 << 11);	//enable rising edge interrupt
				LPC_GPIOINT -> IO2IntEnF |= (1 << 11);	//enable falling edge interrupt

				NVIC_EnableIRQ(EINT3_IRQn);				//enable callback
			}

				if(flag3)
				{
					flag3 = false;

					pulse_width = stop_time - start_time;	//calculate pulse width
					inches = pulse_width/10.0;				//convert width to inches

					printf("Distance = %0.2f inches\n", inches);

					flag1 = true;							//initiate next trigger cycle
				}
	}
}

int main()
{
	//Clock and PLL configuration
	SystemInit();

	if(ULT_ADC)	ultADC();

	if(ULT_PW)	ultPW();

	return 0;
}
