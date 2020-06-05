flags = -Wall -Werror -Wextra -g -c

cola = cola
pruebaCola = pruebaCola


all: cola.o pruebaCola.o

cola.o: $(cola).c $(cola).h
	gcc $(flags) $(cola).c

pruebaCola.o: $(pruebaCola).c
	gcc $(flags) $(pruebaCola).c
