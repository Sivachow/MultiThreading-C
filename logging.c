#include<stdio.h>
#include <stdlib.h>
#include<string.h>
FILE* startLog(int argc, char * argv[]){
    FILE* f;
    char fileName[100] = "prodcon.";
    if(argc == 3){
        strcat(fileName, argv[2]);
        strcat(fileName, ".log");
    }
    else
        strcat(fileName, "log");
    f = fopen(fileName, "a+");
    fprintf(f, "%d %s %s", argc, argv[0], argv[1]);
    return f;
    
}

void logchar(FILE* f, char str){
    fprintf(f, "%c", str);
    return;
}