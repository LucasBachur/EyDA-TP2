#include <stdio.h>
#include <stdlib.h>
#include "pilaG.h"


// Funcion para imprimir ints esta hecha en el punto h porque nos pinto.


int main (){
  // Creando la pila.
  Pila pilaEjemplo = pila_crear ();

  int datosPrueba[10] = {0,1,2,3,4,5,6,7,8,9};

  void *auxiliar;
  for (int i = 0; i < 10; ++i){
    // Apilando un entero.
    pila_apilar (&pilaEjemplo, datosPrueba + i);
    pila_enteros_imprimir (pilaEjemplo);
    printf ("\n");
  }

  for (int i = 0; i < 5; ++i){
    // Desapilando un elemento.
    pila_desapilar (&pilaEjemplo);
    pila_enteros_imprimir (pilaEjemplo);
    printf ("\n");
  }


  for (int i = 0; i < 5; ++i){
    // Apilando un entero y mostrandolo.
    pila_apilar (&pilaEjemplo, datosPrueba + i);
    printf ("%d ", (*(int*) pila_ultimo (pilaEjemplo) ));
    printf ("\n");
  }

  pila_destruir (pilaEjemplo);
  return 0;
}
