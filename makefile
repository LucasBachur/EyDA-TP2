flags = -Wall -Werror -Wextra -g -c

ITree = Interprete/ITree/ITree
pruebaITree = Interprete/ITree/pruebaITree
pila = Interprete/ITree/Pila/pila
pruebaPila = Interprete/ITree/Pila/pruebaPila
cola = Interprete/ITree/Cola/cola
pruebaCola = Interprete/ITree/Cola/pruebaCola
intervalos = Interprete/ITree/Intervalos/intervalos
interpretar = Interprete/interpretar
interprete = Interprete/interprete



interprete: puntoO
	gcc -o interprete.out $(pila).o $(cola).o $(ITree).o $(intervalos).o $(interprete).o $(interpretar).o

all: interprete pruebas

puntoO: colas.o pilas.o intervalos.o ITrees.o interprete.o

pruebas: pruebaCola pruebaPila pruebaITree

pruebaCola: $(pruebaCola).o $(cola).o
	gcc -o testCola.out $(pruebaCola).o $(cola).o

pruebaPila: $(pila).o $(pruebaPila).o
	gcc -o testPila.out $(pila).o $(pruebaPila).o

pruebaITree: $(pila).o $(cola).o $(ITree).o $(intervalos).o $(pruebaITree).o
	gcc -o testITree.out $(pila).o $(cola).o $(ITree).o $(intervalos).o $(pruebaITree).o

colas.o:
	$(MAKE) -C Interprete/ITree/Cola

pilas.o:
	$(MAKE) -C Interprete/ITree/Pila

intervalos.o:
	$(MAKE) -C Interprete/ITree/Intervalos

ITrees.o:
	$(MAKE) -C Interprete/ITree

interprete.o:
	$(MAKE) -C Interprete

cleanWin:
	del /Q /F Interprete\*.o Interprete\ITree\Cola\*.o Interprete\ITree\Pila\*.o Interprete\ITree\Intervalos\*.o Interprete\ITree\*.o *.o *.exe *.out

cleanLin:
	rm -rf *.out *.o */*.o */*.out */*/*.o */*/*.out */*/*/*.o */*/*/*.out
