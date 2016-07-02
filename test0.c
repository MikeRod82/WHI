#include <stdio.h>
#include <unistd.h>
#include <mraa/i2c.h>

#define I2C_ADDR

int main()
{
	char message[12];
	int i;

	mraa_init();

	mraa_i2c_context i2c;
	i2c = mraa_i2c_init(0);

	mraa_i2c_address(i2c, I2C_ADDR);
	
	printf("Enter A Message: ");
	for (i=0; i<20; i++) {
		scanf("%s", &message);
		mraa_i2c_write(i2c, message, 12);
		sleep(1);
	}

	mraa_i2c_stop(i2c);
	return 0;
}
