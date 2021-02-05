CC=gcc

main:
	${CC} -c display.c main.c split_command.c parse_string.c pipe.c execute.c find_command.c pwd_execute.c cd_execute.c ls_execute.c pinfo_execute.c env_execute.c
	$(CC) display.o main.o split_command.o parse_string.o pipe.o execute.o find_command.o pwd_execute.o cd_execute.o ls_execute.o pinfo_execute.o env_execute.o -o Madhuri
Madhuri:
	${CC} -c display.c main.c split_command.c parse_string.c pipe.c execute.c find_command.c pwd_execute.c cd_execute.c ls_execute.c pinfo_execute.c env_execute.c
	$(CC) display.o main.o split_command.o parse_string.o pipe.o execute.o find_command.o pwd_execute.o cd_execute.o ls_execute.o pinfo_execute.o env_execute.o -o Madhuri
