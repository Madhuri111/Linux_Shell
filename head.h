#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<sys/utsname.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>


//universal variables
pid_t current_foreground;
char * name_current_foreground;

//display.c functions
char *directory();
char **take_input();

//split program

char *split_command(char *input);

//pipe program

int execpipe(char *command);

//find_command program
int find_here(char *command);
	
//execute_ls program
int execute(char *command);
int execute_jobs(char **array,int count);
int execute_k_jobs(char **array,int count);

//string parse program
char ** strparse(char *command,char *sep);
	
//ls_execute program
char * formatDate(char *str,time_t val);
int print_pk_ls_l(char *path,char *fileName);
int ls_execute(char *command);
int execute_fg(char **array,int count);
int execute_bg(char **array,int count);
void Handler_CtrlC(int signal);
void Handler_CtrlZ(int signal);
int background_check();



//execute function
int execute(char *command);

//pinfo_execuute,c
int pinfo_execute(char **array,int count);
int pinf(int pin_id);

//env_execute.c file
void setenv_execute(char **array,int count);
void unsetenv_execute(char **array,int count);




//cd_execute function
int execute_cd(char *command);

//pwd_execute function
int execute_pwd();

