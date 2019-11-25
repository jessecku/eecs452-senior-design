#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <AIC_func.h>
#include <sar.h>
#include <stdio.h>
#include <math.h>

#define TABLE_SIZE  64
#define fs 48000.0
#define TEST_SIZE	10
#define MAX_AMP	1
#define GAIN_TABLE_SIZE 14


Int16 sinetable[TABLE_SIZE] = {
		0,3212,6393,9512,12539,15446,18204,20787,
		23170,25329,27245,28898,30273,31356,32137,32609,
		32767,32609,32137,31356,30273,28898,27245,25329,
		23170,20787,18204,,12539,9512,6393,3212,
		0,-3212,-6393,-915446512,-12539,-15446,-18204,-20787,
		-23170,-25329,-27245,-28898,-30273,-31356,-32137,-32609,
		-32767,-32609,-32137,-31356,-30273,-28898,-27245,-25329,
		-23170,-20787,-18204,-15446,-12539,-9512,-6393,-3212
};

//test frequencies
//80, 141, 256, 467, 849, 1544, 2809, 5111, 9298, 14500
Uint16 test_freq[TEST_SIZE] = {
		80, 141, 256, 467, 849, 1544, 2809, 5111, 9298, 14500
};

//stored in <frequency>,<gain> format
float results[TEST_SIZE];

//table of gains
float gain[GAIN_TABLE_SIZE] = {
	0.001, 0.005, 0.01, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
	0.9, 1
};

void main(void)
{
	Uint16 FTV;
  	Uint16 counter,temp,key, i;
	Int16 out;
	Uint16 gain_index;
  	USBSTK5515_init();
  	AIC_init();
	Init_SAR();
	for(i = 0; i < TEST_SIZE; i++){
		FTV = test_freq[i]*(65536)/fs;
		for(gain_index = 0; gain_index < GAIN_TABLE_SIZE; gain_index++){
			counter = 0;
			printf("Can you hear this? Yes(SW1) / No(SW2)\n");
			while(1){
				counter += FTV;
				temp = counter >> 10;
				out = gain[gain_index]*sinetable[temp];
				AIC_write2(out, out);
				key = Get_Key_Human();
				if(key == SW1){
					printf("can hear %d at a gain of %f\n", test_freq[i], gain[gain_index]);
					results[i] = gain[gain_index];
					goto NEXT;
				}
				else if(key == SW2){
					printf("cannot hear %d at a gain of %f\n", test_freq[i], gain[gain_index]);
					results[i] = gain[gain_index];
					break;
				}
			}

		}
		NEXT:

	}
	for(i=0; i < TEST_SIZE; i++)
		printf("%d Hz at %6.3f gain\n", test_freq[i], results[i]);

}
