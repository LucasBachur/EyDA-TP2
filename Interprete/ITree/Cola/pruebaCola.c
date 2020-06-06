/**
 * Archivo para probar nuestra implementacion de colas.
 */

#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

void imprimir_int (void *dato){
  printf ("%d ", (*(int*)dato));
}

void sumar1 (void *dato){
  (*(int*)dato) = (*(int*)dato) + 1;
}

int main (){
  // Creando la cola.
  Cola colaEjemplo = cola_crear ();
  int datosPrueba[11] = {0,1,2,3,4,5,6,7,8,9,10};

  // Encolando elementos.
  for (int i = 0; i < 11; ++i){
    printf ("Encolando: |%d|\n", datosPrueba[i]);
    cola_encolar (&colaEjemplo, datosPrueba + i);
    // Mostrando cola.
    cola_recorrer (colaEjemplo, imprimir_int);   printf ("\n");
  }

  printf ("\n\n");

  // Mostrando primero y luego desencolandolo.
  for (int i = 0; i < 5; ++i){
    printf ("Desencolando elemento ");
    printf (" %d:\n", (*(int*) cola_primero (colaEjemplo) ));
    cola_desencolar (&colaEjemplo);
    cola_recorrer (colaEjemplo, imprimir_int);   printf ("\n");
  }

  // Sumando 1 a cada elemento de la pila.
  printf ("\n\nSumando uno a cada elemento:\n");
  cola_recorrer (colaEjemplo, sumar1);
  cola_recorrer (colaEjemplo, imprimir_int);

  cola_destruir (colaEjemplo);
  return 0;
}
