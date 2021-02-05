shell: \
			display.o \
			main.o \
			split_command.o \
			parse_string.o \
			pipe.o \
			execute.o \
			find_command.o \
			pwd_execute.o \
			cd_execute.o \
			pinfo_execute.o \
			env_execute.o 
	$(CC) -g -o shell $^


main.o: head.h main.c
	$(CC) -g -c main.c
		
display.o: head.h display.c
	$(CC) -g -c display.c


split_command.o: head.h split_command.c
	$(CC) -g -c split_command.c

parse_string.o: head.h parse_string.c
	$(CC) -g -c parse_string.c

pipe.o: head.h pipe.c
	$(CC) -g -c pipe.c

find_command.o: head.h find_command.c
	$(CC) -g -c find_command.c

execute.o: head.h execute.c
	$(CC) -g -c execute.c

cd_execute.o: head.h cd_execute.c
	$(CC) -g -c cd_execute.c

pwd_execute.o: head.h pwd_execute.c
	$(CC) -g -c pwd_execute.c

ls_execute.o: head.h ls_execute.c
	$(CC) -g -c ls_execute.c

pinfo_execute.o: head.h pinfo_execute.c
	$(CC) -g -c pinfo_execute.c

env_execute.o: head.h env_execute.c
	$(CC) -g -c env_execute.c

		
