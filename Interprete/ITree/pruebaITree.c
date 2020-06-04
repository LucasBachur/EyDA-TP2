#include <stdio.h>
#include <stdlib.h>
#include "ITree.h"


int main() {
  // Creando arbol y datos de prueba.
  ITree arbolEjemplo = itree_crear ();
  Intervalo datosPrueba[100];
  for (int i = 0; i < 20; ++i){
    datosPrueba[i].extIzq = i*2;
    datosPrueba[i].extDer = i*3;
  }

  // Insertando datos en el arbol.
  for (int i = 0; i < 20; ++i){
    itree_insertar (&arbolEjemplo, datosPrueba[i]);
  }
  /*printf ("IMPRIMIENDO ARBOL  chad OWO!\n\n");
  print2D (arbolEjemplo);
  itree_insertar (&arbolEjemplo, datosPrueba[0]);

  printf ("IMPRIMIENDO ARBOL  chad OWO!\n\n");
  print2D (arbolEjemplo);*/

  printf ("\n\nImprimiendo arbol con dfs pre-order!\n\n");
  itree_recorrer_dfs (arbolEjemplo, intervalo_imprimir);

  printf ("\n\nImprimiendo arbol bfs!\n\n");
  itree_recorrer_bfs (arbolEjemplo, intervalo_imprimir);

  // Eliminado datos y mostrando.
  /*for (int i = 0; i < 3; ++i){
    itree_eliminar_dato (&arbolEjemplo, datosPrueba[i]);
    printf ("\n");
    print2D (arbolEjemplo);
    printf ("\n");
  }*/
  //itree_eliminar_dato (&arbolEjemplo, datosPrueba[0]);

  Intervalo ejem = intervalo_crear(100.0, 100.0);

  ITree interseccion = itree_intersecar(arbolEjemplo, ejem);

  printf ("IMPRIMIENDO ARBOL  chad OWO!\n\n");
  print2D (arbolEjemplo);

  printf("\n\n\n");

  if(interseccion == NULL) printf("NULL");
  else intervalo_imprimir(interseccion->intervalo);

  itree_destruir (arbolEjemplo);
  return 0;
}
