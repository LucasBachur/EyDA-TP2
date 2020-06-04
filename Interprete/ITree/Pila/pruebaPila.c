#include <stdio.h>
#include <stdlib.h>
#include "pilaG.h"

void imprimir_int (void *dato){
  printf ("%d ", (*(int*)dato));
}

void sumar1 (void *dato){
  (*(int*)dato) = (*(int*)dato) + 1;
}

int main (){
  // Creando la pila.
  Pila pilaEjemplo = pila_crear ();
  int datosPrueba[10] = {0,1,2,3,4,5,6,7,8,9};

  // Apilando elementos.
  for (int i = 0; i < 10; ++i){
    printf ("Apilando |%d|:\n", datosPrueba[i]);
    pila_apilar (&pilaEjemplo, datosPrueba + i);
    // Mostrando pila.
    pila_recorrer (pilaEjemplo, imprimir_int); printf ("\n");
  }

  printf ("\n\n");

  // Desapilando elementos.
  for (int i = 0; i < 5; ++i){
    printf ("Desapilando elementos y mostrando el primero: ");
    pila_desapilar (&pilaEjemplo);
    printf ("%d.\n", (*(int*) pila_ultimo (pilaEjemplo) ));
    pila_recorrer (pilaEjemplo, imprimir_int); printf ("\n");
  }

  // Sumando 1 a cada elemento de la pila.
  printf ("\n\nSumando uno a cada elemento:\n");
  pila_recorrer (pilaEjemplo, sumar1);
  pila_recorrer (pilaEjemplo, imprimir_int);


  pila_destruir (pilaEjemplo);
  return 0;
}
