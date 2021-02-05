#include "head.h"

//Here, am first removing all trailing spaces and tab spaces , then adding the given array without trailing spaces to another array
char *split_command(char *input)
{
	int total=strlen(input);
	int count_sep=0;
	int i=0;
	while(i<total)
	{
		if(!(input[i]==' ') && !(input[i]=='\t'))
		{
			break;
		}
	}
	count_sep=count_sep+i;
	i=0;
	while(i<=(total-count_sep))
	{
		input[i]=input[i+count_sep];
		i++;
	}
	//remove length of trailing spaces
	total=total-count_sep;
	int count=0;
	//copy into another array
	char *dup_array=strdup(input);
	int new_index=0;
	for(int j=0;j<=total;j++)
	{
		if(input[j]==' ' || input[j]=='\t')
		{
			count++;
		}
		else
		{
			if(count>0)
			{
				count=0;
				dup_array[new_index++]=' ';
			}
			dup_array[new_index++]=input[j];
		}
	}
	return dup_array;
}





