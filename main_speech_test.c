/***************************************************************************
	progetto			: "la bussola parlante" con scheda snowboard
    file:				: main_speech_test.c
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SPEECH_PROGRAM	"festival"
int main(int argn,char *argv[]) {

	char buffer[100];
	pid_t pid;
	int i = 30;

	FILE *fp;
	int status;
	fp = popen("festival --tts --pipe --language italian", "w");
	if (fp == NULL)puts("Quancosa non è andato");
	sprintf(buffer,"Fuori rotta di  %d ",i+30);
	fputs(buffer,fp);

	status = pclose(fp);
	if (status == -1) {
		puts("fclose error");/* Error reported by pclose() */
	}
	puts("Fine");


	/*
	for(i = 0;i < 3;i++)
	{
		//sleep(5);
		pid = fork();
		// Child process
		if(pid == 0)
		{
			 questi lasciano dei defunc con espeak
			sprintf(buffer,"\"%s\"",text_to_speech);
			execl(SPEECH_PROGRAM, SPEECH_PROGRAM,buffer, NULL);
			exit(0);

			// echo "come stai" | festival --tts --pipe --language italian
			//sprintf(buffer,"echo \"Ciao %d\" | festival --tts --pipe --batch --language italian ",i,SPEECH_PROGRAM);
			//puts("Sono il processo figlio");puts(buffer);
			//execl(SPEECH_PROGRAM, SPEECH_PROGRAM,buffer, NULL);
			//system (buffer);
			//execl("/bin/echo","/bin/echo","Ciao", "|", "festival --tts --pipe --language italian ", NULL);
			FILE *fp;
			int status;
			fp = popen("festival --tts --pipe --language italian", "w");
			if (fp == NULL)puts("Quancosa non è andatao");
			sprintf(buffer,"Fuori rotta di  %d ",i+30);
			fputs(buffer,fp);

			status = pclose(fp);
			if (status == -1)
			{
				puts("fclose error");

			} else {


			}
			//perror("Error in call_speech_engine");
		}
		else
		{
			printf("Loop %d\n",i);
		}
	}
	*/
	return EXIT_SUCCESS;
}
