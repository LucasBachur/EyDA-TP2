flags = -Wall -Werror -Wextra -g

ITree = ITree/ITree
pruebaITree = ITree/pruebaAVL
pilaG = ITree/Pila/pilaG
pruebaPila = ITree/Pila/pruebaPila
cola = ITree/Cola/cola
pruebaCola = ITree/Cola/pruebaCola

pruebas: pruebaCola pruebaPila pruebaAVL

pruebaCola: $(pruebaCola).o $(cola).o
	gcc -o testCola.out $(pruebaCola).o $(cola).o

cola.o: $(cola).c $(cola).h
	gcc $(flags) -c $(cola).c

pruebaCola.o: $(pruebaCola).c
	gcc $(flags) -c $(pruebaCola).c


pruebaPila: $(pilaG).o $(pruebaPila).o
	gcc -o testPila.out $(pilaG).o $(pruebaPila).o

pilaG.o: $(pilaG).c $(pilaG).h
	gcc $(flags) -c $(pilaG).c

pruebaPila.o: $(pruebaPila).c
	gcc $(flags) -c $(pruebaPila).c


pruebaAVL: $(pilaG).o $(cola).o $(ITree).o $(pruebaITree).o
	gcc -o testAVL.out $(ITree).o $(pruebaITree).o $(pilaG).o $(cola).o

avltree.o: $(pilaG).h $(cola).h $(ITree).c $(ITree).h
	gcc $(flags) -c $(ITree).c

pruebaITree.o: $(pruebaITree).c
	gcc $(flags) -c $(pruebaITree).c


cleanLin:
	rm -rf *.out *.o */*.o */*/*.o

cleanWin:
	del /Q /F ITree\Cola\*.o ITree\Pila\*.o ITree\*.o
