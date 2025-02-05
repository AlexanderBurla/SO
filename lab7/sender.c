#include "coada.h"
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

int g_nIdCoada;

void creazaCoada()
{
    if( ( g_nIdCoada = msgget( KEY , IPC_CREAT | 0666)) <0 )
            perror("msgget");
}

int main()
{
    creazaCoada();
    Mesaj msg;

    while (1)
    {
        printf("Introdu codul mesajului: ");
        scanf("%d", &msg.nTip);
        printf("Introdu textul mesajului: ");
        scanf("%s", msg.achData);

        if( msgsnd (g_nIdCoada , &msg , sizeof (Mesaj), 0 ) <0 )
            perror("msgsnd");
        else
            printf("Mesaj trimis: %s\n", msg.achData);

        if(strcmp (msg.achData , "STOP") ==0 )
            break;

    }
    
    return 0;
}

