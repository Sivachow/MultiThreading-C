#include"trans_sleep.h"
#include <pthread.h>
#include <semaphore.h>
#include<stdlib.h>
#include<stdio.h>
#include"logging.h"
#include <unistd.h>
#include <string.h>
#include<time.h>
/** start_threading(int, int*, int*)
 *  Number of threads, pointer to the array of status of consumers and Summary
 *  Starts the threads and takes input from stdin and Logs out to *.log file
 **/
void start_threading(int threads, int* temp_status, int *temp_summ);

/** reqWork(int, int)
 *  Takes consumer id and flag for requesting or Completing work
 *  It logs out the Completed and Requested work using semaphores.
 **/
void reqWork(int id, int reqCom);

/** threadloop(void *)
 * Takes input a void * arguemnt
 * This is used as a starting point for all the consumer threads.
 **/
void *threadloop( void *arg );

/** input()
 * Reads the input and assigns to the worers as they get free
 **/
void input();

/** changeStatus(int, int)
 * rdWr is the flag to decide whether we are writing or reading the status of consumers
 * thrd is to explain what thread are we modifying or reading
 * It also takes care of Queuing. 
 **/
int changeStatus(int rdWr, int thrd);

/** input_s_t(int)
 * if the stdin character is either s or t, this function deals by taking another input
 * to work or time to sleep
 **/
char input_s_t(int s_t);

/** logSummary()
 * It logs summary into the *.log file after the given worj is finished.
 **/
void logSummary();