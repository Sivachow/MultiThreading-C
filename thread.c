#include"thread.h"

sem_t SwapLock;
sem_t SwapLockStatus;
int threads;
int sleep_ = 0;
int *status;
int *summary;
int endThreads;
clock_t start, end, sync_end;
double cpu_time_used, cpu_time_used_sync;

void start_threading(int temp, int *temp_status, int *temp_summ){
    threads = temp;
    endThreads = 0;
    status = temp_status;
    summary = temp_summ;
    for(int i = 0; i < threads; i++){
        status[i] = 0;
        summary[i] = 0;
    }
    pthread_t trd_id[threads];
    if( sem_init( &SwapLock, 0, 1 ) ) {
                perror( "Sempahore init" );
                exit( -1 );
    }
    if( sem_init( &SwapLockStatus, 0, 1 ) ) {
                perror( "Sempahore init" );
                exit( -1 );
    }
    start = clock();
    for(int i = 0; i < threads; i++){
        if( pthread_create( &trd_id[i], NULL, threadloop,(void *)i) ) {
            perror( "Thread create\n" );
            return;
        }
    }
    input();
    
    while(1){
        int temp = checkStatus();
        if(temp){
            break;
        }
    }
    logSummary();
}

int checkStatus(){
    for(int i = 0; i < threads; i++){
        if(status[i] != 0)
            return 0;
    }
    return 1;
}
void input(){
    char str;
    str = getchar();
    while(1){
        if(str == 'T'){
            str = input_s_t(1);
            continue;
        }

        if(str == 'S'){
            str = input_s_t(0);
            continue;
        }

        if(str == '\n'){
            str = getchar();
        }
        if(str == EOF){
            endThreads = 1;
            break;
        }
    }
}

char input_s_t(int s_t){
    char n[5];
    char buffer[100];
    n[0] = getchar();
    for(int i = 1; i <= 3; i++){
        n[i] = getchar();
        if(n[i] == '\n' || n[i] == EOF){
            n[4] = n[i];
            n[i] = '\0';
            break;
        }
    }

    if(s_t == 1){
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        sprintf(buffer, "\t%.3f ID= %-2d Q= %-3d Work\t\t\t// Parent receives work with n=%s\n",cpu_time_used,0, changeStatus(-2, 0) + 1,n);
        logstr(buffer);
        int rec = -1;
        while(rec == -1){
            rec = changeStatus(0,atoi(n));
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        int temp =  changeStatus(-2, 0);
        if(temp == 0)
            temp++;
        sprintf(buffer, "\t%.3f ID= %-2d Q= %-3d Receive\t\t %s\t// Thread %d takes workk, n=%s\n",cpu_time_used, rec+1 ,temp -1, n, rec + 1, n);
        logstr(buffer);

    }
    else{
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        sprintf(buffer, "\t%.3f ID= %-2d\t\tSleep\t\t %s\t// Parent Sleeps for %s\n",cpu_time_used, 0, n, n);
        //sprintf(buffer, "// Parent Sleeps for %s\n",n);
        logstr(buffer);
        sleep_++;
        Sleep(atoi(n));
    }
    return n[4];
}

void *threadloop( void *arg ) {
    reqWork( (int)arg + 1, 0);
    while(1){
        if(endThreads == 1){
            if(status[(int)arg] == 0)
                changeStatus(-1, (int)arg);
        }
        if(status[(int)arg] != 0){     
            Trans(status[(int)arg]);
            reqWork((int)arg + 1, 1);
            changeStatus(1, (int)arg);
        }
    }
    return 0;
}

void reqWork(int id, int reqCom){
    //0 to req work; 1 to complete work
    sem_wait( &SwapLock );
    char buffer[100];
    if(reqCom == 0){
        sync_end = clock();
        cpu_time_used_sync = ((double) (sync_end - start)) / CLOCKS_PER_SEC;
        sprintf(buffer, "\t%.3f ID= %-2d\t\tAsk\t\t\t\t// Work requested from thread %d\n",cpu_time_used_sync, id, id);
        logstr(buffer);
        sem_post( &SwapLock );
    }
    else{
        sync_end = clock();
        cpu_time_used_sync = ((double) (sync_end - start)) / CLOCKS_PER_SEC;
        sprintf(buffer, "\t%.3f ID= %-2d\t\tComplete\t %d\t//Thread %d completes task, n=%d\n",cpu_time_used_sync, id, status[id-1], id, status[id-1]);
        summary[id-1] = summary[id-1] + 1;
        logstr(buffer);
        sem_post( &SwapLock );
        reqWork(id,0);
    }
}

int changeStatus(int rdWr, int thrd){
    sem_wait( &SwapLockStatus );;
    if(rdWr == 0) 
    {
        for(int i = 0; i < threads; i++){
            if(status[i] == 0){
                status[i] = thrd;
                sem_post( &SwapLockStatus );
                return i; 
            }
        }
        sem_post( &SwapLockStatus );
        return -1;
    }
    if(rdWr == 1){ 
        status[thrd] = 0;
        sem_post( &SwapLockStatus );
        return 1;
    }
    if(rdWr == -1 && status[thrd] == 0){
        sem_post( &SwapLockStatus );
        pthread_exit(0);
        return -1;
    }
    if(rdWr == -2){
        int temp = -1;
        for(int j = 0; j < threads; j++){
            if(status[j] != 0)
                temp++;
        }
        if(temp == -1)
            temp++;
        sem_post( &SwapLockStatus );
        return temp;
    }
}

void logSummary(){
    char buffer[100];
    int temp = 0;
    for(int i = 0; i < threads; i++){
        temp += summary[i];
    }
    sprintf(buffer, "\nSummary:\n\tWork\t\t%3d\n\tAsk\t\t\t%3d\n\tReceive\t\t%3d\n\tComplete\t%3d\n\tSleep\t\t%3d\n", temp, temp + threads, temp, temp, sleep_);
    logstr(buffer);
    for(int i = 0; i < threads; i++){
        sprintf(buffer, "\tThread\t%3d\t%3d\n",i+1, summary[i]);
        logstr(buffer);
    }
    sprintf(buffer, "Transactions per second: \t\t\t%.2f", temp/cpu_time_used_sync);
    logstr(buffer);
}
