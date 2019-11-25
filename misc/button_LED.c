/*
 * main.c
 *      Author: GSI
 */

#include <usbstk5515.h>
#include <usbstk5515_gpio.h>
#include <usbstk5515_i2c.h>
#include <usbstk5515_led.h>
#include <stdio.h>
#include <AIC_func.h>
#include <LCD_FCN.h>
#include <sar.h>

//Addresses of the MMIO for the GPIO out registers: 1,2
#define LED_OUT1 *((ioport volatile Uint16*) 0x1C0A )
#define LED_OUT2 *((ioport volatile Uint16*) 0x1C0B )
//Addresses of the MMIO for the GPIO direction registers: 1,2
#define LED_DIR1 *((ioport volatile Uint16*) 0x1C06 )
#define LED_DIR2 *((ioport volatile Uint16*) 0x1C07 )


//Toggles LED specified by index Range 0 to 3
void toggle_LED(int index)
{
	if(index == 3)  //Blue
		LED_OUT1 = LED_OUT1 ^ (Uint16)(1<<(14));
	else if(index == 2)  //Yellow(ish)
		LED_OUT1 = LED_OUT1 ^ (Uint16)(1<<(15));
	else if(index == 1)  //Red
		LED_OUT2 = LED_OUT2 ^ (Uint16)(1<<(0));
	else if(index == 0)  //Green
		LED_OUT2 = LED_OUT2 ^ (Uint16)(1<<(1));
}

//Makes the GPIO associated with the LEDs the correct direction; turns them off
void My_LED_init()
{
	LED_DIR1 |= 0xC000;
	LED_DIR2 |= 0x0003;

	LED_OUT1 |= 0xC000;  //Set LEDs 0, 1 to off
	LED_OUT2 |= 0x0003;  //Set LEDs 2, 3 to off
}

void main(void)
{
	//Uint16 value;
	Uint16 key;			 // value from Gpain1 SAR (button value)
	USBSTK5515_init(); //Initializing the Processor
	My_LED_init();
	Init_SAR();
	while(1)
	{
		/*printf("Which LED shall we toggle(0, 1, 2, or 3)?\n");
		scanf("%d",&value);
		toggle_LED(value);*/
		key = Get_Key_Human();
		if(key == SW1)
		{
			toggle_LED(0);
			}
	}

}
