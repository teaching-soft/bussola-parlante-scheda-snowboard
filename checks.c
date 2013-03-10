/* checks.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: checks functions
*/
#include <time.h>
#include "checks.h"

#define OUT_ROUTE_TIME_CONTROL	10 // sec.

bool out_route_time_control()
{
			static time_t last_time_check = 0, now;
			// Check for first time
			if (last_time_check == 0)
			{
					last_time_check = time (NULL);
					return false;
			}
			// Calculate how many seconds from last check
			now = time(NULL);
			if(now > (last_time_check + OUT_ROUTE_TIME_CONTROL))
			{
					// It is time to controll
					last_time_check = time (NULL);
					return true;
			}
			else return false;	
}
// -----------------------------------------------------
bool out_route_control()
{
		int out_route;
		
		out_route = how_many_out_route_degrees();

		if(out_route > OUT_ROUTE_LIMIT_DEGREES) return true;
		return false;
}
// -----------------------------------------------------
int how_many_out_route_degrees()
{
		int degrees_to_0,degrees_to_360, out_route;
		// Checks if present route and previous route are in 4 and 1 sector
		if((PRESENT_ROUTE > 270) && (PREVIOUS_ROUTE < 90)) 
		{
				degrees_to_0 = 90 - PREVIOUS_ROUTE;
				degrees_to_360 = 360 - PRESENT_ROUTE;
				out_route = degrees_to_0 + degrees_to_360;
				return out_route;
		}
		
		if ((PREVIOUS_ROUTE > 270) && (PRESENT_ROUTE < 90))
		{
				degrees_to_0 = 90 - PRESENT_ROUTE;
				degrees_to_360 = 360 - PREVIOUS_ROUTE;
				out_route = degrees_to_0 + degrees_to_360;			
				return out_route;
		}
		// We are not around 0/360 degrees
		out_route = PRESENT_ROUTE - PREVIOUS_ROUTE;
		// Make a difference positive
		if(out_route < 0) out_route = out_route * -1;
		return out_route;	
}
