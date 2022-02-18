/***************************************************************************
	progetto			: "la bussola parlante" con scheda snowboard
    file:				: gpio_management.h
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

#ifndef _GPIO_MANAGEMENT_H_
#define _GPIO_MANAGEMENT_H_
#include "global_variables.h"
enum gpio_pin_mode {_GPIO_READ_MODE, _GPIO_WRITE_MODE};
enum gpio_pin_read_status {_GPIO_PIN_IS_ON, _GPIO_PIN_IS_OFF, _GPIO_PIN_IS_ERROR};
enum gpio_pin_set_status {_GPIO_PIN_SET_OFF, _GPIO_PIN_SET_ON};

/* es. set_mode_pin("16",_GPIO_READ_MODE) */
bool set_mode_pin(char *what_pin, enum gpio_pin_mode mode);
/* es. set_pin("16", _GPIO_PIN_SET_OFF); */
bool set_pin_status(char *what_pin, enum gpio_pin_set_status status);
/* es. get_pin("16"); */
enum gpio_pin_read_status get_pin_status(char *what_pin);


#endif // _GPIO_MANAGEMENT_H_ 
