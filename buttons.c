/* buttons.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: buttons function
 */
#include<stdio.h> 
#include "buttons.h"  

int read_buttons(void)
{
	int choise;
	printf("Inserire scelta operatore:");
	scanf("%d",&choise);
	if(choise == TELL_ME_DIRECTION) return TELL_ME_DIRECTION;
	if(choise == SET_DIRECTION) return SET_DIRECTION;	
	return NOT_BUTTONS_PRESSED;
}   
