#include"thread.h"

sem_t SwapLock;
sem_t SwapLockStatus;
int threads;
int *status;
int endThreads;

void start_threading(int temp, int *temp_status){
    threads = temp;
    endThreads = 0;
    status = temp_status;
    for(int i = 0; i < threads; i++){
        status[i] = 0;
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
    char buffer[50];
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
        sprintf(buffer, "// Parent receives work with n=%s\n",n);
        logstr(buffer);
        int rec = -1;
        while(rec == -1){
            rec = changeStatus(0,atoi(n));
        }
        sprintf(buffer, "// Thread %d takes workk, n=%s\n",rec + 1, n);
        
        logstr(buffer);

    }
    else{
        sprintf(buffer, "// Parent Sleeps for %s\n",n);
        logstr(buffer);
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
            printf("%d Work started\n", (int)arg + 1);    
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
    char buffer[50];
    if(reqCom == 0){
        sprintf(buffer, "// Work requested from thread %d\n",id);
        printf("%d Thread req\n", id);
        logstr(buffer);
        sem_post( &SwapLock );
    }
    else{
        sprintf(buffer, "//Thread %d completes task, n=%d\n",id, status[id-1]);
        printf("%d Thread completed\n", id);
        logstr(buffer);
        sem_post( &SwapLock );
    }
}

int changeStatus(int rdWr, int thrd){
    sem_wait( &SwapLockStatus );
    if(rdWr == 0) 
    {
        for(int i = 0; i < threads; i++){
            if(status[i] == 0){
                status[i] = thrd;
                printf("%d Thread Worksss %d\n", i+1, status[i]);
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
}
