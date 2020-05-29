#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"
#include "/home/scalbi/Documents/Programacion/Estructuras de datos y algoritmos/TrabajoPractico2/EyDA-TP2-master/Pila/pilaG.h"
#include "/home/scalbi/Documents/Programacion/Estructuras de datos y algoritmos/TrabajoPractico2/EyDA-TP2-master/Cola/cola.h"


AVLTree avltree_crear (){
  return NULL;
}

void avltree_recorrer_bfs (AVLTree arbol, FuncionVisitante visit){
  if (arbol != NULL){
    Cola queue = cola_crear ();
    cola_encolar (&queue, arbol);
    AVLTree nodo = cola_primero (queue);

    while (!cola_es_vacia (queue)){
      nodo = cola_primero (queue);
      cola_desencolar (queue);
      visit (nodo->dato);
      if (nodo->right != NULL)
        cola_encolar (&queue, nodo->right);
      if (nodo->left != NULL)
        cola_encolar (&queue, nodo->left);
    }
  }
}


void avltree_recorrer_dfs (AVLTree arbol, FuncionVisitante visit){
  if (arbol != NULL){
    Pila stack = pila_crear ();
    pila_apilar (&stack, arbol);
    AVLTree nodo = pila_ultimo (stack);

    while (!pila_es_vacia (stack)){
      nodo = pila_ultimo (stack);
      pila_desapilar (stack);
      visit (nodo->dato);
      if (nodo->right != NULL)
        pila_apilar (&stack, nodo->right);
      if (nodo->left != NULL)
        pila_apilar (&stack, nodo->left);
    }
  }
}


void avltree_destruir (AVLTree raiz, FuncionLibertadora liberadora) {
  if (raiz != NULL){
    avltree_destruir (raiz->left);
    avltree_destruir (raiz->right);
    liberadora (raiz->dato);
    free (raiz)
  }
}
