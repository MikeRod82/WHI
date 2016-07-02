#include <stdio.h>
#include <signal.h>
#include <mraa/pwm.h>
#include <mraa/aio.h>
#include <mraa/gpio.h>

sig_atomic_t volatile isrunning = 1;

// Interrupt Handler
void sig_handler(int sig) {
	if (sig == SIGINT)
		isrunning = 0;
}

int main(){
	// Program Interruprt Handles through terminal
	signal(SIGINT, &sig_handler);

	uint16_t rotary_value = 0;
	float value = 0.0f;
	int button_value = 0;
	mraa_gpio_context led;
	mraa_gpio_context buzzer;
	mraa_aio_context rotary;
	mraa_gpio_context button;
	int countdown;

	led = mraa_gpio_init(6);
	buzzer = mraa_gpio_init(5);
	rotary = mraa_aio_init(0);
	button = mraa_gpio_init(4);

	mraa_gpio_dir(button, MRAA_GPIO_IN);
	mraa_gpio_dir(led, MRAA_GPIO_OUT);
	mraa_gpio_dir(buzzer, MRAA_GPIO_OUT);
		
	if (rotary == NULL || led == NULL || buzzer == NULL || button == NULL) {
		printf("Check Connection: \n");
		if(rotary == NULL){
			printf("A0\n");
		}
		else if(led == NULL){
			printf("D6\n");
		}
		else if(button == NULL){
			printf("D4\n");
		}
		else if(buzzer == NULL){
			printf("D5\n");
		}
		else{}
		return 0;
	 }


	while(isrunning){
		rotary_value = mraa_aio_read(rotary);
		button_value = mraa_gpio_read(button);
		//convert to 0.00 to 1.00 scale
		value = ((float) rotary_value)/102;

		//convert to 0.025 to 0.1 scale (avoid rattle)
		value = value/13.33;
		value = value + 0.025;
 if (value >= .25){
	 mraa_gpio_write(led ,1);
	 mraa_gpio_write(buzzer ,1);
		printf("%f\n", value);
		if(button_value == 1){
			countdown = 5;
		printf("Reset in: %d\n", countdown);
			while (countdown != 0){
	 mraa_gpio_write(led ,0);
	 mraa_gpio_write(buzzer ,0);
		sleep(1);
		countdown--;
		printf("Reset in: %d\n", countdown);
			}
		}
 }
 else{}
	 mraa_gpio_write(led ,0);
	 mraa_gpio_write(buzzer ,0);

	
	}
//shut off output at the end of the program	
	 mraa_gpio_write(led ,0);
	 mraa_gpio_write(buzzer ,0);
	return 0;
}
	
