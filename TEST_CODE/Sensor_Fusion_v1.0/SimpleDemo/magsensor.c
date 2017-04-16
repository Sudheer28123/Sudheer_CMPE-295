/*
 * Sensors.c
 *
 *  Created on: Nov 26, 2016
 *      Author: Sudheer Doddapaneni
 */

#include "magsensor.h"
#include <stdio.h>


/*ADC Initialization function*/
void InitADC(uint16_t adcChnl)
{
	/* Enable CLOCK for ADC peripheral controller */
    LPC_SC->PCONP |= (1 << 12);

    /*Set the clock and Power ON ADC module*/
    LPC_ADC->ADCR = ((1 << PDN_BIT) | (10 << CLCKDIV_BIT));

    /* Select the Port0 Pin23 (P0_23) AD0[0] (J6_15) for ADC function */
    LPC_PINCON->PINSEL1|= 0x01 << 14;

    /* Select the Port0 Pin24 (P0_24) AD0[1] (J6_16) for ADC function */
    //LPC_PINCON->PINSEL1|= 0x01 << 16;

	/* Select ADC Channel 0 by setting bit 0 of ADCR */
    LPC_ADC->ADCR  |= (1 << adcChnl);

	/* Select ADC Channel 1 by setting bit 1 of ADCR */
    //LPC_ADC->ADCR  |= (1 << 1);
}
/*-----------------------------------------------------------*/


/*Function that initializes ADC module and reads Magnetic Sensor data.*/
void MAGSEN(struct MSensor Mag)
{

	 uint16_t adcData=0;
	    uint32_t adc_voltage=0;

		/* Initialize xNextWakeTime - this only needs to be done once. */
	    portTickType xNextWakeTime = xTaskGetTickCount();

	    /*Initialize the ADC controller*/
	    InitADC(Mag.adcChannel);

	for(;;)
	{

        /*Start ADC conversion*/
        LPC_ADC->ADCR |= (1<<START_BIT);

        /* Time delay to allow the ADC channel voltage to stabilize*/
        vTaskDelayUntil( &xNextWakeTime, FREQUENCY_MS );

        /* wait till conversion completes i.e 'DONE' bit is set*/
        while(((LPC_ADC->ADGDR >> DONE_BIT) & 1)==0);
        //while(((LPC_ADC->AD0DR0 >> DONE_BIT) & 1)==0);

        /*Read the 12bit ADC data from ADGDR register*/
        Mag.adcData = (LPC_ADC->ADGDR >> RESULT_BIT) & 0xfff;
        //adcData = (LPC_ADC->ADGDR >> RESULT_BIT) & 0xfff;

        /*Convert the ADC data into corresponding voltage*/
        Mag.adcVoltage = (((uint32_t) Mag.adcData)*VOLTAGE_RANGE) / ADC_RES ;
        //Mag.adcVoltage = ((Mag.adcData)*VOLTAGE_RANGE) / ADC_RES ;
        //adc_voltage = (adcData*VOLTAGE_RANGE) / ADC_RES ;

        /*Print the ADC result*/
        //printf("ADC result: %4d\t",adcData);
        //printf("ADC voltage : %4dmV\n",adc_voltage);
       // printf("ADC result: %4u\t",Mag.adcData);
       // printf("ADC voltage : %4dmV\n",Mag.adcVoltage);

	}
}
/*-----------------------------------------------------------*/


/* The task used for ADC Initialization and Magnetic Sensor data acquisition.*/
void MAGSEN_Task( void *MagSenParam )
{
	//printf("mg\n");
	//Initialization of User-defined structure for ADC based Magnetic sensor.
    struct MSensor MSen;
    MSen.adcChannel = 0;
    MSen.adcData = 0;		//Check the initialization value needed.
    MSen.adcFlag = 0;
    MSen.adcOffset = 0;
    MSen.adcSamplFreq = 0;
    MSen.adcVoltage = 0;	//Check the initialization value needed.

  	//Calling the function that initializes ADC module and reads Magnetic Sensor data.
    MAGSEN(MSen);
}
/*-----------------------------------------------------------*/
