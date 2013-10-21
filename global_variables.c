/* global_variables.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: global variables
 */
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