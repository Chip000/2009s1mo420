/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_SUBGRAD_H
#define HAVE_SUBGRAD_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/myfunc.h"
#include "../include/parser.h"
#include "../include/mytime.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* Estrutura para guardar os parametros do metodo do subgradiente */
struct subgrad_param {
	float e;
	int max_iter;
	int max_iter_no_improv;
};

/*
 * subgrad_parser: Parser para o arquivo contendo os parametros do 
 * metodo de subgradiente.  
 * Retorna 0 em caso de sucesso e 1 caso contrario.
 */
int subgrad_parser(const char *filename, struct subgrad_param *subpar);

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

/* DEBUG FUNCTIONS */

/* 
 * print_subgrad_param: imprime os parametros do metodo do 
 * subgradiente
 */
void print_subgrad_param(struct subgrad_param subpar);

#endif
/* ! HAVE_SUBGRAD_H */
