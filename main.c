/* main.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: main file of talking compass project
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
	
	// First voice message
	// Defined in speech.c
	say_something("Bi Bi compass avviata");

	// Start
	while(1)
	{
		// ==============================
		// Get new compass value, defined in elaborate_compass_degree.c
		get_new_compass_value();
		// ==============================
		// - Capture user input, defined in buttons.c
		operator_choise = read_buttons();
		// Wait for COMPASS_VALUES array is full for the first time
		if(I_CAN_WORK == false) continue;
		// ==============================
		// Execute user request
		if(operator_choise == TELL_ME_DIRECTION) {puts("TELL_ME_DIRECTION");say_direction();}
		if(operator_choise == TELL_ME_ROOLLING) {puts("TELL_ME_ROOLLING");say_rolling();}
		if(operator_choise == TELL_ME_PITCHING) {puts("TELL_ME_PITCHING");say_pitching();}
		if(operator_choise == SET_DIRECTION)
		{
				// Checks if should set or remove route status
				if(DESTINATION_ROUTE == -1)
				{
					DESTINATION_ROUTE = PRESENT_ROUTE;
					say_set_direction() ;puts("SET_DIRECTION");
				}
				else
				{
					DESTINATION_ROUTE = -1;
					say_unset_direction();puts("UN SET_DIRECTION");
				}
		}
		// ==============================
		// Checks if the route is set-up
		if(DESTINATION_ROUTE != -1)
		{
				// Check if the time control has gone
				// Defined in check_route.c
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
	while ((opt = getopt(argn, argv, "adt:vh")) != -1)
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
			case 'a':
				printf("Average on\n");
				AVERAGE = true;;
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