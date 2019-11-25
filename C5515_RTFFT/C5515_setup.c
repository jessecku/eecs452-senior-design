/*
 * C5515_setup.c
 *
 *  Created on: Oct 7, 2011
 *      Author: Kurt Metzger
 *
 *      To replace C5510 AIC23 support with minimal disruption.
 *      For use with the real time FFT.  Not all code is originally
 *      mine.
 */

#include <stdint.h>
#include "../C5505_support/C5505.h"
#include "../C5505_support/register_system.h"
#include "./C5515_inc/usbstk5515_led.h"
//#include "sar.h"

void InitSystem(void);
void ConfigPort();
void USBSTK5515_I2C_init(void);
void AIC3204_setup(uint16_t);
void InitUART(uint16_t);
void InitSPI(void);
void SPIsend(uint16_t);
void Init_SAR();
void adc_initialize();
unsigned long int AIC3204_IO(int16_t LeftValue, int16_t RightValue);
void initialize_UART_device();

uint16_t SW_SPI = 0;
int16_t LeftValue, RightValue;
uint32_t volatile SampleCounter;
uint32_t wait;

void Startup()
{
	InitSystem(); 			// init C5515 PLL
	ConfigPort(); 			// configure port use
    USBSTK5515_I2C_init( ); // Initialize I2C
//    USBSTK5515_wait(1000000); // give some time to the AIC320

	AIC3204_setup(0);		// initialize CODEC to use default
	adc_initialize();       // initialize the ADC/I2S0 interrupt handler
#ifdef vc5505
	InitUART(3);
#else
	InitUART(5);            // assumes 120 MHz clock, sets 1500k baud
	USBSTK5515_ULED_init( ); // Configure user LEDs
#endif
	if (SW_SPI != 0) {
		InitSPI();
	}
	else {
		initialize_UART_device();// initialize UART console support
	}
}

#ifdef vc5505
	#define PLL_100M 1
#else
	#define PLL_120M 1
#endif


void InitSystem(void)
{
    uint16_t i;

// PLL set up from RTC
    // bypass PLL
    CONFIG_MSW = 0x0;

#if (PLL_120M ==1)
    PLL_CNTL2 = 0x8000;
    PLL_CNTL4 = 0x0000;
    PLL_CNTL3 = 0x0806;
    PLL_CNTL1 = 0x8E4A;
#elif (PLL_100M ==1)	// this rate for C5505 only!
    PLL_CNTL2 = 0x8000;
    PLL_CNTL4 = 0x0000;
//	PLL_CNTL1 = 0x8BE8; // for C5515
    PLL_CNTL1 = 0x82FA; // for C5505

#elif (PLL_12M ==1)
    PLL_CNTL2 = 0x8000;
    PLL_CNTL4 = 0x0200;
    PLL_CNTL3 = 0x0806;
    PLL_CNTL1 = 0x82ED;
#elif (PLL_98M ==1)
    // 98.304 MHz
    PLL_CNTL2 = 0x8000;
    PLL_CNTL4 = 0x0000;
    PLL_CNTL3 = 0x0806;
    PLL_CNTL1 = 0x82ED;
#endif

    while ( (PLL_CNTL3 & 0x0008) == 0);
    // Switch to PLL clk
    CONFIG_MSW = 0x1;

    PCGCR1 = 0x0; // enable clocks to peripherals
    PCGCR2 = 0x0; // enable clocks to more peripherals

    // reset peripherals
    PER_RSTCOUNT = 0x20;  // PRSCR reset pulse is 16 cycles
    PER_RESET = 0x00BF;   // PSCR
    for (i=0; i< 200; i++); // allow lots of time to reset
}

void ConfigPort(void)
{
    //  configure port use by peripheral IO lines
    EBSR = 0x1500;
}


void TX_Put(uint16_t value)
{
	uint16_t temp;

	if (SW_SPI != 0){
		SPIsend(value);
	}
	else {
		temp = (value&0xF800) | ((value<<1)&0x0700);
		UART_xmit((temp>>8)&0x00FF);
		UART_xmit(value&0x007F);
	}
}
