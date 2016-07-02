#include <stdio.h>
#include <signal.h>
#include <mraa/pwm.h>
#include <mraa/aio.h>
#include <mraa/gpio.h>

sig_atomic_t volatile isrunning = 1;

void sig_handler(int sig) {
	if (sig == SIGINT)
		isrunning = 0;
}

void do_when_interrupted()
{
	isrunning = 1;
}

int main(){
	signal(SIGINT, &sig_handler);

	uint16_t rotary_value = 0;
	float value = 0.0f;
	int button_value = 0;
	mraa_pwm_context pwm1;
	mraa_pwm_context pwm;
	mraa_aio_context rotary;
	mraa_gpio_context button;
	int countdown;

	pwm1 = mraa_pwm_init(6);
	pwm = mraa_pwm_init(5);
	rotary = mraa_aio_init(0);
	button = mraa_gpio_init(4);

	mraa_gpio_dir(button, MRAA_GPIO_IN);
//	mraa_gpio_isr(button, MRAA_GPIO_EDGE_RISING, &do_when_interrupted, NULL);
		
	if (rotary == NULL || pwm1 == NULL || pwm == NULL) {
		return 1;
		printf("Broken\n");
	 }

	mraa_pwm_period_ms(pwm1, 20);
	mraa_pwm_enable(pwm1, 1);
	mraa_pwm_period_ms(pwm, 20);
	mraa_pwm_enable(pwm, 1);

	while(isrunning){
		rotary_value = mraa_aio_read(rotary);
		button_value = mraa_gpio_read(button);
		//convert to 0.00 to 1.00 scale
		value = ((float) rotary_value)/102;

		//convert to 0.025 to 0.1 scale (avoid rattle)
		value = value/13.33;
		value = value + 0.025;
 if (value >= .25){
	 	mraa_pwm_enable(pwm1, 1);
	 	mraa_pwm_enable(pwm, 1);
		printf("%f\n", value);
		mraa_pwm_write(pwm1, value);
		mraa_pwm_write(pwm, value);
		if(button_value == 1){
			countdown = 5;
		printf("Reset in: %d\n", countdown);
			while (countdown != 0){
		mraa_pwm_enable(pwm1, 0);
		mraa_pwm_enable(pwm, 0);
		sleep(1);
		countdown--;
		printf("Reset in: %d\n", countdown);
			}
		}
 }
 else{
		mraa_pwm_enable(pwm1, 0);
		mraa_pwm_enable(pwm, 0);

	}
	}
		mraa_pwm_write(pwm1, 0.025f);
		mraa_pwm_enable(pwm1, 0);
		mraa_pwm_write(pwm, 0.025f);
		mraa_pwm_enable(pwm, 0);
	return 0;
}
	
