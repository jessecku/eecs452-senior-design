#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <usbstk5515_gpio.h>
#include <stdio.h>
#include <Dsplib.h>
#include "AIC_func.h"
#include "filter.h"
#include <sar.h>
#include <math.h>

//Addresses of the MMIO for the GPIO out registers: 1,2
#define LED_OUT1 *((ioport volatile Uint16*) 0x1C0A )
#define LED_OUT2 *((ioport volatile Uint16*) 0x1C0B )
//Addresses of the MMIO for the GPIO direction registers: 1,2
#define LED_DIR1 *((ioport volatile Uint16*) 0x1C06 )
#define LED_DIR2 *((ioport volatile Uint16*) 0x1C07 )

#define TCR0 		*((ioport volatile Uint16 *)0x1810)
#define TIMCNT1_0 	*((ioport volatile Uint16 *)0x1814)
#define TIME_START  0x8001
#define TIME_STOP   0x8000
Uint16 delta_time;

#define TABLE_SIZE  1024
#define fs 16000.0
#define TEST_SIZE	8
#define MAX_AMP	1
#define REF_V 0.00005

Int16 sinetable[TABLE_SIZE] = {
		0,201,402,603,804,1005,1206,1407,
		1608,1809,2009,2210,2410,2611,2811,3012,
		3212,3412,3612,3811,4011,4210,4410,4609,
		4808,5007,5205,5404,5602,5800,5998,6195,
		6393,6590,6786,6983,7179,7375,7571,7767,
		7962,8157,8351,8545,8739,8933,9126,9319,
		9512,9704,9896,10087,10278,10469,10659,10849,
		11039,11228,11417,11605,11793,11980,12167,12353,
		12539,12725,12910,13094,13279,13462,13645,13828,
		14010,14191,14372,14553,14732,14912,15090,15269,
		15446,15623,15800,15976,16151,16325,16499,16673,
		16846,17018,17189,17360,17530,17700,17869,18037,
		18204,18371,18537,18703,18868,19032,19195,19357,
		19519,19680,19841,20000,20159,20317,20475,20631,
		20787,20942,21096,21250,21403,21554,21705,21856,
		22005,22154,22301,22448,22594,22739,22884,23027,
		23170,23311,23452,23592,23731,23870,24007,24143,
		24279,24413,24547,24680,24811,24942,25072,25201,
		25329,25456,25582,25708,25832,25955,26077,26198,
		26319,26438,26556,26674,26790,26905,27019,27133,
		27245,27356,27466,27575,27683,27790,27896,28001,
		28105,28208,28310,28411,28510,28609,28706,28803,
		28898,28992,29085,29177,29268,29358,29447,29534,
		29621,29706,29791,29874,29956,30037,30117,30195,
		30273,30349,30424,30498,30571,30643,30714,30783,
		30852,30919,30985,31050,31113,31176,31237,31297,
		31356,31414,31470,31526,31580,31633,31685,31736,
		31785,31833,31880,31926,31971,32014,32057,32098,
		32137,32176,32213,32250,32285,32318,32351,32382,
		32412,32441,32469,32495,32521,32545,32567,32589,
		32609,32628,32646,32663,32678,32692,32705,32717,
		32728,32737,32745,32752,32757,32761,32765,32766,
		32767,32766,32765,32761,32757,32752,32745,32737,
		32728,32717,32705,32692,32678,32663,32646,32628,
		32609,32589,32567,32545,32521,32495,32469,32441,
		32412,32382,32351,32318,32285,32250,32213,32176,
		32137,32098,32057,32014,31971,31926,31880,31833,
		31785,31736,31685,31633,31580,31526,31470,31414,
		31356,31297,31237,31176,31113,31050,30985,30919,
		30852,30783,30714,30643,30571,30498,30424,30349,
		30273,30195,30117,30037,29956,29874,29791,29706,
		29621,29534,29447,29358,29268,29177,29085,28992,
		28898,28803,28706,28609,28510,28411,28310,28208,
		28105,28001,27896,27790,27683,27575,27466,27356,
		27245,27133,27019,26905,26790,26674,26556,26438,
		26319,26198,26077,25955,25832,25708,25582,25456,
		25329,25201,25072,24942,24811,24680,24547,24413,
		24279,24143,24007,23870,23731,23592,23452,23311,
		23170,23027,22884,22739,22594,22448,22301,22154,
		22005,21856,21705,21554,21403,21250,21096,20942,
		20787,20631,20475,20317,20159,20000,19841,19680,
		19519,19357,19195,19032,18868,18703,18537,18371,
		18204,18037,17869,17700,17530,17360,17189,17018,
		16846,16673,16499,16325,16151,15976,15800,15623,
		15446,15269,15090,14912,14732,14553,14372,14191,
		14010,13828,13645,13462,13279,13094,12910,12725,
		12539,12353,12167,11980,11793,11605,11417,11228,
		11039,10849,10659,10469,10278,10087,9896,9704,
		9512,9319,9126,8933,8739,8545,8351,8157,
		7962,7767,7571,7375,7179,6983,6786,6590,
		6393,6195,5998,5800,5602,5404,5205,5007,
		4808,4609,4410,4210,4011,3811,3612,3412,
		3212,3012,2811,2611,2410,2210,2009,1809,
		1608,1407,1206,1005,804,603,402,201,
		0,-201,-402,-603,-804,-1005,-1206,-1407,
		-1608,-1809,-2009,-2210,-2410,-2611,-2811,-3012,
		-3212,-3412,-3612,-3811,-4011,-4210,-4410,-4609,
		-4808,-5007,-5205,-5404,-5602,-5800,-5998,-6195,
		-6393,-6590,-6786,-6983,-7179,-7375,-7571,-7767,
		-7962,-8157,-8351,-8545,-8739,-8933,-9126,-9319,
		-9512,-9704,-9896,-10087,-10278,-10469,-10659,-10849,
		-11039,-11228,-11417,-11605,-11793,-11980,-12167,-12353,
		-12539,-12725,-12910,-13094,-13279,-13462,-13645,-13828,
		-14010,-14191,-14372,-14553,-14732,-14912,-15090,-15269,
		-15446,-15623,-15800,-15976,-16151,-16325,-16499,-16673,
		-16846,-17018,-17189,-17360,-17530,-17700,-17869,-18037,
		-18204,-18371,-18537,-18703,-18868,-19032,-19195,-19357,
		-19519,-19680,-19841,-20000,-20159,-20317,-20475,-20631,
		-20787,-20942,-21096,-21250,-21403,-21554,-21705,-21856,
		-22005,-22154,-22301,-22448,-22594,-22739,-22884,-23027,
		-23170,-23311,-23452,-23592,-23731,-23870,-24007,-24143,
		-24279,-24413,-24547,-24680,-24811,-24942,-25072,-25201,
		-25329,-25456,-25582,-25708,-25832,-25955,-26077,-26198,
		-26319,-26438,-26556,-26674,-26790,-26905,-27019,-27133,
		-27245,-27356,-27466,-27575,-27683,-27790,-27896,-28001,
		-28105,-28208,-28310,-28411,-28510,-28609,-28706,-28803,
		-28898,-28992,-29085,-29177,-29268,-29358,-29447,-29534,
		-29621,-29706,-29791,-29874,-29956,-30037,-30117,-30195,
		-30273,-30349,-30424,-30498,-30571,-30643,-30714,-30783,
		-30852,-30919,-30985,-31050,-31113,-31176,-31237,-31297,
		-31356,-31414,-31470,-31526,-31580,-31633,-31685,-31736,
		-31785,-31833,-31880,-31926,-31971,-32014,-32057,-32098,
		-32137,-32176,-32213,-32250,-32285,-32318,-32351,-32382,
		-32412,-32441,-32469,-32495,-32521,-32545,-32567,-32589,
		-32609,-32628,-32646,-32663,-32678,-32692,-32705,-32717,
		-32728,-32737,-32745,-32752,-32757,-32761,-32765,-32766,
		-32767,-32766,-32765,-32761,-32757,-32752,-32745,-32737,
		-32728,-32717,-32705,-32692,-32678,-32663,-32646,-32628,
		-32609,-32589,-32567,-32545,-32521,-32495,-32469,-32441,
		-32412,-32382,-32351,-32318,-32285,-32250,-32213,-32176,
		-32137,-32098,-32057,-32014,-31971,-31926,-31880,-31833,
		-31785,-31736,-31685,-31633,-31580,-31526,-31470,-31414,
		-31356,-31297,-31237,-31176,-31113,-31050,-30985,-30919,
		-30852,-30783,-30714,-30643,-30571,-30498,-30424,-30349,
		-30273,-30195,-30117,-30037,-29956,-29874,-29791,-29706,
		-29621,-29534,-29447,-29358,-29268,-29177,-29085,-28992,
		-28898,-28803,-28706,-28609,-28510,-28411,-28310,-28208,
		-28105,-28001,-27896,-27790,-27683,-27575,-27466,-27356,
		-27245,-27133,-27019,-26905,-26790,-26674,-26556,-26438,
		-26319,-26198,-26077,-25955,-25832,-25708,-25582,-25456,
		-25329,-25201,-25072,-24942,-24811,-24680,-24547,-24413,
		-24279,-24143,-24007,-23870,-23731,-23592,-23452,-23311,
		-23170,-23027,-22884,-22739,-22594,-22448,-22301,-22154,
		-22005,-21856,-21705,-21554,-21403,-21250,-21096,-20942,
		-20787,-20631,-20475,-20317,-20159,-20000,-19841,-19680,
		-19519,-19357,-19195,-19032,-18868,-18703,-18537,-18371,
		-18204,-18037,-17869,-17700,-17530,-17360,-17189,-17018,
		-16846,-16673,-16499,-16325,-16151,-15976,-15800,-15623,
		-15446,-15269,-15090,-14912,-14732,-14553,-14372,-14191,
		-14010,-13828,-13645,-13462,-13279,-13094,-12910,-12725,
		-12539,-12353,-12167,-11980,-11793,-11605,-11417,-11228,
		-11039,-10849,-10659,-10469,-10278,-10087,-9896,-9704,
		-9512,-9319,-9126,-8933,-8739,-8545,-8351,-8157,
		-7962,-7767,-7571,-7375,-7179,-6983,-6786,-6590,
		-6393,-6195,-5998,-5800,-5602,-5404,-5205,-5007,
		-4808,-4609,-4410,-4210,-4011,-3811,-3612,-3412,
		-3212,-3012,-2811,-2611,-2410,-2210,-2009,-1809,
		-1608,-1407,-1206,-1005,-804,-603,-402,-201
};

