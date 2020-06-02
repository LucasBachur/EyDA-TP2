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

int avltree_balance (AVLTree arbol){
  int factorBalance = avltree_altura(arbol->left) - avltree_altura(arbol->right);
  return factorBalance;
}

int avltree_altura(AVLTree arbol){
  int altura = -1;

  if(arbol != NULL){
    altura = max( 1 + avltree_altura(arbol->left), 1 + avltree_altura(arbol->right));
  }

  return altura;
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

void avltree_insertar (AVLTree *arbol, int dato){
  if (*arbol == NULL){
    printf ("Agregando nuevo dato, dato: |%d|\n", dato);
    AVLTree nuevoSubarbol = malloc (sizeof (AVLTNodo));
    nuevoSubarbol->dato = dato;
    nuevoSubarbol->left = avltree_crear ();
    nuevoSubarbol->right = avltree_crear ();
    *arbol = nuevoSubarbol;
  }
  else { // Notese "<" tendra que ser cambiado por una f.

    if (dato < (*arbol)->dato){
      avltree_insertar ((&(*arbol)->left), dato);
    } else{
      avltree_insertar ((&(*arbol)->right), dato);
    }
    int balance = avltree_balance (*arbol);

    *arbol = avltree_balancear (*arbol, balance);
  }
}

AVLTree avltree_balancear (AVLTree arbol, int factorBalance){

  if (factorBalance > 1){
    if (avltree_balance (arbol->left) >= 0){
      arbol = avltree_rotacion_der (arbol);
    }
    else {
      arbol->left = avltree_rotacion_izq (arbol->left);
      arbol = avltree_rotacion_der (arbol);
    }
  }
  else if (factorBalance < -1){
    printf ("hijo der\n");
    // En el caso de balance tras insercion, nunca va a ser igual a 0, pues justamente
    // por algo esta desbalanceado.
    // Ahora bien, cuando estamos balanceando tras eliminacion, puede ser que
    // sea 0, y en ese caso daria lo mismo, por lo que optamos por hacer
    // solo una rotacion simple.
    if (avltree_balance (arbol->right) >= 0){
      printf("buendia\n");
      printf ("hija der del der \n");

      printf ("\nrotando hacia derecha el arbol: \n");

      avltree_recorrer_dfs (arbol->right, imprimir_int);
      printf ("\n");
      arbol->right = avltree_rotacion_der (arbol->right);

      printf ("rotando hacia izq el arbol: \n");
      avltree_recorrer_dfs (arbol, imprimir_int);
      arbol = avltree_rotacion_izq (arbol);
      printf ("\n\n");

    }
    else {
      printf ("hija izq del der \n");
      printf ("rotando hacia izq el arbol: \n");
      avltree_recorrer_dfs (arbol, imprimir_int);
      arbol = avltree_rotacion_izq (arbol);
      printf ("\n\n");
    }
  }

  return arbol;
}

void avltree_eliminar_dato (AVLTree *arbol, int datoQueEliminar){
  AVLTree nodoLiberar = NULL;

  if ((*arbol)->dato == datoQueEliminar){
    if ((*arbol)->left == NULL && (*arbol)->right == NULL){
      free((*arbol));
      *arbol = NULL;
    }
    else if ((*arbol)->left == NULL){
      nodoLiberar = *arbol;
      *arbol = (*arbol)->right;
      free(nodoLiberar);
      nodoLiberar = NULL;
    }
    else if ((*arbol)->right == NULL){
      nodoLiberar = *arbol;
      *arbol = (*arbol)->left;
      free(nodoLiberar);
      nodoLiberar = NULL;
    }
    else{
      (*arbol)->dato = avltree_eliminar_minimo(&((*arbol)->right));
    }
  }
  else{
    // printf("eliminando %d\n",arbol->dato);
    if ((*arbol)->dato > datoQueEliminar) {
      avltree_eliminar_dato (&((*arbol)->left), datoQueEliminar);
    }
    else {
      avltree_eliminar_dato (&((*arbol)->right), datoQueEliminar);
    }
    int balance = avltree_balance (*arbol);

    *arbol = avltree_balancear (*arbol, balance);
  }
}

int avltree_eliminar_minimo (AVLTree *arbol){
  int minimo = -1;
  if ((*arbol)->left == NULL){
    minimo = (*arbol)->dato;
    avltree_eliminar_dato(arbol, (*arbol)->dato);
  }
  else{
    minimo = avltree_eliminar_minimo(&((*arbol)->left));
  }
  return minimo;
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
