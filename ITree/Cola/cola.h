/**
 * Archivo de cabecera de nuestra implementacion de colas enlazadas.
 */

#ifndef __cola_h__
#define __cola_h__

/**
 * Estructura de nodo para cada elemento de la cola.
 */
typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
} GNodo;


/**
 * Estructura de la cola.
 */ 
typedef struct _Cola {
  GNodo *principio;
  GNodo *final;
} *Cola;

typedef void (*FuncionVisitante) (void *dato);

/**
 * Crea un cola
 */
Cola cola_crear ();

/**
 * Dada una cola, determina si esta es vacia o no.
 * Devuelve:  1 si es vacia.
 *            0 si es no vacia.
 */
int cola_es_vacia (Cola);

/**
 * Dada una cola.
 * Devuelve el dato del primer elemento.
 */
void* cola_primero (Cola);

/**
 * Dado un apuntador a una cola y un dato.
 * Modifica la cola, creando un nuevo nodo y colocandolo al final.
 */
void cola_encolar (Cola* , void*);

/**
 * Dado un apuntador cola.
 * Modifica la cola, quitando el primer elemento de la misma y liberandolo.
 */
void cola_desencolar (Cola*);

/**
 * Dada una cola y una funcion.
 * Recorre la cola aplicando la funcion a cada elemento.
 */
void cola_recorrer (Cola, FuncionVisitante);

/**
 * Dada un cola.
 * Desencola todos los elementos hasta que la cola quede vacia.
 */
void cola_destruir (Cola);
#endif
