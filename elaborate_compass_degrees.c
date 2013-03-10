/* elaborate_compass_degree.c
 * author: 5 TIEN
 * date: 23/02/2013
 * description: function to elaborate compass values
 */
#include <stdio.h>
#include <stdlib.h>
#include "elaborate_compass_degrees.h" 
#include "global_variables.h"


#define MAX_COMPASS_VALUES 10
int COMPASS_VALUES[MAX_COMPASS_VALUES];

int read_compass_value();
void insert_read_value_in_vector(int value);
void remove_estremes(void);
void do_new_average_value(void);

void get_new_compass_value()
{
		int new_value;
		new_value = read_compass_value();
		insert_read_value_in_vector(new_value);
		remove_estremes();
		do_new_average_value();
	
}
// ---------------------------------
int read_compass_value(void)
{
	int ret_value;
	ret_value = rand() % 360;
	//printf("New value:%d\n",ret_value);
	return ret_value;
}
// ---------------------------------
void insert_read_value_in_vector(int value)
{
     int static index = 0;
     if(index == MAX_COMPASS_VALUES) index = 0;
     COMPASS_VALUES[index] = value;
     index++;
}
// --------------------------------
void remove_estremes(void)
{
	
}
// -------------------------------
void do_new_average_value(void)
{
	
}
