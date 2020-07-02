flags = -Wall -Werror -Wextra -g -c

ITree = Interprete/ITree/ITree
pila = Interprete/ITree/Pila/pila
cola = Interprete/ITree/Cola/cola
intervalos = Interprete/ITree/Intervalos/intervalos
interpretar = Interprete/interpretar
interprete = Interprete/interprete


interprete: puntoO
	gcc -o interprete.out $(pila).o $(cola).o $(ITree).o $(intervalos).o $(interprete).o $(interpretar).o

puntoO: colas.o pilas.o intervalos.o ITrees.o interprete.o

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
	rm -rf *.out *.o */*.o */*/*.o */*/*/*.o
