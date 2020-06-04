flags = -Wall -Werror -Wextra -g -c

ITree = ITree/ITree
pruebaITree = ITree/pruebaITree
pilaG = ITree/Pila/pilaG
pruebaPila = ITree/Pila/pruebaPila
cola = ITree/Cola/cola
pruebaCola = ITree/Cola/pruebaCola
intervalos = ITree/Intervalos/intervalos

pruebas: pruebaCola pruebaPila pruebaITree intervalos.o

pruebaCola: pruebaCola.o cola.o
	gcc -o testCola.out pruebaCola.o cola.o

cola.o: $(cola).c $(cola).h
	gcc $(flags) $(cola).c

pruebaCola.o: $(pruebaCola).c
	gcc $(flags) $(pruebaCola).c


pruebaPila: pilaG.o pruebaPila.o
	gcc -o testPila.out pilaG.o pruebaPila.o

pilaG.o: $(pilaG).c $(pilaG).h
	gcc $(flags) $(pilaG).c

pruebaPila.o: $(pruebaPila).c
	gcc $(flags) $(pruebaPila).c


pruebaITree: pilaG.o cola.o itree.o intervalos.o pruebaITree.o
	gcc -o testITree.out pilaG.o cola.o ITree.o intervalos.o pruebaITree.o

itree.o: $(pilaG).h $(cola).h $(intervalos).h $(ITree).h $(ITree).c
	gcc $(flags) $(ITree).c

pruebaITree.o: $(pruebaITree).c
	gcc $(flags) $(pruebaITree).c


intervalos.o: $(intervalos).c $(intervalos).h
	gcc $(flags) $(intervalos).c


cleanLin:
	rm -rf *.out *.o */*.o */*/*.o

cleanWin:
	del /Q /F ITree\Cola\*.o ITree\Pila\*.o ITree\Intervalos\*.o ITree\*.o *.o *.exe *.out
