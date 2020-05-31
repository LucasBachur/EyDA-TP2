#include <stdio.h>
#include <stdlib.h>
#include "AVLtree.h"


int main() {
  printf ("buen dia\n");
  // Creando un arbol.
  AVLTree arbolEjemplo = avltree_crear ();

  // Cargando los datos.
  int datosPrueba[20] = {13, 10, 15, 5, 11 ,16, 4 ,6, 3, 14, 17, 18};
  for (int i = 0; i < 12; ++i){
    printf ("Insertando dato\n");
    avltree_insertar (&arbolEjemplo, datosPrueba[i]);
  }

  // Imprimiendo.
  avltree_recorrer_dfs (arbolEjemplo, imprimir_int);

  // Destruyendo
  avltree_destruir_int (arbolEjemplo);
  return 0;
}