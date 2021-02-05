#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "head.h"
#include <string.h>

/*char ** strparse(char *command)
  {
  char *str = strdup(command);
  char **pipelets = (char**)malloc(64 * sizeof(char *));
  char *sep = "|";
  int count = 0;
  pipelets[count++] = strtok(str,sep);
  while(pipelets[count-1])
  pipelets[count++] = strtok(NULL,sep);
  pipelets[count++] = NULL;
  return pipelets;
  }*/

int execpipe(char* command)
{
	//checking pipes
	int n=strlen(command);
	int need=0,flag=0;
	for(int i=0;i<n;i++)
	{
		if(command[i]=='|')
		{
			flag=1;
			need=i;
			break;
		}
	}

	if(flag==0)
	{
		//no pipes

		return execute(command);
	}

					printf("Okay\n");

	char **pipe_cmds =malloc(64 * sizeof(char *));
	pipe_cmds=strparse(command,"|");
	int count=0;
	while(pipe_cmds[count++]);
	count--;

	for(int i=0;i<count;i++)
		pipe_cmds[i]=split_command(pipe_cmds[i]);

	int dup_stdin=dup(0);
	int dup_stdout=dup(1);
	int check=dup(0);
	int prev,nxt;
	int fildes[2];
	flag=0;
	int i;
	for(i=0;i<count;++i)
	{
		if(dup2(check,0)==-1)
		{
			perror("");
		}
		close(check);
		if(i==0)
		{
			flag=0;
		}
		if(i==count-1)
		{
			flag=1;
		}
		if (flag)
		{
			if((dup_stdout,1)==-1)
			{
				perror("");
			}
			close(dup_stdout);
		}
		else
		{
			pipe(fildes);
			check=fildes[0];
			if (dup2(fildes[1], 1) == -1)
			{
				perror("");
			}
			close(fildes[1]);
		}
		//executing pipe commands in list
		int check_pipe=execute(pipe_cmds[i]);
		if(check_pipe)
			break;
	}
	dup2(dup_stdin,0);
	close(dup_stdin);
	dup2(dup_stdout,1);
	close(dup_stdout);
	if(i!=count)
	{
		printf("Command not executed properly\n");
		return -1;	
	}
	return 0;
}


