/***************************************************************************
	progetto			: "la bussola parlante" con scheda snowboard
    file:				: button.c
    begin               : mer apr 21 10:34:57 CET 2011
    copyright           : (C) 2011 by Giancarlo Martini
    email               : gm@giancarlomartini.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include "buttons.h"
#include "gpio_management.h"
#include "speech.h"

#define RESET_ELAPSED_BUTTON_PRESSED_TIME 			1
#define GET_ELAPSED_BUTTON_PRESSED_TIME	 			0

// Default Input
#define	GPIO_139_TELL_POSITION						"139"	// Pin 3
#define	GPIO_138_TELL_PICHING						"138"	// Pin 5
#define	GPIO_137_TELL_ROLLING						"137"	// Pin 7
#define	GPIO_136_SET_INIT_POS						"136"	// Pin 9
#define	GPIO_135_SOMETHING_1							"135"	// Pin 11
#define	GPIO_134_SOMETHING_2							"134"	// Pin 13
#define	GPIO_135_SOMETHING_3							"133"	// Pin 15
#define	GPIO_135_SOMETHING_4							"132"	// Pin 17
// Default Output
#define	GPIO_135_SOMETHING_5							"159"	// Pin 18
#define	GPIO_135_SOMETHING_6							"161"	// Pin 16

void menu_x86(char *what);
int do_x86_job(void);
int do_arm_job(void);
bool get_elapsed_time_after_button_used(int should_reset);

int read_buttons(void) {
#ifdef __i386__
	return do_x86_job();
#endif

#ifdef __arm__
	return do_arm_job();
#endif

}
// --------------------------------------------
int do_x86_job(void) {
	static int first_time = 0;
	static bool key_is_pressed = false;

	char buf[10];
	fd_set selectset;
	struct timespec timeout = {0,1};
	int ret;

	if(first_time == 0) {
		menu_x86("");
		first_time = 1;
	}

	FD_ZERO(&selectset);
	FD_SET(0,&selectset);
	ret =  pselect(1,&selectset,NULL,NULL,&timeout,NULL);
	if(ret == 0) {
		key_is_pressed = false;
		return NOT_BUTTONS_PRESSED;
	}
	// There is data
	read(0,buf,2);
	// Backdoor for exit
	if((buf[0] == 'q') && (buf[1] == 'q')) {
		say_something("Bussola fermata");
		exit(0);
	}
	// Check for the same choise
	if(key_is_pressed == true) return NOT_BUTTONS_PRESSED;

	switch(buf[0] - 48) {
	case TELL_ME_DIRECTION 	:
		menu_x86("Tell me direction");
		key_is_pressed = true;
		return TELL_ME_DIRECTION;
	case SET_DIRECTION 	:
		menu_x86("Set direction");
		key_is_pressed = true;
		return SET_DIRECTION;
	case TELL_ME_ROOLLING 	:
		menu_x86("Tell me rolling");
		key_is_pressed = true;
		return TELL_ME_ROOLLING;
	case TELL_ME_PITCHING 	:
		menu_x86("Tell me pitching");
		key_is_pressed = true;
		return TELL_ME_PITCHING;
	default:
		menu_x86("Wrong choise");
	};
	key_is_pressed = false;
	return NOT_BUTTONS_PRESSED;
}
// --------------------------------------------
int do_arm_job(void) {
	static bool first_time = true;
	static bool key_is_pressed = false;
	int ret_value = NOT_BUTTONS_PRESSED;
	enum gpio_pin_read_status btn_position, btn_pich, btn_roll,btn_set_position;

	if(first_time == true) {
		set_mode_pin(GPIO_139_TELL_POSITION,_GPIO_READ_MODE);
		set_mode_pin(GPIO_138_TELL_PICHING,_GPIO_READ_MODE);
		set_mode_pin(GPIO_137_TELL_ROLLING,_GPIO_READ_MODE);
		set_mode_pin(GPIO_136_SET_INIT_POS,_GPIO_READ_MODE);
		first_time = false;
	}

	btn_position = get_pin_status(GPIO_139_TELL_POSITION);
	btn_pich = get_pin_status(GPIO_138_TELL_PICHING);
	btn_roll = get_pin_status(GPIO_137_TELL_ROLLING);
	btn_set_position = get_pin_status(GPIO_136_SET_INIT_POS);

	// If last time there was not keys pressed, check if now some key is pressed
	if(key_is_pressed == false) {
		if(btn_position == _GPIO_PIN_IS_ON) ret_value = TELL_ME_DIRECTION;
		if(btn_pich == _GPIO_PIN_IS_ON) ret_value = TELL_ME_PITCHING;
		if(btn_roll == _GPIO_PIN_IS_ON) ret_value = TELL_ME_ROOLLING;
		if(btn_set_position == _GPIO_PIN_IS_ON) ret_value = SET_DIRECTION;
		if(ret_value != NOT_BUTTONS_PRESSED) {
			// Set the flag
			key_is_pressed = true;
			// Start the timer
			get_elapsed_time_after_button_used(RESET_ELAPSED_BUTTON_PRESSED_TIME);
			// Return the code
			return ret_value;
		}
		/*if(btn_pich == _GPIO_PIN_IS_ON) {key_is_pressed = true;return TELL_ME_PITCHING;}
		if(btn_roll == _GPIO_PIN_IS_ON) {key_is_pressed = true;return TELL_ME_ROOLLING;}
		if(btn_set_position == _GPIO_PIN_IS_ON) {key_is_pressed = true;return SET_DIRECTION;}*/
	}
	// Check for time elapsed
	if(key_is_pressed == true) {
		if(get_elapsed_time_after_button_used(GET_ELAPSED_BUTTON_PRESSED_TIME) == false)
			return NOT_BUTTONS_PRESSED;
	}

	// Check for button release
	if((btn_position == _GPIO_PIN_IS_OFF) &&	(btn_pich == _GPIO_PIN_IS_OFF) &&
			(btn_roll == _GPIO_PIN_IS_OFF) && (btn_set_position == _GPIO_PIN_IS_OFF)) {
		// Remove the flag
		key_is_pressed = false;
	}
	return NOT_BUTTONS_PRESSED;

}
// --------------------------------------------
void menu_x86(char *what) {
	printf("Choise:%s\n",what);
	puts("Tell me direction (1)\nSet direction (2)\nTell me rolling (3)\nTell me pitching (4)\nExit (qq)");
}
// --------------------------------------------
bool get_elapsed_time_after_button_used(int should_reset) {
	// tv_sec tv_nsec */
	static struct timespec start;
	struct timespec end;

	if(should_reset == RESET_ELAPSED_BUTTON_PRESSED_TIME) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		return false;
	}
	// else check elepsed time
	clock_gettime(CLOCK_MONOTONIC, &end);

	unsigned int sec_elapsed = end.tv_sec - start.tv_sec;
	uint64_t nano_sec_elapsed = end.tv_nsec - start.tv_nsec;
	unsigned int micro_sec_elapsed = (sec_elapsed * 1000000) + (nano_sec_elapsed / 1000);

	// Check for 0.5 sec (500000 micro)
	if(micro_sec_elapsed > 500000) return true;
	return false;
}
