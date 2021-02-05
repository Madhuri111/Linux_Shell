#include "head.h"


int pinf(int pid)
{
        char *filePath = (char *)malloc(1024);
        char str_pid[10] = {"self"};
        if(pid>0)
                sprintf(str_pid,"%d",pid);
    strcpy(filePath,"/proc/");
        strcat(filePath,str_pid); 
        char *fileExePath = (char *)malloc(1024);
        strcpy(fileExePath,filePath);
    strcat(filePath,"/stat");
    strcat(fileExePath,"/exe");
        FILE* fin = fopen(filePath,"r");
        if(!fin) {perror(""); return -1;}
        char fileComm[128];
        int filePid;
        char fileState;
        fscanf(fin,"%d %s %c",&filePid,fileComm,&fileState);
        fclose(fin);
        strcat(filePath,"m");
        FILE *finMem = fopen(filePath,"r");
        if(!finMem) {perror(""); return -1;}
        long unsigned int vmsize;
        fscanf(finMem,"%lu",&vmsize);
        printf("pid -- %d\n",filePid);
        printf("Process Status -- %c memory \n",fileState);
        printf("- %lu {Virtual memory}\n",vmsize);

        //Path of executable
        char exePath[1024];
        int check = readlink(fileExePath,exePath,1024);
        if(check<0) {perror(""); return -1;}
        exePath[check]='\0';
        printf("- Executable Path -- %s\n",exePath);
        fclose(finMem);
        free(filePath);
        return 0;
}




int pinfo_execute(char **array,int count)
{
	if(count==1)
	{
		return pinf(0);
	}
	else
	{
		int i=1;
		while(i<count)
		{
			pinf(atoi(array[i]));
			i++;
		}
	}
	return 0;
}
