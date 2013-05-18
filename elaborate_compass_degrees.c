/* elaborate_compass_degree.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: function to elaborate compass values
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include "elaborate_compass_degrees.h"
#include "global_variables.h"
#include "rs232.h"

#define ANSWER_LENGHT_FOR_CMP10_CMD	4
#define RESET_ELAPSED_TIMER 			1
#define GET_ELAPSED_TIME 			0
#define MAX_COMPASS_VALUES 			10
int COMPASS_VALUES[MAX_COMPASS_VALUES];

int init_serial_port(void);
int write_cmd(int ttys_descriptor, unsigned char cmd);
bool get_elapsed_time(int should_reset);
bool read_compass_value(int* value);
bool query_cmp10(int* value);
void insert_read_value_in_vector(int value);
void do_new_average_value(void);

void get_new_compass_value()
{
	int new_value;
	bool is_value_present;
	is_value_present = read_compass_value(&new_value);
	if(is_value_present == true)
	{
		insert_read_value_in_vector(new_value);
		if(I_CAN_WORK == true) do_new_average_value();
	}
}
// ---------------------------------
bool read_compass_value(int* value)
{
	bool ret;
	ret = query_cmp10(value);
	return ret;


	/*
#ifdef __i386__
	*value = rand() % 360;
	return true;
#endif

#ifdef __arm__
	bool ret;
	ret = query_cmp10(value);
	return ret;
#endif
* */
}
// ---------------------------------
bool query_cmp10(int* value)
{
	static int ttys_cmp10_descriptor;
	static bool i_am_wait_for_reply = false;
	unsigned char buffer[100];
	unsigned int position_value,i;
	if(i_am_wait_for_reply == false)
	{
		ttys_cmp10_descriptor = init_serial_port();
		write_cmd(ttys_cmp10_descriptor,0x23);
		i_am_wait_for_reply = true;
		get_elapsed_time(RESET_ELAPSED_TIMER);
		return false;
	}
	// Check elapsed time, i_am_wait_for_reply is certainly true;
	if(get_elapsed_time(GET_ELAPSED_TIME) == false) return false;
	// Next time new request
	i_am_wait_for_reply = false;
	// Check arrived data lenght
	int bytes_arrived = rs232_buffer_in_lenght(ttys_cmp10_descriptor);
	if (bytes_arrived != ANSWER_LENGHT_FOR_CMP10_CMD)
	{
		printf("SERIAL ERROR: Bytes arrived:%d#",bytes_arrived);
		for(i = 0;i < bytes_arrived;i++)
		{
			rs232_get(ttys_cmp10_descriptor,buffer, 1);
			printf("%d ",buffer[0]);
		}
		puts("#");
		rs232_close(ttys_cmp10_descriptor);
		return false;
	}
	// Get data
	rs232_get(ttys_cmp10_descriptor,buffer, ANSWER_LENGHT_FOR_CMP10_CMD);
	if(COMPASS_DEBUG == true) printf("#Data: %d %d %d %d # Close port\n",buffer[0],buffer[1],buffer[2],buffer[3]);
	rs232_close(ttys_cmp10_descriptor);
	// Move bytes as documentation
	position_value = buffer[0];
	position_value = position_value << 8;
	position_value |= buffer[1];
	*value = position_value;
	PITCHING = (signed char)buffer[2];
	ROLLING = (signed char)buffer[3];
	return true;
}
//-------------------------------------------------------------------------------
bool get_elapsed_time(int should_reset)
{
	// tv_sec tv_nsec */
	static struct timespec start;
	struct timespec end;

	if(should_reset == RESET_ELAPSED_TIMER)
	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		return false;
	}
	// else check elepsed time
	clock_gettime(CLOCK_MONOTONIC, &end);

	unsigned int sec_elapsed = end.tv_sec - start.tv_sec;
	uint64_t nano_sec_elapsed = end.tv_nsec - start.tv_nsec;
	unsigned int micro_sec_elapsed = (sec_elapsed * 1000000) + (nano_sec_elapsed / 1000);

	// Check for 1 sec (1000000 micro)
	if(micro_sec_elapsed > 1000000) return true;
	return false;
}
//-------------------------------------------------------------------------------
int init_serial_port()
{
	int ttys_descriptor = rs232_open(SERIAL_PORT,B9600,CS8,PNONE,SB1);
	// Test port descriptor
	if(COMPASS_DEBUG == true) printf("Open port ");
	if(ttys_descriptor == -1)
	{
		perror("SERIAL ERROR:Port not open!!!\nSerial port is:");
		printf("%s\n",SERIAL_PORT);
		exit(-1);
	}
	return ttys_descriptor;
}
// -------------------------------------
int write_cmd(int ttys_descriptor, unsigned char cmd)
{
	int ret;
	ret = rs232_write(ttys_descriptor,&cmd,1);
	if(COMPASS_DEBUG == true) puts("Send cmd");
	if(ret == -1)
	{
		perror("SERIAL ERROR:I can't write!!");
		exit(-1);
	}
	return ret;
}
// ---------------------------------
void insert_read_value_in_vector(int value)
{
     int static index = 0;
     if(index == MAX_COMPASS_VALUES)
	 {
		 index = 0;
		 I_CAN_WORK = true;
	 }
     COMPASS_VALUES[index] = value / 10;
     index++;
}
// --------------------------------
void do_new_average_value(void)
{
	double sin_degree,cos_degree,sum_sin=0,sum_cos=0,average_sin,average_cos;
	double to_rad = M_PI / 180;
	int i;

	for(i = 0;i < MAX_COMPASS_VALUES;i++)
	{
		sin_degree = sin (COMPASS_VALUES[i] * to_rad);
		cos_degree = cos (COMPASS_VALUES[i] * to_rad);
		sum_sin = sum_sin + sin_degree;
		sum_cos = sum_cos + cos_degree;
	}
	average_sin = sum_sin/MAX_COMPASS_VALUES;
	average_cos = sum_cos/MAX_COMPASS_VALUES;
	PRESENT_ROUTE = (atan2 (average_sin,average_cos) * 180) / M_PI;
	if(PRESENT_ROUTE < 0) PRESENT_ROUTE += 360;

	if(COMPASS_DEBUG == true)
	{
		for(i = 0;i < MAX_COMPASS_VALUES;i++) printf("%d ",COMPASS_VALUES[i]);
		printf("# Av. sin:%f # Av. cos:%f # Dir:%d\n",average_sin, average_cos, PRESENT_ROUTE);
	}


}
