#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ITree.h"
#include "Cola/cola.h"
#include "Pila/pilaG.h"



ITree itree_crear (){
  return NULL;
}

int itree_balance (ITree arbol){
  int factorBalance = itree_altura(arbol->left) - itree_altura(arbol->right);
  return factorBalance;
}

int itree_altura(ITree arbol){
  int altura = -1;

  if(arbol != NULL){
    altura = max2( 1 + itree_altura(arbol->left), 1 + itree_altura(arbol->right));
  }

  return altura;
}

ITree itree_rotacion_der (ITree arbol){
  ITree nodoRelevante = arbol->left;
  arbol->left = nodoRelevante->right;
  nodoRelevante->right = arbol;

  itree_mayor_extDer (&(nodoRelevante->right));
  itree_mayor_extDer (&nodoRelevante);

  return nodoRelevante;
}

ITree itree_rotacion_izq (ITree arbol){
  ITree nodoRelevante = arbol->right;
  arbol->right = nodoRelevante->left;
  nodoRelevante->left = arbol;

  itree_mayor_extDer (&(nodoRelevante->left));
  itree_mayor_extDer (&nodoRelevante);

  return nodoRelevante;
}

void itree_insertar (ITree *arbol, Intervalo nIntervalo){
  if (*arbol == NULL){
    ITree nuevoSubarbol = malloc (sizeof (ITreeNodo));
    nuevoSubarbol->intervalo = nIntervalo;
    nuevoSubarbol->maxExtDer = nIntervalo.extDer;
    nuevoSubarbol->left = itree_crear ();
    nuevoSubarbol->right = itree_crear ();
    *arbol = nuevoSubarbol;
  }
  else { // Notese "<" tendra que ser cambiado por una f.

    if (intervalo_mayor(nIntervalo, (*arbol)->intervalo)){
      itree_insertar ((&(*arbol)->right), nIntervalo);
    } else{
      itree_insertar ((&(*arbol)->left), nIntervalo);
    }

    itree_mayor_extDer (arbol);
    int balance = itree_balance (*arbol);
    *arbol = itree_balancear (*arbol, balance);
  }
}

ITree itree_balancear (ITree arbol, int factorBalance){

  if (factorBalance > 1){
    if (itree_balance (arbol->left) >= 0){
      arbol = itree_rotacion_der (arbol);
    }
    else {
      arbol->left = itree_rotacion_izq (arbol->left);
      arbol = itree_rotacion_der (arbol);
    }
  }
  else if (factorBalance < -1){
    // En el caso de balance tras insercion, nunca va a ser igual a 0, pues justamente
    // por algo esta desbalanceado.
    // Ahora bien, cuando estamos balanceando tras eliminacion, puede ser que
    // sea 0, y en ese caso daria lo mismo, por lo que optamos por hacer
    // solo una rotacion simple.
    if (itree_balance (arbol->right) < 0){
      arbol = itree_rotacion_izq (arbol);
    }
    else {
      arbol->right = itree_rotacion_der (arbol->right);
      arbol = itree_rotacion_izq (arbol);
    }
  }

  return arbol;
}

