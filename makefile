flags = -Wall -Werror -Wextra -g -c

ITree = Interprete/ITree/ITree
pruebaITree = Interprete/ITree/pruebaITree
pilaG = Interprete/ITree/Pila/pilaG
pruebaPila = Interprete/ITree/Pila/pruebaPila
cola = Interprete/ITree/Cola/cola
pruebaCola = Interprete/ITree/Cola/pruebaCola
intervalos = Interprete/ITree/Intervalos/intervalos
interpretar = Interprete/interpretar

## FOR WINDOWS ##
all: puntoO pruebas

interprete: puntoO
	gcc -o interprete.out $(pilaG).o $(cola).o $(ITree).o $(intervalos).o $(interpretar).o

puntoO: colas.o pilas.o intervalos.o ITrees.o interpretar.o

pruebas: pruebaCola pruebaPila pruebaITree

pruebaCola: $(pruebaCola).o $(cola).o
	gcc -o testCola.out $(pruebaCola).o $(cola).o

pruebaPila: $(pilaG).o $(pruebaPila).o
	gcc -o testPila.out $(pilaG).o $(pruebaPila).o

pruebaITree: $(pilaG).o $(cola).o $(ITree).o $(intervalos).o $(pruebaITree).o
	gcc -o testITree.out $(pilaG).o $(cola).o $(ITree).o $(intervalos).o $(pruebaITree).o

colas.o:
	$(MAKE) -C Interprete/ITree/Cola

pilas.o:
	$(MAKE) -C Interprete/ITree/Pila

intervalos.o:
	$(MAKE) -C Interprete/ITree/Intervalos

ITrees.o:
	$(MAKE) -C Interprete/ITree

interpretar.o:
	$(MAKE) -C Interprete

cleanWin:
	del /Q /F Interprete\*.o Interprete\ITree\Cola\*.o Interprete\ITree\Pila\*.o Interprete\ITree\Intervalos\*.o Interprete\ITree\*.o *.o *.exe *.out

cleanLin:
	rm -rf *.out *.o */*.o */*.out */*/*.o */*/*.out */*/*/*.o */*/*/*.out
