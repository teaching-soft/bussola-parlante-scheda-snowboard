/***************************************************************************
	progetto			: "la bussola parlante" con scheda snowboard
    file:				: button.h
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

#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#define NOT_BUTTONS_PRESSED	0
#define TELL_ME_DIRECTION	1
#define SET_DIRECTION		2
#define TELL_ME_ROOLLING		3
#define TELL_ME_PITCHING		4
#define DO_SOMETHING			5

int read_buttons(void);

#endif // _BUTTONS_H_
