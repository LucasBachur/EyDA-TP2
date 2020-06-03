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
  PGNodo *nuevoNodo = malloc (sizeof (PGNodo));
  nuevoNodo->dato = dato;

  nuevoNodo->sig = *pila;
  *pila = nuevoNodo;
}

void pila_desapilar (Pila *pila){
  if (!pila_es_vacia (*pila)){
    PGNodo *temp = (*pila)->sig;
    PGNodo *desapilado = *pila;
    *pila = temp;
    free (desapilado);
  }
}

void pila_recorrer (Pila pila, FuncionVisitante visit){
  while (pila != NULL){
    visit (pila->dato);
    pila = pila->sig;
  }
}

void pila_destruir (Pila pila){
  while (!pila_es_vacia(pila)){
    pila_desapilar (&pila);
  }
}
