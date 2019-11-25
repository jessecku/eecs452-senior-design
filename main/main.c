#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <usbstk5515_gpio.h>
#include <stdio.h>
#include <Dsplib.h>
#include "AIC_func.h"
#include "filter.h"
#include <sar.h>
#include <math.h>
#include <LCD_FCN.h>
#include "header.h"

//Addresses of the MMIO for the GPIO out registers: 1,2
#define LED_OUT1 *((ioport volatile Uint16*) 0x1C0A )
#define LED_OUT2 *((ioport volatile Uint16*) 0x1C0B )
//Addresses of the MMIO for the GPIO direction registers: 1,2
#define LED_DIR1 *((ioport volatile Uint16*) 0x1C06 )
#define LED_DIR2 *((ioport volatile Uint16*) 0x1C07 )


/* 
//used for measuring cycles
#define TCR0 		*((ioport volatile Uint16 *)0x1810)
#define TIMCNT1_0 	*((ioport volatile Uint16 *)0x1814)
#define TIME_START  0x8001
#define TIME_STOP   0x8000
Uint16 delta_time;
*/


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

float test_gain[11]= {
		0.00001, 0.000014125, 0.00019951, 0.00028181,
		0.00039806, 0.00056226, 0.00079420, 
		0.0011218, 0.0015845, 0.0022381, 0.0031614
};

/* hearing test results for left/right ears
stores test_gains that corresponds to test_freq */
float left_results[TEST_SIZE];
float right_results[TEST_SIZE];

