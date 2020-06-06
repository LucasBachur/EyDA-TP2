#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ITree.h"
#include "Cola/cola.h"
#include "Pila/pila.h"


ITree itree_crear (){
  return NULL;
}

int itree_altura(ITree arbol){
  // Se define la altura de un arbol vacio como -1.
  int altura = -1;

  if(arbol != NULL)
    altura = arbol->altura;

  return altura;
}

int itree_factor_balance (ITree arbol){
  int factorBalance = 0;
  if (arbol != NULL)
   factorBalance = itree_altura(arbol->left) - itree_altura(arbol->right);
  return factorBalance;
}

ITree itree_balancear (ITree arbol){
  // Si se le pasa un arbol vacio, itree_factor_balance devolveria 0 y no
  // entraria a ninguna otra funcion.
  int factorBalance = itree_factor_balance (arbol);

  // Si la altura del subarbol izquierdo es mayor...
  if (factorBalance > 1){
    // En el caso de balance tras insercion, nunca va a ser igual a 0, pues justamente
    // por algo esta desbalanceado.
    // Ahora bien, cuando estamos balanceando tras eliminacion, puede ser que
    // sea 0, y en ese caso daria lo mismo, por lo que optamos por hacer
    // solo una rotacion simple.
    if (itree_factor_balance (arbol->left) >= 0)
      // Se tiene un caso de izquierda-izquierda, que requiere una rotacion der.
      arbol = itree_rotacion_der (arbol);
    // Si la altura del subarbol derecho del subarbol izquierdo es mayor.
    else {
      // se tiene un caso de izquierda-derecha, que requiere una rotacion doble.
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
    if (itree_factor_balance (arbol->right) <= 0){
      // Se tiene un caso de derecha-derecha, que requiere una rotacion izq.
      arbol = itree_rotacion_izq (arbol);
    }
    else {
      // se tiene un caso de derecha-izquierda, que requiere una rotacion doble.
      arbol->right = itree_rotacion_der (arbol->right);
      arbol = itree_rotacion_izq (arbol);
    }
  }

  return arbol;
}

ITree itree_rotacion_der (ITree arbol){
  // arbol: A.
  // nodoRelevante: B.
  ITree nodoRelevante = arbol->left;
  // Se cambia el hijo izquierdo de A a el hijo derecho de B.
  arbol->left = nodoRelevante->right;
  // Es necesario actualizar los valores de altura y maxExtDer de A puesto que
  // cambio el hijo izquierdo de A y no sabemos si se siguen manteniendo.
  itree_actualizar_altura(&arbol);
  itree_mayor_extDer (&arbol);
  // Se cambia el hijo derecho de B a A.
  nodoRelevante->right = arbol;
  // Es necesario actualizar los valores de altura y maxExtDer de B por
  // motivos analogos
  itree_actualizar_altura(&nodoRelevante);
  itree_mayor_extDer (&nodoRelevante);

  return nodoRelevante;
}

ITree itree_rotacion_izq (ITree arbol){
  // arbol: A.
  // nodoRelevante: B.
  ITree nodoRelevante = arbol->right;
  // Se cambia el hijo derecho de A a el hijo izquierdo de B.
  arbol->right = nodoRelevante->left;
  // Es necesario actualizar los valores de altura y maxExtDer de A puesto que
  // cambio el hijo derecho de A y no sabemos si se siguen manteniendo.
  itree_actualizar_altura(&arbol);
  itree_mayor_extDer (&arbol);
  // Se cambia el hijo izquierdo de B a A.
  nodoRelevante->left = arbol;
  // Es necesario actualizar los valores de altura y maxExtDer de B por
  // motivos analogos.
  itree_actualizar_altura(&nodoRelevante);
  itree_mayor_extDer (&nodoRelevante);

  return nodoRelevante;
}


// FALTA COMENTAR
void itree_insertar (ITree *arbol, Intervalo nIntervalo){
  if (*arbol == NULL){
    ITree nuevoSubarbol = malloc (sizeof (ITreeNodo));
    nuevoSubarbol->intervalo = nIntervalo;
    nuevoSubarbol->maxExtDer = nIntervalo.extDer;
    nuevoSubarbol->altura = 0;
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
      itree_actualizar_altura(arbol);

      *arbol = itree_balancear (*arbol);
    }
  }
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
      itree_actualizar_altura(arbol);
      *arbol = itree_balancear (*arbol);
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
    itree_actualizar_altura(arbol);
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

void itree_actualizar_altura (ITree *arbol){
  (*arbol)->altura = max2(itree_altura((*arbol)->left),itree_altura((*arbol)->right))+1;
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
