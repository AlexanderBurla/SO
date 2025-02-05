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
	memID = shmget(KEY_MEM, MEM_SIZE, IPC_EXCL | 0666);
	if(memID == -1)
	{
		printf("Eroare obtinere ID memorie partajata\n");
		return 0;
	}
	printf("ID -ul Memoriei partajate a fost obtinut cu succes\n");

	//atasare memorie partajata
	pMem = (char *)shmat(memID, 0, 0);
	if(pMem == (char *)-1)
	{
		printf("Eroare atasare memorie partajata\n");
		return 0;
	}
	printf("Memoria partajata a fost atasata cu succes\n");

	//citesc un sir de caractere din zona de mem partajata
	printf("Am citit din memoriea partajata: %s\n", pMem);

	//detasez memoria partajata
	rez = shmdt(pMem);
	if(rez == -1)
	{
		printf("Eroare detasare memorie partajata\n");
		return 0;
	}
	printf("Memoria partajata a fost detasata cu succes\n");


	return 0;
}
