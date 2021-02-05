#include "head.h"
void display()
{
	//getting username and host
	
		background_check();
		const char *user=getenv("USER");
		char host[256];
		int haha=gethostname(host,sizeof(host));;
		printf("%s@%s:",user,host);
		printf("%s\n",directory());
		current_foreground=-1;
		name_current_foreground=NULL;
		signal(SIGINT,Handler_CtrlC);
		signal(SIGTSTP,Handler_CtrlZ);
		char **command=take_input();

		for(int i=0;command[i]!=NULL;i++)
		{
			command[i]=split_command(command[i]);
			//printf("%s\n",command[i]);

			int k=execpipe(command[i]);
			//printf("Okay\n");

		}
}

int main(int n,char *input[])
{
	int f=1;
	while(f)
	{
		display();
	}
	return 0;
}
