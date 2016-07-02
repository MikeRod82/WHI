#include <stdio.h>
#include <signal.h>
#include <mraa/pwm.h>
#include <mraa/aio.h>
#include <mraa/gpio.h>

//need to define why this is neccessary
sig_atomic_t volatile isrunning = 1;

// Interrupt Handler
void sig_handler(int sig) {
	if (sig == SIGINT)
		isrunning = 0;
}

int main(){
	// Program Interruprt Handles through terminal
	signal(SIGINT, &sig_handler);

	//probably can streamline this process once the sensor
	//data is understood
	uint16_t rotary_value = 0;
	uint16_t rotary0_value = 0;
	float value = 0.0f;
	float value0 = 0.0f;
	int button_value = 0;
	int countdown;

	//define all input and output variable types
	mraa_gpio_context led;
	mraa_gpio_context buzzer;
	mraa_aio_context rotary;
	mraa_aio_context rotary0;
	mraa_gpio_context button;

	// assign values to variable
	led = mraa_gpio_init(6);
	buzzer = mraa_gpio_init(5);
	rotary = mraa_aio_init(0);
	rotary0 = mraa_aio_init(2);
	button = mraa_gpio_init(4);

	// set gpio directions
	mraa_gpio_dir(button, MRAA_GPIO_IN);
	mraa_gpio_dir(led, MRAA_GPIO_OUT);
	mraa_gpio_dir(buzzer, MRAA_GPIO_OUT);

	// check for missing inputs (this still needs to be tested)
	if (rotary == NULL || rotary0 ==NULL || led == NULL || buzzer == NULL || button == NULL) {
		// used to isolate touble causing port(does not work yet)
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


	//Main run loop
	while(isrunning){

		//read values from input ports
		rotary_value = mraa_aio_read(rotary);
		rotary0_value = mraa_aio_read(rotary0);
		button_value = mraa_gpio_read(button);

		//convert to 0.00 to 1.00 scale
		value = ((float) rotary_value)/102;
		value0 = ((float) rotary0_value)/102;

		//convert to 0.025 to 0.1 scale (avoid rattle)
		value = value/13.33;
		value0 = value0/13.33;
		value = value + 0.025;
		value0 = value0 + 0.025;

		//if port A0 is above threshold(values not set)
		if (value >= .25){

			//activate alerts
			mraa_gpio_write(led ,1);
			mraa_gpio_write(buzzer ,1);

			// print alert
			printf("A0:%f\n", value);

			// button press acknowedglement of alarm to reset
			if(button_value == 1){
				// read countdown value
				countdown = 5;
				// Loop Reset counter until 0
				while (countdown != 0){
					// Print Reset Time
					printf("Reset in: %d\n", countdown);
					mraa_gpio_write(led ,0);
					mraa_gpio_write(buzzer ,0);
					sleep(1);
					countdown--;
				}
				printf("Resetting\n");
			}
		}
		else{}
		mraa_gpio_write(led ,0);
		mraa_gpio_write(buzzer ,0);



		if (value0 >= .25){
			mraa_gpio_write(led ,1);
			mraa_gpio_write(buzzer ,1);
			printf("A1:%f\n", value0);
			if(button_value == 1){
				// read countdown value
				countdown = 5;
				// Loop Reset counter until 0
				while (countdown != 0){
					// Print Reset Time
					printf("Reset in: %d\n", countdown);
					mraa_gpio_write(led ,0);
					mraa_gpio_write(buzzer ,0);
					sleep(1);
					countdown--;
				}
				printf("Resetting\n");
			}
		
			
		}
		else{}
		mraa_gpio_write(led ,0);
		mraa_gpio_write(buzzer ,0);

	}

	mraa_gpio_write(led ,0);
	mraa_gpio_write(buzzer ,0);
	return 0;
}

