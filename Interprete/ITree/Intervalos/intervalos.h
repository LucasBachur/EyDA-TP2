#ifndef __intervalos_h__
#define __intervalos_h__

typedef struct _Intervalo {
  double extIzq;
  double extDer;
} Intervalo;

/*
 * Crea un intervalo.
 */
Intervalo intervalo_crear ();

/**
 *  Dados dos intervalos, los compara y determina su relacion.
 *  devuelve: 1 si el primero es estrictamente mayor al segundo.
 *            -1 si es menor.
 *            0 si es igual.
 *  Explicar contexto.
 */
int intervalo_comparacion (Intervalo, Intervalo);


/**
 * Dadoo un intervalo, lo imprime formateado de la siguiente forma:
 * "[a,b] ".
 */
void intervalo_imprimir (Intervalo intervalo);

/**
 * Dado dos intervalos, determina si se intersecan.
 * Devuelve: 1 si hay interseccion.
 *           0 si no la hay.
 */
int intervalo_interseccion (Intervalo, Intervalo);

int intervalo_validar (Intervalo intervalo);


#endif
