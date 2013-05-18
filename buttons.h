/* buttons.h
 * author: 5 TIEN
 * date: 23/02/2013
 * description: buttons function header
 */

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
