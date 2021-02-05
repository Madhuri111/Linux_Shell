#include "head.h"

const char *LIST[]={
		"pwd","cd","ls","pinfo","echo","setenv","unsetenv","jobs","kjob","fg","bg","overkill","quit",""};
int find_here(char *command)
{

	int len=strlen(command);
	int i=0;
	while(i<len)
	{

		if(command[i]==' ')
			break;
		i++;
	}
	int count=i;
	char *comman=(char *)malloc(sizeof(char)*count+2);

	int k;
	for(k=0;k<count;k++)
		comman[k]=command[k];
	comman[k]='\0';

	for(int j=0;j<13;j++)
	{
		if(strcmp(comman,LIST[j])==0)
		{

			return j;
		}
	}
	return -1;
}
