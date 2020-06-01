#include <stdio.h>
#include <stdlib.h>
#include "AVLtree.h"


int main() {
  printf ("buen dia\n");
  // Creando un arbol.
  AVLTree arbolEjemplo = avltree_crear ();
  // Prueba de insersion y eliminacion (Caso 1).

  // // Cargando los datos.
  // int datosPrueba[20] = { 13, 10, 15, 5, 11 , 16, 4, 6, 7};
  // for (int i = 0; i < 9; ++i){
  //   printf ("Insertando dato\n");
  //   avltree_insertar (&arbolEjemplo, datosPrueba[i]);
  // }

  // // Imprimiendo.
  // avltree_recorrer_dfs (arbolEjemplo, imprimir_int);

  // printf("\n");

  // arbolEjemplo = avltree_eliminar_dato (arbolEjemplo, 4);

  // avltree_recorrer_dfs (arbolEjemplo, imprimir_int);

  // printf("\n");

  // // Cargando los datos.
  int datosPrueba[20] = { 13, 10, 15, 5, 11 , 16, 4, 6, 7};
  for (int i = 0; i < 9; ++i){
    printf ("Insertando dato\n");
    avltree_insertar (&arbolEjemplo, datosPrueba[i]);
  }

  // Imprimiendo.
  avltree_recorrer_dfs (arbolEjemplo, imprimir_int);

  printf("\n");

  avltree_eliminar_dato (&arbolEjemplo, 16);

  avltree_recorrer_dfs (arbolEjemplo, imprimir_int);

  printf("\n");


  // Destruyendo
  avltree_destruir_int (arbolEjemplo);

  return 0;
}
