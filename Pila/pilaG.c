#include <stdio.h>
#include <stdlib.h>
#include "pilaG.h"

Pila pila_crear (){
  return NULL;
}

int pila_es_vacia (Pila pila){
  return pila == NULL;
}

void* pila_ultimo (Pila pila){
  return pila->dato;
}

void pila_apilar (Pila *pila, void *dato){
  GNodo *nuevoNodo = malloc (sizeof (GNodo));
  nuevoNodo->dato = dato;

  nuevoNodo->sig = *pila;
  *pila = nuevoNodo;
}

void pila_desapilar (Pila *pila){
  if (!pila_es_vacia (*pila)){
    GNodo *temp = (*pila)->sig;
    GNodo *desapilado = *pila;
    *pila = temp;
    free (desapilado);
  }
}

void pila_enteros_imprimir (Pila pila){
  while (pila != NULL){
    printf ("|%d| ", (*(int*)pila_ultimo (pila)));
    pila = pila->sig;
  }
}

void pila_destruir (Pila pila){
  if (!pila_es_vacia(pila)){
    pila_desapilar (&pila);
    pila_destruir (pila);
  }
}
