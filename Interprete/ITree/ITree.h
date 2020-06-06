#ifndef __ITree_H__
#define __ITree_H__

#include "Intervalos/intervalos.h"

typedef void (*FuncionQueVisita) (Intervalo dato);

typedef struct _ITreeNodo {
  Intervalo intervalo;
  double maxExtDer;
  int altura;
  struct _ITreeNodo *left;
  struct _ITreeNodo *right;
} ITreeNodo;

typedef ITreeNodo *ITree;

#define max2(x, y) (((x) > (y)) ? (x) : (y))
#define max3(x, y, z) (max2 (x, max2 (y, z)))

/**
 * Devuelve lo que determinamos como un arbol vacio.
 */
ITree itree_crear ();

/**
 * Dado un arbol.
 * Devuelve la altura del mismo.
 * Aunque en la declaracion del tipo de dato de arboles agregamos un campo
 * que guarda la altura del arbol, decidimos hacer esta funcion puesto que
 * como consideramos al arbol vacio como NULL, este no tiene campo altura.
 */
int itree_altura(ITree arbol);

/**
 * Dado un arbol.
 * Devuelve el factor de balance de un arbol.
 * Definido como la altura del subarbol izquierdo menos la del subarbol derecho.
 */
int itree_factor_balance (ITree arbol);

/**
 * Dado un arbol, obtiene su factor de balance y de ser nesecario lo balancea
 * aplicando las rotaciones correspondientes y actualizando sus campos de altura
 * y maxExtDer.
 * Devuelve el arbol rotado.
 */
ITree itree_balancear (ITree arbol);

/**
 * Dado un arbol, realiza una rotacion simple a derecha. Ademas se actualizan
 * los campos de altura y maxExtDer de forma que el arbol resultante sea
 * correcto.
 * Devuelve el arbol luego de la rotacion.
 */
ITree itree_rotacion_der (ITree arbol);

/**
 * Dado un arbol, realiza una rotacion simple a izquierda. Ademas se actualizan
 * los campos de altura y maxExtDer de forma que el arbol resultante sea
 * correcto.
 * Devuelve el arbol luego de la rotacion.
 */
ITree itree_rotacion_izq (ITree arbol);

// FALTA COMENTAR


/**
 *  Dado un arbol y un objeto, lo inserta.
 */
void itree_insertar (ITree *arbol, Intervalo);

// No se sabe.
void itree_eliminar_dato (ITree *arbol, Intervalo);
// No se sabe.
Intervalo itree_eliminar_minimo (ITree *arbol);


/**
 * Recorre en profundidad y aplica la funcion visitante.
 */
void itree_recorrer_dfs (ITree arbol, FuncionQueVisita visit);

/**
 * Recorre en anchura y aplica la funcion visitante.
 */
void itree_recorrer_bfs (ITree arbol, FuncionQueVisita visit);

void itree_mayor_extDer (ITree *arbol);

void itree_actualizar_altura (ITree *arbol);

void itree_destruir (ITree raiz);

ITree itree_intersecar (ITree, Intervalo);

#define COUNT 10

void print2D(ITree arbol);

void print2DUtil(ITree arbol, int space);

#endif
