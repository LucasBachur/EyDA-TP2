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

  int datosPrueba[10] = {0,1,2,3,4,5,6,7,8,9};

  void *auxiliar;
  for (int i = 0; i < 10; ++i){
    // Encolando un entero.
    cola_encolar (&colaEjemplo, datosPrueba + i);
    cola_recorrer (colaEjemplo, imprimir_int);
    printf ("\n");
  }

  for (int i = 0; i < 5; ++i){
    // Desencolando 5 elementos.
    cola_desencolar (&colaEjemplo);
    cola_recorrer (colaEjemplo, imprimir_int);
    printf ("\n");
  }


  for (int i = 0; i < 5; ++i){
    // Encolando un entero.
    cola_encolar (&colaEjemplo, datosPrueba + i);
    printf ("%d ", (*(int*) cola_primero (colaEjemplo) ));

    printf ("\n");
  }

  // Probando ver si se modifica la cola con recorrer como seria esperado.

  cola_recorrer (colaEjemplo, sumar1);
  cola_recorrer (colaEjemplo, imprimir_int);

  cola_destruir (colaEjemplo);
  return 0;
}
