/***************************************************************************
	progetto			: "la bussola parlante" con scheda snowboard
    file:				: check_route.c
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
#include <time.h>
#include "check_route.h"

#define OUT_ROUTE_TIME_CONTROL	10 // sec.

bool out_route_time_control() {
	static time_t last_time_check = 0, now;
	// Check for first time
	if (last_time_check == 0) {
		last_time_check = time (NULL);
		return false;
	}
	// Calculate how many seconds from last check
	now = time(NULL);
	if(now > (last_time_check + OUT_ROUTE_TIME_CONTROL)) {
		// It is time to controll
		last_time_check = time (NULL);
		return true;
	} else return false;
}
// -----------------------------------------------------
bool out_route_control() {
	int out_route;
	// Get the degrees
	out_route = how_many_out_route_degrees();
	// Check if negative
	if(out_route < 0) out_route = out_route * -1;
	if(out_route > OUT_ROUTE_LIMIT_DEGREES) return true;
	return false;
}
// -----------------------------------------------------
int how_many_out_route_degrees() {
	int degrees_to_0,degrees_to_360, out_route;
	// Checks if present route and previous route are in 4 and 1 sector
	if((PRESENT_ROUTE > 270) && (DESTINATION_ROUTE < 90)) {
		degrees_to_0 = DESTINATION_ROUTE;
		degrees_to_360 = 360 - PRESENT_ROUTE;
		out_route = degrees_to_0 + degrees_to_360;
		// Route is negative
		return (out_route * -1);
	}

	if ((DESTINATION_ROUTE > 270) && (PRESENT_ROUTE < 90)) {
		degrees_to_0 = PRESENT_ROUTE;
		degrees_to_360 = 360 - DESTINATION_ROUTE;
		out_route = degrees_to_0 + degrees_to_360;
		return out_route;
	}
	// We are not around 0/360 degrees
	out_route = PRESENT_ROUTE - DESTINATION_ROUTE;
	return out_route;
}
