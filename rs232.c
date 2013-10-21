/***************************************************************************
                          rs232.c for "la bussola parlante"
                             -------------------
    begin                : mer apr 21 10:34:57 CET 2011
    copyright            : (C) 2011 by Giancarlo Martini and friends
    email                : gm@giancarlomartini.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "rs232.h"


int _rs232_set(int ttys_descriptor,unsigned int baud,unsigned int data_bits, unsigned int parity, unsigned int stop_bits);
/* For error handling */
int _setrs232_baud(int ttys_descriptor,unsigned int baud);
int _setrs232_databits(int ttys_descriptor,unsigned int data_bits);
int _setrs232_parity(int ttys_descriptor,unsigned int parity);
int _setrs232_stopbits(int ttys_descriptor,unsigned int stop_bits);
int _setrs232_other(int ttys_descriptor);
/*--------------------------------------------------------------------------------------------- */
int rs232_open(const char *ttysPort,unsigned int baud, unsigned int data_bits, unsigned int parity, unsigned int stop_bits)
{
	int ret;
	/* Apre la porta .... */
	int ttys_descriptor = open(ttysPort, O_RDWR | O_NOCTTY | O_NONBLOCK | O_NDELAY);
	/* Controllino..... */
	if (ttys_descriptor == -1) return -1;

	/* Blocco del file */
	flock(ttys_descriptor,LOCK_EX);

	/* Configura la seriale */
	ret = _rs232_set(ttys_descriptor,baud,data_bits,parity,stop_bits);
	if(ret == -1) return ret;

	return ttys_descriptor;
}
/*---------------------------------------------------------------------------------------------*/
int _rs232_set(int ttys_descriptor, unsigned int baud, unsigned int data_bits, unsigned int parity, unsigned int stop_bits)
{
	int ret;
	ret = _setrs232_baud(ttys_descriptor,baud);
	if(ret == -1)
	{
		perror("Set baud");
		printf("ERRNO=%d\n",errno);
		exit(1);
	}
	ret = _setrs232_databits(ttys_descriptor,data_bits);
	if(ret == -1)
	{
		perror("Databits!");
		printf("ERRNO=%d\n",errno);
		exit(1);
	}

	ret =_setrs232_parity(ttys_descriptor,parity);
	if(ret == -1)
	{
		perror("Parity!");
		printf("ERRNO=%d\n",errno);
		exit(1);
	}

	ret =_setrs232_stopbits(ttys_descriptor,stop_bits);
	if(ret == -1)
	{
		perror("Stopbits!");
		printf("ERRNO=%d\n",errno);
		exit(1);
	}

	ret = _setrs232_other(ttys_descriptor);
	if(ret == -1)
	{
		perror("Other!");
		printf("ERRNO=%d\n",errno);
		exit(1);
	}

	return ret;
}
/*--------------------------------------------------------------------------------------------- */
int _setrs232_baud(int ttys_descriptor,unsigned int baud)
{
	int ret;
	struct termios options;
	/* Recupera le informazioni        */
	ret = tcgetattr(ttys_descriptor, &options);
	if(ret == -1)
	{
		perror("Tcgetattr!");
		printf("ERRNO=%d\n",errno);
		exit(1);
	}

	/*  Imposta la velocità           */
	ret = cfsetispeed(&options,baud);
	if(ret == -1)
	{
		perror("Cfsetispeed!");
		printf("ERRNO=%d\n",errno);
		exit(1);
	}

	ret = cfsetospeed(&options,baud);
	if(ret == -1)
	{
		perror("Cfsetospeed!");
		printf("ERRNO=%d\n",errno);
		exit(1);
	}

	ret = tcsetattr(ttys_descriptor, TCSANOW, &options);

	if(ret == -1)
	{
		perror("-------!");
		printf("ERRNO=%d\n",errno);
		exit(1);
	}

	return ret;
}
/*--------------------------------------------------------------------------------------------- */
int _setrs232_databits(int ttys_descriptor,unsigned int data_bits)
{
	int ret;
	struct termios options;
	/* Recupera le informazioni        */
	tcgetattr(ttys_descriptor, &options);

	/* Imposta la dimensione dei dati  */
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= data_bits;
	ret = tcsetattr(ttys_descriptor, TCSANOW, &options);
	return ret;
}
/*--------------------------------------------------------------------------------------------- */
int _setrs232_parity(int ttys_descriptor,unsigned int parity)
{
	int ret;
	struct termios options;
	/* Recupera le informazioni        */
	tcgetattr(ttys_descriptor, &options);

	/* Nessuna parità                  */
	if(parity == PNONE) options.c_cflag &= ~PARENB;
	/* Parità pari                     */
	if(parity == PEVEN)
	{
		options.c_cflag |= PARENB;
		options.c_cflag &= ~PARODD;
	}
	/* Parità dispari                  */
	if(parity == PODD)
	{
		options.c_cflag |= PARENB;
		options.c_cflag |= PARODD;
	}

	/* Se è impostata la parità la gestisce anche in input */
	if((parity == PEVEN) || (parity == PODD))  options.c_iflag |= (INPCK | ISTRIP);


	ret = tcsetattr(ttys_descriptor, TCSANOW, &options);
	return ret;
}
/*--------------------------------------------------------------------------------------------- */
int _setrs232_stopbits(int ttys_descriptor,unsigned int stop_bits)
{
	int ret;
	struct termios options;
	/* Recupera le informazioni        */
	tcgetattr(ttys_descriptor, &options);

	/* Imposta lo stop bit             */
	if(stop_bits == SB1) options.c_cflag &= ~CSTOPB;
	else options.c_cflag |= CSTOPB;

	/* Setta  le opzioni della porta */
	ret = tcsetattr(ttys_descriptor, TCSANOW, &options);
	return ret;

}
/*--------------------------------------------------------------------------------------------- */
int _setrs232_other(int ttys_descriptor)
{
	int ret;
	struct termios options;
	/* Recupera le informazioni        */
	tcgetattr(ttys_descriptor, &options);

	/* Imposta  altre opzioni        */
	options.c_cflag |= (CLOCAL | CREAD);

	/* Modalità raw, disabilita l'eco, abilita il segnale ISIG */
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	/* Imposta il raw mode anche in uscita */
	options.c_oflag &= ~OPOST;
	/* Setta  le opzioni della porta */
	ret = tcsetattr(ttys_descriptor, TCSANOW, &options);
	return ret;
}
/*--------------------------------------------------------------------------------------------- */
int rs232_buffer_in_lenght(int ttys_descriptor)
{
	int ret;
    int nbytes;
    ret = ioctl(ttys_descriptor,FIONREAD,&nbytes);
	if(ret == -1) return -1;
    return nbytes;
}
/*--------------------------------------------------------------------------------------------- */
int rs232_bytes_arrived(int ttys_descriptor, int time_out)
{
	int ret;
	fd_set readfs;
	struct timeval tv;

	FD_ZERO(&readfs);

	FD_SET(ttys_descriptor, &readfs);

	tv.tv_sec = time_out;

	select(ttys_descriptor + 1, &readfs, NULL, NULL,&tv);

	if (FD_ISSET(ttys_descriptor,&readfs))
	{
		int nbytes;
		ret = ioctl(ttys_descriptor,FIONREAD,&nbytes);
		if(ret == -1) return -1;
		return nbytes;
	}
	return 0;
}
/*---------------------------------------------------------------------------------------------*/
int rs232_get(int ttys_descriptor, unsigned char *buffer, unsigned int max_bytes)
{
	int bytes_readed, bytes_aval, ret;

	if(ttys_descriptor == -1) return -1;

	/* Controlla quanti bytes sono arrivati nel caso ritorna subito  */
	bytes_aval = rs232_bytes_arrived(ttys_descriptor,0);

	if(bytes_aval == 0)
	{
		buffer [0] = '\0';
		return 0;
	}

	if((unsigned int)bytes_aval > max_bytes) bytes_readed = max_bytes;
	else bytes_readed = bytes_aval;

	ret = read(ttys_descriptor, buffer,(unsigned int)bytes_readed);

	return ret;
}
/*---------------------------------------------------------------------------------------------*/
void rs232_close(int ttys_descriptor)
{
	/* Sblocco del file     */
	if(ttys_descriptor != -1)
	{
		flock(ttys_descriptor,LOCK_UN);
		close(ttys_descriptor);
	}
}
/*---------------------------------------------------------------------------------------------*/
int rs232_write(int ttys_descriptor, unsigned char * buffer, unsigned int buf_len)
{
	int ret;
	if(ttys_descriptor == -1) return -1;

	ret = write(ttys_descriptor, buffer, buf_len);
	if(ret == -1) return -1;

	return ret;
}