// void itree_eliminar_dato (ITree *arbol, Intervalo datoQueEliminar){
//   ITree nodoLiberar = NULL;
//
//   if ((*arbol)->dato == datoQueEliminar){
//     if ((*arbol)->left == NULL && (*arbol)->right == NULL){
//       free((*arbol));
//       *arbol = NULL;
//     }
//     else if ((*arbol)->left == NULL){
//       nodoLiberar = *arbol;
//       *arbol = (*arbol)->right;
//       free(nodoLiberar);
//       nodoLiberar = NULL;
//     }
//     else if ((*arbol)->right == NULL){
//       nodoLiberar = *arbol;
//       *arbol = (*arbol)->left;
//       free(nodoLiberar);
//       nodoLiberar = NULL;
//     }
//     else{
//       (*arbol)->dato = itree_eliminar_minimo(&((*arbol)->right));
//     }
//   }
//   else{
//     // printf("eliminando %d\n",arbol->dato);
//     if ((*arbol)->dato > datoQueEliminar) {
//       itree_eliminar_dato (&((*arbol)->left), datoQueEliminar);
//     }
//     else {
//       itree_eliminar_dato (&((*arbol)->right), datoQueEliminar);
//     }
//     int balance = itree_balance (*arbol);
//
//     *arbol = itree_balancear (*arbol, balance);
//   }
// }
//
// int itree_eliminar_minimo (ITree *arbol){
//   int minimo = -1;
//   if ((*arbol)->left == NULL){
//     minimo = (*arbol)->dato;
//     itree_eliminar_dato(arbol, (*arbol)->dato);
//   }
//   else{
//     minimo = itree_eliminar_minimo(&((*arbol)->left));
//   }
//   return minimo;
// }
//
// // void itree_destruir (ITree raiz, FuncionLibertadora liberadora) {
// //   if (raiz != NULL){
// //     itree_destruir (raiz->left, liberadora);
// //     itree_destruir (raiz->right, liberadora);
// //     liberadora (raiz->dato);
// //     free (raiz)
// //   }
// // }

void itree_destruir (ITree raiz){
  if (raiz != NULL){
    itree_destruir (raiz->left);
    itree_destruir (raiz->right);
    free (raiz);
  }
}

void itree_recorrer_bfs (ITree arbol, FuncionQueVisita visit){
  if (arbol != NULL){
    Cola queue = cola_crear ();
    cola_encolar (&queue, arbol);
    ITree nodo = cola_primero (queue);

    while (!cola_es_vacia (queue)){
      nodo = cola_primero (queue);
      cola_desencolar (&queue);
      visit (nodo->intervalo);
      if (nodo->right != NULL)
        cola_encolar (&queue, nodo->right);
      if (nodo->left != NULL)
        cola_encolar (&queue, nodo->left);
    }
  }
}

void itree_recorrer_dfs (ITree arbol, FuncionQueVisita visit){
  if (arbol != NULL){
    Pila stack = pila_crear ();
    pila_apilar (&stack, arbol);
    ITree nodo = pila_ultimo (stack);

    while (!pila_es_vacia (stack)){
      nodo = pila_ultimo (stack);
      pila_desapilar (&stack);
      visit (nodo->intervalo);
      if (nodo->right != NULL)
        pila_apilar (&stack, nodo->right);
      if (nodo->left != NULL)
        pila_apilar (&stack, nodo->left);
    }
  }
}

void itree_mayor_extDer (ITree *arbol){
  double maxExtDer;

  if ((*arbol)->left == NULL && (*arbol)->right == NULL){
    maxExtDer = ((*arbol)->intervalo.extDer);
  }
  else if ((*arbol)->left == NULL){
    maxExtDer = max2 ((*arbol)->intervalo.extDer, (*arbol)->right->maxExtDer);
  }
  else if ((*arbol)->right == NULL){
    maxExtDer = max2 ((*arbol)->intervalo.extDer, (*arbol)->left->maxExtDer);
  }
  else{
    maxExtDer = max3 ((*arbol)->intervalo.extDer, (*arbol)->left->maxExtDer, (*arbol)->right->maxExtDer);
  }

  (*arbol)->maxExtDer = maxExtDer;
}

void imprimir_intervalo (Intervalo intervalo){
  printf ("[%0.1f, %0.1f]", intervalo.extIzq, intervalo.extDer);
}

int intervalo_mayor (Intervalo intervalo1, Intervalo intervalo2){
  return intervalo1.extIzq > intervalo2.extIzq;
}

// Wrapper over print2DUtil()
void print2D(ITree arbol){
   // Pass initial space count as 0
   print2DUtil(arbol, 0);
}

void print2DUtil(ITree arbol, int space){
    // Base case
    if (arbol == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(arbol->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    imprimir_intervalo (arbol->intervalo);

    // Process left child
    print2DUtil(arbol->left, space);
}
