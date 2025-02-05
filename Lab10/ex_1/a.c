#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //acest header contine declaratiile functiilor legate de fire de executie

void *afisare_mesaj( void *ptr );

int main()
{
     pthread_t fir1, fir2;
     char *mesaj1 = "Firul 1";
     char *mesaj2 = "Firul 2";
     int  iret1, iret2;

    /* Creaza cele doua fire de executie */

     iret1 = pthread_create( &fir1, NULL, afisare_mesaj, (void*) mesaj1);
     iret2 = pthread_create( &fir2, NULL, afisare_mesaj, (void*) mesaj2);

     	/* 
     	In main se asteapta pana cand firele isi termina executia. 
        Daca nu asteptam, exista riscul ca sa se paraseasca tot programul 
	din cauza unui apel exit dintr-un fir. 
	*/

     pthread_join( fir1, NULL);
     pthread_join( fir2, NULL); 

     printf("Firul 1 a intors: %d\n",iret1);
     printf("Firul 2 a intors: %d\n",iret2);
     exit(0);
}

void *afisare_mesaj( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
}
