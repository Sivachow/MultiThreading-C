#include"logging.h"

FILE *f;
void startLog(int argc, char * argv[]){
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
    fprintf(f, "%s", str);
    return;
}
