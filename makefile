flags = -Wall -Werror -Wextra -g -c

ITree = ITree/ITree
pruebaITree = ITree/pruebaITree
pilaG = ITree/Pila/pilaG
pruebaPila = ITree/Pila/pruebaPila
cola = ITree/Cola/cola
pruebaCola = ITree/Cola/pruebaCola

pruebas: pruebaCola pruebaPila pruebaITree

pruebaCola: $(pruebaCola).o $(cola).o
	gcc -o testCola.out $(pruebaCola).o $(cola).o

cola.o: $(cola).c $(cola).h
	gcc $(flags) $(cola).c

pruebaCola.o: $(pruebaCola).c
	gcc $(flags) $(pruebaCola).c


pruebaPila: $(pilaG).o $(pruebaPila).o
	gcc -o testPila.out $(pilaG).o $(pruebaPila).o

pilaG.o: $(pilaG).c $(pilaG).h
	gcc $(flags) $(pilaG).c

pruebaPila.o: $(pruebaPila).c
	gcc $(flags) $(pruebaPila).c


pruebaITree: $(pilaG).o $(cola).o $(ITree).o $(pruebaITree).o
	gcc -o testITree.out $(ITree).o $(pruebaITree).o $(pilaG).o $(cola).o

avltree.o: $(pilaG).h $(cola).h $(ITree).c $(ITree).h
	gcc $(flags) $(ITree).c

pruebaITree.o: $(pruebaITree).c
	gcc $(flags) $(pruebaITree).c


cleanLin:
	rm -rf *.out *.o */*.o */*/*.o

cleanWin:
	del /Q /F ITree\Cola\*.o ITree\Pila\*.o ITree\*.o
