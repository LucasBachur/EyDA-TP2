#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

Cola cola_crear (){
  return NULL;
}

int cola_es_vacia (Cola cola){
  return cola == NULL;
}

void* cola_primero (Cola cola){
  return cola->principio->dato;
}

void cola_encolar (Cola *cola, void *dato){
  GNodo *nuevoNodo = malloc (sizeof (GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (!cola_es_vacia(*cola)){
    (*cola)->final->sig = nuevoNodo;
  }
  else {
    (*cola) = malloc (sizeof (struct _Cola));
    (*cola)->principio = nuevoNodo;
  }

  (*cola)->final = nuevoNodo;
}

void cola_desencolar (Cola *cola){
  if (!cola_es_vacia (*cola)){
    GNodo *libertador = (*cola)->principio;
    (*cola)->principio = libertador->sig;
    free (libertador);
    libertador = NULL;

    if ((*cola)->principio == NULL){
      free (*cola);
      (*cola) = NULL;
    }
  }
}

void cola_recorrer (Cola cola, FuncionVisitante visit){
  if (!cola_es_vacia (cola)){
    GNodo *iterador = cola->principio;

    for (; iterador != NULL; iterador = iterador->sig){
      visit (iterador->dato);
    }
  }
}

void cola_destruir (Cola cola){
  while (!cola_es_vacia(cola)){
    cola_desencolar (&cola);
  }
}
