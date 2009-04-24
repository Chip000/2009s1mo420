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
	int v;
	int e;
	int max_cost;
	float **cost;
	float **dist;
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
