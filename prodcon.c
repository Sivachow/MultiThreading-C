#include"prodcon.h"

int main(int argc, char *argv[]){
    startLog(argc, argv);
    int status[atoi(argv[1])];
    int summary[atoi(argv[1])];
    start_threading(atoi(argv[1]), status, summary);

    //Making Threads
    return 0;
}

