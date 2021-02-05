#include "head.h"

int execute_pwd()
{
	char path[1005];
	getcwd(path,1004);
	printf("%s \n",path);
	return 0;
}
