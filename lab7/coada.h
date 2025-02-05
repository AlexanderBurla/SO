#ifndef _COADA_H_
#define _COADA_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>

#define KEY 1982

typedef struct
{
	int nTip;
	char achData[1024];
}Mesaj;


#endif
