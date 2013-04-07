/* main_gpio_test.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: main file of snowcompass project
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "gpio_management.h"

#define	GPIO_139_TELL_POSITION						"139" // Pin 3
#define	GPIO_138_TELL_PICHING							"138"	// Pin 5
#define	GPIO_137_TELL_ROLLING							"137"	// Pin 7
#define	GPIO_136_SET_INIT_POS							"136"	// Pin 9
#define	GPIO_135_SOMETHING								"135"	// Pin 11

int main(int argn,char *argv[])
{

	set_mode_pin(GPIO_139_TELL_POSITION,_GPIO_READ_MODE);
	set_mode_pin(GPIO_138_TELL_PICHING,_GPIO_READ_MODE);
	set_mode_pin(GPIO_137_TELL_ROLLING,_GPIO_READ_MODE);
	set_mode_pin(GPIO_136_SET_INIT_POS,_GPIO_READ_MODE);
	set_mode_pin(GPIO_135_SOMETHING,_GPIO_READ_MODE);
	
	// Main loop
	while(1)
	{			
		sleep(1);
		printf("GPIO_139_TELL_POSITION is:%d # GPIO_138_TELL_PICHING is:%d # "
			"GPIO_137_TELL_ROLLING is:%d # GPIO_136_SET_INIT_POS is:%d # GPIO_135_SOMETHING is:%d\n",
			(int)get_pin_status(GPIO_139_TELL_POSITION), (int)get_pin_status(GPIO_138_TELL_PICHING),
			(int)get_pin_status(GPIO_137_TELL_ROLLING),(int)get_pin_status(GPIO_136_SET_INIT_POS),
			(int)get_pin_status(GPIO_135_SOMETHING));
	}
	
	return EXIT_SUCCESS;
}
