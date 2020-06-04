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
pruebas: pruebaCola pruebaPila pruebaITree intervalos.o interpretar

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


pruebaITree: pilaG.o cola.o ITree.o intervalos.o pruebaITree.o
	gcc -o testITree.out pilaG.o cola.o ITree.o intervalos.o pruebaITree.o

ITree.o: $(pilaG).h $(cola).h $(intervalos).h $(ITree).h $(ITree).c
	gcc $(flags) $(ITree).c

pruebaITree.o: $(pruebaITree).c
	gcc $(flags) $(pruebaITree).c


intervalos.o: $(intervalos).c $(intervalos).h
	gcc $(flags) $(intervalos).c

interpretar: interpretar.o pilaG.o cola.o ITree.o intervalos.o
	gcc -o testInterpretar.out interpretar.o pilaG.o cola.o ITree.o intervalos.o

interpretar.o: $(interpretar).c
	gcc $(flags) $(interpretar).c

cleanWin:
	del /Q /F ITree\Cola\*.o ITree\Pila\*.o ITree\Intervalos\*.o ITree\*.o *.o *.exe *.out

cleanLin:
	rm -rf *.out *.o */*.o */*/*.o
