#include <stdio.h>
#include <signal.h>
#include <mraa/aio.h>

sig_atomic_t volatile isrunning = 1;

void sig_handler(int sig) {
	if (sig == SIGINT)
		isrunning = 0;
}

int main(){
	signal(SIGINT, &sig_handler);

	uint16_t rotary_value = 0;
//	uint16_t rotary0_value = 0;
	float value = 0.0f;
//	float value0 = 0.0f;
	uint16_t rotary_value1 = 0;
//	uint16_t rotary2_value = 0;
	float value1 = 0.0f;
//	float value2 = 0.0f;
	mraa_aio_context rotary;
//	mraa_aio_context rotary0;
	mraa_aio_context rotary1;
//	mraa_aio_context rotary2;

	rotary = mraa_aio_init(0);
//	rotary0 = mraa_aio_init(3);
	rotary1 = mraa_aio_init(2);
//	rotary2 = mraa_aio_init(1);

	if (rotary == NULL || rotary1 == NULL) {
		return 1;
	 }

	while(isrunning){
		rotary_value = mraa_aio_read(rotary);
//		rotary0_value = mraa_aio_read(rotary);
		//convert to 0.00 to 1.00 scale
		value = ((float) rotary_value)/102;
//		value0 = ((float) rotary0_value)/102;

		//convert to 0.025 to 0.1 scale (avoid rattle)
		value = value/13.33;
//		value0 = value0/13.33;
		value = value + 0.025;
//		value0 = value0 + 0.025;
		while(value >= .25){
		printf("A0 works\n");
		rotary_value = mraa_aio_read(rotary);
//		rotary0_value = mraa_aio_read(rotary);
		//convert to 0.00 to 1.00 scale
		value = ((float) rotary_value)/102;
//		value0 = ((float) rotary0_value)/102;

		//convert to 0.025 to 0.1 scale (avoid rattle)
		value = value/13.33;
//		value0 = value0/13.33;
		value = value + 0.025;
		}
//		if(value0 >= .25){
//		printf("A3 works\n");
//		}
//		else{}
		
		rotary_value1 = mraa_aio_read(rotary1);
//		rotary2_value = mraa_aio_read(rotary2);
		//convert to 0.00 to 1.00 scale
		value1 = ((float) rotary_value1)/102;
//		value2 = ((float) rotary2_value)/102;

		//convert to 0.025 to 0.1 scale (avoid rattle)
		value1 = value1/13.33;
//		value2 = value2/13.33;
		value1 = value1 + 0.025;
//		value2 = value2 + 0.025;
		while(value1 >= .25){
		printf("A2 works\n");
		rotary_value1 = mraa_aio_read(rotary1);
//		rotary2_value = mraa_aio_read(rotary2);
		//convert to 0.00 to 1.00 scale
		value1 = ((float) rotary_value1)/102;
//		value2 = ((float) rotary2_value)/102;

		//convert to 0.025 to 0.1 scale (avoid rattle)
		value1 = value1/13.33;
//		value2 = value2/13.33;
		value1 = value1 + 0.025;
		}
//		if(value2 >= .25){
//		printf("A0 works\n");
//		}
//		else{}
	}
	return 0;
}
	
