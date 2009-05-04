/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/edgefunc.h"

/*
 * create_edge_array: Cria um vetor contendo as arestas do
 * grafo.
 */
struct edge *create_edge_array(struct graph *G)
{
	int i;
	int j;
	int k;
	
	struct edge *E;

	E = (struct edge *) malloc(G->e * sizeof(struct edge));

	k = 0;
	for (i = 0; i < G->v; i++) {
		for (j = i; j < G->v; j++) {
			if ((G->dist)[i][j] != 0) {
				E[k].u = i;
				E[k].v = j;
				E[k].dist = (G->dist)[i][j];
				E[k].cost = (G->cost)[i][j];
				k++;
			}
		}
	}
	
	return E;

} /* create_edge_array */

/*
 * update_edge_cost: Atualiza a estrutura de arestas para o 
 * novo valor em G.
 */
void update_edge_cost(float **G, int m, struct edge **E)
{

	int i;
	int u;
	int v;

	for (i = 0; i < m; i++) {
		u = (*E)[i].u;
		v = (*E)[i].v;
		(*E)[i].dist = G[u][v];
	}
	
	return;

} /* update_edge_array */

/*
 * free_edge_array: Libera os recursos usados pelo conjunto de 
 * arestas do grafo.
 */
void free_edge_array(struct edge *E)
{
	free(E);
	return;

} /* free_edge_array */

/* DEBUG FUNCTIONS */

/*
 * print_edge_array: Imprime o conjunto de arestas 
 */
void print_edge_array(struct edge *E, int m)
{
	int i;

	fprintf(stderr, ">>>DEBUG: \n");

	for (i = 0; i < m; i++) {
		fprintf(stderr, "%d %d dist= %.2f cost= %.2f\n",
			E[i].u, E[i].v, E[i].dist, E[i].cost);
	}

	fprintf(stderr, "\n");

	return;

} /* print_edge_array */

/* EOF */
