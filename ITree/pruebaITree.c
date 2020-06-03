#include <stdio.h>
#include <stdlib.h>
#include "ITree.h"


int main() {
  // Creando arbol y datos de prueba.
  ITree arbolEjemplo = itree_crear ();
  Intervalo datosPrueba[20];
  for (int i = 0; i < 20; ++i){
    datosPrueba[i].extIzq = i*2;
    datosPrueba[i].extDer = i*3;
  }

  // Insertando datos en el arbol.
  for (int i = 0; i < 20; ++i){
    itree_insertar (&arbolEjemplo, datosPrueba[i]);
  }

  printf ("IMPRIMIENDO ARBOL  chad OWO!\n\n");
  print2D (arbolEjemplo);

  printf ("\n\nImprimiendo arbol con dfs pre-order!\n\n");
  itree_recorrer_dfs (arbolEjemplo, imprimir_intervalo);

  printf ("\n\nImprimiendo arbol bfs!\n\n");
  itree_recorrer_bfs (arbolEjemplo, imprimir_intervalo);

  itree_destruir (arbolEjemplo);
  return 0;
}
