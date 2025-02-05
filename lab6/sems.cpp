/*
 ============================================================================
 Name        :
 Author      :
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>



//declaratii
union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */

           };



struct sembuf sem_look = {0, -1, 0};
struct sembuf sem_unlook = {0, 1, 0};
union semun semopt;


#define KEY_SEM 3456

#define KEY_MEM 2345
#define MEM_SIZE 32

int main(void)
{
	int memID, rez, semID;
	char * pMem;

	//creare zona de memrie partajata
	memID = shmget(KEY_MEM, MEM_SIZE, IPC_CREAT | 0666);
	if(memID == -1)
	{
		printf("Eroare creare memorie partajata\n");
		return 0;
	}
	printf("Memoria partajata a fost creata cu succes\n");

	//creez un semafor binar
	semID = semget(KEY_SEM, 1, IPC_CREAT | 0666);

	if(semID == -1)
	{
		printf("Eroare creare set semafoare\n");
		return 0;
	}
	printf("Setul de semafoare a fost creat cu succes\n");

	//setez valoarea 1
	semopt.val = 1;
	if(semctl(semID, 0, SETVAL, semopt) == -1)
		printf("Eroare setare valoare semafor");



	//atajare memorie partajata
	pMem = (char *)shmat(memID, 0, 0);
	if(pMem == (char *)-1)
	{
		printf("Eroare atasare memorie partajata\n");
		return 0;
	}
	printf("Memoria partajata a fost atasata cu succes\n");


	printf("Obtinere semafor (blocare resursa)...\n");
	//blochez resursa
	if(semop(semID, &sem_look, 1) == -1)
	{
		printf("Eroare semop look \n");
	}
	printf("Semafor obtinut (resursa blocata)...\n");

	//scriu un sir de caractere in zona de mem partajata
	memcpy(pMem, "test", sizeof("test"));

	//astept un enter de la tastatura si tin resursa blocata
	getchar();

	printf("Eliberare semafor (deblocare resursa)...\n");
	//deblochez resursa
	if(semop(semID, &sem_unlook, 1) == -1)
	{
		printf("Eroare semop unlook \n");
	}


	//detasez memoria partajata
	rez = shmdt(pMem);
	if(rez == -1)
	{
		printf("Eroare detajare memorie partajata\n");
		return 0;
	}
	printf("Memoria partajata a fost detasata cu succes\n");

	rez = shmctl(memID, 0, NULL);
	if(rez == -1)
	{
		printf("Eroare stergere memorie partajata\n");
		return 0;
	}
	printf("Memoria partajata a fost stearsa cu succes\n");


	return 0;
}
