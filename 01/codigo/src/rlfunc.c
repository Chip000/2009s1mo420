/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/rlfunc.h"

/* 
 * init_int_array: Cria um vetor do tipo int de tamanho n, inicializado
 * com valor v.
 */
static int *init_int_array(int n, int v)
{
	int *t = (int *) malloc(n * sizeof(int));
	int i;

	for (i = 0; i < n; i++) {
		t[i] = v;
	}

	return t;

} /* init_int_array */

/* 
 * init_float_array: Cria um vetor do tipo float de tamanho n, 
 * inicializado com valor v
 */
static float *init_float_array(int n, float v)
{
	float *t = (float *) malloc(n * sizeof(float));
	int i;
	
	for (i = 0; i < n; i++) {
		t[i] = v;
	}
	
	return t;

} /* init_float_array */

/*
 * min_dist_vertex: retorna o vertice que possui a menor distancia.
 */
static int min_dist_vertex(float *dist, int n, int *visited)
{
	int i;
	int min_vertex;

	float min_dist;

	min_dist = INF;
	min_vertex = -1;

	for (i = 0; i < n; i++) {
		if ((visited[i] == 0) && (dist[i] <= min_dist)) {
			min_dist = dist[i];
			min_vertex = i;
		}
	}

	return min_vertex;

} /* min_dist_vertex */

/*
 * knapsack_dp: Preenche a matriz de programacao dinamica para o 
 * problema da mochila.
 * Entrada:
 *   - Conjunto de arestas do grafo 
 *   - Numero de arestas do grafo
 *   - Peso da mochila
 * Saida:
 *   - Matriz de programacao dinamica preenchida
 *   - Custo da solucao
 */
static float knapsack_dp(struct edge *E, int m, float W, float ***M)
{
	int i;
	int j;
	int ind;
	
	float tmp;

	for (j = 0; j < W + 1; j++) {
		(*M)[0][j] = 0;
	}

	for (i = 0; i < m + 1; i++) {
		(*M)[i][0] = 0;
	}

	for (i = 1; i < m + 1; i++) {
		for (j = 1; j < W + 1; j++) {
			if (E[i-1].cost <= j) {
				ind = (int) (j - E[i-1].cost);
				tmp = ((-1) * E[i-1].dist) + (*M)[i-1][ind];
				
				if (tmp > (*M)[i][j]) {
					(*M)[i][j] = tmp;
				}
				else {
					(*M)[i][j] = (*M)[i-1][j];
				}
			}
			else {
				(*M)[i][j] = (*M)[i-1][j];
			}
		}
	}
	
	return ((*M)[m][(int) W]);

} /* knapsack_dp */


/*
 * knapsack_sol_aux: Funcao auxiliar recursiva que encontra a solucao 
 * a partir da matriz de programacao dinamica.
 * Entrada:
 *   - Conjunto de arestas do problema
 *   - Matriz de programacao dinamica
 *   - Numero de arestas do problema 
 *   - Peso da Mochila
 * Saida:
 *   - Conjunto solucao
 */
static void knapsack_sol_aux(struct edge *E, float **M, int m, int W, 
			     int ***x)
{
	if (m != 0) {
		if (M[m][W] == M[m - 1][W]) {
			(*x)[E[m-1].u][E[m-1].v] = 0;
			(*x)[E[m-1].v][E[m-1].u] = 0;
			knapsack_sol_aux(E, M, m - 1, W, x);			
		}
		else {
			(*x)[E[m-1].u][E[m-1].v] = 1;
			(*x)[E[m-1].v][E[m-1].u] = 1;
			knapsack_sol_aux(E, M, m - 1, W - E[m-1].cost, x);
		}
	}

	return;

} /* knapsack_sol_aux */

/*
 * knapsack_sol: Encontra a solucao a partir da matriz de programacao
 * dinamica.
 * Entrada:
 *   - Conjunto de arestas do problema
 *   - Matriz de programacao dinamica
 *   - Numero de arestas do problema 
 *   - Peso da Mochila
 *   - Numero de vertice do problema
 * Saida:
 *   - Conjunto solucao
 */
