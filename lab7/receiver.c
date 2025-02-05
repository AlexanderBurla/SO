#include "coada.h"
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>


int g_nIdCoada;

void creazaCoada() {
    if ((g_nIdCoada = msgget(KEY, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
    }
}

int main()
{
    creazaCoada();
    Mesaj msg;

    while (1)
    {
        if( msgrcv ( g_nIdCoada , &msg, sizeof(Mesaj), 0 , 0) <0 )
            perror("msgrcv");
        else
            printf("Mesaj primit: %s\n", msg.achData );

        if(strcmp(msg.achData, "STOP" ) == 0 )
            break;      

    }
    


    return 0;
}