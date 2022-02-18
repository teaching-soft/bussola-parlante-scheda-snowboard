/***************************************************************************
	progetto			: "la bussola parlante" con scheda snowboard
    file:				: check_route.h
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

#ifndef _CHECKS_ROUTE_H_
#define _CHECKS_ROUTE_H_

#include "global_variables.h"

#define ROUTE_TOLLERANCE	10
bool out_route_time_control();
bool out_route_control();
int how_many_out_route_degrees();

#endif // _CHECKS_ROUTE_H_
