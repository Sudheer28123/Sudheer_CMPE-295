/*
 * Sensors.h
 *
 *  Created on: Nov 26, 2016
 *      Author: Sudheer Doddapaneni
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"




/* Numerical constants corresponding to Bit positions of ADC registers */
#define BURST_BIT      16u
#define START_BIT      24u
#define PDN_BIT        21u
#define EDGE_BIT       27u
#define DONE_BIT       31u
#define RESULT_BIT     4u
#define CLCKDIV_BIT    8u
#define ADC_RES		   4095u
#define VOLTAGE_RANGE  3300


/* The rate at which ADC data sample is buffered and printed. */
#define FREQUENCY_MS					( 2 / portTICK_RATE_MS )

/*User-defined structure that specifies the ADC parameters for Magnetic sensor.*/
struct MSensor
{
	uint32_t adcSamplFreq;  //ADC Sampling Frequency
	uint16_t adcChannel;    //ADC channel
    uint16_t adcData;       //variable to hold ADC raw data. Check the initialization value needed.
    uint32_t adcVoltage;    //variable to hold voltage corresponding to adcData. Check the initialization value needed.
    uint32_t adcOffset;     //Offset for ADC data correction
    uint32_t adcFlag;       //Reserve flag.

};


/*Function to initialize the ADC module.*/
void InitADC(uint16_t adcChnl);


/*Function to obtain ADC data from Magnetic Sensor and perform necessary conversion.*/
void MAGSEN(struct MSensor Mag);


/*The task used for Magnetic Sensor data acquisition.*/
void MAGSEN_Task(void *MagSenParam);


#endif /* SENSORS_H_ */
