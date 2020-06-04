#ifndef __pilaG_h__
#define __pilaG_h__

typedef struct _PGNodo {
  void *dato;
  struct _PGNodo *sig;
} PGNodo;

typedef PGNodo *Pila;

typedef void (*FuncionVisitante) (void *dato);

/**
 * Crea una pila
 */
Pila pila_crear ();

/**
 * Dada una pila, determina si esta es vacia o no.
 * Devuelve:  1 si es vacia.
 *            0 si es no vacia.
 */
int pila_es_vacia (Pila);

/**
 * Dada una pila.
 * Devuelve el elemento en el tope, es decir el ultimo elemento.
 */
void* pila_ultimo (Pila);

/**
 * Dado un apuntador a una pila, y un dato.
 * Modifica la pila, creando un nuevo nodo y colocandolo en el tope.
 */
void pila_apilar (Pila*, void *dato);

/**
 * Dado un apuntador a una pila, y un dato.
 * Modifica la pila, quitando el tope y liberandolo.
 */
void pila_desapilar (Pila*);

/**
 * Dada una pila y una funcion.
 * Recorre la pila aplicando la funcion a cada elemento.
 */
void pila_recorrer (Pila, FuncionVisitante);

/**
 * Dada un pila.
 * Desapila todos los elementos hasta que quede vacia.
 */
void pila_destruir (Pila);

#endif
