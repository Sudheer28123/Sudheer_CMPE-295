/*
*Created March 10th, 2017
*By Sujeeth Krishna Emmadi
*
*/

#include "ultsensor.h"
#include "portmacro.h"

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


void TIMER0_IRQHandler(void)
{

	unsigned int isrMask;

		//printf("2\n");

		isrMask = LPC_TIM0->IR;
		LPC_TIM0->IR = isrMask;         /* Clear the Interrupt Bit */

		Ult.flag2 = true;



		portEND_SWITCHING_ISR(pdFALSE);

	long yield = 0;
		portYIELD();
}

//delay_us(int d_time) provides a delay in d_time us
void delay_us(int d_time)
{
	LPC_TIM0->MR0  = d_time;                 			  /* Load timer value to generate d_time us delay*/
	LPC_TIM0->TCR  |= (1 <<SBIT_CNTEN);                    /* Start timer by setting the Counter Enable*/
}

void EINT3_IRQHandler(void)
{
		LPC_GPIOINT -> IO2IntClr |= (1 << 11);	//clear interrupt

			if(Ult.rflag)	//enters under rising edge condition
			{
				////printf("4\n");
				Ult.rflag = false;
				Ult.start_time = LPC_TIM1 -> TC;
			}else		//enters under falling edge condition
			{
				//printf("5\n");
				LPC_GPIO1 -> FIOCLR = (1 << 31); 	//make trigger level go LOW
				Ult.rflag = true;
				Ult.flag3 = true;
				Ult.stop_time = LPC_TIM1 -> TC;
			}

			long yield = 0;
		portYIELD();
}

void ULTSEN_init()
{
		//TIMER0 for delay_us()
		LPC_SC->PCONP |= (1 << SBIT_TIMER0); 					  /* Power ON Timer0 */
		LPC_TIM0->MCR  |= (1 << SBIT_MR0I);     			  /* Clear TC on MR0 match and Generate Interrupt*/
		LPC_TIM0->MCR  |= (1 << SBIT_MR0R);
		LPC_TIM0->PR   = getPrescalarForUs(PCLK_TIMER0);      /* Prescalar for 1us */
		NVIC_SetPriority( TIMER0_IRQn, 2);
		NVIC_EnableIRQ(TIMER0_IRQn);                          /* Enable Timer0 Interrupt */

		//setup TIMER1 for determining pulse width
		LPC_SC->PCONP |= (1<<SBIT_TIMER1); 					  /* Power ON Timer1 */
		LPC_TIM1->PR   = getPrescalarForUs(PCLK_TIMER1);      /* Prescalar for 1us */

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
    				taskENTER_CRITICAL();

    				//printf("1\n");
    	    		Ult.flag1 = false;	//does not re-enter until current sensor trigger cycle is completed

    	    		Ult.start_time = 0;
    	    		Ult.stop_time = 0;

    	    		//setup TIMER1 for determining pulse width
    	    		LPC_TIM1->TCR  |= (1 << SBIT_CNTEN);                    /* Start timer by setting the Counter Enable*/

    	    		//sensor trigger
    	    		LPC_GPIO1 -> FIOCLR = (1 << 31);
    	    		LPC_GPIO1 -> FIOSET = (1 << 31);

    	    		taskEXIT_CRITICAL();

    	    		delay_us(100);
    	    		//vTaskDelay(100);
    	    }

    		if(Ult.flag2)
    		{
    			taskENTER_CRITICAL();

    			//printf("3\n");
    				Ult.flag2 = false;

    			taskEXIT_CRITICAL();
    		}

    		if(Ult.flag3)
    		{
    			taskENTER_CRITICAL();

    			//printf("6\n");
    				int pulse_width = 0;
    				int inches = 0;

    				Ult.flag3 = false;
    				pulse_width = Ult.stop_time - Ult.start_time;	//calculate pulse width
    				inches = pulse_width/10;						//convert width to inches

    				printf("Distance = %d inches\n", inches);
    				Ult.flag1 = true;

    			taskEXIT_CRITICAL();

    			portTickType xNextWakeTime = xTaskGetTickCount();
    			vTaskDelayUntil( &xNextWakeTime,configULT_FREQ);
    		}

}

void ULTSEN_Task(void *UltSenParam1)
{
	printf("1\n");
	//printf("0\n");
	Ult.start_time = 0;
	Ult.stop_time = 0;
	Ult.flag1 = true;
	Ult.flag2 = false;
	Ult.flag3 = false;
	Ult.rflag = true;

	/* Initialize xNextWakeTime - this only needs to be done once. */
	    portTickType xNextWakeTime = xTaskGetTickCount();

	    ULTSEN_init();

	while(1)
	{
		//vTaskDelayUntil(xNextWakeTime, (500 / portTICK_RATE_MS));
		ULTSEN();
	}
}
