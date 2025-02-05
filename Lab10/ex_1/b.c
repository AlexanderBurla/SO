#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //de aici provin declaratiile functiilor de lucru cu fire de executie

void *functieC(void *ptr);

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int  counter = 0;// este contorul global, accesibil tuturor firelor

int main()
{
   int rc1, rc2;
   pthread_t fir1, fir2;

   /* Creaza fire independente ce vor executa functia functieC */

   if( (rc1=pthread_create( &fir1, NULL, &functieC, NULL)) )
   {
      perror( "pthread_create fir1 " );
   }

   if( (rc2=pthread_create( &fir2, NULL, &functieC, NULL)) )
   {
      perror( "pthread_create fir2 " );
   }
     	/* 
     	In main se asteapta pana cand firele isi termina executia. 
        Daca nu asteptam, exista riscul ca sa se paraseasca tot programul 
	din cauza unui apel exit dintr-un fir. 
	*/

   pthread_join( fir1, NULL);
   pthread_join( fir2, NULL); 

   exit(0);
}

// Este functia al carei cod se executa in mod multi-fir
void *functieC(void *ptr)
{
   pthread_mutex_lock( &mutex1 ); //Operatia P
   counter++; //cand ajung aici, firul curent e singurul ce are acces asupra resursei, deci se pot efectua prelucrari
   printf("Valoare contor: %d\n",counter);
   pthread_mutex_unlock( &mutex1 );// Operatia V
}
