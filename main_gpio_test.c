/* main_gpio_test.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: main file of snowcompass project
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "gpio_management.h"

// Default Input
#define	GPIO_139_TELL_POSITION						"139"	// Pin 3
#define	GPIO_138_TELL_PICHING							"138"	// Pin 5
#define	GPIO_137_TELL_ROLLING							"137"	// Pin 7
#define	GPIO_136_SET_INIT_POS							"136"	// Pin 9
#define	GPIO_135_SOMETHING_1							"135"	// Pin 11
#define	GPIO_134_SOMETHING_2							"134"	// Pin 13
#define	GPIO_133_SOMETHING_3							"133"	// Pin 15
#define	GPIO_132_SOMETHING_4							"132"	// Pin 17
// Default Output
#define	GPIO_159_SOMETHING_5							"159"	// Pin 18
#define	GPIO_161_SOMETHING_6							"161"	// Pin 16

int main(int argn,char *argv[])
{

	set_mode_pin(GPIO_139_TELL_POSITION,_GPIO_READ_MODE);
	set_mode_pin(GPIO_138_TELL_PICHING,_GPIO_READ_MODE);
	set_mode_pin(GPIO_137_TELL_ROLLING,_GPIO_READ_MODE);
	set_mode_pin(GPIO_136_SET_INIT_POS,_GPIO_READ_MODE);
	set_mode_pin(GPIO_135_SOMETHING_1,_GPIO_READ_MODE);
	set_mode_pin(GPIO_134_SOMETHING_2,_GPIO_READ_MODE);
	set_mode_pin(GPIO_133_SOMETHING_3,_GPIO_READ_MODE);
	set_mode_pin(GPIO_132_SOMETHING_4,_GPIO_READ_MODE);
	
	// Main loop
	while(1)
	{			
		sleep(1);
		printf("Pin 3 is:%d # Pin 5 is:%d # Pin 7 is:%d # Pin 9 is:%d # Pin 11 is:%d # "
			"Pin 13 is:%d # Pin 15 is:%d # Pin 17 is:%d\n",
			(int)get_pin_status(GPIO_139_TELL_POSITION), (int)get_pin_status(GPIO_138_TELL_PICHING),
			(int)get_pin_status(GPIO_137_TELL_ROLLING),(int)get_pin_status(GPIO_136_SET_INIT_POS),
			(int)get_pin_status(GPIO_135_SOMETHING_1),(int)get_pin_status(GPIO_134_SOMETHING_2),(int)get_pin_status(GPIO_133_SOMETHING_3),
			(int)get_pin_status(GPIO_132_SOMETHING_4));
	}
	
	return EXIT_SUCCESS;
}
