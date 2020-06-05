#ifndef __ITree_H__
#define __ITree_H__

#include "Intervalos/intervalos.h"

typedef void (*FuncionQueVisita) (Intervalo dato);
// typedef void (*FuncionLibertadora) (void*);
// /** No se sabe.
//  * Destruye un arbol liberando su memoria.
//  */
// void itree_destruir (ITree arbol, FuncionLibertadora);

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
 * Devuelve un arbol vacío.
 */
ITree itree_crear ();

int itree_balance (ITree arbol);

int itree_altura(ITree arbol);


ITree itree_rotacion_izq (ITree arbol);

ITree itree_rotacion_der (ITree arbol);

ITree itree_balancear (ITree arbol, int factorBalance);

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