static void knapsack_sol(struct edge *E, float **M, int m, int w, 
			 int n, int ***x)
{
	int i;
	int j;

	/* Inicializacao */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			(*x)[i][j] = 0;
		}
	}

	knapsack_sol_aux(E, M, m, w, x);

	return;

} /* knapsack_sol */


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
float knapsack(struct edge *E, int m, int n, float W, int ***x)
{
	float cost;

	int i;
	int j;

	/* Matriz da prog dinamica */
	float **M;

	M = (float **) malloc((m + 1)* sizeof(float **));
	for (i = 0; i < m + 1; i++) {
		M[i] = (float *) malloc((W + 1) * 
					sizeof(float));
	}

	/* Inicializacao da Matriz */
	for (i = 0; i < m + 1; i++) {
		for (j= 0; j < W + 1; j++) {
			M[i][j] = -INF;
		}
	}

	/* Custo inicial */
	cost = INF;
	
	/* Acha o custo da solucao e preenche a Matriz de programacao
	   dinamica */
	cost = knapsack_dp(E, m, W, &M);

	/* Encontra a solucao da mochila dado a Matriz de programacao
	   dinamica */
	knapsack_sol(E, M, m, W, n, x);

	/* Liberando Memoria */
	for (i = 0; i < m + 1; i++) {
		free(M[i]);
	}
	free(M);

	return (-1) * cost;
	
} /* knapsack */


/* RL2 */
/*
 * shortest_path: Utiliza o algoritmo de Dijkstra para encontrar o 
 * caminho mais curto de s a t em um grafo G.
 * Entrada: 
 *   - Matriz de adjacencia contendo as distancias das arestas
 *   - Numero de vertices do grafo.
 *   - Vertice origem
 *   - Vertice destino
 * Saida:
 *   - Conjunto solucao
 *   - Custo do caminho mais curto
 */
float shortest_path(float **G, int n, int s, int t, int ***x)
{
	int i;
	int j;
	int u;
	int S;

	float tmp;
	float cost;

	float *dist;
     
	int *visited;
	int *prev;

	/* Inicializacao */
	cost = 0;
	dist = init_float_array(n, INF);
	prev = init_int_array(n, -1);
	visited = init_int_array(n, 0);

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			(*x)[i][j] = 0;
		}
	}

	S = n;

	/* Valores para o vertice origem */
	dist[s] = 0;
	prev[s] = -1;

	while (S != 0) {
		/* Escolhe o elemento de menor distancia */
		u = min_dist_vertex(dist, n, visited);
		
		visited[u] = 1;
		S --;
		/* Percorre os vizinhos de u */
		for (i = 0; i < n; i++) {
			if (G[u][i] != 0) {
				tmp = dist[u] + G[u][i];
				
				/* Relaxa a aresta (u, i) */
				if (tmp < dist[i]) {
					dist[i] = tmp;
					prev[i] = u;
				}
			}
		}
	}

	/* Encontrando o caminho de s para t 
	   (Conjunto solucao) */
	i = t;
	while (i != s) {
		j = prev[i];
		(*x)[i][j] = (*x)[j][i] = 1;
		i = j;
	}

	/* Custo do caminho de s a t */
	cost = dist[t];

	/* Liberando memoria */
	free(dist);
	free(prev);
	free(visited);

	return cost;

} /* shortest_path */


/* DEBUG FUNCTIONS */

/*
 * print_shortest_path: Imprime o custo e o caminho mais curto da 
 * solucao dada.
 */
void print_shortest_path(int **x, int n, int s, int t, float cost)
{
	
	int i;
	int u;

	fprintf(stdout, "\n>>>DEBUG:\n");
	fprintf(stdout, "Custo: %f\n\n", cost);
	fprintf(stdout, "Vertices do Caminho:\n");

	i = 0;
	u = s;
	fprintf(stdout, "%d ", u);
	while (u != t) {
		if (x[u][i] != 0) {
			fprintf(stderr, "%d ", i);
			u = i;
			i = -1;
		}
		i++;
	}
	fprintf(stdout, "%d ", t);

	fprintf(stderr, "\n");

	return;
} /* print_shortest_path */

/* EOF */
