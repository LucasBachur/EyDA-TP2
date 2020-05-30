#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

Cola cola_crear (){
  Cola cola;
  cola.principio = NULL;
  cola.final = NULL;
  return cola;
}

int cola_es_vacia (Cola cola){
  return cola.final == NULL;
}


void* cola_primero (Cola cola){
  return cola.principio->dato;
}

void cola_encolar (Cola *cola, void *dato){
  GNodo *nuevoNodo = malloc (sizeof (GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->next = NULL;

  if (!cola_es_vacia(*cola)){
    cola->final->next = nuevoNodo;
  }
  else {
    cola->principio = nuevoNodo;
  }

  cola->final = nuevoNodo;
}

void cola_desencolar (Cola *cola){
  if (!cola_es_vacia (*cola)){
    GNodo *libertador = cola->principio;
    cola->principio = libertador->next;
    free (libertador);

    if (cola->principio == NULL){
      cola->final = NULL;
    }
  }
}

void cola_recorrer (Cola cola, FuncionVisitante visit){
  GNodo *iterador = cola.principio;

  for (; iterador != NULL; iterador = iterador->next){
    visit (iterador->dato);
  }
}

void cola_destruir (Cola cola){
  while (!cola_es_vacia(cola)){
    cola_desencolar (&cola);
  }
}
