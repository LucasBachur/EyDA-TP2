flags = -Wall -Werror -Wextra -g -c

all: interprete.o interpretar.o

interpretar.o: interpretar.c
	gcc $(flags) interpretar.c

interprete.o: interprete.c interprete.h
	gcc $(flags) interprete.c
