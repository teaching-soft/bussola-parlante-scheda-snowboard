/* speech.c
 * author: 5 TIEN
 * date: 2/03/2013
 * description: speech functions
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "speech.h"
#include "check_route.h"
#include "global_variables.h"

#define FESTIVAL_DEFAULT_SERVER_HOST "localhost"
#define FESTIVAL_DEFAULT_SERVER_PORT 1314
static int festival_socket_open(const char *host, int port);

// espeak flite festivall
// espeak   -vit+m/f1 "Ciao come stai"
/* echo "come stai" | festival --tts --pipe --language italian
{
	apt-get install festival-italian festival)
	.festivalrc
	(set! main-path "/usr/share/festival")
	(set! libdir main-path)
	(set! lexdir (path-append libdir "dicts"))
	(set! voice_default 'voice_pc_diphone) <--maschile
	(set! voice_default 'voice_lp_diphone) <--femminile

	.festivalvarsrc
	(set! main-path "/usr/share/festival")
	(set! load-path (cons main-path load-path))
*/
//#define SPEECH_PROGRAM	"/usr/bin/espeak"
#define SPEECH_PROGRAM	"festival"
void call_speech_engine(char *text_to_speech);

void say_direction (void)
{
	char buffer [100];
	sprintf(buffer,"Direzione %d gradi",PRESENT_ROUTE);
	call_speech_engine(buffer);
	//puts(buffer);

}
// -------------------------------------------------------
void say_set_direction (void)
{
	char buffer [100];
	sprintf(buffer,"Rotta impostata a %d gradi",PRESENT_ROUTE);
	call_speech_engine(buffer);
	//puts(buffer);
}
// -------------------------------------------------------
void say_unset_direction(void)
{
	call_speech_engine("Impostazione rotta rimossa");
	//puts("Impostazione rotta rimossa");
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
void say_rolling(void)
{
	char buffer [100];
	sprintf(buffer,"Rollio %d gradi",ROLLING);
	call_speech_engine(buffer);
	//puts(buffer);
}
// ------------------------------------------------------
void say_pitching(void)
{
	char buffer [100];
	sprintf(buffer,"Beccheggio %d gradi",PITCHING);
	call_speech_engine(buffer);
	//puts(buffer);

}
// ------------------------------------------------------
void call_speech_engine(char *text_to_speech)
{
	char buffer[200];
	static int socket = -1;
	int n_byte_write;
	if(socket == -1) socket = festival_socket_open(FESTIVAL_DEFAULT_SERVER_HOST, FESTIVAL_DEFAULT_SERVER_PORT);
	if(socket == -1)
	{
		puts("Festival not found, try to start server: festival --server --language italian");
		system ("festival --server --language italian &");
		sleep(2);
		socket = festival_socket_open(FESTIVAL_DEFAULT_SERVER_HOST, FESTIVAL_DEFAULT_SERVER_PORT);
		// Try next time
		if(socket == -1) return;
	}
	//	Set female voice
	strcpy(buffer,"(set! voice_default 'voice_lp_diphone)");
	n_byte_write = write(socket,buffer,strlen(buffer));
	if (n_byte_write < 0) puts("I can't send cmd to festival");
	//--
	sprintf(buffer,"(SayText \"%s\")",text_to_speech);
	n_byte_write = write(socket,buffer,strlen(buffer));
	if (n_byte_write < 0)  if (n_byte_write < 0) puts("I can't send message to speak");
	//--
	//close(socket);
	/* Changed for speeder program
	//char buffer[100];
	pid_t pid;
	pid = fork();
	// Child process
	if(pid == 0)
	{
		//puts("Start child");
		FILE *fp;
		int status;
		fp = popen("festival --tts --pipe --language italian", "w");
		if (fp == NULL) puts("Some was wrong in call_speech_engine (popen) ");
		fputs(text_to_speech,fp);

		status = pclose(fp);
		if (status == -1) puts("Some was wrong in call_speech_engine (pclose)");
		//puts("End child");
		exit(0);
	}
	// Check for the child and remove the zombies
	waitpid(-1, NULL,WNOHANG);
	*/
}
// ---------------------------------------------------------------------
void say_something(char *what)
{
	call_speech_engine(what);
}
// ---------------------------------------------------------------------
static int festival_socket_open(const char *host, int port)
{
    /* Return an FD to a remote server */
    struct sockaddr_in serv_addr;
    struct hostent *serverhost;
    int fd;

    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (fd < 0)
    {
		fprintf(stderr,"festival_client: can't get socket\n");
		return -1;
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    if ((serv_addr.sin_addr.s_addr = inet_addr(host)) == -1)
    {
		/* its a name rather than an ipnum */
		serverhost = gethostbyname(host);
		if (serverhost == (struct hostent *)0)
		{
			fprintf(stderr,"festival_client: gethostbyname failed\n");
			return -1;
		}
		memmove(&serv_addr.sin_addr,serverhost->h_addr, serverhost->h_length);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
    {
		fprintf(stderr,"festival_client: connect to server failed\n");
		return -1;
    }

    return fd;
}
/*
 * 	if(pid == 0)
	{
		questi lasciano dei defunc con espeak
		sprintf(buffer,"\"%s\"",text_to_speech);
		execl(SPEECH_PROGRAM, SPEECH_PROGRAM,buffer, NULL);
		exit(0);

		// echo "come stai" | festival --tts --pipe --language italian
		sprintf(buffer,"echo \"%s\" | %s --tts --pipe --language italian ",text_to_speech,SPEECH_PROGRAM);
		//execl(SPEECH_PROGRAM, SPEECH_PROGRAM,buffer, NULL);
		system (buffer);
		perror("Error in call_speech_engine");
	}
	//puts(text_to_speech);
	*/