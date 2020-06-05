#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ITree/ITree.h"
#include "ITree/Intervalos/intervalos.h"


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
void interprete ();


/**
 * Dada una entrada y un apuntador a un intervalo.
 * Devuelve si esta es valida o no, tambien modifica el intervalo de tal forma
 * que se corresponda con el ingresado.
 * 0: salir
 */
char validar_entrada (char*, Intervalo* );

int validar_coma (char *entrada, int bandera, int i);

int validar_sign_menos (char *entrada, int bandera, int i);

int validar_punto (char *entrada, int bandera, int i);

int validar_numero (char *entrada, int i);

int validar_espacio (char* entrada, int i);

int validar_argumento (char *entrada);


int main (){
  printf ("Buenas, bienvenido al interprete!\n");

  interprete ();

  return 0;
}

char validar_entrada (char* entrada, Intervalo* intervalo){
  char accion = ' ';

  if (!strcmp (entrada, "dfs")){
    accion = 'd';
  }
  else if (!strcmp (entrada, "bfs")){
    accion = 'b';
  }
  else if (!strcmp (entrada, "salir")){
    accion = 's';
  }
  else if ((entrada[0] == 'i' || entrada[0] == 'e' || entrada[0] == '?') && entrada[1] == ' ' && entrada[2] == '['){
    if (validar_argumento (entrada)){
      sscanf (entrada + 3, "%lf,%lf]", &(intervalo->extIzq), &(intervalo->extDer));
      if (validar_intervalo (*intervalo))
        accion = entrada[0];
      else
        printf ("Intervalo invalido: El extremo izquierdo es mayor que el derecho\n");
    }
  }
  else {
    printf ("Comando totalmente invalido.\n");
    printf ("Los comandos validos son:\ni [x,y]\ne [x,y]\n? [x,y]\nbfs\ndfs\n");
    printf ("Ingrese un nuevo comando\n");
  }

  return accion;
}

void interprete (){
  ITree arbolEjemplo = itree_crear ();
  Intervalo intervaloEjemplo;
  char buffer[80], barra;
  char accion = ' ';
  ITree resultado;

  while (accion != 's'){
    scanf ("%[^\n]%c", buffer, &barra);
    accion = validar_entrada (buffer, &intervaloEjemplo);
    switch (accion) {
      case 'i':
        itree_insertar (&arbolEjemplo, intervaloEjemplo);
        break;
      case 'e':
        itree_eliminar_dato (&arbolEjemplo, intervaloEjemplo);
        break;
      case '?':
        resultado = itree_intersecar (arbolEjemplo, intervaloEjemplo);
        if (resultado == NULL)
          printf ("No.\n");
        else {
          printf ("Si, ");
          intervalo_imprimir (resultado->intervalo);
          printf("\n");
          itree_destruir (resultado);
        }
        break;
      case 'd':
        itree_recorrer_dfs (arbolEjemplo, intervalo_imprimir); printf("\n");
        break;
      case 'b':
        itree_recorrer_bfs (arbolEjemplo, intervalo_imprimir); printf("\n");
        break;
      case 's':
        printf ("Gracias por usar el interprete!\n");
        break;
      default:
        break;
    }
  }
  itree_destruir(arbolEjemplo);
}

int validar_argumento (char *entrada){
  int validez = 0;
  // Declarando banderas.
  int coma = 0;     //bandera que indica si se coloco o no una coma.
  int punto = 0;    //bandera que indica si se coloco o no un punto.
  int basura = 0;   //caracteres no desesados dentro del intervalo.
  int espacioM = 0; //espacio mal colocado.
  int menos = 0;    //bandera que indica si se coloco o no un signo menos.
  int i = 3;        //contador luego del '[' en la entrada.

  for (; entrada[i] != ']' && entrada[i] != '\0' && !basura && !espacioM; ++i){
    if (entrada[i] == ',' && validar_coma (entrada, coma, i)) {
      coma = 1;
      punto = 0;
      menos = 0;
    }
    else if (entrada[i] == '-' && validar_sign_menos (entrada, menos, i))
      menos = 1;
    else if (entrada[i] == '.' && validar_punto (entrada, punto, i))
      punto = 1;
    else if (entrada[i] == ' ' && !validar_espacio (entrada, i))
      espacioM = 1;
    else if (entrada[i] != ' ' && !validar_numero (entrada, i))
      basura = 1;
  }

  // Errores...
  if (basura == 1)
    printf ("Basura en el argumento.\n");
  else if (espacioM)
    printf("Hay AL MENOS un espacio mal ubicado.\n");
  else if  (coma == 0)
    printf ("El intervalo esta incompleto.\n");
  else if (entrada[i] == '\0')
    printf ("Todo intervalo debe finalizar con un ].\n");
  else if (entrada[i + 1] != '\0')
    printf ("Mas de un argumento, o basura al final.\n");
  // Sin errores...
  else
    validez = 1;

  return validez;
}

int validar_coma (char *entrada, int bandera, int i){
  return bandera == 0 && validar_numero (entrada, i-1) && (validar_numero (entrada, i+1) || entrada[i + 1] == ' ');
}

int validar_sign_menos (char *entrada, int bandera, int i){
  return bandera == 0 && (entrada[i-1] == ' ' || entrada[i-1] == '[' || entrada[i-1] == ',');
}

int validar_punto (char *entrada, int bandera, int i){
  return bandera == 0 && validar_numero (entrada, i-1) && validar_numero (entrada, i+1);
}

int validar_numero (char *entrada, int i){
  return (entrada[i] >= '0' || entrada[i] <= '9');
}

int validar_espacio (char* entrada, int i){
  return (entrada[i-1] == ',' && validar_numero (entrada, i + 1));
}
