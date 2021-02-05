#include "head.h"

char ** strparse(char *command,char *sep)
{
	char *str = strdup(command);
	char **pipelets = (char**)malloc(64 * sizeof(char *));
//	char *sep = "|";
	int count = 0;
	pipelets[count++] = strtok(str,sep);
	while(pipelets[count-1])
		pipelets[count++] = strtok(NULL,sep);
	pipelets[count++] = NULL;
	return pipelets;
}

