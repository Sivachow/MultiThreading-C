#include"trans_sleep.h"
#include <pthread.h>
#include <semaphore.h>
#include<stdlib.h>
#include<stdio.h>
#include"logging.h"
#include <unistd.h>
#include <string.h>

void start_threading(int threads, int* temp_status);
void reqWork(int id, int reqCom);
void *threadloop( void *arg );
void input();
int changeStatus(int rdWr, int thrd);
char input_s_t(int s_t);