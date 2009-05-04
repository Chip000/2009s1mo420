/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_PARSER_H
#define HAVE_PARSER_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 255

struct graph {
	int v; /* n de vertices */
	int e; /* n de arestas */
	int max_cost; /* restricao de custo maximo */
	float **cost; /* matriz de adjacencia para custos */
	float **dist; /* matriz de adjacencia para distancia */
};

/* Estrutura para guardar os parametros do metodo do subgradiente */
struct subgrad_param {
	float e;
	int max_iter;
	int max_iter_no_improv;
};

/* 
 * graph_parser: Guarda as informacoes do arquivo de entrada na
 * estrutura graph. 
 * Retorna 0 em caso de sucesso e 1 caso contrario.
 */
int graph_parser(const char *filename, struct graph *G);

/*
 * subgrad_parser: Parser para o arquivo contendo os parametros do 
 * metodo de subgradiente.  
 * Retorna 0 em caso de sucesso e 1 caso contrario.
 */
int subgrad_parser(const char *filename, struct subgrad_param *subpar);

/*
 * free_graph: Libera a memoria usada pela estrutura graph.
 */
void free_graph(struct graph G);

/* DEBUG FUNCTIONS */

/* 
 * print_graph: imprime as informacoes contidas na estrutura
 * graph lida.
 */
void print_graph(struct graph G);

/* 
 * print_subgrad_param: imprime os parametros do metodo do 
 * subgradiente
 */
void print_subgrad_param(struct subgrad_param subpar);

#endif
/* ! HAVE_PARSER_H */
