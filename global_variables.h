/*global_variables.h
 * author: 5 TIEN
 * date: 23/02/2013
 * description: global variables
 */

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


#define OUT_ROUTE_LIMIT_DEGREES	5 // degrees

extern int PRESENT_ROUTE;
extern int PREVIOUS_ROUTE;
extern int PITCHING;
extern int ROLLING;
extern bool I_CAN_WORK;
extern char SERIAL_PORT[100];
extern bool COMPASS_DEBUG;
extern const char VERSION[];

#endif // _GLOBAL_VARIABLES_H_