/*
*Created March 10th, 2017
*By Sujeeth Krishna Emmadi
*
*/

#ifndef	ULTSENSOR_H_
#define ULTSENSOR_H_

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include "semphr.h"
#include "portmacro.h"

#define		configULT_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )

#define configULT_FREQ					( 2 / portTICK_RATE_MS )	//task frequency at 2ms

//Bits to set up Timer2 and Timer1
#define SBIT_TIMER2  22
#define SBIT_TIMER1	 2

//Bits to set in MCR that generate interrupt and clear MR0 register
#define SBIT_MR0I    0
#define SBIT_MR0R    1

//Bit to enable counter
#define SBIT_CNTEN   0

//Bits to enable pclks
#define PCLK_TIMER2  12
#define PCLK_TIMER1	 4

//einterrupt3 bit for ULT
#define ULT_INT_PIN  11

typedef enum { false, true } bool;

struct USensor
{
	uint32_t start_time;
	uint32_t stop_time;
	bool flag1;
	bool flag2;
	bool flag3;
	bool rflag;
};

struct USensor Ult;

void TIMER2_IRQHandler(void);

void EINT3_IRQHandler(void);

unsigned int getPrescalarForUs(uint8_t timerPclkBit, int option);

void delay_us(int d_time);

void ULTSEN_init();

void ULTSEN();

void ULTSEN_Task(void *UltSenParam1);


#endif
