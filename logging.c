#include"logging.h"

FILE *f;
sem_t LogLock;

void startLog(int argc, char * argv[]){

    if( sem_init( &LogLock, 0, 1 ) ) {
                perror( "Sempahore init" );
                exit( -1 );
    }

    char fileName[100] = "prodcon.";
    if(argc == 3){
        strcat(fileName, argv[2]);
        strcat(fileName, ".log");
    }
    else
        strcat(fileName, "log");
    f = fopen(fileName, "a+");
}

void logstr(char *str){
    sem_wait(&LogLock);
    fprintf(f, "%s", str);
    sem_post(&LogLock);
    return;
}
