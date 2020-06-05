#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ITree/ITree.h"


/**
 * Dada un arbol.
 * Recurre sobre si misma, escaneando la consola y si la entrada es valida,
 * realiza:
 * "i [a,b]" ==> inserta el intervalo [a,b] en el arbol.
 * "e [a,b]" ==> elimina el intervalo [a,b] del arbol.
 * "? [a,b]" ==> interseca el intervalo [a,b] con los intervalos del arbol
 *                  Imprime "No"        <=> no hay interseccion.
 *                          "Si, [x,y]" <=> existe un intervalo que interseque.
 *                                          siendo [x,y] este.
 * "dfs" ==> imprime los intervalos de larbol con recorrido primero en profundidad.
 * "bfs" ==> imprime los intervalos de larbol con recorrido primero a lo ancho.
 * En todos los casos superiores, se vuelve a llamar a interprete excepto en
 * "salir" ==> corta la recursion.
 *
 */
void interprete (ITree arbol, Intervalo *intervalo);


/**
 * Dada una entrada y un apuntador a un intervalo.
 * Devuelve si esta es valida o no, tambien modifica el intervalo de tal forma
 * que se corresponda con el ingresado.
 * 0: salir
 */
char validar_entrada (char*, Intervalo* );

int main (){
  printf ("Buenas, bienvenido al interprete!\n");
  ITree arbolEjemplo = itree_crear ();
  Intervalo intervaloEjemplo;

  interprete (arbolEjemplo, &intervaloEjemplo);

  itree_destruir(arbolEjemplo);


  return 0;
}

char validar_entrada (char* entrada, Intervalo* intervalo){
  char accion = ' ';
  //printf ("Validando entrada...\n");

  if (!strcmp (entrada, "dfs")){
    accion = 'd';
  }
  else if (!strcmp (entrada, "bfs")){
    accion = 'b';
  }
  else if (!strcmp (entrada, "salir")){
    accion = 's';
  }
  else if ((entrada[0] == 'i' || entrada[0] == 'e' || entrada[0] == '?') && entrada[1] == ' ' && entrada[2] == '[') {
    int comaValida = 0;
    int punto = 0;
    int sePusoCualquieraEnElIntervalo = 0;
    int i = 3;

    for (; entrada[i] != ']' && entrada[i] != '\0' && !sePusoCualquieraEnElIntervalo; ++i){
      if (entrada[i] == ',' && comaValida == 0 && (entrada[i - 1] >= '0' && entrada[i - 1] <= '9') && (entrada[i + 1] >= '0' && entrada[i + 1] <= '9')) {
        //printf ("puso la coma\n");
        comaValida = 1;
        punto = 0;
      }
      else if (entrada[i] == '.' && punto == 0)
        punto = 1;
      else if (entrada[i] < '0' || entrada[i] > '9')
        sePusoCualquieraEnElIntervalo = 1;
      //printf ("Caracter: |%c|\n", entrada[i]);
    }

    if (sePusoCualquieraEnElIntervalo == 1){
      printf ("Argumento no valido, los componentes del intervalo no son numeros\n");
    }
    else if (entrada[i] == '\0'){
      printf ("Falta cerrar con un ] hermano.\n");
    }
    else if  (comaValida == 0){
      printf ("El intervalo esta incompleto. Tiene una cantidad de numeros < 2.\n");
    }
    else if (entrada[i + 1] != '\0') {
      printf ("Mas de un argumento, o basura");
    }
    else {
      sscanf (entrada + 3, "%lf,%lf]", &(intervalo->extIzq), &(intervalo->extDer));
      accion = entrada[0];
    }
  }
  else {
    printf ("Comando invalido, los comandos validos son: \n");
  }
  return accion;
}

void interprete (ITree arbol, Intervalo *intervalo){
  char buffer[80], barra[1];
  scanf ("%[^\n]%c", buffer, barra);
  char accion = validar_entrada (buffer, intervalo);
  ITree resultado;
  switch (accion) {
    case 'i':
      itree_insertar (&arbol, *intervalo);
      interprete (arbol, intervalo);
      break;
    case 'e':
      itree_eliminar_dato (&arbol, *intervalo);
      interprete (arbol, intervalo);
      break;
    case '?':

      resultado = itree_intersecar (arbol, *intervalo);

      if (resultado == NULL)
        printf ("No.\n");
      else {
        printf ("Si, ");
        intervalo_imprimir (resultado->intervalo);
        printf("\n");
        itree_destruir (resultado);
      }

      interprete (arbol, intervalo);
      break;
    case 'd':
      itree_recorrer_dfs (arbol, intervalo_imprimir);
      printf("\n");
      interprete (arbol, intervalo);
      break;
    case 'b':
      itree_recorrer_bfs (arbol, intervalo_imprimir);
      printf("\n");
      interprete (arbol, intervalo);
      break;
    case 's':
      printf ("Gracias por usar el interprete!\n");
      break;
    default:
      interprete (arbol, intervalo);
      break;
  }
}
