#include "coada.h"
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

int g_nIdCoada;

void creazaCoada( void )
{
	printf( "\nCreare coada de mesaje...\n" );
	if( g_nIdCoada = msgget( KEY, IPC_CREAT | 0666 ) < 0 )
		perror( "msgget: " );
	else
		printf( "Coada a fost creata.\n\n" );
}

int main()
{
	printf( "Am intrat in receptor.\n" );
	creazaCoada();
	Mesaj msg;	
	char buf[ sizeof(Mesaj) ];
	
	while(1)
	{
		if( msgrcv( g_nIdCoada, &msg, sizeof( Mesaj ), 0, 0 ) < 0 )
			perror( "Eroare la receptionarea mesajului: " );
		else
			printf( "Am primit mesajul cu textul: \"%s\"\n", msg.achData );	
	}
	
	return 0;
}
