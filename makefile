flags = -Wall -Werror -Wextra -g

AVLTree = AVLTree/AVLtree
pruebaAVLTree = AVLTree/pruebaAVL
pilaG = AVLTree/Pila/pilaG
pruebaPila = AVLTree/Pila/pruebaPila
cola = AVLTree/Cola/cola
pruebaCola = AVLTree/Cola/pruebaCola

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


pruebaAVL: $(pilaG).o $(cola).o $(AVLTree).o $(pruebaAVLTree).o
	gcc -o testAVL.out $(AVLTree).o $(pruebaAVLTree).o $(pilaG).o $(cola).o

avltree.o: $(pilaG).h $(cola).h $(AVLTree).c $(AVLTree).h
	gcc $(flags) -c $(AVLTree).c

pruebaAVLTree.o: $(pruebaAVLTree).c
	gcc $(flags) -c $(pruebaAVLTree).c


cleanLin:
	rm -rf *.out *.o */*.o */*/*.o

cleanWin:
	del /Q /F AVLTree\Cola\*.o AVLTree\Pila\*.o AVLTree\*.o
