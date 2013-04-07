/* main.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: main file of snowcompass project
*/

#include<stdio.h>
#include "buttons.h"
#include "speech.h"
#include "checks.h"
#include "elaborate_compass_degrees.h"
#include "global_variables.h"

int main (void)
{
	int operator_choise,ret;
	while(1)
	{
		// - Capture user input 
		operator_choise = read_buttons();
		if(operator_choise == TELL_ME_DIRECTION) say_direction() ; 
		if(operator_choise == TELL_ME_ROOLLING) say_rolling() ; 
		if(operator_choise == TELL_ME_PITCHING) say_pitching() ; 
		if(operator_choise == SET_DIRECTION) 
		{
				// Checks if should set or remove route status
				if(PREVIOUS_ROUTE == -1)
				{
					PREVIOUS_ROUTE = PRESENT_ROUTE;
					say_set_direction() ;
				}
				else
				{
					PREVIOUS_ROUTE = -1;
					say_unset_direction();
				}			
		}
		// Checks if the route is set-up
		if(PREVIOUS_ROUTE != -1)
		{	
				// Check if the time control has gone
				ret = out_route_time_control();
				if(ret == 1) 
				{
					// Checks the boat out route
					ret = out_route_control();
					if(ret == 1)
						say_out_route();
				}
		}
		// Degrees jobs
		get_new_compass_value();	 
	} 
	return 0;
}	
