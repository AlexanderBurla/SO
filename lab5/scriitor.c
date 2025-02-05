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

#define KEY_MEM 2345
#define MEM_SIZE 32

int main(void)
{
	int memID, rez;
	char * pMem;

	//creare zona de memrie partajata
	memID = shmget(KEY_MEM, MEM_SIZE, IPC_CREAT | 0666);
	if(memID == -1)
	{
		printf("Eroare creare memorie partajata\n");
		return 0;
	}
	printf("Memoria partajata a fost creata cu succes\n");

	//atajare memorie partajata
	pMem = (char *)shmat(memID, 0, 0);
	if(pMem == (char *)-1)
	{
		printf("Eroare atasare memorie partajata\n");
		return 0;
	}
	printf("Memoria partajata a fost atasata cu succes\n");

	printf("astept un enter de la tastatura\n");

	//scriu un sir de caractere in zona de mem partajata
	memcpy(pMem, "test", sizeof("test"));


	getchar();

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
