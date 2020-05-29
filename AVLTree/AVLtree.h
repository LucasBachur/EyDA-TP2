#ifndef __AVLtree_H__
#define __AVLtree_H__

typedef void (*FuncionVisitante) (void*);
typedef void (*FuncionLibertaodra) (void*)

typedef struct _AVLTNodo {
  int dato;
  struct _AVLTNodo *left;
  struct _AVLTNodo *right;
} AVLTNodo;

typedef AVLTNodo *AVLTree;

/**
 * Devuelve un arbol vacío.
 */
AVLTree avltree_crear ();

/**
 * Destruye un arbol liberando su memoria.
 */
void avltree_destruir (AVLTree arbol);

/**
 *  Dado un arbol y un objeto, si esta en el arbol, lo elimina.
 */
void avltree_insertar (AVLTree *arbol, void *dato);

/**
 *  Dado un arbol y un objeto, si esta en el arbol, lo elimina.
 */
void avltree_eliminar (AVLTree *arbol, void *dato);

/**
 * Recorre en profundidad y aplica la funcion visitante.
 */
void avltree_recorrer_dfs (AVLTree arbol, FuncionVisitante visit);

/**
 * Recorre en anchura y aplica la funcion visitante.
 */
void avltree_recorrer_bfs (AVLTree arbol, FuncionVisitante visit);




#endif


// Si se pueden insertar elementos repetidos, como elijo cual eliminar?
