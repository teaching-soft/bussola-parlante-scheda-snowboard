/* gpio_management.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: gpio management
 */ 
 
#include "gpio_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define MAX_FULL_PATH	100
#define MAIN_PATH "/sys/class/gpio/"
#define PIN_EXPORT_FILE "export"
#define PIN_DIRECTION_FILE "direction"
#define PIN_VALUE_FILE "value"


bool export_pin(char *what_pin);

bool export_pin(char *what_pin)
{
	int handle;
	char full_path[MAX_FULL_PATH];
	strcpy(full_path,MAIN_PATH);
	strcat(full_path,PIN_EXPORT_FILE);
	
	//puts(full_path);
	
	handle = open(full_path, O_WRONLY);
	if (handle < 0)
  {
		perror("Cannot open export file.\n");
    return false;
  }
  // handle, what, count, offset
  pwrite (handle,what_pin,strlen(what_pin),0);
  close(handle);
  return true;  
}
// --------------------------------------------------------------
bool set_mode_pin(char *what_pin, enum gpio_pin_mode mode)
{
	int handle;
	char full_path[MAX_FULL_PATH],how[5];
	
	if(export_pin(what_pin) == false) return false;
	
	sprintf(full_path,"%sgpio%s/%s",MAIN_PATH,what_pin,PIN_DIRECTION_FILE);		
	handle = open(full_path, O_WRONLY);
	if (handle < 0)
  {
		perror("Cannot open direction file.\n");
    return false;
  }

  if(mode == _GPIO_READ_MODE) strcpy(how,"in");
  else strcpy(how,"out");
  
  pwrite (handle,what_pin,strlen(how),0);
  close(handle);
  return true;  
}
// --------------------------------------------------------------
bool set_pin_status(char *what_pin, enum gpio_pin_set_status status)
{
	int handle;
	char full_path[MAX_FULL_PATH],how[5];
	sprintf(full_path,"%sgpio%s/%s",MAIN_PATH,what_pin,PIN_VALUE_FILE);
	
	//puts(full_path);

	handle = open(full_path, O_WRONLY);
	if (handle < 0)
  {
		perror("Cannot open value file for write.\n");
    return false;
  }
  // pwrite(handle, what, count, offset)
  if(status == _GPIO_PIN_SET_ON) strcpy(how,"1");
  else strcpy(how,"0");
  
  pwrite (handle,what_pin,strlen(how),0);
  close(handle);
  return true;
}
// --------------------------------------------------------------
enum gpio_pin_read_status get_pin_status(char *what_pin)
{
	int handle;
	char full_path[MAX_FULL_PATH],buf[10];
	sprintf(full_path,"%sgpio%s/%s",MAIN_PATH,what_pin,PIN_VALUE_FILE);
	
	//puts(full_path);

	handle = open(full_path, O_RDONLY);
	if (handle < 0)
  {
		perror("Cannot open file for read.\n");
    return false;
  }
  // pread (handle, buffer, num_byte, offset)
	pread (handle,buf,1,0);
	close(handle);
		
  if(buf[0] == '1') return _GPIO_PIN_SET_ON;
  else return _GPIO_PIN_SET_OFF;
}



// --------------------------------------------------------------------------
