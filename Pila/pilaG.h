#ifndef __pilaG_h__
#define __pilaG_h__

typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *Pila;

// Crea una pila general.
Pila pila_crear ();

// Dada una pila, determina si es vacia.
int pila_es_vacia (Pila);

// Dada una pila, devuelve el elemento en el tope.
void* pila_ultimo (Pila);

// Dada una pila y un elemento, lo agrega a la pila.
void pila_apilar (Pila*, void *dato);

// Dada una pila, elimina el elemento en el tope.
void pila_desapilar (Pila*);

// Dada una pila, la imprime.
void pila_enteros_imprimir (Pila);

// Dada una pila, libera la memoria utilizada.
void pila_destruir (Pila);

#endif
