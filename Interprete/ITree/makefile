flags = -Wall -Werror -Wextra -g -c

ITree = ITree
pruebaITree = pruebaITree
cola = Cola/cola
intervalos = Intervalos/intervalos
pila = Pila/pilaG

all: ITree.o pruebaITree.o

ITree.o: $(ITree).c $(ITree).h $(pila).h $(intervalos).h $(cola).h
	gcc $(flags) $(ITree).c

pruebaITree.o: $(pruebaITree).c
	gcc $(flags) $(pruebaITree).c
