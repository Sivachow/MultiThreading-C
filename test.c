#include <pthread.h>
#include<stdlib.h>
#include<stdio.h>
void *threadloop( void *arg ) {
	int i;

	printf( "Start thread\n" );
	printf( "End thread\n" );
	return( 0 );
}

int main(){
    pthread_t id;
    printf("HI\n");
    if( pthread_create( &id, NULL, threadloop, (void *)NULL ) ) {
			perror( "Thread create" );
			return( -1 );
	}
    printf("HIIII %lu\n", id);
    return 0;
}