#include "head.h"

int execute_cd(char *command)
{
	char **array=strparse(command," ");
	int count=0;
	while(array[count++]);
	count--;
	if(count != 2 && count != 1)
	{
		fprintf(stderr,"%s\n","cd command");
		return -1;
	}
	if(count==1 || strcmp(array[1],"~")==0)
	{
		int check=chdir(getenv("PWD"));
		if(check<0)
			perror("Error");
	}
	else
	{
		int check=chdir(array[1]);
		if(check<0)
			perror("Error");
	}
	return 0;
}
