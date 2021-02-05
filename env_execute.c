#include "head.h"
void setenv_execute(char **array,int count)
{
	if(count==1)
	{
		fprintf(stderr,"Need more arguements");
	}
	else if(count>3)
	{
		fprintf(stderr,"more arguements");
	}
	else if(count==2)
	{
		if(setenv(array[1],"",1)!=0)
		{
			fprintf(stderr,"Error in creating");
		}
	}
	else if(count==3)
	{
		if(setenv(array[1],array[2],1)!=0)
		{
			fprintf(stderr,"Error in creating");
		}
	}
	return;
}
void unsetenv_execute(char **array,int count)
{
	if(count==0)
	{
		fprintf(stderr,"Very few arguements");
		return;
	}
	else if(count>2)
	{
		fprintf(stderr,"More than required arguements");
		return;
	}
	else if(count==2)
	{
		if(unsetenv(array[1])!=0)
		{
			fprintf(stderr,"Error in implementing");
		}
		return;
	}
	return;
}
