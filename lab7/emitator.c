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
	printf( "Am intrat in emitator.\n" );
	creazaCoada();
	Mesaj msg;
	int nIdx=0;
	msg.nTip=0xFF;
	
	while(1)
	{
		sprintf( msg.achData, "Mesajul de maxima importantza %d ", nIdx );
		if( msgsnd( g_nIdCoada, &msg, sizeof( Mesaj ), 0 ) < 0 )
			perror( "Eroare la trimiterea mesajului: " );
		else
			printf( "Am trimis cu succes mesajul %d\n", nIdx );
			
		nIdx++;
		sleep( 1 );			
	}	
	return 0;
}
