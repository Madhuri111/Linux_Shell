#include "head.h"


char **take_input()
{
	
		char random[1024];
		char *buffer=random;
		size_t random_size=1024;
		int characters=getline(&buffer,&random_size,stdin);
		char *store=strdup(random);
		char *separator=";\n";
		int start=0;
		char **array=malloc(50*sizeof(char *));
		array[start++]=strtok(store,separator);
		while(array[start-1]!=NULL)
		{
			array[start++]=strtok(NULL,separator);
		}
		array[start++]=NULL;
		return array;
		//return tokanize(buffer);
}
char *directory()
{
	//char uni_path[1005];
	char *current_path = getenv("PWD");
	char *uni_path = (char *)malloc(1000);
	getcwd(uni_path,1000);
	int h=strlen(uni_path);
	int p=strlen(current_path);
	int flag=0,i;
	if(h==p)
		return "~";
	else if(h>=p)
	{
		char *temp = (char *)malloc(sizeof(uni_path)+1);
		temp[0]='~';
		for(i=p;i<=h;i++)
			temp[i-p+1]=uni_path[i];
		//uni_path[0]='~';

		return temp;
	}
	return uni_path;
}
