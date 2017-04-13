					#####Sensor_Fusion_v1.0#####
1) Main project is SimpleDemo

2) Include CMSISv1p30_LPC17xx
	   FreeRTOS_Library
	   SimpleDemo (self_proj)

3) Current frequency of tasks are 2ms, with equal priority. Printf to show sensor values are commented.

4)If sensor values need to be determined
	- uncomment printf in ultsensor.c and magsensor.c
	- change configULT_FREQ to 600 in ultsensor.h
	- change configADC_FREQ to 500 in magsensor.h 	
  NOTE: you will encounter hardfaults because of the processing time taken by printf(). But the processor will
	run and output the sensors several times before that.