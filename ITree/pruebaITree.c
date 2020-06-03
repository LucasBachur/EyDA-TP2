#include <stdio.h>
#include <stdlib.h>
#include "ITree.h"


int main() {
  // Creando arbol y datos de prueba.
  ITree arbolEjemplo = itree_crear ();
  Intervalo datosPrueba[5];
  for (int i = 0; i < 5; ++i){
    datosPrueba[i].extIzq = 0;
    datosPrueba[i].extDer = i;
  }

  // Insertando datos en el arbol.
  for (int i = 0; i < 5; ++i){
    itree_insertar (&arbolEjemplo, datosPrueba[i]);
  }
  printf ("IMPRIMIENDO ARBOL  chad OWO!\n\n");
  print2D (arbolEjemplo);
  itree_insertar (&arbolEjemplo, datosPrueba[0]);

  printf ("IMPRIMIENDO ARBOL  chad OWO!\n\n");
  print2D (arbolEjemplo);

  // printf ("\n\nImprimiendo arbol con dfs pre-order!\n\n");
  // itree_recorrer_dfs (arbolEjemplo, imprimir_intervalo);
  //
  // printf ("\n\nImprimiendo arbol bfs!\n\n");
  // itree_recorrer_bfs (arbolEjemplo, imprimir_intervalo);

  // Eliminado datos y mostrando.
  for (int i = 0; i < 3; ++i){
    itree_eliminar_dato (&arbolEjemplo, datosPrueba[i]);
    printf ("\n");
    print2D (arbolEjemplo);
    printf ("\n");
  }
  itree_eliminar_dato (&arbolEjemplo, datosPrueba[0]);

  itree_destruir (arbolEjemplo);
  return 0;
}
