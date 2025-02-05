#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define nrLin   (5)
#define nrTr   (13)


//- un alt mod de initializare (static) pt un mutex:
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;
int poz[ nrTr ];
pthread_t tid[ nrTr ];

//-afisare trenuri care intra in gara
void afisare( void )
{
	int i;

	pthread_mutex_lock( &mutex );
	printf( "Trenuri care intra in gara: " );
	for( i = 0; i < nrTr; i++ )
		if( poz[ i ] == 1 )
			printf( " %d", i );
	printf( "\r\n" );
	pthread_mutex_unlock( &mutex );
}

//-rutina unui thread
void* trece( void* sind )
{
	int pauza, ind;

	ind = atoi( (char*)sind );
	sem_wait( &sem );
	poz[ ind ] = 1;
	afisare();
	pauza = 1 + (int)( 3.0 * rand() / (RAND_MAX+1.0) );
	sleep( pauza );
	poz[ ind ] = 2;
	sem_post( &sem );
	free( sind ); //-Eliberarea memoriei alocate in main !!
}

void main( int argc, char* argv[] )
{
	char* sind;
	int i;

	sem_init( &sem, 0, nrLin );
	for( i = 0; i < nrTr; i++ )
	{
		sind = (char*) malloc (5 * sizeof( char ) );
		sprintf( sind, "%d", i );
		pthread_create( &tid[i], NULL, trece, sind );
	}
	for( i = 0; i < nrTr; i++ )
		pthread_join( tid[ i ], NULL );
}
