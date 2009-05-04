/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */


#ifndef HAVE_MYFUNC_H
#define HAVE_MYFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/edgefunc.h"

#define INF 999999999

/* RL1 */
/*
 * knapsack: Resolve o problema da mochila usando algoritmo de 
 * programacao dinamica (pseudopolinomial)
 * Entrada:
 *   - Conjunto de arestas do grafo 
 *   - Numero de arestas do grafo
 *   - Numero de vertices do grafo
 *   - Peso da mochila
 * Saida:
 *   - Conjunto solucao 
 *   - Custo da solucao
 */
float knapsack(struct edge *E, int m, int n, float W, int ***x);

/* RL2 */
/*
 * shortest_path: Utiliza o algoritmo de Dijkstra para encontrar 
 * o caminho mais curto de s a t em um grafo G.
 * Entradas: 
 *   - Matriz de adjacencia contendo as distancias das arestas
 *   - Numero de vertices do grafo.
 *   - Vertice origem
 *   - Vertice destino
 * Saidas:
 *   - Conjunto solucao
 *   - Custo do caminho mais curto
 */
float shortest_path(float **G, int n, int s, int t, int ***x);


/* DEBUG FUNCTIONS */

/*
 * print_shortest_path: Imprime o custo e o caminho mais curto 
 * da solucao dada.
 */
void print_shortest_path(int **x, int n, int s, int t, float cost);

#endif 
/* ! HAVE_MYFUNC_H */
