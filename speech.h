/***************************************************************************
	progetto			: "la bussola parlante" con scheda snowboard
    file:				: speech.h
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

#ifndef _SPEECH_H_
#define _SPEECH_H_

void say_direction (void);
void say_set_direction (void);
void say_unset_direction(void);
void say_rolling(void);
void say_pitching(void);
void say_out_route(void);
void say_something(char *what);

#endif // _SPEECH_H_
