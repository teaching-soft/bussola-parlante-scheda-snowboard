/***************************************************************************
	progetto			: "la bussola parlante" con scheda snowboard
    file:				: globa_variables.c
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
#include "global_variables.h"

int PRESENT_ROUTE = -1;
int DESTINATION_ROUTE = -1;
int PITCHING = -1;
int ROLLING = -1;
bool I_CAN_WORK = false;
char SERIAL_PORT[100] = "/dev/ttyO2" ;
bool COMPASS_DEBUG = false;
bool AVERAGE = false;
const char VERSION[] = "0.2";
