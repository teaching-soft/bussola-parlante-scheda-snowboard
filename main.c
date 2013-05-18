/* main.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: main file of snowcompass project
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "buttons.h"
#include "speech.h"
#include "check_route.h"
#include "elaborate_compass_degrees.h"
#include "global_variables.h"

char DEFAULT_SERIAL_PORT[] = "/dev/ttyUSB0";
void command_line_parser(int argn, char* argv[]);


int main (int argn, char* argv[])
{
	int operator_choise;
	bool ret;

	// Check for command line options
	command_line_parser(argn,argv);

	say_something("BI Bi compass avviata");

	// Start
	while(1)
	{
		// ==============================
		// Degrees jobs
		get_new_compass_value();
		// ==============================
		// - Capture user input
		operator_choise = read_buttons();
		// Wait for COMPASS_VALUES is full
		if(I_CAN_WORK == false) continue;
		if(operator_choise == TELL_ME_DIRECTION) {puts("TELL_ME_DIRECTION");say_direction();}
		if(operator_choise == TELL_ME_ROOLLING) {puts("TELL_ME_ROOLLING");say_rolling();}
		if(operator_choise == TELL_ME_PITCHING) {puts("TELL_ME_PITCHING");say_pitching();}
		if(operator_choise == SET_DIRECTION)
		{
				// Checks if should set or remove route status
				if(PREVIOUS_ROUTE == -1)
				{
					PREVIOUS_ROUTE = PRESENT_ROUTE;
					say_set_direction() ;puts("SET_DIRECTION");
				}
				else
				{
					PREVIOUS_ROUTE = -1;
					say_unset_direction();puts("UN SET_DIRECTION");
				}
		}
		// ==============================
		// Checks if the route is set-up
		if(PREVIOUS_ROUTE != -1)
		{
				// Check if the time control has gone
				ret = out_route_time_control();
				if(ret == true)
				{
					// Checks the boat out route
					ret = out_route_control();
					if(ret == true) say_out_route();
				}
		}
	}
	return 0;
}
// ---------------------------------------------
void command_line_parser(int argn, char* argv[])
{
	int opt;
	strcpy(SERIAL_PORT,DEFAULT_SERIAL_PORT);
	while ((opt = getopt(argn, argv, "dt:vh")) != -1)
	{
        switch (opt)
		{
			case 'd':
				puts("Debug mode on");
				COMPASS_DEBUG = true;
				break;
			case 't':
				printf("Device used:%s\n",optarg);
				strcpy(SERIAL_PORT,optarg);
				break;
			case 'v':
				printf("Program version:%s\n",VERSION);
				say_something("Usato opzione -v, esco");
				exit(0);
				break;
			case 'h':
				puts("Options:\n-d debug mode on\n-t tty port used es. /dev/ttyS0\n-v program version\n-h this information");
				say_something("Usato opzione -h, esco");
				exit(0);
				break;
		}
    }
}