flags = -Wall -Werror -Wextra -g

AVLTree = AVLTree/AVLtree
pilaG = Pila/pilaG
pruebaPila = Pila/pruebaPila
cola = Cola/cola
pruebaCola = Cola/pruebaCola

pruebas: pruebaCola pruebaPila

pruebaCola: $(cola).o $(pruebaCola).o
	gcc -o testCola.out $(cola).o $(pruebaCola).o

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


avltree.o: $(AVLTree).c $(AVLTree).h
	gcc $(flags) -c $(AVLTree).c


clean:
	rm -rf *.out *.o */*.o
