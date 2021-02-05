#include "head.h"

typedef struct process
{
	pid_t id;
	char *name;
	int state;
}process;
process process_background[1024];
process gfproc;
process bgproc;
int number_process=0;

void Handler_CtrlZ(int signal)
{
	if(current_foreground==-1)
	{
		//if it remains same
		return;
	}
	kill(current_foreground,SIGTSTP);
	//copying background name to foreground
	strcpy(process_background[number_process].name,name_current_foreground);
	//changing background values
	process_background[number_process].id=current_foreground;
	process_background[number_process].state=0;
	number_process++;
//	printf("%d\n",number_process );
	printf("%s %d\n",name_current_foreground ,current_foreground);
	fflush(stdout);
}

void Handler_CtrlC(int signal)
{
	if(current_foreground==-1)
	{
		//if it remains same
		return;
	}

	kill(current_foreground,SIGINT);
	fflush(stdout);
}
int background_check()
{
	//this function is to write to console whenever our background gets finsihed successfully
	pid_t x_pid;
	int need;
	int i=0;
	while(i<number_process)
	{
		if(process_background[i].id!=0)
		{
			x_pid=waitpid(process_background[i].id,&need,WNOHANG);
			if(x_pid==process_background[i].id)
			{
				printf("Background process completed successfully %s with pid %d with status %d\n", process_background[i].name,x_pid,WIFEXITED(need));
				process_background[i].id=0; //because it is done
			}
		}
		i++;
	}
	return 0;
}

int execute_fg(char **array,int count)
{
	int pin_required=atoi(array[1]);
	int j=0,flag=0;
	if(count!=2)
	{
		fprintf(stderr,"%s\n","Invalid Arguements");
		return -1;
	}
	while(j<number_process)
	{
		if(process_background[j].id)
			flag++;
		if(flag==pin_required)
		{
			int status;
			pid_t num=waitpid(process_background[j].id,&status,WUNTRACED|WCONTINUED);
			int check=kill(process_background[j].id,SIGCONT);
			if(!check)
			{
				process_background[j].id=0;
			}
			return check;
		}
		j++;
	}
	if(j==number_process)
	{
		fprintf(stderr,"%s\n","Use valid process index");
		return -1;
	}
	return 0;
}
int execute_bg(char **array,int count)
{
	int pin_required=atoi(array[1]);
	int j=0,flag=0;
	if(count!=2)
	{
		fprintf(stderr,"%s\n","Invalid Arguements");
		return -1;
	}
	while(j<number_process)
	{
		if(process_background[j].id)
			flag++;
		if(flag==pin_required)
		{
			int status;
			//iNSTEADING OF MAKING IT WAIT , CONTINUE IT
			//waitpid(process_background[j].id,&status,WUNTRACED|WCONTINUED);
			int check=kill(process_background[j].id,SIGCONT);
			process_background[j].state=1;
			return check;
		}
		j++;
	}
	if(j==number_process)
	{
		fprintf(stderr,"%s\n","Use valid process index");
		return -1;
	}
	return 0;
}


int execute_jobs(char **array,int count)
{
	int flag=0;
	if(count!=1)
	{
		fprintf(stderr,"%s\n","Enter jobs");
		return -1;
	}
	int j=0;
				printf("%d\n", number_process);

	while(j<number_process)
	{
		if(process_background[j].id != 0)
		{
			flag++;
			if(process_background[j].state!=0)
			{
				printf("[ %d ] \t running  %s  [%d] \n",flag,process_background[j].name,process_background[j].id);
			}
			else
			{
				printf("[ %d ] \t stopped  %s  [%d] \n",flag,process_background[j].name,process_background[j].id);

			}
		}
		j++;
	}
	return 0;
}


