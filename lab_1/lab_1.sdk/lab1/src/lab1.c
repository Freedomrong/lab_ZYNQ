/*
 * lab1.c
 *
 *  Created on: 2019Äê2ÔÂ22ÈÕ
 *      Author: Administrator
 */


#include "xparameters.h"
#include "xgpio.h"

int main(void)
{
	//Variables Declarations
	XGpio push, led;
	int i,push_check;
	int out = 0;
	int val = 1;
	xil_printf("Lab1 application started.... \r \n");
	int delay_value = 9999999;

	//AXI GPIO Initialization
	XGpio_Initialize(&push,XPAR_BTNS_5BITS_DEVICE_ID);
	XGpio_Initialize(&led,XPAR_LEDS_8BITS_DEVICE_ID);

	//AXI GPIO Set Direction
	XGpio_SetDataDirection(&push,1,0xffffffff);
	XGpio_SetDataDirection(&led,1,0x00000000);

	while(1)
	{
		push_check = XGpio_DiscreteRead(&push, 1);
		switch(push_check)
		{
		case 1:  //BTNC
			delay_value = 9999999;
			break;
		case 2: //BTND
			val = -1;
			break;
		case 4:  //BTNL
			delay_value = 19999999;
			break;
		case 8:  //BTNR
			delay_value = 40999999;
			break;
		case 16:  //BTNU
			val = 1;
			break;

		default:
			break;
		}

		out = out + val;
		if (out > 63)
		{
			out = 0;
		}
		if (out < 0)
		{
			out = 63;
		}
		XGpio_DiscreteWrite(&led,1,out);
		for (i = 0;i<delay_value;i++);
	}
	return (0);
}

