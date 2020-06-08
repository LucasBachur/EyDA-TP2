#include <stdio.h>
#include <stdlib.h>
#include "ITree.h"


int main() {
  // Creando arbol y datos de prueba.
  ITree arbolEjemplo = itree_crear ();
  Intervalo datosPrueba[10];
  for (int i = 0; i < 10; ++i){
    datosPrueba[i].extIzq = i*2;
    datosPrueba[i].extDer = i*3;
  }

  // Insertando datos en el arbol.
  for (int i = 0; i < 10; ++i){
    itree_insertar (&arbolEjemplo, datosPrueba[i]);
  }
  printf ("IMPRIMIENDO ARBOL!\n\n");
  print2D (arbolEjemplo);


  Intervalo ejem = intervalo_crear(3.0, 3.0);

  ITree interseccion = itree_intersecar(arbolEjemplo, ejem);


  printf("\n\n\n");
  printf("Interserccion:\n");
  if(interseccion == NULL) printf("NULL");
  else intervalo_imprimir(interseccion->intervalo);

  printf("\n");

  itree_destruir (arbolEjemplo);

  return 0;
}
