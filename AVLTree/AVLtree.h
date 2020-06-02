#ifndef __AVLtree_H__
#define __AVLtree_H__

typedef void (*FuncionQueVisita) (int);
typedef void (*FuncionLibertadora) (void*);

typedef struct _AVLTNodo {
  int dato;
  struct _AVLTNodo *left;
  struct _AVLTNodo *right;
} AVLTNodo;

typedef AVLTNodo *AVLTree;

#define max(x, y) (((x) > (y)) ? (x) : (y))


void imprimir_int (int dato);
/**
 * Devuelve un arbol vacío.
 */
AVLTree avltree_crear ();

int avltree_balanceado(AVLTree arbol);

int avltree_altura(AVLTree arbol);

AVLTree avltree_balancear (AVLTree arbol, int);

AVLTree avltree_rotacion_izq (AVLTree arbol);

AVLTree avltree_rotacion_der (AVLTree arbol);

void avltree_eliminar_dato (AVLTree *arbol, int dato);

int avltree_eliminar_minimo (AVLTree *arbol);

/**
 * Destruye un arbol liberando su memoria.
 */
void avltree_destruir (AVLTree arbol, FuncionLibertadora);

void avltree_destruir_int (AVLTree raiz);

/**
 *  Dado un arbol y un objeto, lo inserta.
 */
void avltree_insertar (AVLTree *arbol, int dato);


/**
 * Recorre en profundidad y aplica la funcion visitante.
 */
void avltree_recorrer_dfs (AVLTree arbol, FuncionQueVisita visit);

/**
 * Recorre en anchura y aplica la funcion visitante.
 */
void avltree_recorrer_bfs (AVLTree arbol, FuncionQueVisita visit);




#endif


// Si se pueden insertar elementos repetidos, como elijo cual eliminar?
