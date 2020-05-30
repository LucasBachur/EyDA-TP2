/**
 * Funciones de colas generales.
 */

#ifndef __cola_h__
#define __cola_h__

typedef struct _GNodo {
  void *dato;
  struct _GNodo *next;
} GNodo;

typedef struct _Cola {
  GNodo *principio;
  GNodo *final;
} Cola;
// Por que no *Cola?

typedef void (*FuncionVisitante) (void *dato);

/**
 * Crea un cola
 */
Cola cola_crear ();

/**
 * Determina si una cola es vacia o no.
 */
int cola_es_vacia (Cola);

/**
 * Crea un cola
 */
void* cola_primero (Cola);

/**
 * Crea un cola
 */
void cola_encolar (Cola*, void*);

/**
 * Crea un cola
 */
void cola_desencolar (Cola*);

/**
 * Crea un cola
 */
void cola_recorrer (Cola, FuncionVisitante);

/**
 * Crea un cola
 */
void cola_destruir (Cola);


#endif
