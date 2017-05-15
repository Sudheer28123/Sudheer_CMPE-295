/*
*Created March 10th, 2017
*By Sujeeth Krishna Emmadi
*
*/

#include "ultsensor.h"
#include "portmacro.h"

unsigned int getPrescalarForUs(uint8_t timerPclkBit, int option)
{
    unsigned int pclk,prescalarForUs;
	
	if(option == 0)
	{
		pclk = (LPC_SC->PCLKSEL0 >> timerPclkBit) & 0x03; /* get the pclk info for required timer */
	}else{
		pclk = (LPC_SC->PCLKSEL1 >> timerPclkBit) & 0x03; /* get the pclk info for required timer */
	}

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


void TIMER2_IRQHandler(void)
{

	unsigned int isrMask;

		//printf("2\n");

		isrMask = LPC_TIM2->IR;
		LPC_TIM2->IR = isrMask;         /* Clear the Interrupt Bit */

		Ult.flag2 = true;
}

//delay_us(int d_time) provides a delay in d_time us
void delay_us(int d_time)
{
	LPC_TIM2->MR0  = d_time;                 			  /* Load timer value to generate d_time us delay*/
	LPC_TIM2->TCR  |= (1 <<SBIT_CNTEN);                    /* Start timer by setting the Counter Enable*/
}

void EINT3_IRQHandler(void)
{	
	//rising edge interrupt at ULTSEN_Task
	if((LPC_GPIOINT -> IO2IntStatR & (1 << ULT_INT_PIN)) == (1 << ULT_INT_PIN))
	{
		LPC_GPIOINT -> IO2IntClr |= (1 << ULT_INT_PIN);	//clear interrupt
		Ult.start_time = LPC_TIM1 -> TC;
	}

	//falling edge interrupt at ULTSEN_Task
	if((LPC_GPIOINT -> IO2IntStatF & (1 << ULT_INT_PIN)) == (1 << ULT_INT_PIN))
	{
		LPC_GPIOINT -> IO2IntClr |= (1 << ULT_INT_PIN);	//clear interrupt
		Ult.stop_time = LPC_TIM1 -> TC;
		LPC_GPIO1 -> FIOCLR = (1 << 31); 	//make trigger level go LOW
		Ult.flag3 = true;
	}
}

void ULTSEN_init()
{
		//TIMER0 for delay_us()
		LPC_SC->PCONP |= (1 << SBIT_TIMER2); 					  /* Power ON Timer2 */
		LPC_TIM2->MCR  |= (1 << SBIT_MR0I);     			  /* Clear TC on MR0 match and Generate Interrupt*/
		LPC_TIM2->MCR  |= (1 << SBIT_MR0R);
		LPC_TIM2->PR   = getPrescalarForUs(PCLK_TIMER2,1);      /* Prescalar for 1us */
		NVIC_SetPriority( TIMER2_IRQn, 2);
		NVIC_EnableIRQ(TIMER2_IRQn);                          /* Enable Timer2 Interrupt */

		//setup TIMER1 for determining pulse width
		LPC_SC->PCONP |= (1<<SBIT_TIMER1); 					  /* Power ON Timer1 */
		LPC_TIM1->PR   = getPrescalarForUs(PCLK_TIMER1,0);      /* Prescalar for 1us */

		//sensor trigger
		LPC_GPIO1 -> FIODIR |= (1 << 31);

		//setting up GPIO pin as input
		LPC_GPIO2 -> FIODIR &= ~(1 << 11);
		LPC_GPIOINT -> IO2IntClr |= (1 << 11);	//clear interrupt
		LPC_GPIOINT -> IO2IntEnR |= (1 << 11);	//enable rising edge interrupt
		LPC_GPIOINT -> IO2IntEnF |= (1 << 11);	//enable falling edge interrupt
		NVIC_SetPriority( EINT3_IRQn, 1);
		NVIC_EnableIRQ(EINT3_IRQn);				//enable callback
}


void ULTSEN()
{
    	if(Ult.flag1)
    	    {
    				//printf("1\n");
    	    		Ult.flag1 = false;	//does not re-enter until current sensor trigger cycle is completed

    	    		Ult.start_time = 0;
    	    		Ult.stop_time = 0;

    	    		//setup TIMER1 for determining pulse width
    	    		LPC_TIM1->TCR  |= (1 << SBIT_CNTEN);                    /* Start timer by setting the Counter Enable*/

    	    		//sensor trigger
    	    		LPC_GPIO1 -> FIOCLR = (1 << 31);
    	    		LPC_GPIO1 -> FIOSET = (1 << 31);

    	     		delay_us(100);
    	    		//vTaskDelay(100);
    	    }

    		if(Ult.flag2)
    		{
    	  			//printf("3\n");
    				Ult.flag2 = false;
    		}

    		if(Ult.flag3)
    		{
    			//printf("6\n");
    				int pulse_width = 0;
    				int inches = 0;
    				int temp = 0;

    				Ult.flag3 = false;
    				pulse_width = Ult.stop_time - Ult.start_time;	//calculate pulse width
    				inches = pulse_width/10;						//convert width to inches
    				temp = inches;
    				final_data[6] = (uint8_t)(temp >> 8);
    				final_data[7] = (uint8_t)inches;

    				//printf("Distance = %d cm\t", inches);
    				Ult.flag1 = true;

    			portTickType xNextWakeTime = xTaskGetTickCount();
    			vTaskDelayUntil( &xNextWakeTime,configULT_FREQ);
    		}

}

void ULTSEN_Task(void *UltSenParam1)
{
	//printf("1\n");
	//printf("0\n");
	Ult.start_time = 0;
	Ult.stop_time = 0;
	Ult.flag1 = true;
	Ult.flag2 = false;
	Ult.flag3 = false;
	Ult.rflag = true;

	ULTSEN_init();

	while(1)
	{
		ULTSEN();
	}
}
