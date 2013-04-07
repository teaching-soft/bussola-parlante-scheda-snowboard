/* gpio_management.h
 * author: 5 TIEN
 * date: 23/02/2013
 * description: gpio management
 */ 
 
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
