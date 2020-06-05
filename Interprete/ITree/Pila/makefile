flags = -Wall -Werror -Wextra -g -c

pila = pilaG
pruebaPila = pruebaPila

all: pilaG.o pruebaPila.o

pilaG.o: $(pila).h $(pila).c
	gcc $(flags) $(pila).c

pruebaPila.o: $(pruebaPila).c
	gcc $(flags) $(pruebaPila).c
