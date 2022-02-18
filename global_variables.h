/***************************************************************************
	progetto			: "la bussola parlante" con scheda snowboard
    file:				: global_variables.h
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

#ifndef _GLOBAL_VARIABLES_H_
#define _GLOBAL_VARIABLES_H_

// For use pwrite and pread
#define _XOPEN_SOURCE 500

#ifndef bool
#define bool unsigned char
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif


#define OUT_ROUTE_LIMIT_DEGREES		5 // degrees

extern int PRESENT_ROUTE;
extern int DESTINATION_ROUTE;
extern int PITCHING;
extern int ROLLING;
extern bool I_CAN_WORK;
extern char SERIAL_PORT[100];
extern bool COMPASS_DEBUG;
extern bool AVERAGE;
extern const char VERSION[];

#endif // _GLOBAL_VARIABLES_H_