//Makes the GPIO associated with the LEDs the correct direction; turns them off
void My_LED_init()
{
	LED_DIR1 |= 0xC000;
	LED_DIR2 |= 3;

	LED_OUT1 |= 0xC000;  //Set LEDs 0, 1 to off
	LED_OUT2 |= 3;  //Set LEDs 2, 3 to off
}

//test frequencies
Uint16 test_freq[TEST_SIZE] = {
		1000, 2000, 3000, 3750, 4250, 5000, 6000, 7000
};

//stored in <frequency>,<gain> format
float results[TEST_SIZE];

void main()
{
	Uint16 FTV;
	Uint16 counter,temp,key, i;
	Int16 out;
	float gain;
	Int16 hold;
	Int16 x_right, x_left;

	// Input buffers
	Int16 right_dbuffer1[size+2]={0};
	Int16 right_dbuffer2[size+2]={0};
	Int16 right_dbuffer3[size+2]={0};
	Int16 right_dbuffer4[size+2]={0};
	Int16 right_dbuffer5[size+2]={0};
	Int16 right_dbuffer6[size+2]={0};
	Int16 right_dbuffer7[size+2]={0};
	Int16 right_dbuffer8[size+2]={0};

	Int16 left_dbuffer1[size+2]={0};
	Int16 left_dbuffer2[size+2]={0};
	Int16 left_dbuffer3[size+2]={0};
	Int16 left_dbuffer4[size+2]={0};
	Int16 left_dbuffer5[size+2]={0};
	Int16 left_dbuffer6[size+2]={0};
	Int16 left_dbuffer7[size+2]={0};
	Int16 left_dbuffer8[size+2]={0};

	// Filter outputs
	Int16 r1, r2, r3, r4, r5, r6, r7, r8;
	Int16 l1, l2, l3, l4, l5, l6, l7, l8;

	Int32 y_right, y_left;

	// AIC output
	Int16 right, left;

	USBSTK5515_init();  //Initializing the Processor
	AIC_init();  //Initializing the Audio Codec
	My_LED_init();
	TCR0 = TIME_STOP;
	TCR0 = TIME_START;//Resets the time register
	Uint16 start_time;
	Uint16 end_time;
	hold = 0;

	// Hearing test
	for(i = 0; i < TEST_SIZE; i++){
		FTV = test_freq[i]*(65536)/fs;
		for(gain = 0; gain <= 1; gain += 0.00001){
			counter = 0;
			hold = 0;

			while(1){
				if(hold > 10000){
					if(gain != 1)
						break;
					else{
						LED_OUT2 ^= 0x0001;
						hold = 0;
					}
				}

				counter += FTV;
				temp = counter >> 6;
				out = gain*sinetable[temp];
				AIC_write2(out, out);
				key = Get_Key_Human();
				if(key == SW1 && gain != 0){
					results[i] = gain;
					printf("%d Hz at %f gain\n", test_freq[i], gain);
					goto NEXT;
				}
				hold++;
			}
		}
		NEXT:
	}
	printf("Hearing test complete\n");

	for(i=0; i < TEST_SIZE ; i++){
		if(results[i] <= REF_V)
			results[i] = 1;
		else
			results[i] =results[i]/REF_V;
	}

	// Gain coefficients in 32 bit Q8
	Int32 gain1 = results[0]*256;
	Int32 gain2 = results[1]*256;
	Int32 gain3 = results[2]*256;
	Int32 gain4 = results[3]*256;
	Int32 gain5 = results[4]*256;
	Int32 gain6 = results[5]*256;
	Int32 gain7 = results[6]*256;
	Int32 gain8 = results[7]*256;

	while(1)
	{
		AIC_read2(&x_right, &x_left);
		start_time = TIMCNT1_0;

		//RIGHT EAR
		//-------------------------------------------------------------
		fir(&x_right,   	// input
			B1,				// coef
			&r1,			// output
			right_dbuffer1,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_right,   	// input
			B2,				// coef
			&r2,			// output
			right_dbuffer2,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_right,   	// input
			B3,				// coef
			&r3,			// output
			right_dbuffer3,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_right,   	// input
			B4,				// coef
			&r4,			// output
			right_dbuffer4,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_right,   	// input
			B5,				// coef
			&r5,			// output
			right_dbuffer5,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_right,   	// input
			B6,				// coef
			&r6,			// output
			right_dbuffer6,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_right,   	// input
			B7,				// coef
			&r7,			// output
			right_dbuffer7,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_right,   	// input
			B8,				// coef
			&r8,			// output
			right_dbuffer8,	// Z-1 blocks and more
			1,			// number to process
			size);			// number of parameters

		y_right = gain1 * (Int32)r1
				+ gain2 * (Int32)r2
				+ gain3 * (Int32)r3
				+ gain4 * (Int32)r4
				+ gain5 * (Int32)r5
				+ gain6 * (Int32)r6
				+ gain7 * (Int32)r7
				+ gain8 * (Int32)r8;

		y_right = (y_right + 0x0000080) >> 8; // TODO Convert to a 16-bit Q15 with rounding and saturation.

		if (y_right > 32767)
			y_right = 32767;
		if (y_right < -32768)
			y_right = -32768;

		right = (Int16) y_right;

		//LEFT EAR
		//-------------------------------------------------------------
		fir(&x_left,   		// input
			B1,				// coef
			&l1,			// output
			left_dbuffer1,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_left,   		// input
			B2,				// coef
			&l2,			// output
			left_dbuffer2,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_left,   		// input
			B3,				// coef
			&l3,			// output
			left_dbuffer3,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_left,   		// input
			B4,				// coef
			&l4,			// output
			left_dbuffer4,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_left,   		// input
			B5,				// coef
			&l5,			// output
			left_dbuffer5,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_left,   		// input
			B6,				// coef
			&l6,			// output
			left_dbuffer6,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_left,   		// input
			B7,				// coef
			&l7,			// output
			left_dbuffer7,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		fir(&x_left,   		// input
			B8,				// coef
			&l8,			// output
			left_dbuffer8,	// Z-1 blocks and more
			1,				// number to process
			size);			// number of parameters

		y_left = gain1 * (Int32)l1
			   + gain2 * (Int32)l2
			   + gain3 * (Int32)l3
			   + gain4 * (Int32)l4
			   + gain5 * (Int32)l5
			   + gain6 * (Int32)l6
			   + gain7 * (Int32)l7
			   + gain8 * (Int32)l8;

		// Convert to a 16-bit Q15 with rounding and saturation.
		y_left = (y_left + 0x0000080) >> 8;

		if (y_left > 32767)
			y_left = 32767;
		if (y_left < -32768)
			y_left = -32768;

		left = (Int16) y_left;

		end_time = TIMCNT1_0;
		delta_time = (start_time-end_time) << 1;
		AIC_write2(right,left);
	}
}
