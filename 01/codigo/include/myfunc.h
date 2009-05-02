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

#define INF 2<<20

/* 
 * init_int_array: Cria um vetor do tipo int de tamanho n, inicializado
 * com valor v.
 */
int *init_int_array(int n, int v);

/* 
 * init_float_array: Cria um vetor do tipo float de tamanho n, 
 * inicializado com valor v
 */
float *init_float_array(int n, float v);

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
