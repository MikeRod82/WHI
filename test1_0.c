#include <stdio.h>
#include <signal.h>
#include <mraa/aio.h>
#include <python.h>

sig_atomic_t volatile isrunning = 1;

void sig_handler(int sig) {
	if (sig == SIGINT)
		isrunning = 0;
}

int main(){
	signal(SIGINT, &sig_handler);

	uint16_t rotary_value = 0;
	float value = 0.0f;
	mraa_aio_context rotary;

	rotary = mraa_aio_init(0);

	if (rotary == NULL) {
		return 1;
	 }

	while(isrunning){
		rotary_value = mraa_aio_read(rotary);
		//convert to 0.00 to 1.00 scale
		value = ((float) rotary_value)/102;

		//convert to 0.025 to 0.1 scale (avoid rattle)
		value = value/13.33;
		value = value + 0.025;
		if(value >= .25){
		printf("%f\n", value);
		}
		else{}
	}
	return 0;
}
	
