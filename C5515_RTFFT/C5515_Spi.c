/* File name: Spi.c

	Simple SPI support for the C5505/C5515.
	Meant for use with the DE2-70 FPGA VGA graphics support.

	25Sep2010 .. initial version .. K.Metzger

*/

#include <stdint.h>
#include "../C5505_support/C5505.h"

void InitSPI(void)
{
   SPICCR = SPI_RST;      // reset the SPI
   SPICCR = 0;            // bring out of reset
   PCGCR1 &= ~SPICG;      // enable the SPI peripheral clock (0 enables) 
   SPICDR = 2;            // set the divide value
   SPICCR = SPI_CLKEN;    // turn on the spi output clock
   SPIDCR1 = 0x0400;      
   SPIDCR2 = 0x0000;
   SPICMD1 = 0x0000;
   
   IODIR1 = 0;
   PDINHIBR1 &= !0x2000;  // enable GPIO 13 pull down
}

void SPIsend(uint16_t value)
{
    SPIDAT2 = value;                   		// load value to be sent
    SPICMD2 = 0x107A;                  		// configure and initiate 16-bit transfer
    while ((SPISTAT1 & 0x0004) == 0);  		// wait for transfer to complete
    while (SPIDAT1 !=0) {                   // if VGA FIFO almost full, wait until it isn't
    	SPIDAT2 = 0xFF00;            		// VGA NOP command
        SPICMD2 = 0x107A;                  	// configure and initiate 16-bit transfer
        while ((SPISTAT1 & 0x0004) == 0);  	// wait for transfer to complete
    }
}
