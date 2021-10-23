#include"logging.h"
#include<stdlib.h>
#include<stdio.h>
#include"prodcon.h"
#include"trans_sleep.h"

int main(int argc, char *argv[]){
    FILE *f = startLog(argc, argv);
    input(f);
    return 0;
}
void input(FILE * f){
    char str;
    while(str != EOF){
        str = getchar();
        fprintf(f, "%c", str);
    }
}