void main()
	{
	Uint32 k;
	Uint16 FTV;
	Uint16 counter,temp,key, i;
	Uint16 gain;
	Int16 out, nothing, hold;
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
	
	
	if (InitializeCPU(100, 5515)==0) while(1);
	ConfigPort();
	
	Init_SAR();
	AIC_init();  //Initializing the Audio Codec
	My_LED_init();
	LCD_init(); //Initializing the LCD and I2C


//	TCR0 = TIME_STOP;
//	TCR0 = TIME_START;//Resets the time register
//	Uint16 start_time, end_time;

/*** for testing purposes ***/
/*
	Uint16 test;
	printf("Testing? (1/0)\n");
	scanf("%d", &test);
	if(test)
		goto SKIP;
*/
/****************************/


/******** HEARING TEST ********/
	// Clear lcd
	clear_screen();
	
/***** Left ear *****/
	for(i = 0; i < TEST_SIZE; i++){
		FTV = test_freq[i]*(65536)/fs;
		for(gain = 0; gain < 11; gain++){
			left_test();
			// Print frequency
			if(i == 0) L_1000_HZ();
			else if(i == 1) L_2000_HZ();
			else if(i == 2) L_3000_HZ();
			else if(i == 3) L_3750_HZ();
			else if(i == 4) L_4250_HZ();
			else if(i == 5) L_5000_HZ();
			else if(i == 6) L_6000_HZ();
			else  L_7000_HZ();

			// Print on screen
			print_screen();

			counter = 0;
			hold = 0;
			
			while(1){
				
				//causes delays to create beeping sounds
				if(!(hold%2500)){
					for(k = 0; k < 10000; k++){
						key = Get_Key_Human();
						if(key == SW1 && gain !=0){
							left_results[i] = test_gain[gain];
							goto NEXT;
						}
					}
				}
				
				/* moves onto next gain after a certain
				period of time. if the gain is already
				at max, Red LED toggles. */
				if(hold > 10000){
					if(gain < 10)
						break;
					else{
						LED_OUT2 ^= 0x0001;
						hold = 0;
					}
				}
				
				/* Direct Digital Synthesis */
				counter += FTV;
				temp = counter >> 6;
				out = test_gain[gain]*sinetable[temp];
				AIC_write2(nothing, out);
				
				/*If the user pushes the button, moves onto
				next frequency*/
				key = Get_Key_Human();
				if(key == SW1 && gain != 0){
					left_results[i] = test_gain[gain];
					//printf("Left ear: %d Hz at %f gain\n", test_freq[i], gain);
					goto NEXT;
				}
				hold++;
			}
			
			/* longer delay for the transition between two frequencies */
			for(k = 0; k < 500000; k++){
				key = Get_Key_Human();
				if(key == SW1 && gain !=0){
					left_results[i] = test_gain[gain];
					goto NEXT;
				}
			}
		}
		NEXT:
		LED_OUT2 |= 3; //Resets LEDS

	}

/***** Right ear *****/
	for(i = 0; i < TEST_SIZE; i++){
		FTV = test_freq[i]*(65536)/fs;
		for(gain = 0; gain < 11; gain++){
			
			//Print "right test"
			right_test();
			
			// Print frequency
			if(i == 0) R_1000_HZ();
			else if(i == 1) R_2000_HZ();
			else if(i == 2) R_3000_HZ();
			else if(i == 3)	R_3750_HZ();
			else if(i == 4) R_4250_HZ();
			else if(i == 5) R_5000_HZ();
			else if(i == 6) R_6000_HZ();
			else R_7000_HZ();

			// Print on screen
			print_screen();
			
			counter = 0;
			hold = 0;
			
			while(1){
				
				if(!(hold%2500)){
					for(k = 0; k < 10000; k++){
						key = Get_Key_Human();
						if(key == SW1 && gain !=0){
							right_results[i] = test_gain[gain];
							goto DONE;
						}
					}
				}
				if(hold > 10000){
					if(gain < 10)
						break;
					else{
						LED_OUT2 ^= 0x0001;
						hold = 0;
					}
				}
				counter += FTV;
				temp = counter >> 6;
				out = test_gain[gain]*sinetable[temp];
				AIC_write2(out, nothing);
				key = Get_Key_Human();
				if(key == SW1 && gain != 0){
					right_results[i] = test_gain[gain];
					//printf("Right ear: %d Hz at %f gain\n", test_freq[i], gain);
					goto DONE;
				}
				hold++;
			}
			for(k = 0; k < 500000; k++){
				key = Get_Key_Human();
				if(key == SW1 && gain !=0){
					right_results[i] = test_gain[gain];
					goto DONE;
				}
			}
		}
		DONE:
		LED_OUT2 |= 3;
	}
	
	//printf("Hearing test complete\n");
	clear_screen();
	print_done();
	
	// Print on screen
	print_screen();
	
	/* if the results are less than the reference voltage(or gain)
	set results to 1, otherwise divide it by the reference voltage
	to find how much amplification is needed*/
	
	for(i=0; i < TEST_SIZE ; i++){
		if(right_results[i] <= REF_V)
			right_results[i] = 1;
		else
			right_results[i] =right_results[i]/REF_V;

		if(left_results[i] <= REF_V)
			left_results[i] = 1;
		else
			left_results[i] =left_results[i]/REF_V;
	}

/*** testing purposes ***/
/*
#define test 20
	if(0){
		SKIP:
		printf("Hearing test skipped\n");
		left_results[0] = test;
		left_results[1] = test;
		left_results[2] = test;
		left_results[3] = test;
		left_results[4] = test;
		left_results[5] = test;
		left_results[6] = test;
		left_results[7] = test;

		right_results[0] = test;
		right_results[1] = test;
		right_results[2] = test;
		right_results[3] = test;
		right_results[4] = test;
		right_results[5] = test;
		right_results[6] = test;
		right_results[7] = test;
	}
*/

/********  FILTER CONFIGURATION ********/

	// Gain coefficients in 32 bit Q8
	Int32 lGain1 = 1*left_results[0]*256/16;
	Int32 lGain2 = 1*left_results[1]*256/16;
	Int32 lGain3 = 1*left_results[2]*256/16;
	Int32 lGain4 = 1*left_results[3]*256/16;
	Int32 lGain5 = 1*left_results[4]*256/16;
	Int32 lGain6 = 1*left_results[5]*256/16;
	Int32 lGain7 = 1*left_results[6]*256/16;
	Int32 lGain8 = 1*left_results[7]*256/16;

	Int32 rGain1 = 1*right_results[0]*256/16;
	Int32 rGain2 = 1*right_results[1]*256/16;
	Int32 rGain3 = 1*right_results[2]*256/16;
	Int32 rGain4 = 1*right_results[3]*256/16;
	Int32 rGain5 = 1*right_results[4]*256/16;
	Int32 rGain6 = 1*right_results[5]*256/16;
	Int32 rGain7 = 1*right_results[6]*256/16;
	Int32 rGain8 = 1*right_results[7]*256/16;

/******** AUDITORY ENHANCEMENT ********/
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

		y_right = rGain1 * (Int32)r1
				+ rGain2 * (Int32)r2
				+ rGain3 * (Int32)r3
				+ rGain4 * (Int32)r4
				+ rGain5 * (Int32)r5
				+ rGain6 * (Int32)r6
				+ rGain7 * (Int32)r7
				+ rGain8 * (Int32)r8;

		y_right = (y_right + 0x0000080) >> 8; //Convert to a 16-bit Q15 with rounding and saturation.

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

		y_left = lGain1 * (Int32)l1
			   + lGain2 * (Int32)l2
			   + lGain3 * (Int32)l3
			   + lGain4 * (Int32)l4
			   + lGain5 * (Int32)l5
			   + lGain6 * (Int32)l6
			   + lGain7 * (Int32)l7
			   + lGain8 * (Int32)l8;

		
		y_left = (y_left + 0x0000080) >> 8; // Convert to a 16-bit Q15 with rounding and saturation.

		if (y_left > 32767)
			y_left = 32767;
		if (y_left < -32768)
			y_left = -32768;

		left = (Int16) y_left;
		
		//end_time = TIMCNT1_0;
		//delta_time = (start_time-end_time) << 1;
		
		AIC_write2(right,left);
	}
}
