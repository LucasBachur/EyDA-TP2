flags = -Wall -Werror -Wextra -g -c -Os

ITree = ITree/ITree
pruebaITree = ITree/pruebaITree
pilaG = ITree/Pila/pilaG
pruebaPila = ITree/Pila/pruebaPila
cola = ITree/Cola/cola
pruebaCola = ITree/Cola/pruebaCola
intervalos = ITree/Intervalos/intervalos
pruebaIntervalo = ITree/Intervalos/pruebaIntervalo

pruebas: pruebaCola pruebaPila pruebaITree pruebaIntervalo

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


pruebaITree: $(pilaG).o $(cola).o $(ITree).o $(intervalos).o $(pruebaITree).o
	gcc -o testITree.out $(ITree).o $(pruebaITree).o $(pilaG).o $(cola).o $(intervalos).o

itree.o: $(pilaG).h $(cola).h $(intervalos).h $(ITree).h $(ITree).c
	gcc $(flags) $(ITree).c

pruebaITree.o: $(pruebaITree).c
	gcc $(flags) $(pruebaITree).c


pruebaIntervalo: $(pruebaIntervalo).o $(intervalos).o
	gcc -o testIntervalo.out $(intervalos).o $(pruebaIntervalo).o

intervalos.o: $(intervalos).c $(intervalos).h
	gcc $(flags) $(intervalos).c

pruebaIntervalo.o: $(pruebaIntervalo).c
	gcc $(flags) $(pruebaIntervalo).c



cleanLin:
	rm -rf *.out *.o */*.o */*/*.o

cleanWin:
	del /Q /F ITree\Cola\*.o ITree\Pila\*.o ITree\Intervalos\*.o ITree\*.o *.o *.exe
