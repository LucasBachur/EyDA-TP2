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
  else {
    int comparacion = intervalo_comparacion (nIntervalo, (*arbol)->intervalo);

    if (comparacion != 0){
      if (comparacion > 0){
        itree_insertar ((&(*arbol)->right), nIntervalo);
      }
      else if (comparacion < 0){
        itree_insertar ((&(*arbol)->left), nIntervalo);
      }

      itree_mayor_extDer (arbol);
      int balance = itree_balance (*arbol);
      *arbol = itree_balancear (*arbol, balance);
    }
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

void itree_eliminar_dato (ITree *arbol, Intervalo datoQueEliminar){
  if ((*arbol) != NULL){
    ITree nodoLiberar = NULL;
    int comparacion = intervalo_comparacion (datoQueEliminar, (*arbol)->intervalo);

    if (comparacion == 0){
      // Caso 1
      if ((*arbol)->left == NULL && (*arbol)->right == NULL){
        free((*arbol));
        *arbol = NULL;
      }
      // Caso 2.1
      else if ((*arbol)->left == NULL){
        nodoLiberar = *arbol;
        *arbol = (*arbol)->right;
        free(nodoLiberar);
        nodoLiberar = NULL;
      }
      // Caso 2.2
      else if ((*arbol)->right == NULL){
        nodoLiberar = *arbol;
        *arbol = (*arbol)->left;
        free(nodoLiberar);
        nodoLiberar = NULL;
      }
      // Caso 3
      else{
        (*arbol)->intervalo = itree_eliminar_minimo(&((*arbol)->right));
      }
    }
    else{
      // Buscar a la izq.
      if (comparacion < 0) {
        itree_eliminar_dato (&((*arbol)->left), datoQueEliminar);
      }
      // Buscar a la der.
      else {
        itree_eliminar_dato (&((*arbol)->right), datoQueEliminar);
      }
      // Actualizar arbol luego de que se haya eliminado.
      itree_mayor_extDer (arbol);
      int balance = itree_balance (*arbol);
      *arbol = itree_balancear (*arbol, balance);
    }
  }
}

Intervalo itree_eliminar_minimo (ITree *arbol){
  Intervalo minimo;
  if ((*arbol)->left == NULL){
    minimo = (*arbol)->intervalo;
    itree_eliminar_dato(arbol, (*arbol)->intervalo);
  }
  else{
    minimo = itree_eliminar_minimo(&((*arbol)->left));
    itree_mayor_extDer (arbol);
  }
  return minimo;
}

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
    ITree nodo;

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
    ITree nodo;

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

ITree itree_intersecar (ITree arbol, Intervalo intervaloQueInterseca){
  ITree resultado = NULL;
  if (arbol != NULL){
    if (intervalo_interseccion(arbol->intervalo, intervaloQueInterseca) == 1){
      resultado = arbol;
    }
    else if(arbol->left != NULL && intervaloQueInterseca.extIzq <= arbol->left->maxExtDer){
      resultado = itree_intersecar (arbol->left, intervaloQueInterseca);
    }
    else {
      resultado = itree_intersecar (arbol->right, intervaloQueInterseca);
    }
  }
  return resultado;
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
    intervalo_imprimir (arbol->intervalo);
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf(" %0.1f", arbol->maxExtDer);

    // Process left child
    print2DUtil(arbol->left, space);
}
