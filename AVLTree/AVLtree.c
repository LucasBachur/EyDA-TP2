#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLtree.h"
#include "Cola/cola.h"
#include "Pila/pilaG.h"

void imprimir_int (int dato){
  printf ("%d ", dato);
}

AVLTree avltree_crear (){
  return NULL;
}

int avltree_balanceado(AVLTree arbol){
  int factorBalance = avltree_altura(arbol->left) - avltree_altura(arbol->right);
  return factorBalance == -1 || factorBalance == 1 || factorBalance == 0;
}

int avltree_altura(AVLTree arbol){
  int altura = -1;

  if(arbol != NULL){
    altura = max( 1 + avltree_altura(arbol->left), 1 + avltree_altura(arbol->right));
  }

  return altura;
}

AVLTree avltree_balancear (AVLTree arbol, char *caso){
  AVLTree nuevoArbol = NULL;
  // Desbalance hacia afuera, rotacion simple.

  if (!strcmp (caso, "ii")){
    nuevoArbol = avltree_rotacion_der(arbol);

  } else if (!strcmp (caso, "dd")){
    nuevoArbol = avltree_rotacion_izq(arbol);
  } else if (!strcmp (caso, "di")){
    arbol->right = avltree_rotacion_der(arbol->right);
    nuevoArbol = avltree_rotacion_izq(arbol);
  } else{
    arbol->left = avltree_rotacion_izq(arbol->left);
    nuevoArbol = avltree_rotacion_der(arbol);
  }
  return nuevoArbol;
}

AVLTree avltree_rotacion_der (AVLTree arbol){
  AVLTree nodoRelevante = arbol->left;
  arbol->left = nodoRelevante->right;
  nodoRelevante->right = arbol;
  return nodoRelevante;
}

AVLTree avltree_rotacion_izq (AVLTree arbol){
  AVLTree nodoRelevante = arbol->right;
  arbol->right = nodoRelevante->left;
  nodoRelevante->left = arbol;
  return nodoRelevante;
}

char avltree_insertar (AVLTree *arbol, int dato){
  printf ("avltree_insertar\n");
  char mov = ' '; // si fue a la izquierda: i. derecha: d

  if (*arbol == NULL){
    printf ("Agregando nuevo dato, dato: |%d|\n", dato);
    AVLTree nuevoSubarbol = malloc (sizeof (AVLTNodo));
    nuevoSubarbol->dato = dato;
    nuevoSubarbol->left = avltree_crear ();
    nuevoSubarbol->right = avltree_crear ();
    *arbol = nuevoSubarbol;
  }
  // modularizar estos if.
  else { // Notese "<" tendra que ser cambiado por una f.
    char sigMov = ' '; // si fue a la izquierda: i. derecha: d.
    char balanceRequerido[3];
    if (dato < (*arbol)->dato){
      mov = 'i';
      sigMov = avltree_insertar ((&(*arbol)->left), dato);
    } else{
      mov = 'd';
      sigMov = avltree_insertar ((&(*arbol)->right), dato);
    }
    balanceRequerido[0] = mov;
    balanceRequerido[1] = sigMov;
    balanceRequerido[2] = '\0';

    // (patito).
    if (!avltree_balanceado (*arbol)){
      *arbol = avltree_balancear (*arbol, balanceRequerido);
    }
  }
  return mov;
}

// void avltree_destruir (AVLTree raiz, FuncionLibertadora liberadora) {
//   if (raiz != NULL){
//     avltree_destruir (raiz->left, liberadora);
//     avltree_destruir (raiz->right, liberadora);
//     liberadora (raiz->dato);
//     free (raiz)
//   }
// }

void avltree_destruir_int (AVLTree raiz){
  if (raiz != NULL){
    avltree_destruir_int (raiz->left);
    avltree_destruir_int (raiz->right);
    free (raiz);
  }
}

void avltree_recorrer_bfs (AVLTree arbol, FuncionQueVisita visit){
  if (arbol != NULL){
    Cola queue = cola_crear ();
    cola_encolar (&queue, arbol);
    AVLTree nodo = cola_primero (queue);

    while (!cola_es_vacia (queue)){
      nodo = cola_primero (queue);
      cola_desencolar (&queue);
      visit (nodo->dato);
      if (nodo->right != NULL)
        cola_encolar (&queue, nodo->right);
      if (nodo->left != NULL)
        cola_encolar (&queue, nodo->left);
    }
  }
}


void avltree_recorrer_dfs (AVLTree arbol, FuncionQueVisita visit){
  if (arbol != NULL){
    Pila stack = pila_crear ();
    pila_apilar (&stack, arbol);
    AVLTree nodo = pila_ultimo (stack);

    while (!pila_es_vacia (stack)){
      nodo = pila_ultimo (stack);
      pila_desapilar (&stack);
      visit (nodo->dato);
      if (nodo->right != NULL)
        pila_apilar (&stack, nodo->right);
      if (nodo->left != NULL)
        pila_apilar (&stack, nodo->left);
    }
  }
}
