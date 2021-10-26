#include"prodcon.h"

int main(int argc, char *argv[]){
    startLog(argc, argv);
    int status[atoi(argv[1])];
    start_threading(atoi(argv[1]), status);

    //Making Threads
    return 0;
}

