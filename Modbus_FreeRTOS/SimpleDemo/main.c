/*
    FreeRTOS V6.1.0 - Copyright (C) 2010 Real Time Engineers Ltd.

    ***************************************************************************
    *                                                                         *
    * If you are:                                                             *
    *                                                                         *
    *    + New to FreeRTOS,                                                   *
    *    + Wanting to learn FreeRTOS or multitasking in general quickly       *
    *    + Looking for basic training,                                        *
    *    + Wanting to improve your FreeRTOS skills and productivity           *
    *                                                                         *
    * then take a look at the FreeRTOS books - available as PDF or paperback  *
    *                                                                         *
    *        "Using the FreeRTOS Real Time Kernel - a Practical Guide"        *
    *                  http://www.FreeRTOS.org/Documentation                  *
    *                                                                         *
    * A pdf reference manual is also available.  Both are usually delivered   *
    * to your inbox within 20 minutes to two hours when purchased between 8am *
    * and 8pm GMT (although please allow up to 24 hours in case of            *
    * exceptional circumstances).  Thank you for your support!                *
    *                                                                         *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/*
 * This is a very simple demo that demonstrates task and queue usages only.
 * Details of other FreeRTOS features (API functions, tracing features,
 * diagnostic hook functions, memory management, etc.) can be found on the
 * FreeRTOS web site (http://www.FreeRTOS.org) and in the FreeRTOS book.
 * Details of this demo (what it does, how it should behave, etc.) can be found
 * in the accompanying PDF application note.
 *
*/

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

#include  "mb.h"
/* ----------------------- Defines ------------------------------------------*/
#define REG_INPUT_START 1000
#define REG_INPUT_NREGS 4
#define SLAVE_ID 		0x0A

/* ----------------------- Static variables ---------------------------------*/
static USHORT   usRegInputStart = REG_INPUT_START;
static USHORT   usRegInputBuf[REG_INPUT_NREGS];
#define FREQUENCY_MS					( 100 / portTICK_RATE_MS )
#define		configMODBUS_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )

void MODBUS_Task( void *ModbusParam)
{
	 portTickType xNextWakeTime = xTaskGetTickCount();
	 eMBErrorCode    eStatus;

	    eStatus = eMBInit( MB_RTU, SLAVE_ID, 0, 9600, MB_PAR_NONE );   //intialization

	    /* Enable the Modbus Protocol Stack. */
	    eStatus = eMBEnable();

	    // Initialise some registers
	    usRegInputBuf[1] = 0x1234;
	    usRegInputBuf[2] = 0x5678;
	    usRegInputBuf[3] = 0x9abc;

	    vTaskDelayUntil( &xNextWakeTime, FREQUENCY_MS );
	    for( ;; )
	    {
	        (void)eMBPoll();

	        /* Here we simply count the number of poll cycles. */
	        usRegInputBuf[0]++;
	    }
}
/*Main function.*/
int main(void)
{
    //Clock and PLL configuration
    SystemInit();

	//printf("Main function. Creating Queues and Tasks.\n");

	/* Creating the MODBUS_Task, which initializes the Magnetic Sensor module and then reads sensor data regularly. */
	xTaskCreate( MODBUS_Task, ( signed char * ) "MODBUS", configMINIMAL_STACK_SIZE, NULL, configMODBUS_TASK_PRIORITY, NULL );

	/* Start the tasks running. */
	vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	printf("\nCRITICAL ERROR!! Reached End of Main.");
	for( ;; );
}
/*-----------------------------------------------------------*/


/**
 -----------------------------------------------------------------------------------------------------------------------
 eMBRegInputCB
 -----------------------------------------------------------------------------------------------------------------------
*   Event Handler for GPI module
*
* 	@date       			DEC/02/2013
* 	@author                         FW_DEV_2
* 	@pre                            None
* 	@return	 			None
************************************************************************************************************************
*/
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;
   // printf("check1");
    if( ( usAddress >= REG_INPUT_START ) && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
       // printf("%c", pucRegBuffer);
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

/**
 -----------------------------------------------------------------------------------------------------------------------
 eMBRegHoldingCB
 -----------------------------------------------------------------------------------------------------------------------
*   Event Handler for GPI module
*
* 	@date       			DEC/02/2013
* 	@author                         FW_DEV_2
* 	@pre                            None
* 	@return	 			None
************************************************************************************************************************
*/
eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;
//printf("check2");
    if (eMode == MB_REG_READ)
    {
        if( ( usAddress >= REG_INPUT_START )&& ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
        {
            iRegIndex = ( int )( usAddress - usRegInputStart );
            while( usNRegs > 0 )
            {
                *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
                *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
                iRegIndex++;
                usNRegs--;
            }
        }
    }
    if (eMode == MB_REG_WRITE)
    {
        if( ( usAddress >= REG_INPUT_START )&& ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
        {
            iRegIndex = ( int )( usAddress - usRegInputStart );
            while( usNRegs > 0 )
            {
                usRegInputBuf[iRegIndex] =  ((unsigned int) *pucRegBuffer << 8) | ((unsigned int) *(pucRegBuffer+1));
                pucRegBuffer+=2;
                iRegIndex++;
                usNRegs--;
            }
        }
    }

    return eStatus;
}

/**
 -----------------------------------------------------------------------------------------------------------------------
 eMBRegCoilsCB
 -----------------------------------------------------------------------------------------------------------------------
*   Event Handler for GPI module
*
* 	@date       			DEC/02/2013
* 	@author                         FW_DEV_2
* 	@pre                            None
* 	@return	 			None
************************************************************************************************************************
*/
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,eMBRegisterMode eMode )
{
    printf("Inside eMBRegCoilsCB\n ");
    *pucRegBuffer = 0xAF;
	//return MB_ENOREG;
    return MB_ENOERR;
}

/**
 -----------------------------------------------------------------------------------------------------------------------
 eMBRegDiscreteCB
 -----------------------------------------------------------------------------------------------------------------------
*   Event Handler for GPI module
*
* 	@date       			DEC/02/2013
* 	@author                         FW_DEV_2
* 	@pre                            None
* 	@return	 			None
************************************************************************************************************************
*/
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}





