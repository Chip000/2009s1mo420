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

/* 
 * parser: Guarda as informacoes do arquivo de entrada na
 * estrutura graph. 
 * Retorna 0 em caso de sucesso e 1 caso contrario.
 */
int parser(const char *filename, struct graph *G);

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

#endif
/* ! HAVE_PARSER_H */