int execute(char *command)
{
	int org_out=dup(1);
	int org_in=dup(0);
	

	char **array=strparse(command," ");
	int count=0;
	while(array[count++]);
	count--;
	int stt=count;
	//printf("count--%d\n",count );
	int i;

	//checking input redirection
	for(i=0;i<count;i++)
	{
		if(strcmp(array[i],"<")==0)
			break;
	}

	char *str_input;
	if(i==count)
		str_input=NULL;
	else
		str_input=array[i+1];
	if(str_input)
	{

		int fd;
		fd=open(str_input,O_RDONLY);
		if(fd==-1)
			perror("");
		close(0);
		if(dup2(fd,0)!=0)
			perror("");
		close(fd);
	}
	//checking output redirection
	for(i=0;i<count;i++)
	{
		if(strcmp(array[i],">")==0)
			break;
	}
	char *str_output;
	if(i==count)
		str_output=NULL;
	else
		str_output=array[i+1];
	if(str_output)
	{

		int fd;
		fd=open(str_output,O_WRONLY | O_CREAT | O_TRUNC,0644);
		if(fd==-1)
			perror("");
		close(1);
		if(dup2(fd,1)!=1)
			perror("");
		close(fd);
	}
	//checking append redirection
	for(i=0;i<count;i++)
	{
		if(strcmp(array[i],">>")==0)
			break;
	}
	char *str_append;
	if(i==count)
		str_append=NULL;
	else
		str_append=array[i+1];

	if(str_append)
	{

		int fd;
		fd=open(str_append,O_WRONLY | O_CREAT | O_APPEND,0644);
		if(fd==-1)
			perror("");
		close(1);
		if(dup2(fd,1)!=1)
			perror("");
		close(fd);
	}
	

	int number=find_here(command);

	int current=0;
	//printf("%d\n", number);
	//printf("Came\n");

	if(number==-1)
	{

		int check_background=0;
		//current=out_command(command);
		//if number is not there in list, then it might be a background process
		if(array[count-1]=="&")
		{
			check_background=1;
		}
		int stat=0;
		pid_t pid_check=fork();
		//error if <0 , created child process if =0 , returned to parent if positive
		if(pid_check<0) perror(" ");
		else if(pid_check==0)
		{
			//successfully created child process
			//replace & in background
			if(check_background==1)
			{
				array[count-1]=NULL;

			}
			//then this child process should call execvp
			int new=execvp(array[0],array);
			if(new<0)
			{
				perror(" ");
				exit(1);
			}
		}
		//if it is foreground process
		else if(!check_background)
		{
			//parent process
			current_foreground=pid_check;
			name_current_foreground=array[0];
			//if it is foreground process then you have to wait till it completes
			pid_t ppid;
			ppid=waitpid(pid_check,&stat,WUNTRACED);if(ppid<0) perror(" ");

		}
		//if not all above , then parent process for background process
		else
		{
			kill(pid_check,SIGCONT);
			process_background[number_process].name=array[0];
			process_background[number_process].state=1;
			process_background[number_process].id=pid_check;
			number_process++;
			printf("%s  [%d] \n",array[0],pid_check);
		}
		current=stat;
	}
	else if(number==0)
	{
			//pwd commmand
			current = execute_pwd();
			
	}
	else if(number==1)
	{
			//cd command
			current = execute_cd(command);
	}
	else if(number==2)
	{
			//ls command
			//current=ls_execute(command);
	}
	else if(number==3)
	{
			//pinfo command
			current=pinfo_execute(array,stt);
	}
	else if(number==4)
	{
			//echo command
			for(int i=1;i<stt;i++)
			{
				printf("%s ",array[i]);
			}
			printf("\n");
			return 0;
	}
	else if(number==5)
	{
			//setenv command
			setenv_execute(array,stt);
	}
	else if(number==6)
	{
			//unsetenv command
			unsetenv_execute(array,stt);
	}
	else if(number==7)
	{
			//jobs command
			current=execute_jobs(array,count);
	}
	else if(number==8)
	{
			//kjob command
			//current=execute_k_jobs(array,count);
	}
	else if(number==9)
	{
			//execute fg
			current=execute_fg(array,count);
	}
	else if(number==10)
	{
			//execute bg
			current=execute_bg(array,count);
	}
	else if(number==11)
	{
			//execute overkill
			for(int j=number_process-1;j>=0;j--)
			{
				kill(process_background[j].id,9);
			}
			current=1;
	}
	else if(number==12)
	{
		//execute quit
		exit(0);
	}

	dup2(org_out,1);
	dup2(org_in,0);
	close(org_out);
	close(org_in);
	background_check();
	return current;
}

