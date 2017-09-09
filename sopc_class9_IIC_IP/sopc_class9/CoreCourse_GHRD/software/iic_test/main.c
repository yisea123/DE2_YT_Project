#include <stdio.h>
#include <stdint.h>
#include "unistd.h"
#include "system.h"
#include "oc_i2c_regs.h"
#include "oc_i2c.h"
#include "alt_types.h"


alt_u8 a[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
alt_u8 b[32] = {};


int cpr(alt_u8 *buf0,alt_u8 *buf1,alt_u8 num)
{
	int i;
	for(i=0;i<num;i++)
	{
		if(buf0[i] != buf1[i])
			return i + 1;
	}
	return 0;
}

int main(void){

	int i;

	while(1){

		InitI2C(OC_IIC_0_BASE, 100000, 0);

			I2CWrite(OC_IIC_0_BASE, 0xA2, 32, a, 32);
			usleep(100000);
			I2CRead(OC_IIC_0_BASE, 0xA2, 32, b, 32);
			i = cpr(a,b,32);
			if(i)
			{
				printf("error %d",i);
			}
			else
				printf("ok");

			usleep(1000000);
	}
}