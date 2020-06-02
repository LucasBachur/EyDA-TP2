#include <stdio.h>
#include <stdlib.h>
#include "ITree.h"


int main() {
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

  printf ("IMPRIMIENDO ARBOL  virgin OWO!\n\n");
  itree_recorrer_dfs (arbolEjemplo, imprimir_intervalo);

  printf ("IMPRIMIENDO ARBOL  chad OWO!\n\n");
  print2D (arbolEjemplo);

  itree_destruir (arbolEjemplo);

  return 0;
}
