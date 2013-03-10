/* speech.c
 * author: 5 TIEN
 * date: 2/03/2013
 * description: speech functions
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "speech.h"
#include "checks.h"
#include "global_variables.h"

#define SPEECH_PROGRAM	"/usr/bin/espeak"
void call_speech_engine(char *text_to_speech);

void say_direction (void)
{
	char buffer [100];
	sprintf(buffer,"La direzione è %d gradi",PRESENT_ROUTE);
	call_speech_engine(buffer);
	puts(buffer);
	 
}
// -------------------------------------------------------
void say_set_direction (void)
{
	char buffer [100];
	sprintf(buffer,"La rotta è impostata a %d gradi",PRESENT_ROUTE);
	call_speech_engine(buffer);
	puts(buffer);	 
}
// -------------------------------------------------------
void say_unset_direction(void)
{
	call_speech_engine("Impostazione rotta rimossa");
	puts("Impostazione rotta rimossa");
}   
// -------------------------------------------------------
void say_out_route(void)
{
	char buffer [100];
	int out_route;
	out_route = how_many_out_route_degrees ();
	sprintf(buffer,"Fuori rotta di %d gradi",out_route);
	call_speech_engine(buffer);
	
	// speech!!
}
// ------------------------------------------------------
void call_speech_engine(char *text_to_speech)
{
	char buffer[100];
	pid_t pid;
	
	pid = fork();
	// Child process	
  if(pid == 0)
  {
			
			/* questi lasciano dei defunc
			sprintf(buffer,"%s \"%s\"",SPEECH_PROGRAM,text_to_speech);
			system (buffer);
			exit(0);*/

			sprintf(buffer,"\"%s\"",text_to_speech);
			execl(SPEECH_PROGRAM, SPEECH_PROGRAM,buffer, NULL);
			perror("Error in call_speech_engine");
  }
  puts(text_to_speech);
}