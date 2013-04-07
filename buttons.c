/* buttons.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: buttons function
 */
#include<stdio.h> 
#include "buttons.h"  

#define	GPIO_139_TELL_POSITION						"139"
#define	GPIO_138_TELL_PICHING							"138"
#define	GPIO_137_TELL_ROLLING							"137"
#define	GPIO_136_SET_INIT_POS							"136"
#define	GPIO_135_SOMETHING								"135"

int read_buttons(void)
{
	int choise;
#ifdef __i386__
// Usare stdin con select
	printf("Inserire scelta operatore:");
	scanf("%d",&choise);
	if(choise == TELL_ME_DIRECTION) return TELL_ME_DIRECTION;
	if(choise == SET_DIRECTION) return SET_DIRECTION;	
	if(choise == TELL_ME_ROOLLING) return TELL_ME_ROOLLING;
	if(choise == TELL_ME_PITCHING) return TELL_ME_PITCHING;
	//if(choise == DO_SOMETHING) return 
#endif

#ifdef __arm__




#endif	
	return NOT_BUTTONS_PRESSED;
}   
 