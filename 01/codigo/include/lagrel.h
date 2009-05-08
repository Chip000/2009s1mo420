/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_LAGREL_H
#define HAVE_LAGREL_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/edgefunc.h"
#include "../include/mytime.h"
#include "../include/parser.h"
#include "../include/rlfunc.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define W_STEP 0.01

/*
 * lag_heuristic: Heuristica lagrangeana que calcula os valores dos 
 * limitantes usando o metodo do subgradiente, encontrando a solucao
 * do problema.
 * Entrada:
 *   - Parametros para o metodo do subgradiente
 *   - Informacoes sobre o grafo de entrada
 *   - Relaxacao a ser feita
 *   - Nome do arquivo de saida que tera os valores dos limitantes
 *     a cada iteracao
 */
void lag_heuristic(struct subgrad_param *subpar, 
		   struct graph *G, 
		   int rel,
		   const char *filename);

#endif
/* ! HAVE_LAGREL_H */
