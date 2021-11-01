#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<semaphore.h>

/** startLog(int, int*)
 * This function takes the *.log file name and also the number of consumer threads
 **/
void startLog(int argc, char * argv[]);

/** logstr(char*)
 * This Logs out into the *.log file, whatever the input is 
 **/
void logstr(char * str);

