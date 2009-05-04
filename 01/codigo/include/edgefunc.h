/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_EDGEFUNC_H
#define HAVE_EDGEFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

/* Estrutura de representando as arestas do grafo */
struct edge {
	int u;
	int v;
	float dist;
	float cost;
};

/*
 * create_edge_array: Cria um vetor contendo as arestas do
 * grafo.
 */
struct edge *create_edge_array(struct graph *G);

/*
 * update_edge_cost: Atualiza a estrutura de arestas para o 
 * novo valor em G.
 */
void update_edge_cost(float **G, int m, struct edge **E);

/*
 * free_edge_array: Libera os recursos usados pelo conjunto de 
 * arestas do grafo.
 */
void free_edge_array(struct edge *E);

/* DEBUG FUNCTIONS */

/*
 * print_edge_array: Imprime o conjunto de arestas 
 */
void print_edge_array(struct edge *E, int m);

#endif
/* ! HAVE_EDGEFUNC_H */
